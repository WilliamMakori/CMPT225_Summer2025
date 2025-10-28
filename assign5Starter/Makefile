# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -pedantic -Wall -Wextra -std=c++17

# Target executable
TARGET = main

# For deleting the target
TARGET_DEL = main.exe

# Source files
SRCS = Graph.cpp experiments.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule to build and run the executable
all: $(TARGET) run

# Rule to link object files into the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the executable
run:
	./$(TARGET)

# Clean rule to remove generated files for Windows
clean:
	del $(TARGET_DEL) $(OBJS)
	

# for Linux and MacOS (I hope)
remove:
	\rm -f $(TARGET) $(OBJS) *.o