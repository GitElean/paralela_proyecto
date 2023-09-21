#! /bin/sh

# Configura las flags del compilador
export CXXFLAGS="-O3"

cmake -S . -B build
