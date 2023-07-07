CC = g++
CFLAGS = -std=c++17
SRC = gap_instance.cpp gap_solution.cpp greedy1.cpp greedy2.cpp lsRelocate.cpp lsSwap.cpp genAlg.cpp random.cpp vnd.cpp multistartGen.cpp main.cpp 
OBJ = $(patsubst %.cpp, build/%.o, $(SRC))
EXEC = gap_simulator

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

build/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
