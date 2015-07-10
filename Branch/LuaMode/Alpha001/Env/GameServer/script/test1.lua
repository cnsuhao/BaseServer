module("test1", package.seeall)
local test2 = require("test2")

function init()
	return true
end

function add()
	local userid = 10007908
	local tRet = LoadRecord("select * from user where id = "..userid)
	local nRecordCount = tRet.RecordCount
	local nCount = table.getn(tRet)
	printTable(tRet)
end

function printTable(t, n)
	if "table" ~= type(t) then
		return 0;
	end

	n = n or 0;

	local str_space = "";
	for i = 1, n do
		str_space = str_space.."  ";
	end
	print(str_space.."{");

	for k, v in pairs(t) do
		local str_k_v = str_space.."  ["..tostring(k).."] = ";
		if "table" == type(v) then
			print(str_k_v);
			printTable(v, n + 1);
		else
			str_k_v = str_k_v..tostring(v);
			print(str_k_v);
		end
	end

	print(str_space.."}");
end