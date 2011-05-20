@echo off
cd %~dp0

if "%1"=="/r" (
    if exist build (rmdir /S /Q build)
    if exist bin (rmdir /S /Q bin)
    if exist doc (rmdir /S /Q doc)
)

if not exist build (mkdir build)
cd build

cls
cmake ../ -DTEST_APP=ON -DCMAKE_BUILD_TYPE=Debug -DDOC=ON && msbuild FakeInput.sln /p:Configuration=Release

cd ..

@echo on
