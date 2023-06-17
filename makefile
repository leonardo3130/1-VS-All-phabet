COMPILER=g++
SOURCES=main.cpp Character.cpp Player.cpp Map.cpp Game.cpp Bullet.cpp Monster.cpp
EXECUTABLE=gioca
FLAGS=-lncurses -w

all: $(EXECUTABLE)

$(EXECUTABLE) : $(SOURCES)
	$(COMPILER) -o $(EXECUTABLE) $(SOURCES) $(FLAGS)


clean:
	@if [ -f $(EXECUTABLE) ]; then	\
		rm $(EXECUTABLE); \
		echo "Eseguibile rimosso."; \
	else \
		echo "Eseguibile già rimosso."; \
	fi

reset:
	rm -r Archivio/*

run:
	./$(EXECUTABLE)

