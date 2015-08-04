--邮件系统
module("systems.mail.mailsystem" , package.seeall)
setfenv(1, systems.mail.mailsystem)

local actorevent       = require("actorevent.actorevent")
local netmsgdispatcher = require("utils.net.netmsgdispatcher")
local dbretdispatcher  = require("utils.net.dbretdispatcher")
local mailmgr          = require("base.mailmanager.mailmanager")
local actormoney       = require("systems.actorsystem.actormoney")
local actorfunc        = require("utils.actorfunc")

require("protocol")

local LActor = LActor
local System = System
local mailLang = Lang.Mail
local protocol = MailSystemProtocol
local dbCmd = DbCmd.EntityCmd
local sysId = SystemId.enMailSystemID

local PER_PAGE = 64 --每个包包含邮件的上限--分包发送，每次64封

MAIL_FILE_MAX = 3  				-- 邮件附件最大数量
MAIL_BOX_MAX  = 200 			-- 邮件最大数量
MAIL_WILL_BE_FULL = 199 		-- 系统邮件过多警告

SEND_MAIL_COST = 10 			-- 发送邮件消耗(金币)

TYPE_ITEM 	= 1 -- 物品类型
TYPE_MONEY 	= 2 -- 金钱类型

-- 邮件类型
MT_PRIVATE	= 1	-- 私人邮件
MT_SYSTEM	= 2	-- 系统邮件
MT_POWER	= 3	-- 体力邮件

local function getMailDyanmicVar(actor)
	local actorId = LActor.getActorId(actor)
	local var = LActor.getDyanmicVar(actor)
	if not var then return end

	var.mailData = var.mailData or {}
	local mailData = var.mailData
	mailData[actorId] = mailData[actorId] or {}
	return mailData[actorId]
end

--初始化玩家MailList
function initMailList(actor)
	local var_d = getMailDyanmicVar(actor)
	if not var_d then return end
	if nil == var_d[MT_PRIVATE] then var_d[MT_PRIVATE] 	= {} end
	if nil == var_d[MT_SYSTEM] 	then var_d[MT_SYSTEM] 	= {} end
	if nil == var_d[MT_POWER] 	then var_d[MT_POWER] 	= {} end
	return var_d
end


--获取玩家MailList
function getMailList(actor)
	local var_d = getMailDyanmicVar(actor)
	if not var_d then return end
	return var_d
end

-- 根据类型获取邮件列表
function getMailListByType(actor, mailType)
	if mailType < MT_PRIVATE or mailType > MT_POWER then
		return
	end

	local mailList = getMailList(actor)
	if not mailList then
		return
	end

	return mailList[mailType]
end

--获取某封邮件属性
function getMail(actor, mailId)
	for i = MT_PRIVATE, MT_POWER do
		local mailList = getMailListByType(actor, i)
		if mailList then
			if mailList[mailId] then
				return mailList[mailId]
			end
		end
	end
end

-- 判断邮件是否存在
function isExist(actor, mailType, mailId)
	if mailType < MT_PRIVATE or mailType > MT_POWER then
		return false
	end

	local mailList = getMailListByType(actor, mailType)
	if not mailList then
		return false
	end

	return nil ~= mailList[mailId]
end

--获取邮件数量
function getMailCount(mailList)
	if not mailList then 
		return 0
	end

	local count = 0
	for _, _ in pairs(mailList) do
		count = count + 1
	end
	return count
end

-- 获取某一类型邮件数量
function getMailCountByType(actor, mailType)
	if mailType < MT_PRIVATE or mailType > MT_POWER then
		return 0
	end

	local mailList = getMailListByType(actor, mailType)
	if not mailList then
		return 0
	end

	local count = 0
	for _, _ in pairs(mailList) do
		count = count + 1
	end
	return count
end

--获取禁发邮件时间
function getForbidTime(actor)
	local var_s = LActor.getSysVar(actor)
	return var_s.mailforbidtime or 0
end

--检测是否禁止发邮件
function isForbid(actor)
	local time = getForbidTime(actor)
	local now = System.getNowTime()
	if now > time then
		setForbidTime(actor, 0)
		return false
	end
	return true
end

--设置禁发邮件时间
--if var_s.mailforbidtime = nil and duration = 0 --->不带任何设置
function setForbidTime(actor, duration)
	local var_s = LActor.getSysVar(actor)
	local now = System.getNowTime()
	local time = 0
	if duration > 0 then -- 1
		time = now + duration
	end
	if duration == 0 or time > (var_s.mailforbidtime or 0) then
		var_s.mailforbidtime = time
	end
end

--获取未读邮件的数量
function getUnReadCount(actor)
	-- local mailList = getMailList(actor)
	-- if not mailList then return end
	-- local unReadCount = 0
	-- for _,mail in pairs(mailList) do
	-- 	if mail then
	-- 		if mail.status == 0 then
	-- 			unReadCount = unReadCount + 1
	-- 		end
	-- 	end
	-- end
	-- return unReadCount
end

-- 获取某一类型的未读邮件数量
function getUnReadCountByType(actor, mailType)
	if mailType < MT_PRIVATE or mailType > MT_POWER then
		return
	end

	local mailList = getMailListByType(actor, mailType)
	if not mailList then 
		return 
	end

	local unReadCount = 0
	for _, mail in pairs(mailList) do
		if mail then
			if mail.status == 0 then
				unReadCount = unReadCount + 1
			end
		end
	end
	return unReadCount
end

-- 根据类型向客户端发送未读的数量
function sendUnReadCountByType(actor, mailType)
	if mailType < MT_PRIVATE or mailType > MT_POWER then
		return
	end

	local unReadCount = getUnReadCountByType(actor, mailType)
	local pack = LDataPack.allocPacket(actor, sysId, protocol.sSendUnReadCount)
	if not pack then
		return
	end
	LDataPack.writeData(pack, 2,
		dtByte, mailType, 
		dtInt, 	unReadCount
		)
	LDataPack.flush(pack)
	return unReadCount
end

--读取数据库邮件列表
function loadDBMailList(actor, packet)
	--print("[MAIL]loadDBMailList")
	if actor == nil or packet == nil then return end
	local count = LDataPack.readWord(packet) --在增加一个邮件时这里只是1
	local attachmentFlag = false --是否存在附件的标记
	local mailFlag = false --是否存在未读邮件的标记

	local mailList = initMailList(actor)
	if not mailList then 
		return
	end

	local mail
	--print("[MAIL]loadDBMailList count = "..count)
	for i=1, count do
		mail = {}
		--邮件基本信息,从数据库读取
		mail.mailId, mail.aId, mail.mailType, mail.status, mail.senderId, mail.sendTick, mail.sendName, mail.title, mail.context
			= LDataPack.readData(packet, 9, dtInt64, dtInt, dtInt, dtInt, dtInt, dtUint, dtString, dtString, dtString)

		--附件信息，从数据库读取
		mail.attachmentList = {}
		for j=1, MAIL_FILE_MAX do
			attachment = {}
			attachment.type, attachment.param, attachment.count, attachment.bind, attachment.quality
				= LDataPack.readData(packet, 5, dtInt, dtInt, dtInt, dtInt, dtInt)
			--有附件
			if attachment.type > 0 then
				attachmentFlag = true
				table.insert(mail.attachmentList, attachment)
			end
		end

		mail.senderLv = LDataPack.readInt(packet)
		
		mailType = mail.mailType
		if mailType >= MT_PRIVATE and mailType <= MT_POWER then
			if false == isExist(actor, mailType, mail.mailId) then
				-- 邮件未读
				if mail.status == 0 then
					mailFlag = true
				end

				-- 不得超过上限
				local mailCount = getMailCountByType(actor, mailType)
				if mailCount < MAIL_BOX_MAX then
					mailList[mailType][mail.mailId] = mail
				end
			end
		end
	end

	-- 通知客户端
	local pack
	if mailFlag then
		--print("[MAIL]loadDBMailList Haven new mail")
		pack = LDataPack.allocPacket(actor, sysId, protocol.sAddNewMail)
		if pack then 
			LDataPack.writeChar(pack, 0)
			LDataPack.flush(pack) 
		end

		-- 发送未读数量
		for i = MT_PRIVATE, MT_POWER do
			sendUnReadCountByType(actor, i)
		end
	end

	-- 如果有附件
	if attachmentFlag then
		--print("[MAIL]loadDBMailList Haven attachmentFlag")
		pack = LDataPack.allocPacket(actor, sysId, protocol.sNotifyGetMailFile)
		if pack then
			LDataPack.writeChar(pack, 0)
			LDataPack.flush(pack) 
		end
	end

	-- 如果邮件数量即将满
	for i = MT_PRIVATE, MT_POWER do
		local curMailCount = getMailCountByType(actor, i)
		if curMailCount >= MAIL_WILL_BE_FULL then
			--print("[MAIL]loadDBMailList CurMail is will full:curMailCount = "..curMailCount..";WillFullCount = "..MAIL_WILL_BE_FULL)
			pack = LDataPack.allocPacket(actor, sysId, protocol.sMailBoxFull)
			if pack then
				LDataPack.writeChar(pack, i)
				LDataPack.flush(pack)
			end
		end
	end
end

--发送到dbserver读取邮件
function SendDbLoadMail(actor, mailId, mailType)
	--print("[MAIL]SendDbLoadMail mailId = "..mailId..";mailType = "..mailType or 0)
	if actor == nil or mailId == nil then return end
	mailType = mailType or 0
	System.SendToDb(LActor.getServerId(actor), siEntity, dbCmd.dcLoadMail, 3, dtInt, LActor.getActorId(actor), dtInt64, mailId, dtByte, mailType)
end

--发送到dbserver删除邮件
function SendDbDeleteMail(actor, mailIdList)
	if not mailIdList then return end
	local count = #mailIdList / 2
	System.SendToDb(LActor.getServerId(actor), siEntity, dbCmd.dcDeleteMail, count+2, dtInt, LActor.getActorId(actor), dtInt, count, unpack(mailIdList) )
end

--发送到dbserver删除邮件附件
function SendDbDeleteActtachment(actor, mailIdList)
	if not mailIdList then return end
	local count = #mailIdList / 2
	System.SendToDb(LActor.getServerId(actor), siEntity, dbCmd.dcDeleteMailFile, count+2, dtInt, LActor.getActorId(actor), dtInt, count, unpack(mailIdList) )
end

--发送到dbserver更新邮件状态
function SendDbUpdateMailStatus(actor, mailIdList, status)
	if not mailIdList then return end
	local count = #mailIdList / 2
	System.SendToDb(LActor.getServerId(actor), siEntity, dbCmd.dcUpdateMailStatus, count+3, dtInt, LActor.getActorId(actor), dtInt, count, dtInt, status, unpack(mailIdList))
end

--发送到dbserver获取actorid
function SendDbGetActorIdFromName(actor, name)
	if not name then return end
	System.SendToDb(LActor.getServerId(actor), siEntity, dcCmd.dcGetActorIdFromName, 3, dtInt, LActor.getActorId(actor), dtInt, LActor.getServerId(actor), dtString, name)
end

---对数据库执行某个方法
function sendDbByFunc(actor, mailIdList, func, ...)
	local idx = 1
	local perCount = 20
	local sendTable = {}
	for _, mailId in ipairs(mailIdList) do
		table.insert(sendTable, dtInt64)
		table.insert(sendTable, mailId)
		idx = idx + 1
		if idx >= perCount then --分包
			func(actor, sendTable, ...)
			sendTable = {}
			idx = 1
		end
	end
	if #sendTable > 0 then
		func(actor, sendTable, ...)
	end
end

--向包写入一封邮件信息
--提供给客户端获取邮件列表使用
local function writeSingleMail(packet, mail)
	if packet == nil or mail == nil then return end
	LDataPack.writeData(packet, 8,
					dtInt64, mail.mailId,
					dtByte, mail.mailType,
					dtByte,	mail.status,
					dtInt, mail.senderId,
					dtString, mail.sendName or "",
					dtInt, mail.senderLv,
					dtUint, mail.sendTick,
					dtString, mail.title or "",
					dtString, mail.context or "" )

	LDataPack.writeByte(packet, #mail.attachmentList)

	for _, attachment in ipairs(mail.attachmentList) do
		LDataPack.writeData(packet, 5,
					dtInt, attachment.type,
					dtInt, attachment.param,
					dtInt, attachment.count,
					dtInt, attachment.bind,
					dtInt, attachment.quality)
	end
end

--初始化发送到客户端的邮件包
function initMailListPack(actor, sendFlag, sendCount, mailType)
	local pack = LDataPack.allocPacket(actor, sysId, protocol.sGetMailList)
	if pack then
		LDataPack.writeByte(pack, mailType)
		LDataPack.writeInt(pack, sendFlag)
		LDataPack.writeInt(pack, sendCount)
	end
	return pack
end

--客户端获取邮件列表
function clientGetMailList(actor)
	for mailtype = MT_PRIVATE, MT_POWER do
		-- 获取该类型的邮件列表
		local mailList = getMailListByType(actor, mailtype)
		if not mailList then 
			return 
		end

		local count = getMailCount(mailList) --邮件总数
		if count > MAIL_BOX_MAX then
			count = MAIL_BOX_MAX
		end

		local pack , mail
		-- local packCount = math.ceil(count / PER_PAGE) --大于等于X的整数
		local sendCount = 0 		-- 发送数量
		local sendFlag = 0 			-- 发送标记 0 为第一次，1 为附加
		if count <= 0 then --没有需要发送的邮件
			pack = LDataPack.allocPacket(actor, sysId, protocol.sGetMailList)
			if pack then
				LDataPack.writeByte(pack, mailtype)
				LDataPack.writeInt(pack, sendFlag)
				LDataPack.writeInt(pack, sendCount)
				LDataPack.flush(pack)
			end
		else
			sendCount = math.min(PER_PAGE, count)
			local perPage = 0
			pack = initMailListPack(actor, sendFlag, sendCount, mailtype)

			for _, mail in pairs(mailList) do
				--print("get mail-->"..mail.mailId)
				writeSingleMail(pack, mail) --附加数据至包中
				perPage = perPage + 1
				if perPage >= sendCount then --包够了就发送
					LDataPack.flush(pack)
					count = count - sendCount
					if count > 0 then --有剩余的邮件就继续
						sendFlag = 1
						sendCount = math.min(PER_PAGE, count)
						perPage = 0
						pack = initMailListPack(actor, sendFlag, sendCount, mailtype)
					else 
						break 
					end
				end
			end
		end

		-- 发送未读邮件数量
		sendUnReadCountByType(actor, mailtype)
	end
end


--从一封邮件中提取附件
--clear为false的时候仅仅判定是否有附件，而不会提取且清空附件表
function getAttachmentFromMail(actor, mail, clear)
	local getFlag = false
	if not mail or not mail.attachmentList then return getFlag end

	for _, att in pairs(mail.attachmentList) do
		if att.type == TYPE_ITEM then
			if clear then
				LActor.addItem(actor, att.param, att.quality, 0, att.count, att.bind, "GetMailFile", 87)
			end
			getFlag = true

		elseif att.type == TYPE_MONEY then
			if clear then
				actormoney.changeMoney(actor, att.param, att.count, 1, true, "mail", "attachmentList", mail.sendName)
			end
			getFlag = true
		end
	end

	if clear then mail.attachmentList = {} end --清空列表
	return getFlag
end

--获取提取附件时需要的最少格子数量
function canGetMailItem(actor, mail)
	local count = 0
	local bind
	if not mail or #mail.attachmentList <= 0 then 
		return count 
	end

	for _, att in pairs(mail.attachmentList) do
		if att.type == TYPE_ITEM then
			if 1 == att.bind then
				bind = true
			else
				bind = false
			end
			--count = count + Item.getAddItemNeedGridCount(actor, att.param, att.count, att.quality, 0, att.bind)
			if not LActor.canAddItem(actor, att.param, att.count, att.quality, 0, bind) then
				return false
			end

			bind = nil
		end
	end

	return true
end

--领取邮件附件
function clientGetAttachment(actor, packet)
	--print("[MAIL]clientGetAttachment")
	local mailtype = LDataPack.readByte(packet)	-- 邮件类型
	local getType = LDataPack.readByte(packet)	-- 提取类型(0 一键提取； 1 单个提取)
	--print("[MAIL]clientGetAttachment mailType = "..mailtype..";getType = "..getType)

	if MT_PRIVATE == mailtype then				-- 私人邮箱不存在附件
		return
	end

	if mailtype < MT_PRIVATE or mailtype > MT_POWER then 
		return
	end

	local searchMailList = {}--检索的列表

	if getType == 0 then
		searchMailList = getMailListByType(actor, mailtype)
		--print("[MAIL]clientGetAttachment oneKey attach, mailCount = "..getMailCountByType(actor, mailtype))
	else
		--print("[MAIL]clientGetAttachment attach one mail")
		local mailId = LDataPack.readInt64(packet)
		local mail = getMail(actor, mailId)

		if mail then 
			searchMailList = {mail} 
		end
	end

	if not searchMailList then return end

	local delMailId = {}
	local itemCount = 0

	local canAddItem = true

	--#获取需要的格子数量#
	for _, mail in pairs(searchMailList) do
		--itemCount = itemCount + getMailItemCount(actor, mail)
		if not canGetMailItem(actor, mail) then
			canAddItem = false
			break
		end
	end

	--#如果格子太少则提取失败#
	if not canAddItem then
		--print("[MAIL]clientGetAttachment bag blank is not enough")
		LActor.sendTipmsg(actor, mailLang.tip001, ttMessage);
		return
	end

	--#获取需要提取的mailId#
	for _, mail in pairs(searchMailList) do
		if getAttachmentFromMail(actor, mail, false) then
			table.insert(delMailId, mail.mailId)
		end
	end

	--#先从数据库删除mail附件再给予玩家
	if #delMailId > 0 then
		sendDbByFunc(actor, delMailId, SendDbDeleteActtachment)
		local mail
		for _,mailId in pairs(delMailId) do
			mail = getMail(actor,mailId)
			if mail then
				mail.status = 1 --标记已读
				getAttachmentFromMail(actor, mail, true)
			end
		end
	end

	-- 发送客户端消息
	--print("[MAIL]clientGetAttachment sendClient msg")
	local pack = LDataPack.allocPacket(actor, sysId, protocol.sGetMailItem)
	if not pack then return end
	LDataPack.writeData(pack, 1, dtInt, 0)
	LDataPack.writeData(pack, 1, dtByte, mailtype)
	LDataPack.flush(pack)

	-- 发送未读邮件数量
	sendUnReadCountByType(actor, mailtype)

	return
end

--阅读邮件
function clientReadMail(actor, packet)
	local mailList = getMailList(actor)
	if not mailList then return end
	local mailId, readMail
	local readMailList = {}
	local mailType  = LDataPack.readByte(packet)
	local readCount = LDataPack.readInt(packet)
	readCount = math.min(readCount, MAIL_BOX_MAX)
	for i=1, readCount do
		mailId = LDataPack.readInt64(packet)
		readMail = getMail(actor, mailId)
		if readMail and mailType == readMail.mailType then
			readMail.status = 1
			table.insert(readMailList, mailId)
		end
	end

	--发数据库更新邮件状态
	sendDbByFunc(actor, readMailList, SendDbUpdateMailStatus, 1)

	--通知客户端
	local unReadCount = getUnReadCountByType(actor, mailType)
	local flag = 0
	if unReadCount > 0 then flag = 1 end
	--发送是否还有未读信息
	local pack = LDataPack.allocPacket(actor, sysId, protocol.sReadMail)
	if pack then
		LDataPack.writeByte(pack, mailType)
		LDataPack.writeByte(pack, flag)
		LDataPack.flush(pack)
	end

	--发送未读信息数量
	sendUnReadCountByType(actor, mailType)
end

--删除邮件
function clientDeleteMail(actor, packet)
	--print("[MAIL]clientDeleteMail")
	local mailtype= LDataPack.readByte(packet)
	local delType = LDataPack.readByte(packet)
	--print("[MAIL]clientDeleteMail mailtype = "..mailtype..";deltype = "..delType)
	if mailtype < MT_PRIVATE or mailtype > MT_POWER then 
		return
	end

	local isReload = false
	local delMailId = {}
	local mailList = getMailListByType(actor, mailtype)
	--print("[MAIL]clientDeleteMail mailcount = "..getMailCountByType(actor, mailtype))
	if not mailList then return end

	local mailCount = getMailCount(mailList)
	--print("[MAIL]clientDeleteMail mailcount = "..mailCount)
	if mailCount >= MAIL_BOX_MAX then
		--print("[MAIL]clientDeleteMail needReload")
		isReload = true
	end

	--筛选需要删除的邮件
	if delType == 0 then
		for _, mail in pairs(mailList) do
			if #mail.attachmentList <= 0 then
				table.insert(delMailId, mail.mailId)
			end
		end
	else
		local mailId
		local num = LDataPack.readByte(packet)
		if num > MAIL_BOX_MAX then
			return
		end
		--获取要删除的邮件
		for i=1, num do
			mailId = LDataPack.readInt64(packet)
			--print("del mail-->"..mailId)
			table.insert(delMailId, mailId)
		end
	end
	--print("[MAIL]clientDeleteMail delCount = "..#delMailId)
	--发送到数据库
	sendDbByFunc(actor, delMailId, SendDbDeleteMail)
	--删除邮件
	for _, mailId in pairs(delMailId) do
		if mailList[mailId] then
			mailList[mailId] = nil
		end
	end
	LActor.sendTipmsg(actor, mailLang.tip002, ttMessage)
	--发送更新后的未读邮件
	local pack = LDataPack.allocPacket(actor, sysId, protocol.sDeleteMail)
	if pack then
		LDataPack.writeData(pack, 1, dtInt, 0)
		LDataPack.writeData(pack, 1, dtByte, mailtype)
		LDataPack.flush(pack) 
	end
	sendUnReadCountByType(actor, mailtype)

	-- 重新加载邮件
	if isReload then
		SendDbLoadMail(actor, 0, mailtype)
	end
end

--发送邮件
function clientSendMail(actor, packet)
	---print("clientSendMail")
	local mailtype= LDataPack.readByte(packet)
	local nameStr = LDataPack.readString(packet)
	local title = LDataPack.readString(packet)
	local context = LDataPack.readString(packet)

	if mailtype < MT_PRIVATE or mailtype > MT_POWER then
		return
	end

	if isForbid(actor) then
		LActor.sendTipmsg(actor, mailLang.tip003, ttMessage)
		return
	end

	--不能发信给不存在的人
	if not LActor.isExistActorByName(nameStr) then
		LActor.sendTipmsg(actor, mailLang.tip007, ttMessage)
		return
	end

	--不能发送给自己
	if nameStr == LActor.getName(actor) then
		LActor.sendTipmsg(actor, mailLang.tip005, ttMessage)
		return
	end

	--不能发送空内容的邮件
	if not context or context == "" then
		LActor.sendTipmsg(actor, mailLang.tip006, ttMessage)
		return
	end

	--判断金币够不够
	if actormoney.getMoneyEx(actor, mtCoin) < SEND_MAIL_COST then
		LActor.sendTipmsg(actor, mailLang.tip004, ttMessage)
		return
	end

	actormoney.consumeMoney(actor, mtCoin, -SEND_MAIL_COST, 1, true, "mail", "send")

	local mail = {}
	mail.mailId         = System.allocSeries()
	mail.mailType       = mailtype
	mail.status         = 0
	mail.senderId       = LActor.getActorId(actor)
	mail.sendName       = LActor.getName(actor)
	mail.sendTick       = System.getNowTime()
	mail.title          = title or ""
	mail.context        = context or ""
	mail.senderLv       = LActor.getIntProperty(actor, P_LEVEL)
	mail.attachmentList = {} --附件列表

	mailmgr.AddMailByActorName(nameStr, mail)

	--确认操作成功
	local pack = LDataPack.allocPacket(actor, sysId, protocol.sSendMail)
	LDataPack.writeChar(pack, mailtype)
	LDataPack.flush(pack)
end

_G.ReloadMailFromDb = function(actor, mailId)
	print("[MAIL]ReloadMailFromDb")
	if not actor then return end
	local mail = getMail(actor, mailId)
	if mail ~= nil then return end
	print("[MAIL]Start SendDbLoadMail")
	SendDbLoadMail(actor, mailId, 0)
end

--[[
功能:系统发送邮件接口(供脚本调用)
参数:
	 receiverId 接收玩家ID
	 title 邮件标题
	 context 邮件内容
	 attachmentList 附件列表 : 附件最大数量(MAIL_FILE_MAX)
	 						   每一个附件的属性如下:
	 						   type:1 是物品 2 是金钱
	 						   sort:物品ID或金钱类型
	 						   num:物品或者金钱数量
	 						   bind:是否绑定(1 是，0 否)
	 						   quality:品质
--]]
_G.SendMail = function (receiverId, title, context, attachmentList)
	-- 创建邮件
	local mail = {}
	mail.mailId         = System.allocSeries()
	mail.mailType       = MT_SYSTEM
	mail.status         = 0
	mail.senderId       = 0
	mail.sendName       = “SYSTEM”
	mail.sendTick       = System.getNowTime()
	mail.title          = title or ""
	mail.context        = context or ""
	mail.senderLv       = 0
	mail.attachmentList = {} --附件列表

	if #attachmentList > 0 then
		local fileCount = #attachmentList
		fileCount = math.min(fileCount, MAIL_FILE_MAX)
		for i = 1, fileCount do
			local attachment = {}
			attachment.type 	= attachmentList[i].type 	or 0
			attachment.sort 	= attachmentList[i].sort 	or 0
			attachment.num  	= attachmentList[i].num  	or 0
			attachment.bind 	= attachmentList[i].bind 	or 0
			attachment.quality	= attachmentList[i].quality or 0

			table.insert(mail.attachmentList, attachment)
		end
	end

	-- 发送邮件
	mailmgr.AddMailByActorId(receiverId, mail)
end

--[[
功能:系统发送邮件接口(供C++调用)
参数:
	 receiverId 接收玩家ID
	 title 邮件标题
	 context 邮件内容
	 attachmentList 附件列表 : 附件最大数量(MAIL_FILE_MAX)
	 						   每一个附件的属性如下:
	 						   type:1 是物品 2 是金钱
	 						   sort:物品ID或金钱类型
	 						   num:物品或者金钱数量
	 						   bind:是否绑定(1 是，0 否)
	 						   quality:品质
--]]
_G.SendMailEx = function (receiverId, title, context, type1, sort1, num1, bind1, quality1, 
						type2, sort2, num2, bind2, quality2, type3, sort3, num3, bind3, quality3)
	local attachmentList = {}
	local attachment = {}
	if nil ~= type1 and type1 > 0 then
		attachment = {}
		attachment.type 	= type1    or 0
		attachment.sort 	= sort1    or 0
		attachment.num  	= num1     or 0
		attachment.bind 	= bind1    or 0
		attachment.quality	= quality1 or 0
		table.insert(mail.attachmentList, attachment)
	end

	if nil ~= type2 and type2 > 0 then
		attachment = {}
		attachment.type 	= type2    or 0
		attachment.sort 	= sort2    or 0
		attachment.num  	= num2     or 0
		attachment.bind 	= bind2    or 0
		attachment.quality	= quality2 or 0
		table.insert(mail.attachmentList, attachment)
	end

	if nil ~= type3 and type3 > 0 then
		attachment = {}
		attachment.type 	= type3    or 0
		attachment.sort 	= sort3    or 0
		attachment.num  	= num3     or 0
		attachment.bind 	= bind3    or 0
		attachment.quality	= quality3 or 0
		table.insert(mail.attachmentList, attachment)
	end

	SendMail(receiverId, title, context, attachmentList)
end

function onLogin(actor)
	SendDbLoadMail(actor, 0, 0)
end



actorevent.reg(aeUserLogin, onLogin)

netmsgdispatcher.reg(sysId, protocol.cGetMailList, clientGetMailList)
netmsgdispatcher.reg(sysId, protocol.cGetMailFile, clientGetAttachment)
netmsgdispatcher.reg(sysId, protocol.cReadMail, clientReadMail)
netmsgdispatcher.reg(sysId, protocol.cDeleteMail, clientDeleteMail)
netmsgdispatcher.reg(sysId, protocol.cSendMail, clientSendMail)

dbretdispatcher.reg(siEntity, dbCmd.dcLoadMail, loadDBMailList)

