module("test1" , package.seeall)
local test2 = require("test2")

function test1()
	local ntest1 = test2.test2()
	return true
end