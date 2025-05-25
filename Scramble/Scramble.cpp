#include "Scramble.h"
#include <fstream>

using std::ifstream;

// Implementation for Scramble game logic

Scramble::Scramble() :  stage(Zero), numCorrect(0){
	// Initliaze unassigned values
}

Scramble::~Scramble() {

}

void Scramble::game_intro() {
	cout << "Welcome to the Scrameble Game!\nYou must scramble five words to win the game!\n";
	cout << "The more words you get correct, the harder it gets!\n Good luck.\n";
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
	words.close();
	return true;
}

bool Scramble::start_game() {
	bool started = false;
	if (stage == Zero) { // Start first level 
		swap_stage();
		started = true;
	}
	else if (stage == End) {
		started = false;
	}
	else
		// Game is in primary three stages
		started = true;
	return started;
}

void Scramble::swap_stage()
{
	if (numCorrect < 2) {
		stage = First;
	}
	else if (numCorrect >= 2 && numCorrect < 4) {
		stage = Second;
	}
	else if (numCorrect == 4) {
		stage = Last;
	}
	else if (numCorrect >= 5) {
		stage = End;
		end_game();
	}

}

string Scramble::CheckStage()
{
	swap_stage();
	// Get a word from the appropiate iterator, tick it, and pass word to player
	if (stage == First) {
		string current = *small_word_it;
		small_word_it++;
		return current;
	}
	else if (stage == Second) {
		string current = *medium_word_it;
		medium_word_it++;
		return current;
	}
	else if (stage == Last) {
		string current = *large_word_it;
		large_word_it++;
		return current;
	}
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

