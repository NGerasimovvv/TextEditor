EXEC = uVuIM
SOURCES = Start.cpp Adapter.cpp Model.cpp View.cpp Controller.cpp MyString.cpp
FLAGS = -std=c++17 -O2 -o
CURSE = -lncurses
CC = g++

all: build run

build: $(SOURCES)
	$(CC) $(FLAGS) $(EXEC) $(SOURCES) $(CURSE)

run:
	./$(EXEC)

debug:
	$(CC) -g $(FLAGS) $(EXEC) $(SOURCES) $(CURSE)