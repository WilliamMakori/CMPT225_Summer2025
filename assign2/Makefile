CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17


# Targets for each problem
problem1: problem1.cpp
	$(CXX) $(CXXFLAGS) -o problem1 problem1.cpp
	./problem1

problem2: problem2.cpp
	$(CXX) $(CXXFLAGS) -o problem2 problem2.cpp
	./problem2

problem3: problem3.cpp
	$(CXX) $(CXXFLAGS) -o problem3 problem3.cpp
	./problem3
	
# for Windows and PowerShell
clean:
	del /Q problem1 problem2 problem3
	@echo clean done

# for Linux and MacOS
remove:
	rm -f problem1 problem2 problem3
	@echo remove done
