@echo off
rem cls

rem ȫ�ֱ�������
rem set packname=ServerRelease_%date:~0,4%-%date:~5,2%-%date:~8,2%_%time:~0,2%-%time:~3,2%.7z
rem set packname=%packname: =0% 
set packname=ServerRelease.7z
set options_7z=-mx=9 -ms=200m -mmt 

if exist "%packname%" del "%packname%"

echo ��������ļ�
7za a -t7z %packname% CrossServer.exe CrossServer.pdb GameServer.exe GameServer.pdb LoginServer.exe LoginServer.pdb RelationServer.exe RelationServer.pdb %options_7z%

echo ���txt��bat�����ļ�
7za a -t7z %packname% �����⽨��.sql ��Ϸ�⽨��.sql �˺ſ⽨��.sql %options_7z%

move %packname% ..\%packname%
echo %packname%����������

pause
