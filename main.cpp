#define OLC_PGE_APPLICATION
#include "color.hpp"

#include <string>
#include <fstream>
#include <array>
#include <algorithm>
#include "letter.h"

void checkWord(word & secret, word& guess, std::array<found, 5>& line) {
	// reset appearences in both words
	for (auto& g : guess.value) g.appear = false;
	for (auto& s : secret.value) s.appear = false;
	
	// check for greens:
	for (int guessIndex = 0; guessIndex < 5; guessIndex++) {
		for (int secretIndex = 0; secretIndex < 5; secretIndex++) {

			if (guess.value[guessIndex] == secret.value[secretIndex] 
				&& !guess.value[guessIndex].appear && !secret.value[secretIndex].appear) {
				if (guessIndex == secretIndex) line[guessIndex] = GREEN;
				else line[guessIndex] = YELLOW;

				guess.value[guessIndex].appear = true;
				secret.value[secretIndex].appear = true;
			}
		}
	}

}

void printWord(const word& guess, const std::array<found, 5>& line)
{
	for (int i = 0; i < 5; i++) {
		switch (line[i]) {
		case DEFAULT:
			std::cout << hue::bright_white << guess.value[i].val << hue::reset;
			break;
		case YELLOW:
			std::cout << hue::bright_white_on_yellow << guess.value[i].val << hue::reset;
			break;
		case GREEN:
			std::cout << hue::bright_white_on_green << guess.value[i].val << hue::reset;
			break;
		}

	}
	std::cout << "\n";

}

bool sortChar(const char& a, const char& b) {
	return int(b) > int(a);
}

bool pred(const std::string& a, const std::string& b) {
	for (int i = 0; i < 5; i++) {
		if (a[i] == b[i]) continue;
		if (sortChar(a[i], b[i]))
			return true;
		else return false;
	}
	return false;
}

// these 2 functions have been checked
bool isValid(std::array<std::string, 12972>& validGuesses, const word& gues) {
	std::string guess = gues.toString(); // i think this doesnt work
	return isValid(validGuesses, guess);
}

bool isValid(std::array<std::string,12972>& validGuesses, const std::string guess) { // this doesnt work because valid is no longer sorted.
	auto it = std::find(validGuesses.begin(), validGuesses.end(), guess);
	if (it != validGuesses.end()) return true;
	//if (std::binary_search(validGuesses.begin(), validGuesses.end(), guess, pred)) {
	//	return true;
	//}
	return false;
}

int main()
{
	std::array<std::string, 317> answers;
	std::array<std::string, 12972> validGuesses;
	std::ifstream valid("valid.txt");
	std::string temp;
	int i = 0;
	while (std::getline(valid, temp)) {
		validGuesses[i] = temp;
		i++;
	}
	std::ifstream wordle("wordle.txt");
	i = 0;
	while (std::getline(wordle, temp)) {
		answers[i] = temp;
		i++;
	}
	srand(static_cast<unsigned int>(time(NULL)));
	word secret = word(answers[rand() % 317]);
	//std::cout << secret.toString() << std::endl;
	
	//checkWord(secret, guess, output);
	//printWord(guess, output);
	std::array<found, 5> output = { DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT };
	std::cout << "wordle! enter a word\n";
	bool found = false;
	int numGuesses = 0;
	while (!found) {
		output = { DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT };
		
		// get input
		std::string input;
		std::cin >> input;
		if (!isValid(validGuesses,input)) {
			std::cout << "ivalid word. Try again\n";
			continue;
		}
		word guess = word(input);
		checkWord(secret, guess, output);
		bool win = true;
		for (auto& a : output) {
			if (a != GREEN) {
				win = false;
			}
		}
		numGuesses += 1;
		if (win) {
			printWord(guess, output);
			std::cout << "YOU WIN IN " << numGuesses << std::endl;
			found = true;
			std::cout << "press any key to exit...";
			std::cin.get();
			std::cin.get();
			continue;
		}
		printWord(guess, output);
	}
	return 0;
}
