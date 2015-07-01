rem === 1. 入口服务器 ===
cd LoginServer
	del "Common/Debug" /s /q
	del "GAMEBASECODEMT/Debug" /s /q
	del "MSGSERVER/Debug" /s /q
	del "ServerSocket/Debug" /s /q
cd..

rem === 2. 关系服务器 ===
cd RelationServer
	del "Common/Debug" /s /q
	del "GAMEBASECODEMT/Debug" /s /q
	del "RelationServer/Debug" /s /q
	del "RelationServer/PhpThread/Debug" /s /q
	del "RelationServer/LogicThread/Debug" /s /q
	del "ServerSocket/Debug" /s /q
cd..

rem === 3. 游戏服务器 ===
cd GameServer
	del "Common/Debug" /s /q
	del "GAMEBASECODEMT/Debug" /s /q
	del "LuaPlus/Debug" /s /q
	del "MSGSERVER/Debug" /s /q
	del "MSGSERVER/AIThread/Debug" /s /q
	del "MSGSERVER/LoginThread/Debug" /s /q
	del "MSGSERVER/GameThread/Debug" /s /q
	del "MSGSERVER/RelationThread/Debug" /s /q
	del "ServerSocket/Debug" /s /q
cd..

rem === 4. 跨服服务器 ===
cd CrossServer
	del "Common/Debug" /s /q
	del "GAMEBASECODEMT/Debug" /s /q
	del "ServerSocket/Debug" /s /q
	del "CrossServer/LogicThread/Debug" /s /q
cd..

rem === 5. lib文件 ===
cd Lib
	cd LoginServer
		del Common_d.lib /s /q
		del GameBaseCodeMT_d.lib /s /q
		del ServerSocket_d.lib /s /q
	cd..
	cd RelationServer
		del Common_d.lib /s /q
		del GameBaseCodeMT_d.lib /s /q
		del LogicKernel_d.lib /s /q
		del PhpKernel_d.lib /s /q
		del ServerSocket_d.lib /s /q
	cd..
	cd GameServer
		del AIKernel_d.lib /s /q
		del Common_d.lib /s /q
		del GameBaseCodeMT_d.lib /s /q
		del LuaPlus_d.lib /s /q
		del GameKernel_d.lib /s /q
		del LoginKernel_d.lib /s /q	
		del RelationKernel_d.lib /s /q		
	cd.. 
	cd CrossServer
		del Common_d.lib /s /q
		del GameBaseCodeMT_d.lib /s /q
		del LogicKernel_d.lib /s /q
		del ServerSocket_d.lib /s /q
	cd..
cd..

rem === 6. 清理Env ===
cd Env
	cd RelationServer
		del RelationServer_d.exe /s /q
		del RelationServer_d.pdb /s /q
		del RelationServer_d.ilk /s /q
		del RelationServer_d.exe.manifest /s /q
		del LoginServer_d.exe /s /q
		del LoginServer_d.pdb /s /q
		del LoginServer_d.ilk /s /q
		del LoginServer_d.exe.manifest /s /q
	cd..
	cd GameServer
		del GameServer_d.exe /s /q
		del GameServer_d.pdb /s /q
		del GameServer_d.ilk /s /q
		del GameServer_d.exe.manifest /s /q
	cd..
	cd CrossServer
		del CrossServer_d.exe /s /q
		del CrossServer_d.pdb /s /q
		del CrossServer_d.ilk /s /q
		del CrossServer_d.exe.manifest /s /q
	cd..
cd..