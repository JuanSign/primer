@g++ %1.cpp -o %1 -std=c++20 -O2 ^
  -Wall -Wextra -Wshadow ^
  -D_GLIBCXX_DEBUG ^
  -fsanitize=undefined -fsanitize-undefined-trap-on-error ^
  -Wl,--stack=268435456
