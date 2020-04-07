#!/bin/bash
cmake -GNinja --build -S . -B build && \
ninja -C build
