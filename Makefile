CXX = g++
CXXFLAGS = -Wall -Werror -O2 -std=gnu++11 -g
LDFLAGS = -lSDL2 -lSDL2_image -pthread -lSDL2_ttf
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))

all: main

main: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

obj/%.o: src/%.cpp | obj
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj:
	@mkdir -p $@

clean:
	rm -rf obj main
