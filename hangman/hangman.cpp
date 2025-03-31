#include "hangman.h"

hangman::hangman(std::string file_path)
{
	word_list = import_words(file_path);
}

void hangman::play()
{
	std::system("cls");
	int word_to_play = rand()% word_list.size();
	word = word_list[word_to_play];
	char_list = std::string(word.size(), '_');
	misses = 0;
	guesses = "";
	char game_stat = 'c';
	while (game_stat == 'c')
	{
		draw_hangman();
		draw_word();
		std::string guess = get_input();
		guesses += guess;
		guesses += ' ';
		misses += uppdate_char_list(guess);
		game_stat = win_lose_continue();
		std::system("cls");
		if (game_stat == 'w') {
			draw_win();
			return;
		}
		if (game_stat == 'l') {
			draw_lose();
			return;
		}
	}
}

std::vector<std::string> hangman::import_words(std::string path)
{
	std::vector<std::string> word_list;
	std::fstream file(path);
	std::string word;
	while (file >> word) word_list.push_back(word);
	file.close();
	return word_list;
}

std::string hangman::get_input()
{
	std::string out = "";
	int state = 1;
	std::cout << "Guess a letter/word:\n";
	while (state) {
		if (state == 2) std::cout << "Your input contains invalid characters, try again:\n";
		if (state == 3) std::cout << "You have already guessed that, try again:\n";
		std::cin >> out;
		state = 0;
		for (char& c : out) {
			if(c < 'a') c += 'a' - 'A';
			if ('a' > c || c > 'z') {
				state = 2;
				break;
			}
		}
		for (int i = 0; i < guesses.size(); i++) {
			int j = 0;
			for (; i + j < guesses.size() && j < out.size(); j++) {
				if(out[j] != guesses[i + j]) break;
			}
			if (j == out.size() && (i + j == guesses.size() || guesses[i + j] == ' ')) {
				state = 3;
				break;
			}
			for (; i < guesses.size() && guesses[i] != ' '; i++);
		}
	}
	return out;
}

void hangman::draw_hangman()
{
	std::cout << " +------+       \n";
	std::cout << " |      |       \n";
	std::string hangman_ = 
		" |      O       \n"
		" |     /|\\     \n"
		" |     / \\     \n";
	int mask[] = { 8, 25, 24, 26, 40, 42 };
	for (int i = 5; i >= misses; i--) {
		hangman_[mask[i]] = ' ';
	}
	std::cout << hangman_;
	std::cout << " |              \n";
	std::cout << "/ \\            \n";
	std::cout << "----------------\n";
	std::cout << "\n";
}

void hangman::draw_word()
{
	std::cout << "Word: " << char_list << '\n';
	std::cout << "Guesses: " << guesses << "\n\n";
}

char hangman::win_lose_continue()
{
	if (misses == 6) return 'l';
	for (char c : char_list) if (c == '_') return 'c';
 	return 'w';
}

bool hangman::uppdate_char_list(std::string str)
{
	bool mis = true;
	if (str.size() == 1) {
		char c = str[0];
		for (int i = 0; i < word.size(); i++) {
			if (word[i] != c) continue;
			char_list[i] = c;
			mis = false;
		}
	} else {
		if (str != word) return true;
		char_list = word;
		mis = false;
	}
	return mis;
}

void hangman::draw_win()
{
	
	std::cout << '\n';
	std::cout << "\t#################\n";
	std::cout << "\t##   You win   ##\n";
	std::cout << "\t#################\n\n";
	draw_word();
}

void hangman::draw_lose()
{
	draw_hangman();
	std::cout << "\t##################\n";
	std::cout << "\t##   You lose   ##\n";
	std::cout << "\t##################\n";
	std::cout << "\n\t" << word << '\n';
}
