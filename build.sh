#!/bin/bash

function title() { echo -e ">>> $1"; }
function hr() { echo -e "\n==================================================\n"; }
function runTests()
{
    for file in $1
    do
        ls $file
        ./$file
        echo -e "\n"
    done
}

BASEDIR=`dirname $0`
cd $BASEDIR

rebuild=false
buildType="Release"
testApp="OFF"
doc="OFF"

while [ $# -gt 0 ]
do
    if [ $1 == "-r" ]
    then
        rebuild=true
    elif [ $1 == "-D" ]
    then
        buildType="Debug"
    elif [ $1 == "-test" ]
    then
        testApp="ON"
    elif [ $1 == "-doc" ]
    then
        doc="ON"
    fi

    shift
done

if [ $rebuild == true ]
then
    rm -rf ./build
    rm -rf ./bin
    rm -rf ./doc
fi

mkdir ./build
cd ./build

clear &&
    title "CMAKE:\n" &&
        cmake -DCMAKE_BUILD_TYPE=$buildType -DTEST_APP=$testApp -DDOC=$doc ../ && hr &&
    title "MAKE:\n" &&
        make

