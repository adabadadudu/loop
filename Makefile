GCC = g++
src = $(wildcard src/*.cpp)
flags = -Wall -Wextra -Wpedantic -Wconversion -Wnon-virtual-dtor -Werror -std=c++17


build: 
	$(GCC) $(src) $(flags) -o loop

all: build

clean:
	rm loop