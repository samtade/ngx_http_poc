#! /bin/bash

rm -rf $EXT_DIR

mkdir -p $EXT_DIR

cd $WORK_DIR/src

dep ensure

CGO_CFLAGS="-I $NDK_DIR/src" \
    go build \
    -v \
    -x \
    -buildmode=c-shared \
    -o $EXT_DIR/libngx_go_poc.so \
    libngx_go_poc.go
