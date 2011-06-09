@echo off
cd %~dp0

set buildType=Release
set test=OFF
set doc=OFF

for %%A in (%*) do (
    if "%%A"=="/r" (
        if exist build (rmdir /S /Q build)
        if exist bin (rmdir /S /Q bin)
        if exist doc (rmdir /S /Q doc)
    )
        
    if "%%A"=="/D" ( :: debug build type
        set buildType=Debug
    )

    if "%%A"=="/test" ( :: build testing applications
        set test=ON
    )

    if "%%A"=="/doc" ( :: generate documentation
        set doc=ON
    )
)

if not exist build (mkdir build)
cd build

cls
    cmake ../ -DTEST_APP=%test% -DCMAKE_BUILD_TYPE=%buildType% -DDOC=%doc% && msbuild FakeInput.sln /p:Configuration=Release

cd ..

@echo on
