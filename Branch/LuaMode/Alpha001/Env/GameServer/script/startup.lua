-- ���ð���·���������������Ҫ�Զ����·�����ͱ����ڹ���Ŀ¼�½���lua\systems�ļ���
package.path = package.path .. ";F:/Pro_MyGame/LuaMode/Alpha001/Env/GameServer/script/?.lua"

-- ���ؾ�̬����
dofile("script/item_type.lua")	-- ��Ʒ���ͱ�

local test1 = require("test1")
local test2 = require("test2")
function start()
	local bResult = true
	
	-- ��ʼ��test1
	if (bResult) then bResult = test1.init() end
	
	-- ��ʼ��test2
	if (bResult) then bResult = test2.init() end
	
	-- ���ؽ��
	Lua:SetResult(bResult)	
end