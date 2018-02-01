#include <iostream>
#include "othello.h"

using namespace main_savitch_14;
using namespace std;
	int main() {
		int count = 0;
		othello game;
		string move;
		game.display_status();
		for (int i = 0; i < 10; i++) {
			
			cin >> move;

			game.make_move(move);

			game.display_status();
		}



		int i;
		std::cin >> i;
		return 0;
	}



