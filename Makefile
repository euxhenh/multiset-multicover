CFLAGS = -Iincludes -I/Users/ehasanaj/miniconda3/envs/ml38/include/python3.8 -std=c++17 -DDEBUG -D_FORTIFY_SOURCE=2 \
	-D_GLIBCXX_ASSERTIONS -O2 -Wall
CC = g++
SRC = $(wildcard src/multiset_multicover/*.cpp)
SRC := $(filter-out src/multiset_multicover/python_interface.cpp, $(SRC))
OBJ = $(SRC:.cpp = .o)

all: TestSet clean

TestSet: test_set.o $(OBJ)
	$(CC) $(CFLAGS) -o test_set test_set.o $(OBJ)

test_set.o:
	$(CC) $(CFLAGS) -c test/test_set.cpp

clean:
	rm -f *.o