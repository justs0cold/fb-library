@echo off
g++ -std=c++26 -Wall -Werror -Wextra -Wpedantic -I include examples/main.cpp -o main.exe -lstdc++exp