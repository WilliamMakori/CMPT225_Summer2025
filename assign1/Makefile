CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17

# Source and object files
SRC = MyFloat.cpp assign1.cpp
OBJ = $(SRC:.cpp=.o)

# Executable name
TARGET = assign1

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp file into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# for Windows and PowerShell
clean:
	del /Q $(TARGET).exe *.o
	@echo clean done

# for Linux and MacOS
remove:
	rm -f $(TARGET) *.o
	@echo remove done