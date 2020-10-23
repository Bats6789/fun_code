OBJ = CBW_SDLTools.o CBW_FileTools.o CBW_SDLDrawTools.o
OUTPUT = ../lib/libCBW_lib.a
INCLUDE = -I .. -L ../lib
LINKER_FLAG = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -Bdynamic

CC=gcc

all: $(OBJ)
	ar -rcs $(OUTPUT) $(OBJ)

%.o: %.c
	${CC} -c $< $(INCLUDE) $(LINKER_FLAG) -o $@

clean:
	del *.o
