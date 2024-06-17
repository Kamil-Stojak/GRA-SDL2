# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -g

# SDL2 flags
SDL2_CFLAGS = -IC:/msys64/mingw64/include/SDL2 -Dmain=SDL_main
SDL2_LDFLAGS = -LC:/msys64/mingw64/lib -lmingw32 -mwindows -lSDL2main -lSDL2

# Source files
SRCS = GameLoop.cpp main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable
TARGET = GRA

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(SDL2_LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
