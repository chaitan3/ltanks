CC = emcc
FLAGS = -Wall -O2 -s USE_SDL=2 -s ASSERTIONS=1 -s ASYNCIFY=1
LINC = -L./SDL2_ttf/.libs/ -L./SDL2_ttf/freetype/objs/.libs/
LIBS = -lSDL2_ttf -lfreetype
INC = -I./SDL2_ttf/
TARGET = ltanks.html
OBJ = main.bc loadfile.bc drawscreen.bc scale.bc gui.bc bmp_loader.bc play.bc
FILES = --preload-file data/default.ltg --preload-file data/font.ttf \
				--preload-file data/LaserTank.lvl --preload-file data/sidebar.bmp \
				--preload-file ltanks.conf
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@ $(LINC) $(LIBS) $(FILES)
%.bc : %.c
	$(CC) $(FLAGS) $(INC) -c $< -o $@
clean:
	rm -f $(OBJ) $(TARGET) *.js
