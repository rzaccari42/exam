CFLAGS = -Wall -Wextra -Werror -g

filter:

test: filter
	valgrind ./filter fuck42
