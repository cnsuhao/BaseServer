rem === Debug版本服务器一键编译 ===
rem 如果联合编译发生失败则暂停，这样可以根据Monitor界面知道具体的编译失败原因
call ClearDebugBin.bat


rem === 1. 编译关系服务器 ===
BuildConsole .\Build\RelationServer.sln /log=[BuildLog][Debug]RelationServer.txt /prj="Common,GameBaseCodeMT,LogicKernel,PhpKernel,ServerSocket,RelationServer" /rebuild /cfg="Debug|Win32"
IF %ERRORLEVEL% NEQ 0 pause
rem ==========================

rem === 2. 编译登陆服务器 ===
BuildConsole .\Build\LoginServer.sln /log=[BuildLog][Debug]LoginServer.txt /prj="Common,GameBaseCodeMT,ServerSocket,MsgServer" /rebuild /cfg="Debug|Win32"
IF %ERRORLEVEL% NEQ 0 pause
rem ==========================

rem === 3. 编译游戏服务器 ===
BuildConsole .\Build\GameServer.sln /log=[BuildLog][Debug]GameServer.txt /prj="Common,GameBaseCodeMT,LuaPlus,GameKernel,LoginKernel,RelationKernel,MsgServer" /rebuild /cfg="Debug|Win32"
IF %ERRORLEVEL% NEQ 0 pause
rem ==========================

rem === 4. 编译跨服服务器 ===
BuildConsole .\Build\CrossServer.sln /log=[BuildLog][Debug]CrossServer.txt /prj="Common,GameBaseCodeMT,LogicKernel,ServerSocket,CrossServer" /rebuild /cfg="Debug|Win32"
IF %ERRORLEVEL% NEQ 0 pause
rem ==========================
