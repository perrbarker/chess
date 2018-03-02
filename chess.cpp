/****************************************************************
File: Chess.exe			
Description: a game of chess	

Author: Dalton Tinoco, Perry Barker		 
Class: Compsci 110	
Date:11/17/14	

I hereby certify that this program is entirely my own work.
*****************************************************************/
#include "stdafx.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

//enumerated data type
enum CHESS_PIECE
{
	BLANK,
	PAWN_B, ROOK_B, KNIGHT_B, BISHOP_B, QUEEN_B, KING_B,
	PAWN_W, ROOK_W, KNIGHT_W, BISHOP_W, QUEEN_W, KING_W,
	BLACK, WHITE
};

//global constants
const int ROWS = 8;
const int COLS = 8;

void printBoardFunction();
void displayFunction(CHESS_PIECE &piece);
void piecesetFunction(int piece, CHESS_PIECE &piece_set);
void whiteBlackFunction(const int ROWS, CHESS_PIECE whiteBlack[][COLS], CHESS_PIECE chessBoard[][COLS], int i, int k, CHESS_PIECE &PIECE_TYPE);
void checkmovementFunction(CHESS_PIECE piece_set, const int ROWS, const int ROW_1, const int COL_1, CHESS_PIECE chessBoard[][COLS], bool valid[][COLS], CHESS_PIECE whiteBlack[][COLS]);

int main(int argc, char const *argv[])
{
	int piece;
	int i = 0; //loop var
	int k = 0; //loop var
	int invalidMove = 0;
	int ROW_1, COL_1, ROW_2, COL_2;
	int pTurn = 0;
	int kings_count = 0;
	CHESS_PIECE piece_set;
	CHESS_PIECE PIECE_TYPE = BLANK;
	CHESS_PIECE whiteBlack[ROWS][COLS];
	bool exitVal = false;
	bool valid[ROWS][COLS];
	string command = "?";

	CHESS_PIECE chessBoard[ROWS][COLS];
	//set chessboard as blank
	for (i = 0; i < ROWS; ++i)
	{
		for (k = 0; k < COLS; ++k)
		{
			chessBoard[i][k] = BLANK;
		}
	}

	chessBoard[0][0] = ROOK_B;
	chessBoard[0][1] = KNIGHT_B;
	chessBoard[0][2] = BISHOP_B;
	chessBoard[0][3] = KING_B;
	chessBoard[0][4] = QUEEN_B;
	chessBoard[0][5] = BISHOP_B;
	chessBoard[0][6] = KNIGHT_B;
	chessBoard[0][7] = ROOK_B;

	chessBoard[1][0] = PAWN_B;
	chessBoard[1][1] = PAWN_B;
	chessBoard[1][2] = PAWN_B;
	chessBoard[1][3] = PAWN_B;
	chessBoard[1][4] = PAWN_B;
	chessBoard[1][5] = PAWN_B;
	chessBoard[1][6] = PAWN_B;
	chessBoard[1][7] = PAWN_B;

	chessBoard[7][0] = ROOK_W;
	chessBoard[7][1] = KNIGHT_W;
	chessBoard[7][2] = BISHOP_W;
	chessBoard[7][3] = QUEEN_W;
	chessBoard[7][4] = KING_W;
	chessBoard[7][5] = BISHOP_W;
	chessBoard[7][6] = KNIGHT_W;
	chessBoard[7][7] = ROOK_W;

	chessBoard[6][0] = PAWN_W;
	chessBoard[6][1] = PAWN_W;
	chessBoard[6][2] = PAWN_W;
	chessBoard[6][3] = PAWN_W;
	chessBoard[6][4] = PAWN_W;
	chessBoard[6][5] = PAWN_W;
	chessBoard[6][6] = PAWN_W;
	chessBoard[6][7] = PAWN_W;

	cout << "Type \"HELP\" for the list of commands. If you know the rules, have fun!" << endl;
	//start main game loop here
	while (true)
	{
		if (exitVal == true)
		{
			break;
		}
		//command input for beta testing
		while (true)
		{
			kings_count = 0;
			for (int i = 0; i < ROWS; ++i)
			{
				for (int k = 0; k < COLS; ++k)
				{
					if ((chessBoard[i][k] == KING_B) || (chessBoard[i][k] == KING_W))
					{
						kings_count += 1;
					}
				}
			}
			if (kings_count < 2)
			{
				exitVal = true;
				break;
			}
			for (i = 0; i < ROWS; ++i)
			{
				for (k = 0; k < COLS; ++k)
				{
					whiteBlackFunction(ROWS, whiteBlack, chessBoard, i, k, PIECE_TYPE);
					whiteBlack[i][k] = PIECE_TYPE;

				}
			}
			//print current state of the chessboard
			for (i = 0; i < ROWS; ++i)
			{
				cout << i + 1;
				for (k = 0; k < COLS; ++k)
				{
					displayFunction(chessBoard[i][k]);
				}
				cout << endl;
			}
			cout << "  1   2   3   4   5   6   7   8" << endl;
			cout << "Enter a command, type help for list of commands... ";
			while (true)
			{
				cin >> command;
				cin.clear();
				cin.ignore();
				if ((command != "PLACE") && (command != "MOVE") && (command != "EXIT") && (command != "HELP") && (command != "RULES"))
				{
					cout << "Invalid command! Please try again..." << endl;
					continue;
				}
				else
				{
					break;
				}
			}
			if (command == "PLACE")
			{
				cout << "enter location to place any piece (x,y): ";
				cin >> i;
				cin >> k;
				cout << "enter number of piece to place at " << i << "," << k << ": ";
				cin >> piece;
				piecesetFunction(piece, piece_set);
				chessBoard[i - 1][k - 1] = piece_set;
				break;
			}
			else if (command == "RULES")
			{
				cout << "      **Welcome to the game of CHESS**" << endl << endl;
				cout << "Object of the game is to take the opponent's KING." << endl;
				cout << "Commands are: MOVE, EXIT, PLACE, and HELP." << endl;
				cout << "*Input MOVE to select a coordinate (y,x)" << endl;
				cout << "*Then select coordinate(y, x) to MOVE piece to." << endl;
				cout << " Each PIECE has a restricted move set." << endl << endl;
				cout << "**PAWN (PW/PB) can move 2 spaces forward if they are in their intial space." << endl;
				cout << "  Otherwise, PAWN can only move 1 space and take opponent pieces" << endl; 
				cout << "  that are diagonally in front." << endl;
				cout << "  If PAWN reaches otherside of the board, PAWN becomes any piece." << endl << endl;
				cout << "**ROOK (RW/RB) can move up, down, left, right, any amount of spaces" << endl;
				cout << "  ROOK can not move through ally pieces." << endl << endl;
				cout << "**BISHOP (BW/BB) can move only diagonlly in any direction" << endl; 
				cout <<"   (up / left, up / right, down / left, and down / right)" << endl;
				cout << "  BISHOP can not move through ally pieces." << endl << endl;
				cout << "**KNIGHT (KW/KB) can move in 8 directions in a 2 spaces by 1 space sequence." << endl;
				cout << "  KNIGHT can move over any piece." << endl << endl;
				cout << "**QUEEN (QW/QB) can move in any amount of spaces in any direction" << endl; 
				cout << "  Including diagonally." << endl;
				cout << "  QUEEN can not move through ally pieces." << endl << endl;
				cout << "**KING (*W/*B) can move 1 space in any direction." << endl;
				cout << "  Space must be empty or an enemy piece." << endl << endl;
				cout << "*Input EXIT to quit game." << endl;
				cout << "*Input PLACE to place a piece on the board." << endl;
				cout << "*Input HELP to display list of commands." << endl << endl;
				cout << "      WHITE always plays first." << endl << endl;
			}
			else if (command == "MOVE")
			{
				for (i = 0; i < ROWS; ++i)
				{
					for (k = 0; k < COLS; ++k)
					{
						valid[i][k] = false;
					}
				}
				//movement routine
				while (true)
				{
					cin.clear();
					cout << "select a piece to move (x,y): ";
					cin >> ROW_1;
					cin >> COL_1;
					ROW_1 -= 1;
					COL_1 -= 1;
					if ((whiteBlack[ROW_1][COL_1] == WHITE) && (pTurn == 1))
					{
						cout << "Please select Black piece!" << endl;
						continue;
					}
					else if ((whiteBlack[ROW_1][COL_1] == BLACK) && (pTurn == 0))
					{
						cout << "Please select White piece!" << endl;
						continue;
					}
					piece_set = chessBoard[ROW_1][COL_1];
					//Check selected pieces rule set
					checkmovementFunction(piece_set, ROWS, ROW_1, COL_1, chessBoard, valid, whiteBlack);
					for (i = 0, invalidMove = 0; i < ROWS; ++i)
					{
						for (k = 0; k < COLS; ++k)
						{
							if (valid[i][k] == false)
							{
								++invalidMove;
							}
						}
					}
					if (invalidMove == 64)
					{
						cout << "piece cannot move! please select another piece..." << endl;
						continue;
					}
					else
					{
						break;
					}
				}
				//function to check for taking of pieces, and swap location of moved piece from (ROW_1, COL_1) to (ROW_2, COL_2)
				//this is a mockup of the actual function, proof of concept right now
				while (true)
				{
					cin.clear();
					cout << "Select where to move " << piece_set << " to (x, y): ";
					cin >> ROW_2;
					cin >> COL_2;
					cout << "after input" << endl;
					ROW_2 -= 1;
					COL_2 -= 1;
					if (valid[ROW_2][COL_2] != true)
					{
						cout << "invalid move!" << endl;
						continue;
					}
					else
					{
						chessBoard[ROW_2][COL_2] = piece_set;
						chessBoard[ROW_1][COL_1] = BLANK;
						if (pTurn == 0)
						{
							pTurn += 1;
						}
						else if (pTurn == 1)
						{
							pTurn -= 1;
						}
						break;
					}
				}
				continue;
			}
			else if (command == "HELP")
			{
				cout << "PLACE: places a piece on the board." << endl;
				cout << "MOVE: moves a piece on the board" << endl;
				cout << "EXIT: exit program." << endl;
				cout << "RULES: displays the rules to the game." << endl;
			}
			else if (command == "EXIT")
			{
				exitVal = true;
				break;
			}

		}
	}

	system("Pause");
	return 0;
}

void displayFunction(CHESS_PIECE &piece)
{
	switch (piece)
	{
	case 0:
		cout << "|  |";
		break;
	case 1:
		cout << "|PB|";
		break;
	case 2:
		cout << "|RB|";
		break;
	case 3:
		cout << "|KB|";
		break;
	case 4:
		cout << "|BB|";
		break;
	case 5:
		cout << "|QB|";
		break;
	case 6:
		cout << "|*B|";
		break;
	case 7:
		cout << "|PW|";
		break;
	case 8:
		cout << "|RW|";
		break;
	case 9:
		cout << "|KW|";
		break;
	case 10:
		cout << "|BW|";
		break;
	case 11:
		cout << "|QW|";
		break;
	case 12:
		cout << "|*W|";
		break;
	default:
		cout << "An unexpected error has occured: display fuction!" << endl;
		break;
	}
}
//this function selects the piece that will be used to replace the currently selected movement tile
void piecesetFunction(int piece, CHESS_PIECE &piece_set)
{
	switch (piece)
	{
	case 0:
		piece_set = BLANK;
		break;
	case 1:
		piece_set = PAWN_B;
		break;
	case 2:
		piece_set = ROOK_B;
		break;
	case 3:
		piece_set = KNIGHT_B;
		break;
	case 4:
		piece_set = BISHOP_B;
		break;
	case 5:
		piece_set = QUEEN_B;
		break;
	case 6:
		piece_set = KING_B;
		break;
	case 7:
		piece_set = PAWN_W;
		break;
	case 8:
		piece_set = ROOK_W;
		break;
	case 9:
		piece_set = KNIGHT_W;
		break;
	case 10:
		piece_set = BISHOP_W;
		break;
	case 11:
		piece_set = QUEEN_W;
		break;
	case 12:
		piece_set = KING_W;
		break;
	default:
		cout << "An unexpected error has occured: piece set function!" << endl;
		break;
	}

}

//white, black or blank fucntion
void whiteBlackFunction(const int ROWS, CHESS_PIECE whiteBlack[][COLS], CHESS_PIECE chessBoard[][COLS], const int i, const int k, CHESS_PIECE &PIECE_TYPE)
{
	if (chessBoard[i][k] == 0)
	{
		PIECE_TYPE = BLANK;
	}
	else if ((chessBoard[i][k] >= 1) && (chessBoard[i][k] <= 6))
	{
		PIECE_TYPE = BLACK;
	}
	else if ((chessBoard[i][k] >= 7) && (chessBoard[i][k] <= 12))
	{
		PIECE_TYPE = WHITE;
	}
}

//movement checking function
void checkmovementFunction(CHESS_PIECE piece_set, const int ROWS, const int ROW_1, const int COL_1, CHESS_PIECE chessBoard[][COLS], bool valid[][COLS], CHESS_PIECE whiteBlack[][COLS])
{
	int i, k, j;
	bool isWhite = false;
	if ((chessBoard[ROW_1][COL_1] >= 1) && (chessBoard[ROW_1][COL_1] <= 6))
	{
		isWhite = false;
	}
	else if ((chessBoard[ROW_1][COL_1] >= 7) && (chessBoard[ROW_1][COL_1] <= 12))
	{
		isWhite = true;
		switch (piece_set)
		{
		case 7:
			piece_set = PAWN_B;
			break;
		case 8:
			piece_set = ROOK_B;
			break;
		case 9:
			piece_set = KNIGHT_B;
			break;
		case 10:
			piece_set = BISHOP_B;
			break;
		case 11:
			piece_set = QUEEN_B;
			break;
		case 12:
			piece_set = KING_B;
			break;
		default:
			cout << "an unexpected error has occured: piece translation, with piece " << piece_set << "- 6..." << endl;
			break;
		}
	}
	switch (piece_set)
	{
		//pawn
	case 1:
		if (isWhite == false)
		{
			if (chessBoard[ROW_1 + 1][COL_1] == BLANK)
			{
				valid[ROW_1 + 1][COL_1] = true;
				if ((chessBoard[ROW_1 + 2][COL_1] == BLANK) && (ROW_1 == 1))
				{
					valid[ROW_1 + 2][COL_1] = true;
				}
			}
			if (whiteBlack[ROW_1 + 1][COL_1 + 1] == WHITE)
			{
				valid[ROW_1 + 1][COL_1 + 1] = true;
			}
			if (whiteBlack[ROW_1 + 1][COL_1 - 1] == WHITE)
			{
				valid[ROW_1 + 1][COL_1 - 1] = true;
			}
		}
		else if (isWhite == true)
		{
			if (chessBoard[ROW_1 - 1][COL_1] == BLANK)
			{
				valid[ROW_1 - 1][COL_1] = true;
				if ((chessBoard[ROW_1 - 2][COL_1] == BLANK) && (ROW_1 == 6))
				{
					valid[ROW_1 - 2][COL_1] = true;
				}
			}
			if (whiteBlack[ROW_1 + 1][COL_1 + 1] == BLACK)
			{
				valid[ROW_1 - 1][COL_1 + 1] = true;
			}
			if (whiteBlack[ROW_1 + 1][COL_1 - 1] == BLACK)
			{
				valid[ROW_1 - 1][COL_1 - 1] = true;
			}
		}
		break;
		//rook
	case 2:
		for (i = ROW_1 + 1, j = 0; i < 8; ++i, ++j)
		{
			if (chessBoard[i][COL_1] == BLANK)
			{
				valid[i][COL_1] = true;
			}
			else if (isWhite == false)
			{
				if (whiteBlack[i][COL_1] == WHITE)
				{
					valid[i][COL_1] = true;
					break;
				}
				else if (whiteBlack[i][COL_1] == BLACK)
				{
					break;
				}
			}
			else if (isWhite == true)
			{
				if (whiteBlack[i][COL_1] == BLACK)
				{
					valid[i][COL_1] = true;
					break;
				}
				else if (whiteBlack[i][COL_1] == WHITE)
				{
					break;
				}
			}
		}
		for (i = ROW_1 - 1, j = 0; i > -1; --i, ++j)
		{
			if (chessBoard[i][COL_1] == BLANK)
			{
				valid[i][COL_1] = true;
			}
			else if (isWhite == false)
			{
				if (whiteBlack[i][COL_1] == WHITE)
				{
					valid[i][COL_1] = true;
					break;
				}
				else if (whiteBlack[i][COL_1] == BLACK)
				{
					break;
				}
			}
			else if (isWhite == true)
			{
				if (whiteBlack[i][COL_1] == BLACK)
				{
					valid[i][COL_1] = true;
					break;
				}
				else if (whiteBlack[i][COL_1] == WHITE)
				{
					break;
				}
			}
		}
		for (i = COL_1 + 1, j = 0; i < 8; ++i, --j)
		{
			if (chessBoard[ROW_1][i] == BLANK)
			{
				valid[ROW_1][i] = true;
			}
			else if (isWhite == false)
			{
				if (whiteBlack[ROW_1][i] == WHITE)
				{
					valid[ROW_1][i] = true;
					break;
				}
				else if (whiteBlack[ROW_1][i] == BLACK)
				{
					break;
				}
			}
			else if (isWhite == true)
			{
				if (whiteBlack[ROW_1][i] == BLACK)
				{
					valid[i][COL_1] = true;
					break;
				}
				else if (whiteBlack[ROW_1][i] == WHITE)
				{
					break;
				}
			}
		}
		for (i = COL_1 - 1, j = 0; i > -1; --i, ++j)
		{
			if (chessBoard[ROW_1][i] == BLANK)
			{
				valid[ROW_1][i] = true;
			}
			else if (isWhite == false)
			{
				if (whiteBlack[ROW_1][i] == WHITE)
				{
					valid[ROW_1][i] = true;
					break;
				}
				else if (whiteBlack[i][COL_1] == BLACK)
				{
					break;
				}
			}
			else if (isWhite == true)
			{
				if (whiteBlack[ROW_1][i] == BLACK)
				{
					valid[ROW_1][i] = true;
					break;
				}
				else if (whiteBlack[ROW_1][i] == WHITE)
				{
					break;
				}
			}
		}
		break;
	//Knight
	case 3:
		//check +2 +1
		if (chessBoard[ROW_1 + 2][COL_1 + 1] == BLANK)
		{
			valid[ROW_1 + 2][COL_1 + 1] = true;
		}
		else if (isWhite == false)
		{
			if (whiteBlack[ROW_1 + 2][COL_1 + 1] == WHITE)
			{
				valid[ROW_1 + 2][COL_1 + 1] = true;
			}
		}
		else if (isWhite == true)
		{
			if (whiteBlack[ROW_1 + 2][COL_1 + 1] == BLACK)
			{
				valid[ROW_1 + 2][COL_1 + 1] = true;
			}
		}
		//check +2 -1
		if (chessBoard[ROW_1 + 2][COL_1 - 1] == BLANK)
		{
			valid[ROW_1 + 2][COL_1 - 1] = true;
		}
		else if (isWhite == false)
		{
			if (whiteBlack[ROW_1 + 2][COL_1 - 1] == WHITE)
			{
				valid[ROW_1 + 2][COL_1 - 1] = true;
			}
		}
		else if (isWhite == true)
		{
			if (whiteBlack[ROW_1 + 2][COL_1 - 1] == BLACK)
			{
				valid[ROW_1 + 2][COL_1 - 1] = true;
			}
		}
		//check -2 +1
		if (chessBoard[ROW_1 - 2][COL_1 + 1] == BLANK)
		{
			valid[ROW_1 - 2][COL_1 + 1] = true;
		}
		else if (isWhite == false)
		{
			if (whiteBlack[ROW_1 - 2][COL_1 + 1] == WHITE)
			{
				valid[ROW_1 - 2][COL_1 + 1] = true;
			}
		}
		else if (isWhite == true)
		{
			if (whiteBlack[ROW_1 - 2][COL_1 + 1] == BLACK)
			{
				valid[ROW_1 - 2][COL_1 + 1] = true;
			}
		}
		//checl -2 -1
		if (chessBoard[ROW_1 - 2][COL_1 - 1] == BLANK)
		{
			valid[ROW_1 - 2][COL_1 - 1] = true;
		}
		else if (isWhite == false)
		{
			if (whiteBlack[ROW_1 - 2][COL_1 - 1] == WHITE)
			{
				valid[ROW_1 - 2][COL_1 - 1] = true;
			}
		}
		else if (isWhite == true)
		{
			if (whiteBlack[ROW_1 - 2][COL_1 - 1] == BLACK)
			{
				valid[ROW_1 - 2][COL_1 - 1] = true;
			}
		}
		//check +1 +2
		if (chessBoard[ROW_1 + 1][COL_1 + 2] == BLANK)
		{
			valid[ROW_1 + 1][COL_1 + 2] = true;
		}
		else if (isWhite == false)
		{
			if (whiteBlack[ROW_1 + 1][COL_1 + 2] == WHITE)
			{
				valid[ROW_1 + 1][COL_1 + 2] = true;
			}
		}
		else if (isWhite == true)
		{
			if (whiteBlack[ROW_1 + 1][COL_1 + 2] == BLACK)
			{
				valid[ROW_1 + 1][COL_1 + 2] = true;
			}
		}
		//check -1 +2
		if (chessBoard[ROW_1 - 1][COL_1 + 2] == BLANK)
		{
			valid[ROW_1 - 1][COL_1 + 2] = true;
		}
		else if (isWhite == false)
		{
			if (whiteBlack[ROW_1 - 1][COL_1 + 2] == WHITE)
			{
				valid[ROW_1 - 1][COL_1 + 2] = true;
			}
		}
		else if (isWhite == true)
		{
			if (whiteBlack[ROW_1 - 1][COL_1 + 2] == BLACK)
			{
				valid[ROW_1 - 1][COL_1 + 2] = true;
			}
		}
		//check -1 -2
		if (chessBoard[ROW_1 - 1][COL_1 - 2] == BLANK)
		{
			valid[ROW_1 - 1][COL_1 - 2] = true;
		}
		else if (isWhite == false)
		{
			if (whiteBlack[ROW_1 - 1][COL_1 - 2] == WHITE)
			{
				valid[ROW_1 - 1][COL_1 - 2] = true;
			}
		}
		else if (isWhite == true)
		{
			if (whiteBlack[ROW_1 - 1][COL_1 - 2] == BLACK)
			{
				valid[ROW_1 - 1][COL_1 - 2] = true;
			}
		}
		//check +1 -2
		if (chessBoard[ROW_1 + 1][COL_1 - 2] == BLANK)
		{
			valid[ROW_1 + 1][COL_1 - 2] = true;
		}
		else if (isWhite == false)
		{
			if (whiteBlack[ROW_1 + 1][COL_1 - 2] == WHITE)
			{
				valid[ROW_1 + 1][COL_1 - 2] = true;
			}
		}
		else if (isWhite == true)
		{
			if (whiteBlack[ROW_1 + 1][COL_1 - 2] == BLACK)
			{
				valid[ROW_1 + 1][COL_1 - 2] = true;
			}
		}
		break;
	//bishop
	case 4:
		for (i = ROW_1 + 1, k = COL_1 + 1, j = 0; i < 8, k < 8; ++i, ++k)
		{
			if (chessBoard[i][k] == BLANK)
			{
				valid[i][k] = true;
			}
			else if (isWhite == false)
			{
				if (whiteBlack[i][k] == WHITE)
				{
					valid[i][k] = true;
					break;
				}
				else if (whiteBlack[i][k] == BLACK)
				{
					break;
				}
			}
			else if (isWhite == true)
			{
				if (whiteBlack[i][k] == BLACK)
				{
					valid[i][k] = true;
					break;
				}
				else if (whiteBlack[i][k] == WHITE)
				{
					break;
				}
			}
		}
		for (i = ROW_1 - 1, k = COL_1 + 1; i > -1, k < 8; --i, ++k)
		{
			if (chessBoard[i][k] == BLANK)
			{
				valid[i][k] = true;
			}
			else if (isWhite == false)
			{
				if (whiteBlack[i][k] == WHITE)
				{
					valid[i][k] = true;
					break;
				}
				else if (whiteBlack[i][k] == BLACK)
				{
					break;
				}
			}
			else if (isWhite == true)
			{
				if (whiteBlack[i][k] == BLACK)
				{
					valid[i][k] = true;
					break;
				}
				else if (whiteBlack[i][k] == WHITE)
				{
					break;
				}
			}
		}
		for (i = ROW_1 - 1, k = COL_1 - 1; i > -1, k > -1; --i, --k)
		{
			if (chessBoard[i][k] == BLANK)
			{
				valid[i][k] = true;
			}
			else if (isWhite == false)
			{
				if (whiteBlack[i][k] == WHITE)
				{
					valid[i][k] = true;
					break;
				}
				else if (whiteBlack[i][k] == BLACK)
				{
					break;
				}
			}
			else if (isWhite == true)
			{
				if (whiteBlack[i][k] == BLACK)
				{
					valid[i][k] = true;
					break;
				}
				else if (whiteBlack[i][k] == WHITE)
				{
					break;
				}
			}
		}
		for (i = ROW_1 + 1, k = COL_1 - 1; i < 8, k > -1; ++i, --k)
		{
			if (chessBoard[i][k] == BLANK)
			{
				valid[i][k] = true;
			}
			else if (isWhite == false)
			{
				if (whiteBlack[i][k] == WHITE)
				{
					valid[i][k] = true;
					break;
				}
				else if (whiteBlack[i][k] == BLACK)
				{
					break;
				}
			}
			else if (isWhite == true)
			{
				if (whiteBlack[i][k] == BLACK)
				{
					valid[i][k] = true;
					break;
				}
				else if (whiteBlack[i][k] == WHITE)
				{
					break;
				}
			}
		}
		break;
		//queen
	case 5:
		for (i = ROW_1 + 1, j = 0; i < 8; ++i)
		{
			if (chessBoard[i][COL_1] == BLANK)
			{
				valid[i][COL_1] = true;
			}
			else if (isWhite == false)
			{
				if (whiteBlack[i][COL_1] == WHITE)
				{
					valid[i][COL_1] = true;
					break;
				}
				else if (whiteBlack[i][COL_1] == BLACK)
				{
					break;
				}
			}
			else if (isWhite == true)
			{
				if (whiteBlack[i][COL_1] == BLACK)
				{
					valid[i][COL_1] = true;
					break;
				}
				else if (whiteBlack[i][COL_1] == WHITE)
				{
					break;
				}
			}
		}
		for (i = ROW_1 - 1, j = 0; i > -1; --i)
		{
			if (chessBoard[i][COL_1] == BLANK)
			{
				valid[i][COL_1] = true;
			}
			else if (isWhite == false)
			{
				if (whiteBlack[i][COL_1] == WHITE)
				{
					valid[i][COL_1] = true;
					break;
				}
				else if (whiteBlack[i][COL_1] == BLACK)
				{
					break;
				}
			}
			else if (isWhite == true)
			{
				if (whiteBlack[i][COL_1] == BLACK)
				{
					valid[i][COL_1] = true;
					break;
				}
				else if (whiteBlack[i][COL_1] == WHITE)
				{
					break;
				}
			}
		}
		for (i = COL_1 + 1, j = 0; i < 8; ++i)
		{
			if (chessBoard[ROW_1][i] == BLANK)
			{
				valid[ROW_1][i] = true;
			}
			else if (isWhite == false)
			{
				if (whiteBlack[ROW_1][i] == WHITE)
				{
					valid[ROW_1][i] = true;
					break;
				}
				else if (whiteBlack[ROW_1][i] == BLACK)
				{
					break;
				}
			}
			else if (isWhite == true)
			{
				if (whiteBlack[ROW_1][i] == BLACK)
				{
					valid[i][COL_1] = true;
					break;
				}
				else if (whiteBlack[ROW_1][i] == WHITE)
				{
					break;
				}
			}
		}
		for (i = COL_1 - 1, j = 0; i > -1; --i)
		{
			if (chessBoard[ROW_1][i] == BLANK)
			{
				valid[ROW_1][i] = true;
			}
			else if (isWhite == false)
			{
				if (whiteBlack[ROW_1][i] == WHITE)
				{
					valid[ROW_1][i] = true;
					break;
				}
				else if (whiteBlack[i][COL_1] == BLACK)
				{
					break;
				}
			}
			else if (isWhite == true)
			{
				if (whiteBlack[ROW_1][i] == BLACK)
				{
					valid[ROW_1][i] = true;
					break;
				}
				else if (whiteBlack[ROW_1][i] == WHITE)
				{
					break;
				}
			}
		}
		for (i = ROW_1 + 1, k = COL_1 + 1, j = 0; i < 8, k < 8; ++i, ++k)
		{
			if (chessBoard[i][k] == BLANK)
			{
				valid[i][k] = true;
			}
			else if (isWhite == false)
			{
				if (whiteBlack[i][k] == WHITE)
				{
					valid[i][k] = true;
					break;
				}
				else if (whiteBlack[i][k] == BLACK)
				{
					break;
				}
			}
			else if (isWhite == true)
			{
				if (whiteBlack[i][k] == BLACK)
				{
					valid[i][k] = true;
					break;
				}
				else if (whiteBlack[i][k] == WHITE)
				{
					break;
				}
			}
		}
		for (i = ROW_1 - 1, k = COL_1 + 1; i > -1, k < 8; --i, ++k)
		{
			if (chessBoard[i][k] == BLANK)
			{
				valid[i][k] = true;
			}
			else if (isWhite == false)
			{
				if (whiteBlack[i][k] == WHITE)
				{
					valid[i][k] = true;
					break;
				}
				else if (whiteBlack[i][k] == BLACK)
				{
					break;
				}
			}
			else if (isWhite == true)
			{
				if (whiteBlack[i][k] == BLACK)
				{
					valid[i][k] = true;
					break;
				}
				else if (whiteBlack[i][k] == WHITE)
				{
					break;
				}
			}
		}
		for (i = ROW_1 - 1, k = COL_1 - 1; i > -1, k > -1; --i, --k)
		{
			if (chessBoard[i][k] == BLANK)
			{
				valid[i][k] = true;
			}
			else if (isWhite == false)
			{
				if (whiteBlack[i][k] == WHITE)
				{
					valid[i][k] = true;
					break;
				}
				else if (whiteBlack[i][k] == BLACK)
				{
					break;
				}
			}
			else if (isWhite == true)
			{
				if (whiteBlack[i][k] == BLACK)
				{
					valid[i][k] = true;
					break;
				}
				else if (whiteBlack[i][k] == WHITE)
				{
					break;
				}
			}
		}
		for (i = ROW_1 + 1, k = COL_1 - 1; i < 8, k > -1; ++i, --k)
		{
			if (chessBoard[i][k] == BLANK)
			{
				valid[i][k] = true;
			}
			else if (isWhite == false)
			{
				if (whiteBlack[i][k] == WHITE)
				{
					valid[i][k] = true;
					break;
				}
				else if (whiteBlack[i][k] == BLACK)
				{
					break;
				}
			}
			else if (isWhite == true)
			{
				if (whiteBlack[i][k] == BLACK)
				{
					valid[i][k] = true;
					break;
				}
				else if (whiteBlack[i][k] == WHITE)
				{
					break;
				}
			}
		}
		break;
		//king
	case 6:
		//diagional
		if (chessBoard[ROW_1 + 1][COL_1 + 1] == BLANK)
		{
			valid[ROW_1 + 1][COL_1 + 1] = true;
		}
		if (chessBoard[ROW_1 + 1][COL_1 - 1] == BLANK)
		{
			valid[ROW_1 + 1][COL_1 - 1] = true;
		}
		if (chessBoard[ROW_1 - 1][COL_1 + 1] == BLANK)
		{
			valid[ROW_1 - 1][COL_1 + 1] = true;
		}
		if (chessBoard[ROW_1 - 1][COL_1 - 1] == BLANK)
		{
			valid[ROW_1 - 1][COL_1 - 1] = true;
		}
		//verticle
		//up
		if (chessBoard[ROW_1 + 1][COL_1] == BLANK)
		{
			valid[ROW_1 + 1][COL_1] = true;
		}
		//down
		if (chessBoard[ROW_1 - 1][COL_1] == BLANK)
		{
			valid[ROW_1 - 1][COL_1] = true;
		}
		//left
		if (chessBoard[ROW_1][COL_1 - 1] == BLANK)
		{
			valid[ROW_1][COL_1 - 1] = true;
		}
		//right
		if (chessBoard[ROW_1][COL_1 + 1] == BLANK)
		{
			valid[ROW_1][COL_1 + 1] = true;
		}
		break;
		//default case
	default:
		break;
	}
	return;
}