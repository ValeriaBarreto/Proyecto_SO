CXX = g++
CXXFLAGS = -std=c++11 -Iinclude
SRC = src/main.cpp src/system.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = monitor

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
