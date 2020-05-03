LIBS=-L../Libraries/lib -I../Libraries/
FLAGS=-mwindows -lmingw32 -mconsole -lSDL2main -lSDL2 -lSDL2_ttf
all:
	gcc puzzleSolver.c -o puzzleSolver.exe -g
	gcc puzzleSolverGraphics.c -o puzzleSolverGraphics.exe -g ${LIBS} ${FLAGS}
