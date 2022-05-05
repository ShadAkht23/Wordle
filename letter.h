#pragma once

#include <string>
#include <iostream>

enum found {
	DEFAULT, YELLOW, GREEN
};

struct letter {
	letter(char a) {
		val = a;
	}
	bool operator==(const letter& rhs) const {
		return val == rhs.val;
	}
	letter() {}
	char val;
	bool appear = false;
};

struct word {
	word(const std::string& a) {
		for (int i = 0; i < (signed int)a.size(); i++) {
			value[i] = a[i];
		}
	}
	void output() {
		for (const auto& let : value) {
			std::cout << let.val;
		}
		std::cout << "\n";
	}
	std::string toString() const  {
		std::string a = "";
		for (const auto& v : value) {
			a += v.val;
		}
		return a;
	}
	letter value[5];

};