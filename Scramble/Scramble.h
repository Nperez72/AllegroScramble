#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

enum Stage {
	Zero,     // Game not started yet
	First,   // Give small words
	Second, // Give medium words
	Last,  // Give large words
	End   // Game is finished
};

// Interface for game logic in word scramble
class Scramble {
	public:
		// Constructor
		Scramble();

		// Destructor to clean up vectors
		~Scramble();

		// Prompt user with info when game starts
		void game_intro();

		// Load all words from text file and return true if successful
		bool load_words();

		// Begin game and return false when game ends
		bool start_game();

		// Check at which stage the player is at, and give the appropriate problem
		string CheckStage();

		// Take a word and return a scrambled version
		string scramble_word(string word);

		// Displays game stats when game is over (words correct, etc.)
		void end_game();
	private:
		int numCorrect; // Number of words player got correct
		vector<string> smallWords; // Words with length <= Small
		vector<string> mediumWords; // Words with length > Small and <= Medium
		vector<string> largeWords; // Words with length > Medium and <= Large
		Stage stage; // Identifies what words to give player

		// Helper method to choose what word goes into each vector
		void insert_word(string word);
		// Helper method to swap stages based on correct answers
		void swap_stage();
			
		// Iterators to keep track of each word list
		vector<string>::iterator small_word_it = smallWords.begin();
		vector<string>::iterator medium_word_it = mediumWords.begin();
		vector<string>::iterator large_word_it = largeWords.begin();
};

enum Word { // Defined constants for word lengths
	Small = 4,
	Medium = 6,
	Large = 8
};

