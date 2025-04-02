#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

class hangman {
	std::vector<std::wstring> word_list;
	std::wstring word = L"";
	std::wstring char_list = L"";
	std::wstring guesses = L"";
	int misses = 0;

	std::vector<std::wstring> import_words(std::wstring);
	std::wstring get_input();
	void draw_hangman();
	void draw_word();
	char win_lose_continue();
	bool uppdate_char_list(std::wstring); 

	void draw_win();
	void draw_lose();

public:
	hangman(std::wstring);
	void play();
};