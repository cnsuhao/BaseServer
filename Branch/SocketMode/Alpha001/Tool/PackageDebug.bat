@echo off

del Package\RelationServer_d.exe /q
del Package\RelationServer_d.pdb /q
del Package\LoginServer_d.exe /q
del Package\LoginServer_d.pdb /q
del Package\GameServer_d.exe /q
del Package\GameServer_d.pdb /q
del Package\CrossServer_d.exe /q
del Package\CrossServer_d.pdb /q


copy Env\RelationServer\RelationServer_d.exe Package\RelationServer_d.exe /y
copy Env\RelationServer\RelationServer_d.pdb Package\RelationServer_d.pdb /y
copy Env\RelationServer\LoginServer_d.exe Package\LoginServer_d.exe /y
copy Env\RelationServer\LoginServer_d.pdb Package\LoginServer_d.pdb /y
copy Env\GameServer\GameServer_d.exe Package\GameServer_d.exe /y
copy Env\GameServer\GameServer_d.pdb Package\GameServer_d.pdb /y
copy Env\CrossServer\CrossServer_d.exe Package\CrossServer_d.exe /y
copy Env\CrossServer\CrossServer_d.pdb Package\CrossServer_d.pdb /y

cd Package
call pack_Debug.bat