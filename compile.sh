#!/bin/bash
cmake -DCMAKE_BUILD_TYPE=Debug -GNinja -S . -B build && \
ninja -C build galaxy_server
