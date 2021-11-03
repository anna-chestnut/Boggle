// Engineering Coding Test Example Driver.
// Copyright Bungie Inc. 2021.

// ---------- includes

#include "boggle.h"

#include <algorithm>	// find_if()
#include <iostream>		// cout
#include <conio.h>		// _getch();

// ---------- driver code

void boggle_driver()
{
	c_boggle my_boggle;

	// Setup the dictionary.
	const std::vector<std::string> g_dictionary = {
		// These words SHOULD be in the solution to the example board:
		"abed", "abo", "aby", "aero", "aery", "bad", "bade", "bead", "bed", "boa", "bore", "bored", "box", "boy", "bread",
		"bred", "bro", "broad", "byre", "byroad", "dab", "deb", "derby", "dev", "oba", "obe", "orb", "orbed", "orby",
		"ore", "oread", "read", "reb", "red", "rev", "road", "rob", "robe", "robed", "verb", "very", "yob", "yore",

		// These words should NOT be in the solution to the example board:
		"robbed", "robber", "board", "dove",
	};
	my_boggle.set_legal_words(g_dictionary);

	// First board to solve; the example from instructions document.
	const std::vector<std::string> result = my_boggle.solve_board(3, 3, std::string("yoxrbaved"));

	std::cout << "Result:\n " << std::endl;

	for (auto v : result) {
		std::cout << v << ", " << std::endl;
	}

	// Make sure that the results include the first 43 words from our basic dictionary, but nothing else...
	if (result.size() != 43 ||
		std::find_if(
			g_dictionary.begin(),
			g_dictionary.begin() + 43,
			[result](std::string word) { return std::find(result.begin(), result.end(), word) == result.end(); })
		!= g_dictionary.begin() + 43)
	{
		std::cout << "BOGGLE: Wrong solution to 'example from instructions document'." << std::endl;
	}
	else
	{
		std::cout << "BOGGLE: Correct solution to 'example from instructions document'." << std::endl;
	}

	// More boards to solve here... ?
}

int main()
{
	// Coding Test questions -- test harnesses
	boggle_driver();

	// Wait for input to terminate.
	std::cout << std::endl << "Press any key to quit." << std::endl;
	_getch();

	return 0;
}
