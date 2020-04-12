#!/bin/bash
cmake -DCMAKE_BUILD_TYPE=Debug -GNinja --build -S . -B build && \
ninja -C build
