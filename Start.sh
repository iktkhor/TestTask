#!/bin/bash

cd build
cmake ..
cmake --build .
cd ..
cp build/Debug/ConvertApp.exe .
