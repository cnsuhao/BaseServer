rem === Debug�汾������һ������ ===
rem ������ϱ��뷢��ʧ������ͣ���������Ը���Monitor����֪������ı���ʧ��ԭ��
call ClearDebugBin.bat


rem === 1. �����ϵ������ ===
BuildConsole .\Build\RelationServer.sln /log=[BuildLog][Debug]RelationServer.txt /prj="Common,GameBaseCodeMT,LogicKernel,PhpKernel,ServerSocket,RelationServer" /rebuild /cfg="Debug|Win32"
IF %ERRORLEVEL% NEQ 0 pause
rem ==========================

rem === 2. �����½������ ===
BuildConsole .\Build\LoginServer.sln /log=[BuildLog][Debug]LoginServer.txt /prj="Common,GameBaseCodeMT,ServerSocket,MsgServer" /rebuild /cfg="Debug|Win32"
IF %ERRORLEVEL% NEQ 0 pause
rem ==========================

rem === 3. ������Ϸ������ ===
BuildConsole .\Build\GameServer.sln /log=[BuildLog][Debug]GameServer.txt /prj="Common,GameBaseCodeMT,LuaPlus,GameKernel,LoginKernel,RelationKernel,MsgServer" /rebuild /cfg="Debug|Win32"
IF %ERRORLEVEL% NEQ 0 pause
rem ==========================

rem === 4. ������������ ===
BuildConsole .\Build\CrossServer.sln /log=[BuildLog][Debug]CrossServer.txt /prj="Common,GameBaseCodeMT,LogicKernel,ServerSocket,CrossServer" /rebuild /cfg="Debug|Win32"
IF %ERRORLEVEL% NEQ 0 pause
rem ==========================
