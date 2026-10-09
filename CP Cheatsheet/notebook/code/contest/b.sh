g++ $1.cpp -o $1 -std=c++20 -O2 \
  -Wall -Wextra -Wshadow \
  -D_GLIBCXX_DEBUG \
  -fsanitize=address,undefined -g
