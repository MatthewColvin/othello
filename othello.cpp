
#include <algorithm> 
#include <cassert>    
#include <cctype>    
#include <iomanip>    
#include <iostream>   
#include <queue>     
#include <cstdio>
#include "colors.h"
#include <string>  
#include <ctime>
#include <cstring>
#include "othello.h" 
#include "game.h"
using namespace std;

namespace main_savitch_14
{
	

	othello::othello()
		: game()
	{
		skip = 0;
		restart();
	}

	game* othello::clone() const
	{
		return new othello(*this);
	}

	void othello::compute_moves(queue<string>& moves) const
	{
		string move = "..";
		for (char i = '1'; i < '9'; i++) {
			for (char c = 'A'; c < 'I'; c++) {
				move[0] = i;
				move[1] = c;
				if (is_legal(move)) {
					moves.push(move);
				}
			}
		}
		if (moves.empty()) { moves.push("****"); }
	}

	void othello::display_status() const
	{
		
		cout << "Othello" << endl<<endl;
		cout << "Last move was:" ;
		if(pre_move == "****"){cout<< "PASS" <<endl;}
		else{cout << pre_move << endl;}

		queue<string> legal_moves;
		compute_moves(legal_moves);
		
		cout << "Your moves are: ";
		if(legal_moves.size()==1 && legal_moves.front()== "****"){cout<< "PASS" ;}
		else{
		while (!legal_moves.empty()) {
			cout << legal_moves.front() << ' ';
			legal_moves.pop();
		}}
		cout << endl;
	
		
		//numbers
		std::cout << "      ";
		for (int g = 1; g < 9; g++) {
			std::cout << g << "    ";
		}
		std::cout << endl;
		//top

		std::cout << "     " ;
		for (int j = 0; j < 13; j++) {
			std::cout << "___";
		}
		std::cout << std::endl;
		//end of top

		//middle
		char cordinate;//used to add letters next to board
		cordinate = 'A';
		for (int i = 0; i < 7; i++, cordinate++) {
			
			std::cout << "    ";
			std::cout << "|";
			for (int j = 0; j < 7; j++) {
				std::cout << "    " << "|";
			}
			std::cout << "    " << "|" << std::endl;
			
	
			std::cout << "  " << cordinate << " ";
			for (int k = 0; k < 8; k++) {
				std::cout << "|" << " " << board[i][k] << " ";
			}
			std::cout << "|" << std::endl;

			std::cout << "    ";
			std::cout << "|";
			for (int j = 0; j < 7; j++) {
				std::cout << "____" << "|";
			}
			std::cout << "____" << "|" << std::endl;

		}

		//last row
		std::cout << "    ";
			std::cout << "|";
			for (int j = 0; j < 7; j++) {
				std::cout << "    " << "|";
			}
			std::cout << "    " << "|" << std::endl;
		std::cout << "  H ";
		for (int i = 0; i < 8; i++) {
			std::cout << "|" << " " << board[7][i] << " ";
		}
		std::cout << "|" << endl;
		std::cout << "    ";
		std::cout << "|";
		for (int j = 0; j < 7; j++) {
			std::cout << "____" << "|";
		}
		std::cout << "____" << "|" << std::endl;
		
		cout<< "Evaluation(negative is good for you): "<< evaluate() << endl;
		
		if(winning()==HUMAN){cout<< "Your winning" << endl ;}
		if(winning()==COMPUTER){cout<< "Computer winning" << endl;}



	}

	int othello::evaluate() const
	{
		int white_score=0, black_score=0;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				
				if (board[i][j].is_black()) { black_score++; }
				if (board[i][j].is_white()) { white_score++; }
				
				if (i == 0) {//edge of board gets another point
					if (board[i][j].is_black()) { black_score++; }
					if (board[i][j].is_white()) { white_score++; }
				}
				if (i == 7) {//edge of board gets another point
					if (board[i][j].is_black()) { black_score++; }
					if (board[i][j].is_white()) { white_score++; }
				}
				if (j == 0) {//edge of board gets another point
					if (board[i][j].is_black()) { black_score++; }
					if (board[i][j].is_white()) { white_score++; }
				}
				if (j == 7) {//edge of board gets another point
					if (board[i][j].is_black()) { black_score++; }
					if (board[i][j].is_white()) { white_score++; }
				}
				// Corners
				if (j == 7 && i== 7) {
					if (board[i][j].is_black()) { black_score += 2; }
					if (board[i][j].is_white()) { white_score += 2; }
				}
				if (j == 7 && i== 0) {
					if (board[i][j].is_black()) { black_score += 2; }
					if (board[i][j].is_white()) { white_score += 2; }
				}
				if (j == 0 && i== 7) {
					if (board[i][j].is_black()) { black_score += 2; }
					if (board[i][j].is_white()) { white_score += 2; }
				}
				if (j == 0 && i== 0) {
					if (board[i][j].is_black()) { black_score += 2; }
					if (board[i][j].is_white()) { white_score += 2; }
				}
				// space next to corner is bad
				if (j == 1 && i== 1) {
					if (board[i][j].is_black()) { black_score -= 2; }
					if (board[i][j].is_white()) { white_score -= 2; }
				}
				if (j == 0 && i== 1) {
					if (board[i][j].is_black()) { black_score -= 2; }
					if (board[i][j].is_white()) { white_score -= 2; }
				}
				if (j == 1 && i== 0) {
					if (board[i][j].is_black()) { black_score -= 2; }
					if (board[i][j].is_white()) { white_score -= 2; }
				}
				//////
				if (j == 0 && i== 6) {
					if (board[i][j].is_black()) { black_score -= 2; }
					if (board[i][j].is_white()) { white_score -= 2; }
				}
				if (j == 1 && i== 7) {
					if (board[i][j].is_black()) { black_score -= 2; }
					if (board[i][j].is_white()) { white_score -= 2; }
				}
				if (j == 1 && i== 6) {
					if (board[i][j].is_black()) { black_score -= 2; }
					if (board[i][j].is_white()) { white_score -= 2; }
				}
				//////
				if (j == 6 && i== 6) {
					if (board[i][j].is_black()) { black_score -= 2; }
					if (board[i][j].is_white()) { white_score -= 2; }
				}
				if (j == 7 && i== 6) {
					if (board[i][j].is_black()) { black_score -= 2; }
					if (board[i][j].is_white()) { white_score -= 2; }
				}
				if (j == 6 && i== 7) {
					if (board[i][j].is_black()) { black_score -= 2; }
					if (board[i][j].is_white()) { white_score -= 2; }
				}
				//////
				if (j == 6 && i== 0) {
					if (board[i][j].is_black()) { black_score -= 2; }
					if (board[i][j].is_white()) { white_score -= 2; }
				}
				if (j == 7 && i== 1) {
					if (board[i][j].is_black()) { black_score -= 2; }
					if (board[i][j].is_white()) { white_score -= 2; }
				}
				if (j == 6 && i== 1) {
					if (board[i][j].is_black()) { black_score -= 2; }
					if (board[i][j].is_white()) { white_score -= 2; }
				}
			}
		}
		return(black_score - white_score); //-(time(NULL)*rand())%30);
	}

	bool othello::is_game_over() const
	{
		// Two simple cases:    
		if (moves_completed() == 0) {
			return false;
		}
		if (moves_completed() == 64) {
			return true;
		}
		if (skip >= 2) {
			return true;
		}
		
		
		return false;
	}

	bool othello::is_legal(const string& move) const
	{

		if (move == "****") { return true; }
		//easy stuff

		if (strlen(move.c_str()) != 2) { return false; }//makes sure move is 2 characters
		if (isalpha(move[0]) && isalpha(move[1])) { return false; } // if they are both letters invalid
		if (isdigit(move[0]) && isdigit(move[1])) { return false; }// if they are both numbers invalid

		int coloum, row; // colums are numbers //rows are letters
						 //row and coloum will represent the actual array indeces
		if (isalpha(move[0])) { row = toupper(move[0]);     row -= 65; }
		if (isdigit(move[0])) { coloum = move[0];          coloum -= 49; }
		if (isalpha(move[1])) { row = toupper(move[1]);     row -= 65; }
		if (isdigit(move[1])) { coloum = move[1];           coloum -= 49; }
		//row and coloum represent the actual array indeces
		
		if (row > 7 || coloum > 7) { return false; }//out of array indeces
		
		if (board[row][coloum].is_white() || board[row][coloum].is_black()) { return false; } // check to see if peice is there already
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//harder moves to tell if legal
		space movetobe;
		if (last_mover() == COMPUTER) {
			movetobe.make_white();
		}
		if (last_mover() == HUMAN) {
			movetobe.make_black();
		}
		
		
		if (row != 0) {//edge of board
			//upper
			if (movetobe.are_oppsite(board[row - 1][coloum])) {
				int i = row - 1;
				space tmp(true, true, true);

				while (tmp.are_oppsite(movetobe)) {
					tmp = board[i][coloum];
					i--;
					if (i < 0 || i > 7 ) { break; }
				}
				if (movetobe.are_same(board[i + 1][coloum])) {
					return true;
				}

			}
		}
		if (row != 7) {//edge
			//lower
			if (movetobe.are_oppsite(board[row + 1][coloum])) {

				int i = row + 1;
				space tmp(true, true, true);

				while (tmp.are_oppsite(movetobe)) {
					tmp = board[i][coloum];
					i++;
					if (i < 0 || i > 7) { break; }
				}
				if (movetobe.are_same(board[i - 1][coloum])) {
					return true;
				}


			}
		}
		if (coloum != 0) {
			//left
			if (movetobe.are_oppsite(board[row][coloum - 1])) {
				int i = coloum - 1;
				space tmp(true, true, true);

				while (tmp.are_oppsite(movetobe)) {
					tmp = board[row][i];
					i--;
					if (i < 0 || i > 7) { break; }
				}
				if (movetobe.are_same(board[row][i + 1])) {
					return true;
				}
			}
		}
		if (coloum != 7) {
			//right
			if (movetobe.are_oppsite(board[row][coloum + 1])) {
				int i = coloum + 1;
				space tmp(true, true, true);

				while (tmp.are_oppsite(movetobe)) {
					tmp = board[row][i];
					i++;
					if (i < 0 || i > 7) { break; }
				}
				if (movetobe.are_same(board[row][i - 1])) {
					return true;
				}

			}
		}

		if (row != 7 && coloum != 7) {
			//bottom right 
			if (movetobe.are_oppsite(board[row + 1][coloum + 1])) {
				int i = coloum + 1;
				int j = row + 1;
				space tmp(true, true, true);

				while (tmp.are_oppsite(movetobe)) {
					tmp = board[j][i];
					i++;
					j++;
					if (i < 0 || i > 7 || j < 0 || j > 7 ) { break; }
				}
				if (movetobe.are_same(board[j - 1][i - 1])) {
					return true;
				}

			}
		}
		if (row != 0 && coloum != 0) {
			//upper left not done
			if (movetobe.are_oppsite(board[row - 1][coloum - 1])) {
				int i = coloum - 1;
				int j = row - 1;
				space tmp(true, true, true);

				while (tmp.are_oppsite(movetobe)) {
					tmp = board[j][i];
					i--;
					j--;
					if (i < 0 || i > 7 || j < 0 || j > 7) { break; }
				}
				if (movetobe.are_same(board[j + 1][i + 1])) {
					return true;
				}
			}
		}

		if (row != 0 && coloum != 7) {
			// upper right not done
			if (movetobe.are_oppsite(board[row - 1][coloum + 1])) {
				int i = coloum + 1;
				int j = row - 1;
				space tmp(true, true, true);

				while (tmp.are_oppsite(movetobe)) {
					tmp = board[j][i];
					i++;
					j--;
					if (i < 0 || i > 7 || j < 0 || j > 7) { break; }
				}
				if (movetobe.are_same(board[j + 1][i - 1])) {
					return true;
				}
			}
		}

		if (row != 7 && coloum != 0) {
			//bottom left not done
			if (movetobe.are_oppsite(board[row + 1][coloum - 1])) {
				int i = coloum - 1;
				int j = row + 1;
				space tmp(true, true, true);

				while (tmp.are_oppsite(movetobe)) {
					tmp = board[j][i];
					i--;
					j++;
					if (i < 0 || i > 7 || j < 0 || j > 7) { break; }
				}
				if (movetobe.are_same(board[j - 1][i + 1])) {
					return true;
				}
			}
		}

		return false;
	}

	void othello::make_move(const string& move)
	{
		pre_move = move;
		if (move == "****") {
			skip++;
			game::make_move(" ");
			return;
		}
		int coloum, row; // colums are numbers //rows are letters
		//row and coloum will represent the actual array indeces
		if (isalpha(move[0])) { row = toupper(move[0]);     row -= 65;}
		if (isdigit(move[0])) { coloum = move[0];          coloum -= 49;}
		if (isalpha(move[1])) { row = toupper(move[1]);     row -= 65;}
		if (isdigit(move[1])) { coloum = move[1];           coloum -= 49;}
		//row and coloum represent the actual array indeces
		if (last_mover() == COMPUTER) {
			board[row][coloum].make_white();
		}
		if (last_mover() == HUMAN) {
			board[row][coloum].make_black();
		}
		//must flip all peices in between 
		
		// subtraction from row moves up board
		// subtraction from coloum moves the left
		
		if (row != 0){
		//upper
			if (board[row][coloum].are_oppsite(board[row - 1][coloum])) {
				int i = row - 1;
				space tmp(true, true, true);

				while (tmp.are_oppsite(board[row][coloum])) {
					tmp = board[i][coloum];
					i--;
					if (i < 0 || i > 7) { break; }
				}
				if (board[row][coloum].are_same(board[i + 1][coloum])) {
					while (i < row - 2) {
						board[i + 2][coloum].flip();
						i++;
					}
				}
			}
			
		}

		if (row != 7) {
		//lower
			if (board[row][coloum].are_oppsite(board[row + 1][coloum])) {

				int i = row + 1;
				space tmp(true, true, true);

				while (tmp.are_oppsite(board[row][coloum])) {
					tmp = board[i][coloum];
					i++;
					if (i < 0 || i > 7) { break; }
				}
				if (board[row][coloum].are_same(board[i - 1][coloum])) {
					while (i > row + 2) {
						board[i - 2][coloum].flip();
						i--;
					}
				}
			}

			
		}

		if (coloum != 0) {
		//left
			if (board[row][coloum].are_oppsite(board[row][coloum - 1])) {
				int i = coloum - 1;
				space tmp(true, true, true);

				while (tmp.are_oppsite(board[row][coloum])) {
					tmp = board[row][i];
					i--;
					if (i < 0 || i > 7) { break; }
				}
				if (board[row][coloum].are_same(board[row][i + 1])) {
					while (i < coloum - 2) {
						board[row][i + 2].flip();
						i++;
					}
				}
			}
		}

		if (coloum != 7) {
		//right
			if (board[row][coloum].are_oppsite(board[row][coloum + 1])) {
				int i = coloum + 1;
				space tmp(true, true, true);

				while (tmp.are_oppsite(board[row][coloum])) {
					tmp = board[row][i];
					i++;
					if (i < 0 || i > 7 ) { break; }
				}
				if (board[row][coloum].are_same(board[row][i - 1])) {
					while (i > coloum + 2) {
						board[row][i - 2].flip();
						i--;
					}
				}
			}
		}
		if (row != 7 && coloum != 7) {
		//bottom right not done
			if (board[row][coloum].are_oppsite(board[row + 1][coloum + 1])) {
				int i = coloum + 1;
				int j = row + 1;
				space tmp(true, true, true);

				while (tmp.are_oppsite(board[row][coloum])) {
					tmp = board[j][i];
					i++;
					j++;
					if (i < 0 || i > 7 || j < 0 || j > 7) { break; }
				}
				if (board[row][coloum].are_same(board[j - 1][i - 1])) {
					while (i > coloum + 2) {
						board[j - 2][i - 2].flip();
						i--;
						j--;
					}
				}
			}

		}

		if (row != 0 && coloum != 0){
		//upper left not done
			if (board[row][coloum].are_oppsite(board[row - 1][coloum - 1])) {
				int i = coloum - 1;
				int j = row - 1;
				space tmp(true, true, true);

				while (tmp.are_oppsite(board[row][coloum])) {
					tmp = board[j][i];
					i--;
					j--;
					if (i < 0 || i > 7 || j < 0 || j > 7) { break; }
				}
				if (board[row][coloum].are_same(board[j + 1][i + 1])) {
					while (i < coloum - 2) {
						board[j + 2][i + 2].flip();
						i++;
						j++;
					}
				}
			}
		}

		if (row != 0 && coloum != 7) {
		// upper right not done
			if (board[row][coloum].are_oppsite(board[row - 1][coloum + 1])) {
				int i = coloum + 1;
				int j = row - 1;
				space tmp(true, true, true);

				while (tmp.are_oppsite(board[row][coloum])) {
					tmp = board[j][i];
					i++;
					j--;
					if (i < 0 || i > 7 || j < 0 || j > 7) { break; }
				}
				if (board[row][coloum].are_same(board[j + 1][i - 1])) {
					while (i > coloum + 2) {
						board[j + 2][i - 2].flip();
						i--;
						j++;
					}
				}
			}
		}

		if (row != 7 && coloum != 0) {
		//bottom left not done
			if (board[row][coloum].are_oppsite(board[row + 1][coloum - 1])) {
				int i = coloum - 1;
				int j = row + 1;
				space tmp(true, true, true);

				while (tmp.are_oppsite(board[row][coloum])) {
					tmp = board[j][i];
					i--;
					j++;
					if (i < 0 || i > 7 || j < 0 || j > 7) { break; }
				}
				if (board[row][coloum].are_same(board[j - 1][i + 1])) {
					while (i < coloum - 2) {
						board[j - 2][i + 2].flip();
						i++;
						j--;
					}
				}
			}
		}
		
		
		queue<string> moves;
		compute_moves(moves);
		if (moves.front()=="pass" && moves.size()==1) {//no moves but to pass
			skip++;
		}
		
		game::make_move(" ");
		skip = 0;
	}

	void othello::restart()
	{
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				board[i][j].make_neutral();
			}
		}
		board[3][4].make_black();
		board[3][3].make_white();
		board[4][3].make_black();
		board[4][4].make_white();



	}

	othello::who othello::winning() const
	{
		int blackcount=0;
		int whitecount=0;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j].is_white()) { whitecount++; }
				if (board[i][j].is_black()) { blackcount++; }
			}
		}
		
		if (blackcount > whitecount) { return COMPUTER; }
		if (blackcount < whitecount) { return HUMAN;  }
		if (blackcount == whitecount) { return NEUTRAL; }
		

	}
	string othello::get_user_move() const
	{
		queue<string> moves;
		compute_moves(moves);
		if(moves.size()== 1 && moves.front() == "****"){
		cout<<"NO MOVES"<<endl;
		return moves.front();
		}
		
		string answer;

		display_message("Your move, please: ");
		getline(cin, answer);
		return answer;
	}

	
}
