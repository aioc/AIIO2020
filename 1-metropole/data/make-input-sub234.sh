#!/bin/bash
set -e

# Compile generator
cd gen/

g++ main.cpp -O2 -o ../gen-sub234

cd ..

# Generate data
./gen-sub234

# Handmade cases
cp handmade/* .

# Delete compiled generators.
rm gen-sub234
