#include "Scramble.h"
#include <fstream>

using std::ifstream;

// Implementation for Scramble game logic

Scramble::Scramble() {

}

Scramble::~Scramble() {

}

void Scramble::game_intro() {

}

bool Scramble::load_words() {
	ifstream words("dictionary.txt");
	string word;

	if (!words.is_open()) {
		return false;
	}

	while (getline (words, word)) {
		insert_word(word);
	}
	return true;
}

bool Scramble::start_game() {
	return false;
}

string Scramble::scramble_word(string word) {
	char temp;
	int randIndex;
	// Randomly shuffle the letters in the word
	for (int i = 0; i < word.length(); i++) {
		randIndex = rand() % word.length(); // Choose random letter in word
		temp = word[i];
		word[i] = word[randIndex]; // Swap letters
		word[randIndex] = temp;
	}
	return word;
}

void Scramble::end_game() {

}

void Scramble::insert_word(string word) {
	if (word.length() <= Small) {
		smallWords.push_back(word);
		return;
	}
	if (word.length() > Small && word.length() <= Medium) {
		mediumWords.push_back(word);
		return;
	}
	if (word.length() >= Large){
		largeWords.push_back(word);
	}
}
