#include "Scramble.h"
#include <allegro5/allegro.h>
#include <allegro5/timer.h>
#include <allegro5/threads.h>

// Keeps track of player status
struct {
	bool finished = false;
	bool timedOut = false;
	const double timerLimit = 10.0;
} player;

// Game instance
Scramble game;

// Function pointers for each threador
void* input(ALLEGRO_THREAD* thread, void* arg);
void* timer_thread(ALLEGRO_THREAD* thread, void* arg);

int main() {

	if (!al_init()) {
		cout << "Allegro not found" << endl;
		return -1;
	}
	
	if (!game.load_words()) {
		cout << "Failed to load words!" << endl;
		return -1;
	}

	/*
	* Allegro has functionality for managing a thread and managing a timer.
	* Input and timer will run on separate threads since they are separate tasks
	* that should be done in parallel.
	*/

	ALLEGRO_THREAD* inputThread = al_create_thread(input, nullptr);
	if (!inputThread) {
		cout << "Failed to create input thread" << endl;
		return -1;
	}
	ALLEGRO_THREAD* timerThread = al_create_thread(timer_thread, nullptr);
	if (!timerThread) {
		cout << "Failed to create timer thread" << endl;
	}

	// Begin game loop and other threads
	game.start_game();
	al_start_thread(inputThread);
	al_start_thread(timerThread);

	// Yield to the other threads in a regular interval (CPU efficient)
	while (!player.finished && !player.timedOut) {
		al_rest(0.1);
	}

	if (player.timedOut) {
		cout << "\nTime's up!" << endl;
		game.end_game();
	}

	// Clean up threads
	al_destroy_thread(timerThread);
	al_destroy_thread(inputThread);
	

	return 0;
}

/*
* User has 60 seconds to scramble a total of five words.
* User will only receive a new word if they solve current word.
* They must re-answer until they get current word correct.
* Loop exits when user is timed out
*/
void* input(ALLEGRO_THREAD* thread, void* arg) {
	player.finished = false;

	while (!player.timedOut && !player.finished) {
		std::string match = game.check_stage();
		std::string scramble = game.scramble_word(match);
		cout << "Unscramble the word: " << scramble << ". You have 60 seconds.\n";
		std::string answer;

		while (!player.timedOut) {
			std::cin >> answer;
			if (answer == match) {
				cout << "Great job!\n";
				game.score_point();
				break; // Get a new word
			}
			else {
				cout << "Nope. Wrong answer. Try again:\n";
				game.wrong_counter();
			}
		}
	}

	return nullptr;
}

/*
*  Run the timer on a seprate thread so that timer does not need tick
*  after each time user answers. Allows time to run out correctly if player
*  remians idle.
*/
void* timer_thread(ALLEGRO_THREAD* thread, void* arg) {
	ALLEGRO_TIMER* timer = al_create_timer(player.timerLimit);
	al_start_timer(timer);

	// Wait for the timer to tick once (after 60 seconds)
	double start = al_get_time();
	while (al_get_time() - start < player.timerLimit && !player.finished) {
		al_rest(0.1);
	}
	// If timer ticks, and player is not finished, a timeout is issued
	if (!player.finished) {
		player.timedOut = true;
	}

	al_destroy_timer(timer);

	return nullptr;
}
