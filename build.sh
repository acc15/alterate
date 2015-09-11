#!/bin/bash

if [ ! -f environment.sh ]; then
    echo Create environment.sh file. Use environment.sh.sample as template
    exit 1
fi

source environment.sh

mkdir -p build
cd build/
cmake ../

make all
