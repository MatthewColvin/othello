#include <iostream>
#include "game.h"
#include "othello.h"
using namespace std;
using namespace main_savitch_14;
int main() {
	othello instance;
	othello::who winner;
	
	winner = instance.play();
	switch (winner) {
		case othello::HUMAN:       cout << " !!!! YOU WIN !!!!" << endl; break;
		case othello::COMPUTER:    cout << " I WIN" << endl; break;
		case othello::NEUTRAL:     cout << "Draw Play again?" << endl; break;
	}
	int i;
	cin >> i >> i;
	return 0;
}
