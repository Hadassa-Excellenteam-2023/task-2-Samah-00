// Chess 
#include "Chess.h"
#include "Game.h"	// added this include in order to add arithmatics to the game

int main()
{
//	string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr"; 
	string board = "R#BQKB#R################################################r#bqkb#r";
	Chess a(board);
	Game game;	// added this line
	int codeResponse = 0;
	string res = a.getInput();
	while (res != "exit")
	{
		/* 
		codeResponse value : 
		Illegal movements : 
		11 - there is not piece at the source  
		12 - the piece in the source is piece of your opponent
		13 - there one of your pieces at the destination 
		21 - illegal movement of that piece 
		31 - this movement will cause you checkmate

		legal movements : 
		41 - the last movement was legal and cause check 
		42 - the last movement was legal, next turn 
		*/

		/**/ 
		// put your code here instead of that code
		/*
		cout << "code response >> ";
		cin >> codeResponse;
		*/
		codeResponse = game.play(res);
		/**/

		a.setCodeResponse(codeResponse);
		res = a.getInput(); 
	}

	cout << endl << "Exiting " << endl; 
	return 0;
}