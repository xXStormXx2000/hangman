#include "hangman.h"
#include <time.h>
#include <iostream>
#include <locale>

int main() {
	srand(time(NULL));
	std::locale::global(std::locale("en_US.UTF-8"));
	std::wcout.imbue(std::locale());
	std::wcin.imbue(std::locale());

	bool play = true;
	while (play) {
		hangman game(L"words.txt");
		game.play();
		std::wcout << L"\n\nDo you want to play agen? Y/other\n";
		wchar_t c;
		std::wcin >> c;
		play = false;
		if (c == 'Y') play = true;
	}
	
}