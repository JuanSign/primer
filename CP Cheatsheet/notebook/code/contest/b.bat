@echo off
setlocal
set f=-std=c++20 -O2 -Wall -Wextra -Wshadow -D_GLIBCXX_DEBUG
set s=-fsanitize=undefined -fsanitize-undefined-trap-on-error
g++ %1.cpp -o %1 %f% %s% -Wl,--stack=268435456
