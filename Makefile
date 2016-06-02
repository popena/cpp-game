CXX = g++
CXXFLAGS = -Wall -Werror -O2 -std=gnu++11
LIBS = -lSDL2 -lSDL2_image -lSDL_net -pthread

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LIBS)

clean:
	rm -f $(OBJECTS) $(TARGET)
