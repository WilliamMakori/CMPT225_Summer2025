# Makefile for compiling friendFunctions.cpp

CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = friendFunctions
SRC = friendFunctions.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
