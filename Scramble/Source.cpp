#include "Scramble.h"
#include <allegro5/allegro.h>
#include <allegro5/timer.h>
#include <allegro5/threads.h>


struct {
	bool finished = false;
	bool timedOut = false;
} player;

void* input(ALLEGRO_THREAD* thread, void* arg);
void* timer_thread(ALLEGRO_THREAD* thread, void* arg);

int main() {

	if (!al_init()) {
		cout << "Allegro not found" << endl;
		return -1;
	}
	
	Scramble game;
	if (!game.load_words()) {
		cout << "Failed to load words!" << endl;
		return -1;
	}

	/*
	* Allegro has functionality for managing a thread and managing a timer.
	* Input and timer will run on separate threads since they are separate tasks
	* that should be done in parallel.
	*/

	ALLEGRO_TIMER* timer = al_create_timer(60.0);

	ALLEGRO_THREAD* inputThread = al_create_thread(input, nullptr);
	if (!inputThread) {
		cout << "Failed to create input thread" << endl;
		return -1;
	}
	ALLEGRO_THREAD* timerThread = al_create_thread(timer_thread, nullptr);
	if (!timerThread) {
		cout << "Failed to create timer thread" << endl;
	}

	al_start_thread(inputThread);
	al_start_thread(timerThread);

	while (!player.finished && !player.timedOut) {
		al_rest(0.1);
	}

	if (player.timedOut) {
		cout << "\nTime's up!" << endl;
	}
	else if (player.finished) {
		cout << "\nYou finished before time ran out!" << endl;
	}
	


	return 0;
}

void* input(ALLEGRO_THREAD* thread, void* arg) {
	player.finished = false;
	cout << "Unscramble the word. You have 60 seconds.\n";
	string answer;
	std::cin >> answer;
	player.finished = true;

	return nullptr;
}

void* timer_thread(ALLEGRO_THREAD* thread, void* arg) {
	ALLEGRO_TIMER* timer = al_create_timer(60.0);
	al_start_timer(timer);

	// Wait for the timer to tick once (after 60 seconds)
	double start = al_get_time();
	while (al_get_time() - start < 60.0 && !player.finished) {
		al_rest(0.1);
	}
	// If timer ticks, and player is not finished, a timeout is issued
	if (!player.finished) {
		player.timedOut = true;
	}

	al_destroy_timer(timer);

	return nullptr;
}
