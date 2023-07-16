#!/usr/bin/env bash

#build bash
function build() {
    # current directory
    current_dir="${PWD}"

    build_dir="./build"

    if [-d $build_dir ]; then
        echo "Deleted folder: ${build_dir}"
        rm -rf $build_dir
    fi

    echo "Created building folder: ${build_dir}"
    mkdir $build_dir

    echo "Entering folder: ${build_dir}"
    cd $build_dir

    echo "Start building bast ..."
    if [ $1 -eq 1 ]; then
        cmake .. -DBUILD_TESTING=YES -DCMAKE_BUILD_TYPE=Debug $cmake_gen  -DCMAKE_TOOLCHAIN_FILE=~/Desktop/code/cpp/env/vcpkg/scripts/buildsystems/vcpkg.cmake  -DVCPKG_TARGET_TRIPLET=x64-linux -DCMAKE_INSTALL_PREFIX=../install/debug
    elif [ $1 -eq 2 ]; then
        cmake .. -DBUILD_TESTING=YES -DCMAKE_BUILD_TYPE=Release $cmake_gen  -DCMAKE_TOOLCHAIN_FILE=~/Desktop/code/cpp/env/vcpkg/scripts/buildsystems/vcpkg.cmake  -DVCPKG_TARGET_TRIPLET=x64-linux -DCMAKE_INSTALL_PREFIX=../install/release
    fi

    #if errors then exit
    if [ "$?" != "0" ]; then
        exit -1
    fi

    $make_program $make_flags

    #if errors then exit
    if [ "$?" != "0" ]; then
        exit -1
    fi

    # go back current dictory
    cd $current_dir

    #ok
}

make_program=make
make_flags=''
cmake_gen=''
parallel=1

case $(uname) in
 FreeBSD)
    nproc=$(sysctl -n hw.ncpu)
    ;;
 Darwin)
    nproc=$(sysctl -n hw.ncpu) # sysctl -n hw.ncpu is the equivalent to nproc on macOS.
    ;;
 *)
    nproc=$(nproc)
    ;;
esac

case nproc in
 1)
    parallel=$(( nproc + 1 ))
    ;;
 2)
    parallel=$(( nproc + 1 ))
    ;;
 *)
    parallel=$(( nproc + 2 ))
    ;;
esac


if [ -f /usr/bin/make ]; then
    make_flags="$make_flags -j$parallel"
elif [-f /usr/bin/ninja ]; then
    make_program=ninja
    cmake_gen='-GNinja'
fi

if [ "$1" = "-t" ]; then
    build 1
else
    build 2
fi



