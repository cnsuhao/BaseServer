@echo off

del Package\RelationServer.exe /q
del Package\RelationServer.pdb /q
del Package\LoginServer.exe /q
del Package\LoginServer.pdb /q
del Package\GameServer.exe /q
del Package\GameServer.pdb /q
del Package\CrossServer.exe /q
del Package\CrossServer.pdb /q

copy Env\RelationServer\RelationServer.exe Package\RelationServer.exe /y
copy Env\RelationServer\RelationServer.pdb Package\RelationServer.pdb /y
copy Env\RelationServer\LoginServer.exe Package\LoginServer.exe /y
copy Env\RelationServer\LoginServer.pdb Package\LoginServer.pdb /y
copy Env\GameServer\GameServer.exe Package\GameServer.exe /y
copy Env\GameServer\GameServer.pdb Package\GameServer.pdb /y
copy Env\CrossServer\CrossServer.exe Package\CrossServer.exe /y
copy Env\CrossServer\CrossServer.pdb Package\CrossServer.pdb /y

cd Package
call pack_Release.bat