@echo off
chcp 65001 > nul 
setlocal enabledelayedexpansion


set BUILD_DIR=build
set INSTALL_DIR=install
set GENERATOR="Visual Studio 17 2022"
set CONFIG=Release                      

:choice
echo WARNING! IF YOU RUN THIS SCRIPT, YOU WILL DELETE build AND install FOLDERS
set /P c=Are you sure you want to continue[Y/N]?
if /I "%c%" EQU "Y" goto :proceed
if /I "%c%" EQU "N" goto :cancel
goto :choice

:proceed
if exist %BUILD_DIR% rmdir /s /q %BUILD_DIR%
if exist %INSTALL_DIR% rmdir /s /q %INSTALL_DIR%


mkdir %BUILD_DIR%
mkdir %INSTALL_DIR%
cd %BUILD_DIR%


cmake .. -G %GENERATOR% -DCMAKE_INSTALL_PREFIX=..\%INSTALL_DIR% 


cmake --build . --config %CONFIG%
cmake --install . --config %CONFIG%

move .\Release\* ..\%INSTALL_DIR% 
cd ..
echo Success! Result saved in %INSTALL_DIR%/
pause
exit

:cancel
echo Cancelled
pause
exit