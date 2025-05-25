#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/timer.h>

using std::cout, std::endl;

struct {
	bool finished = false;
	bool timedOut = false;
} player;

void* input(ALLEGRO_THREAD* thread, void* arg);

int main() {

	if (!al_init()) {
		cout << "Allegro not found" << endl;
	}

	ALLEGRO_THREAD* thread1 = NULL, * thread2 = NULL;


	return 0;
}
