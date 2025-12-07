TARGET = main
SOURCES = main.cpp base64/base64.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = $(wildcard */*.h)

CFLAGS = -Wall -std=c++23

all: main

main: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) -o main

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean all

clean:
	rm -f *.o $(OBJECTS) main