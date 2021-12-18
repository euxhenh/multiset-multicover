CFLAGS = -Iincludes -I/Users/ehasanaj/miniconda3/envs/ml38/include/python3.8 -std=c++17 -DDEBUG
CC = g++
SRC = $(wildcard src/multiset_multipacking/*.cpp)
OBJ = $(SRC:.cpp = .o)

all: TestSet clean

TestSet: test_set.o $(OBJ)
	$(CC) $(CFLAGS) -o test_set test_set.o $(OBJ)

test_set.o:
	$(CC) $(CFLAGS) -c tests/test_set.cpp

clean:
	rm -f *.o