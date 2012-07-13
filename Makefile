CC = clang
#CC = emscripten/emcc
FLAGS = -Wall
LIBS = -lSDL -lSDL_ttf
TARGET = ltanks
OBJ = main.o loadfile.o drawscreen.o scale.o gui.o bmp_loader.o play.o
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)
%.o : %.c
	$(CC) $(FLAGS) -c $<
clean:
	rm -f $(OBJ) $(TARGET)

win:
	gcc -Wall main.c loadfile.c drawscreen.c scale.c gui.c bmp_loader.c  play.c -o ltanks.exe -mwindows  -lmingw32 -lSDLmain -lSDL -lSDL_ttf
	strip ltanks.exe
