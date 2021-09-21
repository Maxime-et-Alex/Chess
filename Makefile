CC = g++
EXEC = Chess
FLAGS = -Wall -Werror -pedantic
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
STD = -std=c++17
S = src
O = obj
B = bin

all: $(O) $(B) $(O)/Main.o
	$(CC) $(O)/*.o -o $(B)/$(EXEC) $(LIBS)

$(O)/Main.o: $(O)/Engine.o
	$(CC) $(S)/Main.cpp -c -o $(O)/Main.o $(STD) $(FLAGS)

$(O)/Engine.o: $(O)/BoardDisp.o
	$(CC) $(S)/sfml/Engine.cpp -c -o $(O)/Engine.o $(STD) $(FLAGS)

$(O)/BoardDisp.o: $(O)/Board.o $(O)/PieceDisp.o
	$(CC) $(S)/sfml/BoardDisp.cpp -c -o $(O)/BoardDisp.o $(STD) $(FLAGS)

$(O)/PieceDisp.o:
	$(CC) $(S)/sfml/PieceDisp.cpp -c -o $(O)/PieceDisp.o $(STD) $(FLAGS)

$(O)/Board.o: $(O)/Rules.o
	$(CC) $(S)/game/Board.cpp -c -o $(O)/Board.o $(STD) $(FLAGS)

$(O)/Rules.o: $(O)/Piece.o
	$(CC) $(S)/game/Rules.cpp -c -o $(O)/Rules.o $(STD) $(FLAGS)

$(O)/Piece.o:
	$(CC) $(S)/game/Piece.cpp -c -o $(O)/Piece.o $(STD) $(FLAGS)

clean: $(O) $(B)
	rm -r $(O)
	rm -r $(B)

$(O):
	mkdir $(O)

$(B):
	mkdir $(B)
