CXX = g++
CXXFLAGS = -O3 -std=c++14 -Wall -I ../BSPLib/bsp/include/ -pthread
LINKER = $(CXX)
LDFLAGS = -pthread

TARGET = ./bin/play-against-pc
SOURCES = play-against-pc.cc $(wildcard **/*.cc)
OBJECTS = $(SOURCES:.cc=.o)

DEPS = $(OBJECTS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINKER) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $(CXXINCL) $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPS)

-include $(DEPS)