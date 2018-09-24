CXX=g++-5
CXXFLAGS=-std=c++14 -Wall -Werror=vla -MMD
EXEC=./bin/jsnake
VIEW=./src/view/textdisplay.o
OBJECTS=./src/main.o ./src/posn.o ./src/subject.o ./src/map.o ./src/snake.o ./src/apple.o ${VIEW}
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 -lncurses

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean

