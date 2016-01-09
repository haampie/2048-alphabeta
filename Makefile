CXX = g++
CXXFLAGS = -std=c++14 -pthread -Wall
LINKER = $(CXX)
LDFLAGS = -pthread

TARGET = ./bin/2048
SOURCES = 2048.cc $(wildcard **/*.cc)
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