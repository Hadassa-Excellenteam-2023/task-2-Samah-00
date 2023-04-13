"# task-2-Samah-00" 
The design of the project:

Piece class - an abstract base class for all the different chess pieces. 
It defines common properties and methods that all the pieces share, such as their color and position on the board,
it has a pure virtual function that checks the movement logic of the piece, the method is implemented differently
in each one of the derived classes.

Pawn class - inherits from the Piece class. note that the movement method for the Pawn class always return false
(and code 21) since the pawns aren't implemented in this project.

Knight class - inherits from the Piece class. note that the movement method for the Pawn class always return false
(and code 21) since the pawns aren't implemented in this project.

Bishop class - inherits from the Piece class and implement the movement logic for bishops,
including the ability to move diagonally.

Rook class - inherits from the Piece class and implement the movement logic for rooks, 
including the ability to move horizontally and vertically.

Queen class - inherits from the Piece class and implement the movement logic for queens, 
including the ability to move diagonally, horizontally, and vertically.

King class - inherits from the Piece class and implement the movement logic for kings, 
including the ability to move one square in any direction.

Board class - represents the game board and contain a matrix of pointers to Piece objects. 
It has methods for initializing the board, moving pieces, and checking for checkmate and check.

Player class - represents a player in the game and contain their color. 
It has methods for making moves.

Game class - the main class that ties everything together and controls the flow of the game. 
It will create two Player objects and a Board object. 
It alternates between the players making moves until the game is over.


In each iteration, the main loop in the main class calls the Game::Play() function which is responsible for
extracting the input values, calling the makeMove method of the Player class to check whether the move is legal or not, 
handling the result of the move and returning a suitable code to the main. 

The Piece class is a base class for all the pieces 
and the Board class is responsible for updating the pieces on the board and checking whether the king is in check or not.

For instance, the Piece class and its subclasses (King, Queen, Rook, etc.) check the legality of the moves. 
The Player class is responsible for keeping track of the pieces of a player and updating them after a move. 
Finally, the Board class is responsible for updating the state of the board and checking whether the king is in check.

Please note that I added '#include "Game.h"' to the main as well as created a Game object and called it game in order
to handle the logic of the chess game.

Please also note that I updated the board string in the main so that it doesn't have knights or pawns because they are't
implemented in this project.