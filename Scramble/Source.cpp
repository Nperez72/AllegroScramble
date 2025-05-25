#include <iostream>
#include "Scramble.h"
#include <allegro5/allegro.h>
#include <allegro5/timer.h>

using std::cout;
using std::endl;

struct {
	bool finished = false;
	bool timedOut = false;
} player;

void* input(ALLEGRO_THREAD* thread, void* arg);

int main() {

	if (!al_init()) {
		cout << "Allegro not found" << endl;
	}
	
	Scramble game;

	string word = game.scramble_word("hello");
	cout << "Scrambled word: " << word << endl;

	ALLEGRO_THREAD* thread1 = NULL, * thread2 = NULL;


	return 0;
}
