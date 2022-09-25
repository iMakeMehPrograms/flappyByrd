#!/bin/sh 
set -e
set -x
g++ -std=c++20 -g -Wall -Wextra -Werror -pedantic \
    game.cpp io.cpp \
    CENGINE/cengine.cpp \
    TANIMLIB/animation.cpp \
    TANIMLIB/screen.cpp \
    TANIMLIB/utility.cpp \
    -o flappybyrd