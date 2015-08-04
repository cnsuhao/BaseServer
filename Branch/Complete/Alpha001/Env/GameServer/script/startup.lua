-- 设置包的路径包含；如果不需要自定义的路径，就必须在工作目录下建立lua\systems文件夹
package.path = package.path .. ";F:/Pro_MyGame/LuaMode/Alpha001/Env/GameServer/script/?.lua"

-- 加载静态数据
dofile("script/item_type.lua")	-- 物品类型表

local test1 = require("test1")
local test2 = require("test2")
function start()
	local bResult = true
	
	-- 初始化test1
	if (bResult) then bResult = test1.init() end
	
	-- 初始化test2
	if (bResult) then bResult = test2.init() end
	
	-- 返回结果
	Lua:SetResult(bResult)	
end