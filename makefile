CXX = g++
CXXFLAGS = -g -MMD -L/usr/X11R6/lib -lX11
SOURCES = ${wildcard *.cc}
OBJECTS = ${SOURCES:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

EXEC: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
	
-include ${DEPENDS}

.PHONY: clean
clean :
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
