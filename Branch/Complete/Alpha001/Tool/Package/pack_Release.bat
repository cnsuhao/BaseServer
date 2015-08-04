@echo off
rem cls

rem 全局变量设置
rem set packname=ServerRelease_%date:~0,4%-%date:~5,2%-%date:~8,2%_%time:~0,2%-%time:~3,2%.7z
rem set packname=%packname: =0% 
set packname=ServerRelease.7z
set options_7z=-mx=9 -ms=200m -mmt 

if exist "%packname%" del "%packname%"

echo 打包程序文件
7za a -t7z %packname% CrossServer.exe CrossServer.pdb GameServer.exe GameServer.pdb LoginServer.exe LoginServer.pdb RelationServer.exe RelationServer.pdb %options_7z%

echo 打包txt与bat类型文件
7za a -t7z %packname% 常量库建表.sql 游戏库建表.sql 账号库建表.sql %options_7z%

move %packname% ..\%packname%
echo %packname%打包生成完毕

pause
