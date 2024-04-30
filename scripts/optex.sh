#!/bin/bash

# script directory
SCRIPT_DIR=$(cd $(dirname $0); pwd)
echo "SCRIPT_DIR: $SCRIPT_DIR"

# go to parent of script directory
cd $SCRIPT_DIR/..
ROOT_DIR=$(pwd)

# create build directory
mkdir -p $ROOT_DIR/build

# compile
#optex -kanji=utf8 -synctex=1 -interaction=nonstopmode -output-directory=$ROOT_DIR/build $ROOT_DIR/main.tex
optex -kanji=utf8 -synctex=1  -output-directory=$ROOT_DIR/build $ROOT_DIR/main.tex

