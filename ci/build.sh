#!/bin/bash -e

builddir="${TRAVIS_BUILD_DIR}/build"

mkdir -p ${builddir}
cd ${builddir}

cmake ..
make
tests/fat_test
