@echo off
rem cls

rem ȫ�ֱ�������
rem set packname=ServerDebug_%date:~0,4%-%date:~5,2%-%date:~8,2%_%time:~0,2%-%time:~3,2%.7z
rem set packname=%packname: =0% 
set packname=ServerDebug.7z
set options_7z=-mx=9 -ms=200m -mmt 

if exist "%packname%" del "%packname%"

echo ��������ļ�
7za a -t7z %packname% CrossServer_d.exe CrossServer_d.pdb GameServer_d.exe GameServer_d.pdb LoginServer_d.exe LoginServer_d.pdb RelationServer_d.exe RelationServer_d.pdb %options_7z%

echo ���txt��bat�����ļ�
7za a -t7z %packname% �����⽨��.sql ��Ϸ�⽨��.sql �˺ſ⽨��.sql %options_7z%

move %packname% ..\%packname%
echo %packname%����������

pause
