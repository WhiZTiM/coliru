#include <iostream>
#include <future>
#include <chrono>

using namespace std::chrono_literals;

/*
 * Demande de licence, fonction bloquante.
 */
int response()
{
    std::this_thread::sleep_for(3s);

    /*
     * Ici plein de fonction qui bloque et utilise des fonctions reseau totalement bloquante.
     */

	return 123;
}

int main()
{
    /*
     * Attente de reponse pendant 5 secondes maxi.
     */
	std::future<int> f = std::async(std::launch::async, response);
	int elapsed = 0;
	bool done = false;

	while (!done) {
		std::cout << "Tentative de réception... :-o\n";

        std::future_status s = f.wait_for(1s);

		if (s == std::future_status::ready) {
			done = true;
		} else {
			elapsed += 1;
			done = elapsed > 5;
		}
	}

	if (elapsed > 5) {
		std::cout << "Pas eu le temps de recevoir...\n";
	} else {
		std::cout << "Réponse reçue! -> " << f.get() << "\n";
	}
	
	return 0;
}