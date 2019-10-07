#! /bin/bash

cd $NGX_DIR

CFLAGS="-g -O0" \
    ./configure \
      --prefix=/etc/nginx \
      --sbin-path=/usr/sbin/nginx \
      --pid-path=/var/run/nginx.pid \
      --http-log-path=/var/log/nginx/access.log \
      --error-log-path=/var/log/nginx/error.log \
      --with-ld-opt="-L$EXT_DIR -lngx_go_poc" \
      --with-cc-opt="-I $EXT_DIR" \
      --with-debug \
      --add-module=$NDK_DIR \
      --add-module=$WORK_DIR

make
make install