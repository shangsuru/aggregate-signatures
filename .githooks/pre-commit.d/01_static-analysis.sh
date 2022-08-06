#!/usr/bin/env bash

echo "[githook] Running clang-tidy for static analysis"

BUILDFOLDER=build
cmake -S . -B ${BUILDFOLDER} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

clang-tidy -p ${BUILDFOLDER} -extra-arg=-Wno-unknown-warning-option -export-fixes=fixes.yaml src/*.cpp tests/*.cpp
if [[ -f "fixes.yaml" ]]; then
    echo -n "Apply changes ... "
    clang-apply-replacements .
    echo "Done"
    rm fixes.yaml
    exit 1
fi