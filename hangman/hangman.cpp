#include "hangman.h"

hangman::hangman(std::wstring file_path)
{
	word_list = import_words(file_path);
}

void hangman::play()
{
	std::system("cls");
	int word_to_play = rand()% word_list.size();
	word = word_list[word_to_play];
	char_list = std::wstring(word.size(), '_');
	misses = 0;
	guesses = L"";
	char game_stat = 'c';
	while (game_stat == 'c')
	{
		draw_hangman();
		draw_word();
		std::wstring guess = get_input();
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

std::vector<std::wstring> hangman::import_words(std::wstring path)
{
	std::vector<std::wstring> word_list;
	std::wfstream file(path);
	std::wstring word;
	while (file >> word) word_list.push_back(word);
	file.close();
	return word_list;
}

std::wstring hangman::get_input()
{
	std::wstring out = L"";
	int state = 1;
	std::wcout << L"Guess a letter/word:\n";
	while (state) {
		if (state == 2) std::wcout << L"Your input contains invalid characters, try again:\n";
		if (state == 3) std::wcout << L"You have already guessed that, try again:\n";
		std::wcin >> out;
		state = 0;
		for (wchar_t& c : out) {
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
	std::wcout << L" +------+       \n";
	std::wcout << L" |      |       \n";
	std::wstring hangman_ = 
		L" |      O       \n"
		L" |     /|\\     \n"
		L" |     / \\     \n";
	int mask[] = { 8, 25, 24, 26, 40, 42 };
	for (int i = 5; i >= misses; i--) {
		hangman_[mask[i]] = ' ';
	}
	std::wcout << hangman_;
	std::wcout << L" |              \n";
	std::wcout << L"/ \\            \n";
	std::wcout << L"----------------\n";
	std::wcout << L"\n";
}

void hangman::draw_word()
{
	std::wcout << L"Word: " << char_list << '\n';
	std::wcout << L"Guesses: " << guesses << L"\n\n";
}

char hangman::win_lose_continue()
{
	if (misses == 6) return 'l';
	for (char c : char_list) if (c == '_') return 'c';
 	return 'w';
}

bool hangman::uppdate_char_list(std::wstring str)
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
	
	std::wcout << '\n';
	std::wcout << L"\t#################\n";
	std::wcout << L"\t##   You win   ##\n";
	std::wcout << L"\t#################\n\n";
	draw_word();
}

void hangman::draw_lose()
{
	draw_hangman();
	std::wcout << L"\t##################\n";
	std::wcout << L"\t##   You lose   ##\n";
	std::wcout << L"\t##################\n";
	std::wcout << L"\n\t" << word << '\n';
}
