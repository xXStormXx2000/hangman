#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

class hangman {
	std::vector<std::string> word_list;
	std::string word = "";
	std::string char_list = "";
	std::string guesses = "";
	int misses = 0;

	std::vector<std::string> import_words(std::string);
	std::string get_input();
	void draw_hangman();
	void draw_word();
	char win_lose_continue();
	bool uppdate_char_list(std::string); 

	void draw_win();
	void draw_lose();

public:
	hangman(std::string);
	void play();
};