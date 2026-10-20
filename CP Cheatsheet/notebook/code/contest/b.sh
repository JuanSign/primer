f="-std=c++20 -O2 -Wall -Wextra -Wshadow -D_GLIBCXX_DEBUG"
g++ $1.cpp -o $1 $f -fsanitize=address,undefined -g
