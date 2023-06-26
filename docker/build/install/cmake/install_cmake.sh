#!/usr/bin/env bash

set -e

cd "$(dirname "${BASH_SOURCE[0]}")"

THREAD_NUM=$(nproc)

# Install grpc.
VERSION="3.26.4"
PKG_NAME="CMake-${VERSION}.tar.gz"

tar xzf "${PKG_NAME}"
pushd CMake-${VERSION}
./configure --prefix=/usr/local/
make -j${THREAD_NUM}
make install
popd

rm -rf PKG_NAME CMake-${VERSION}