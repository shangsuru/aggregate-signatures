#!/usr/bin/env bash

cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build build
./build/src/benchmark