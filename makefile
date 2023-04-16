SOURCES=main.cpp Character.cpp Player.cpp Map.cpp Game.cpp Bullet.cpp Monster.cpp
EXECUTABLE=gioca

all: $(EXECUTABLE)

$(EXECUTABLE) : $(SOURCES)
	g++ -o $(EXECUTABLE) $(SOURCES) -lncurses -w
	./$(EXECUTABLE)
	rm $(EXECUTABLE)

