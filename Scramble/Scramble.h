#include <string>
#include <iostream>
#include <vector>

using std::string, std::vector;


// Interface for game logic in word scramble
class Scramble {
	public:
		// Construtor
		Scramble();

		// Destructor to clean up vectors
		~Scramble();

		// Prompt user with info when game starts
		void game_intro();

		// Load all words from text file and return true if succesful
		bool load_words();

		// Begin game and return true if player wins
		bool start_game();

		// Take a word and return a scrambled version
		string scramble_word(string word);

		// Displays game stats when game is over (words correct, etc.)
		void end_game();
	private:
		int numCorrect; // Number of words player got correct
		enum Word { // Defined constants for word lengths
			Small = 4,
			Medium = 6,
			Large = 8
		};
		vector<string> smallWords; // Words with length <= Word.Small
		vector<string> mediumWords; // Words with length > Word.Small and <= Word.Medium
		vector<string> largeWords; // Words with length > Word.Medium and <= Word.Large
};
