#!/bin/bash

# script directory
SCRIPT_DIR=$(cd $(dirname $0); pwd)
# echo "SCRIPT_DIR: $SCRIPT_DIR"

# go to parent of script directory
cd $SCRIPT_DIR/..
ROOT_DIR=$(pwd)
DATEHOURLABEL=$(date "+%Y.%m.%d_%H:%M:%S")

git archive --format=zip --output=$ROOT_DIR/../dp_$DATEHOURLABEL.zip HEAD
echo "Created zip file: $ROOT_DIR/../dp_$DATEHOURLABEL.zip"

