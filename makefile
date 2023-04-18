SOURCES=main.cpp Character.cpp Player.cpp Map.cpp Game.cpp Bullet.cpp Monster.cpp
EXECUTABLE=gioca
COMPILER=g++
FLAGS=-lncurses -w

all: $(EXECUTABLE)

$(EXECUTABLE) : $(SOURCES)
	$(COMPILER) -o $(EXECUTABLE) $(SOURCES) $(FLAGS)
	./$(EXECUTABLE)
	rm $(EXECUTABLE)

