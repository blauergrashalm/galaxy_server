#!/bin/bash
cmake -DCMAKE_BUILD_TYPE=Release -GNinja -S . -B build && \
ninja -C build galaxy_server
