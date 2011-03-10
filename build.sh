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

if [ $# -gt 0 ]
then
    if [ $1 == "-r" ]
    then
        rebuild="TRUE"
    fi
fi

if test -d ./build
then
    if [ "$rebuild" == "TRUE" ]
    then
        rm -r ./build
        mkdir ./build
    fi
fi

mkdir ./build
cd ./build

clear &&
    title "CMAKE:\n" &&
        cmake -DCMAKE_BUILD_TYPE=Debug ../ && hr &&
    title "MAKE:\n" &&
        make

