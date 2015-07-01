rem === Release版本服务器一键编译 ===
rem 如果联合编译发生失败则暂停，这样可以根据Monitor界面知道具体的编译失败原因
call ClearReleaseBin.bat

rem === 1. 编译登陆服务器 ===
BuildConsole ..\Build\LoginServer.sln /log=[BuildLog][Release]LoginServer.txt /prj="Common,DataBase,ServerSocket,MsgServer" /rebuild /cfg="Release|Win32"
IF %ERRORLEVEL% NEQ 0 pause
rem ==========================

rem === 2. 编译游戏服务器 ===
BuildConsole ..\Build\GameServer.sln /log=[BuildLog][Release]GameServer.txt /prj="Common,DataBase,LuaPlus,GameKernel,LoginKernel,RelationKernel,MsgServer" /rebuild /cfg="Release|Win32"
IF %ERRORLEVEL% NEQ 0 pause
rem ==========================
