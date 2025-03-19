CC=g++
CFLAGS=-Wall -pthread -std=c++17
SRC=src/main.cpp
OUT=philosophers

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

lint:
	cpplint --extensions=cpp,h $(SRC)

clean:
	rm -f $(OUT)
