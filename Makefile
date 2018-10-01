SRC_DIR		= ./src
OBJ_DIR		= ./build
BIN_DIR		= ./bin
SRC_FILE	= ${addprefix ${SRC_DIR}/, posn.cc subject.cc map.cc snake.cc apple.cc textdisplay.cc}
OBJ_FILE	= ${addprefix ${OBJ_DIR}/, main.o posn.o subject.o map.o snake.o apple.o textdisplay.o}
INCLUDE		= -lX11 -lncurses
DEPENDS		= ${OBJ_FILE:.o=.d}

CXX=g++
CXXFLAGS=-std=c++17 -Wall -Werror=vla -MMD
EXEC=${addprefix ${BIN_DIR}/, jsnake}

.PHONY : clean directories

all: directories ${EXEC}

-include ${DEPENDS}

${EXEC} : ${OBJ_FILE}
	${CXX} ${OBJ_FILE} -o ${EXEC} ${INCLUDE}

${OBJ_DIR}/%.o : ${SRC_DIR}/%.cc
	${CXX} ${CXXFLAGS} -c  $< -o $@

${OBJ_DIR}/%.o : ${SRC_DIR}/models/%.cc
	${CXX} ${CXXFLAGS} -c  $< -o $@

${OBJ_DIR}/%.o : ${SRC_DIR}/views/%.cc
	${CXX} ${CXXFLAGS} -c  $< -o $@

${OBJ_DIR}/%.o : ${SRC_DIR}/controllers/%.cc
	${CXX} ${CXXFLAGS} -c  $< -o $@

directories: ${OBJ_DIR} ${BIN_DIR}

${OBJ_DIR} :
	mkdir -p ${OBJ_DIR}

${BIN_DIR} :
	mkdir -p ${BIN_DIR}

clean :
	rm ${OBJ_FILE} ${DEPENDS} ${EXEC}
	rmdir ${OBJ_DIR} ${BIN_DIR}