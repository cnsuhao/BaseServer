rem === Release�汾������һ������ ===
rem ������ϱ��뷢��ʧ������ͣ���������Ը���Monitor����֪������ı���ʧ��ԭ��
call ClearReleaseBin.bat

rem === 1. �����½������ ===
BuildConsole ..\Build\LoginServer.sln /log=[BuildLog][Release]LoginServer.txt /prj="Common,DataBase,ServerSocket,MsgServer" /rebuild /cfg="Release|Win32"
IF %ERRORLEVEL% NEQ 0 pause
rem ==========================

rem === 2. ������Ϸ������ ===
BuildConsole ..\Build\GameServer.sln /log=[BuildLog][Release]GameServer.txt /prj="Common,DataBase,LuaPlus,GameKernel,LoginKernel,RelationKernel,MsgServer" /rebuild /cfg="Release|Win32"
IF %ERRORLEVEL% NEQ 0 pause
rem ==========================
