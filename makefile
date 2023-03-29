SOURCES=main.cpp Character.cpp Player.cpp Map.cpp
EXECUTABLE=gioca

all: $(EXECUTABLE)

$(EXECUTABLE) : $(SOURCES)
	g++ -lncurses -o $(EXECUTABLE) $(SOURCES) -w
	./$(EXECUTABLE)
	rm $(EXECUTABLE)

