SOURCES=main.cpp
EXECUTABLE=gioca

all: $(EXECUTABLE)

$(EXECUTABLE) : $(SOURCES)
	g++ -lncurses -o $(EXECUTABLE) $(SOURCES)
	./$(EXECUTABLE)
	rm $(EXECUTABLE)
