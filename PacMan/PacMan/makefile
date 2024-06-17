# Kompilator
CXX = g++

# Flagi kompilatora
CXXFLAGS = -std=c++11 -Wall -g

# Flagi dla SDL2 i SDL2_image
SDL2_CFLAGS = -IC:/msys64/mingw64/include/SDL2 -Dmain=SDL_main
SDL2_LDFLAGS = -LC:/msys64/mingw64/lib -lmingw32 -mwindows -lSDL2main -lSDL2 -lSDL2_image

# Pliki źródłowe
SRCS = GameLoop.cpp main.cpp TextureManager.cpp

# Pliki obiektowe
OBJS = $(SRCS:.cpp=.o)

# Nazwa pliku wykonywalnego
TARGET = GRA

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(SDL2_LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
