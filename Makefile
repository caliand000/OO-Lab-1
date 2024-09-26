CC=g++
CFLAGS=-std=c++17 -Wall -g


# The source files we use for building custom_tests
ALL_SRC=mainProj2.cpp
#$(wildcard *.cpp)

# The file to store compilation errors
#ERROR_LOG=errors.txt

# The name of the resulting executable
APP=test
#2> $(ERROR_LOG)
custom_tests:
	$(CC) $(CFLAGS) $(ALL_SRC) -o $(APP) 

clean:
	rm -f $(APP)
