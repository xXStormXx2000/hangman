#include "hangman.h"
#include <time.h>
#include <iostream>

int main() {
	srand(time(NULL));
	bool play = true;
	while (play) {
		hangman game("words.txt");
		game.play();
		std::cout << "\n\nDo you want to play agen? Y/other\n";
		char c;
		std::cin >> c;
		play = false;
		if (c == 'Y') play = true;
	}
	
}