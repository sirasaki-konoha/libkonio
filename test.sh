#!/usr/bin/env sh

CFLAGS="-std=c99 -O0 -g -fsanitize=undefined,address"
CC=gcc

build_test() {
    mkdir -p test/output

    for file in test/*.c; do
        name=$(basename "$file" .c)
        out="test/output/$name"

        echo "$CC $CFLAGS $file src/other.c src/directory/directory.c src/reader/reader.c src/writer/writer.c -o $out"

        $CC $CFLAGS "$file" \
            src/other.c \
						src/kutil.c \
            src/directory/directory.c \
            src/reader/reader.c \
            src/writer/writer.c \
            -o "$out"
    done
}

exec_test() {
    for exe in test/output/*; do
        echo "Running $exe"

        if ! "$exe"; then
            echo "== test $exe failed! =="
            continue
        fi

        echo "== $exe passed =="
    done
}

build_test
exec_test
