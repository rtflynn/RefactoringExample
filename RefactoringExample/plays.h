#pragma once
#include <unordered_map>
#include <string>


class Play {
public:
	std::string m_name;
	Play(std::string name="") : m_name(name) {}

	virtual int amountFor(int audience) = 0;
	virtual int volumeCreditsFor(int audience) { 
		return std::max(audience - 30, 0);
	};
};

class Comedy : public Play {
public:
	Comedy(std::string name = "") : Play(name) {
	}
	int amountFor(int audience) override {
		int result = 30000;
		if (audience > 20) {
			result += 10000 + 500 * (audience - 20);
		}
		result += 300 * audience;
		return result;
	}
	int volumeCreditsFor(int audience) { 
		int result =  Play::volumeCreditsFor(audience);
		// Add extra credit for every ten comedy attendees
		result += std::floor(audience / 5);
		return result;
	}
};

class Tragedy : public Play {
public:
	Tragedy(std::string name="") : Play(name) {}
	int amountFor(int audience) override { 
		int result = 40000;
		if (audience > 30) { result += 1000 * (audience - 30); }
		return result;
	}
};

Tragedy hamlet("Hamlet");
Comedy aslike("As you like it");
Tragedy othello("Othello");

struct Plays {
	std::unordered_map<std::string, Play*> m_plays;
	Plays(std::unordered_map<std::string, Play*> plays) : m_plays(plays) {}
};
Plays plays({ {"hamlet", &hamlet}, {"as-like", &aslike}, {"othello", &othello} });