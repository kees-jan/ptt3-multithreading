# In this directory, type one of the following:
#   make
#   make all
#   make test

# Name of your test-executable
EXEC = testMessageQueue

# -I directives for the directories of your include files
INCLUDE_LOCATIONS = -I. -I../inc -I /usr/src/googletest/googletest/include

# -L directives for the locations of your libraries
LIBRARY_LOCATIONS = -L../../gtest -L../../gtest/lib

# -l directives for the libaries you need (leave out the lib and the .a parts)
LINKED_LIBRARIES = -lgtest -lgtest_main

# Name of your sources
SOURCES = $(wildcard *.cpp)

#Don't change these
CXX = g++
CXXFLAGS += -ggdb3 -Wall -Wextra -std=c++17
CPPFLAGS += -D_REENTRANT -DDEBUG $(INCLUDE_LOCATIONS)
OBJECTS = $(SOURCES:.cpp=.o)
DEPENDENCY_FILES = $(addprefix .,$(OBJECTS:.o=.d))

LDFLAGS = -pthread $(LIBRARY_LOCATIONS)

all: $(EXEC)

# Tell make to include the dependency information for your cpp files,
# if they exist, and if we are not executing "clean".
#
# Using dependency information, if you edit a .h file, all relevant
# .cpp files will be rebuilt.
ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPENDENCY_FILES)
endif

# Tells make how to compile a single source file, and to generate
# dependency information for it.
%.o:%.cpp Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ -MD -MP -MF .$*.d

# Create the testappMain target
$(EXEC): $(OBJECTS) ../src/libmessagequeue.a
	$(CXX) $(LDFLAGS) $^ -o $@ $(LINKED_LIBRARIES)

# If you change your Makefile, you probably want to rebuild your code
$(OBJECTS): Makefile

# Run your tests
test: $(EXEC)
	./$(EXEC)

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS) $(DEPENDENCY_FILES)

.PHONY: clean all test
