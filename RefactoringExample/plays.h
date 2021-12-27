#pragma once
#include <unordered_map>
#include <string>

enum class playType {
	comedy,
	tragedy,
	none
};

class Play {
public:
	std::string m_name;
	playType m_type;
	Play(std::string name="", playType type=playType::none) : m_name(name), m_type(type) {}

	virtual int amountFor(int audience) = 0;
	virtual int volumeCreditsFor(int audience) = 0;
};

class Comedy : public Play {
public:
	Comedy(std::string name = "") : Play(name, playType::comedy) {
	}
	int amountFor(int audience) override { return -1; }
	int volumeCreditsFor(int audience) override { return -1; }
};

class Tragedy : public Play {
public:
	Tragedy(std::string name="") : Play(name, playType::tragedy) {}
	int amountFor(int audience) override { return -1; }
	int volumeCreditsFor(int audience) override { return -1; }
};

Tragedy hamlet("Hamlet");
Comedy aslike("As you like it");
Tragedy othello("Othello");

struct Plays {
	std::unordered_map<std::string, Play*> m_plays;
	Plays(std::unordered_map<std::string, Play*> plays) : m_plays(plays) {}
};
Plays plays({ {"hamlet", &hamlet}, {"as-like", &aslike}, {"othello", &othello} });