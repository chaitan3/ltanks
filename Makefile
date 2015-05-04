CC = emcc
FLAGS = -Wall -Os -s USE_SDL=2 -s ASYNCIFY=1
LINC = -L./SDL2_ttf/.libs/ -L./SDL2_ttf/freetype/objs/.libs/
LIBS = -lSDL2_ttf -lfreetype
INC = -I./SDL2_ttf/

PROJ = ltanks
TARGET = $(PROJ).html
CONTENT = $(PROJ).js $(PROJ).html* $(PROJ).data 
OBJ = main.bc loadfile.bc drawscreen.bc scale.bc gui.bc bmp_loader.bc play.bc
FILES = --preload-file data/default.ltg --preload-file data/font.ttf \
				--preload-file data/LaserTank.lvl --preload-file data/sidebar.bmp \
				--preload-file $(PROJ).conf
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@ $(LINC) $(LIBS) $(FILES)
%.bc : %.c
	$(CC) $(FLAGS) $(INC) -c $< -o $@
clean:
	rm -f $(OBJ) $(CONTENT)

dir: 
	rm -rf build
	mkdir build 
	cp $(CONTENT) build
