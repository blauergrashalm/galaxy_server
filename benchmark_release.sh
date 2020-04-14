#!/bin/bash
./compile_release.sh
valgrind --tool=callgrind ./build/galaxy_server
