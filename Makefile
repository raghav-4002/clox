all: compile
		./main
compile:
		gcc -Wall -Wextra -Wpedantic *.c -o main
