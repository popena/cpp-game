CXX = g++
CXXFLAGS = -Werror -Wall -O2
LIBS = -lSDL2 -lSDL2_image

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
TARGET = src/main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LIBS)

clean:
	rm -f $(OBJECTS) $(TARGET)
