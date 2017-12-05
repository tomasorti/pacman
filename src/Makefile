CC=g++
CFLAGS=-g -I. -I..
LDFLAGS=-lSDL2_mixer -L/usr/lib64 -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image 

SOURCES=$(wildcard *.cpp)
OBJDIR=../obj
OBJECTS=$(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))
EXECUTABLE=../pacman

all: $(info EXECUTABLE is [${EXECUTABLE}])  $(EXECUTABLE)

$(EXECUTABLE): $(OBJDIR) $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	rm -f $(EXECUTABLE)
