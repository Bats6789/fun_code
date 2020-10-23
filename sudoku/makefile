LIBS=-L../Libraries/lib -I../Libraries/
FLAGS=-mwindows -lmingw32 -mconsole -lSDL2main -lSDL2 -lSDL2_ttf -std=c99
all:
	gcc puzzleSolver.c -o puzzleSolver.exe -g -std=c99
	gcc puzzleSolverGraphics.c -o puzzleSolverGraphics.exe -g ${LIBS} ${FLAGS}
