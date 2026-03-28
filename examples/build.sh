#!/usr/bin/env sh

CFLAGS="-std=c99 -O0 -g -fsanitize=undefined,address"
CC=gcc

build_example() {
    mkdir -p output

    for file in *.c; do
        name=$(basename "$file" .c)
        out="output/$name"

        echo "$CC $CFLAGS -I ../src $file ../src/other.c ../src/directory/directory.c ../src/reader/reader.c ../src/writer/writer.c -o $out"

        $CC $CFLAGS -I ../src \
						"$file" \
            ../src/other.c \
						../src/kutil.c \
            ../src/directory/directory.c \
            ../src/reader/reader.c \
            ../src/writer/writer.c \
            -o "$out"
    done
}

build_example
