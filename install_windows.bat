@echo off
chcp 65001 > nul 
setlocal enabledelayedexpansion


set BUILD_DIR=build
set INSTALL_DIR=install
set GENERATOR="Visual Studio 17 2022"
set CONFIG=Release                      

:: Очистка предыдущей сборки
if exist %BUILD_DIR% rmdir /s /q %BUILD_DIR%
if exist %INSTALL_DIR% rmdir /s /q %INSTALL_DIR%

:: Создание директорий
mkdir %BUILD_DIR%
cd %BUILD_DIR%

:: Генерация проекта
cmake .. -G %GENERATOR% -DCMAKE_INSTALL_PREFIX=..\%INSTALL_DIR% 

:: Компиляция (для MSVC)
cmake --build . --config %CONFIG%
cmake --install . --config %CONFIG%


cd ..
echo Success! Result saved in %INSTALL_DIR%/
pause