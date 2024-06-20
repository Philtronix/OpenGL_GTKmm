#!/bin/bash

g++ main.cpp \
    examplewindow.cpp \
    COpenGL.cpp \
    -lepoxy \
    -o example \
    `pkg-config --cflags --libs gtkmm-4.0` \
    -lglfw3 \
    -lassimp \
    -std=c++17
