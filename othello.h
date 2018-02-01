
#ifndef MAIN_SAVITCH_CONNECT4
#define MAIN_SAVITCH_CONNECT4
#include <queue>    
#include <string>   
#include "game.h" 
#include "space.h"

namespace main_savitch_14
{
	class othello : public game
	{
	public:
		static const int ROWS = 8;
		static const int COLUMNS = 8;
		othello();

	protected:
		virtual game* clone() const;
		virtual void compute_moves(std::queue<std::string>& moves) const;
		virtual void display_status() const;
		virtual int evaluate() const;
		virtual bool is_game_over() const;
		virtual bool is_legal(const std::string& move) const;
		virtual void make_move(const std::string& move);
		virtual void restart();
		virtual who winning()const;
		virtual std::string get_user_move()const;
		
	private:
		std::string pre_move;
		space board[8][8];
		int skip;
		
		// board[rows][coloums] very important
	};
}

#endif
