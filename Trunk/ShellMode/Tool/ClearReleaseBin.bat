rem === 1. 入口服务器 ===
cd LoginServer
	del "Common/Release" /s /q
	del "GAMEBASECODEMT/Release" /s /q
	del "MSGSERVER/Release" /s /q
	del "ServerSocket/Release" /s /q
cd..

rem === 2. 关系服务器 ===
cd RelationServer
	del "Common/Release" /s /q
	del "GAMEBASECODEMT/Release" /s /q
	del "RelationServer/Release" /s /q
	del "RelationServer/PhpThread/Release" /s /q
	del "RelationServer/LogicThread/Release" /s /q
	del "ServerSocket/Release" /s /q
cd..

rem === 3. 游戏服务器 ===
cd GameServer
	del "Common/Release" /s /q
	del "GAMEBASECODEMT/Release" /s /q
	del "LuaPlus/Release" /s /q
	del "MSGSERVER/Release" /s /q
	del "MSGSERVER/AIThread/Release" /s /q
	del "MSGSERVER/LoginThread/Release" /s /q
	del "MSGSERVER/GameThread/Release" /s /q
	del "MSGSERVER/RelationThread/Release" /s /q
	del "ServerSocket/Release" /s /q
cd..

rem === 4. 跨服服务器 ===
cd RelationServer
	del "Common/Release" /s /q
	del "GAMEBASECODEMT/Release" /s /q
	del "ServerSocket/Release" /s /q
	del "CrossServer/LogicThread/Release" /s /q
cd..

rem === 5. lib文件 ===
cd Lib
	cd LoginServer
		del Common.lib /s /q
		del GameBaseCodeMT.lib /s /q
		del ServerSocket.lib /s /q
	cd..
	cd RelationServer
		del Common.lib /s /q
		del GameBaseCodeMT.lib /s /q
		del LogicKernel.lib /s /q
		del PhpKernel.lib /s /q
		del ServerSocket.lib /s /q
	cd..
	cd GameServer
		del AIKernel.lib /s /q
		del Common.lib /s /q
		del GameBaseCodeMT.lib /s /q
		del LuaPlus.lib /s /q
		del GameKernel.lib /s /q
		del LoginKernel.lib /s /q	
		del RelationKernel.lib /s /q		
	cd.. 
	cd CrossServer
		del Common.lib /s /q
		del GameBaseCodeMT.lib /s /q
		del LogicKernel.lib /s /q
		del ServerSocket.lib /s /q
	cd..
cd..

rem === 6. 清理Env ===
cd Env
	cd RelationServer
		del RelationServer.exe /s /q
		del RelationServer.pdb /s /q
		del LoginServer.exe /s /q
		del LoginServer.pdb /s /q
	cd..
	cd GameServer
		del GameServer.exe /s /q
		del GameServer.pdb /s /q
	cd..
		cd CrossServer
		del CrossServer.exe /s /q
		del CrossServer.pdb /s /q
	cd..
cd..