#!/bin/bash

WARNING='\033[1;31m'
INFO='\033[1;32m'
NC='\033[0m'

FUSE_DIR="/tmp/ej-fuse"

echo -e "${WARNING}You need to install git, libfuse-dev, libcurl4-openssl-dev, libssl-dev for run this script${NC}"

echo -e "${INFO}Clone git repo${NC}"
git clone https://github.com/blackav/ejudge-fuse.git $FUSE_DIR
cd $FUSE_DIR/src
if ! make; then
    echo -e "${WARNING}Some libs not found! Please install it${NC}"
    rm -rf $FUSE_DIR
    exit
fi

echo -e "${INFO}All done!${NC}"
