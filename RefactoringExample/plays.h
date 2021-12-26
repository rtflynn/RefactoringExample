#pragma once
#include <unordered_map>
#include <string>

enum class playType {
	comedy,
	tragedy,
	none
};

struct Play {
	std::string m_name;
	playType m_type;
	Play(std::string name="", playType type=playType::none) : m_name(name), m_type(type) {}
};
Play hamlet("Hamlet", playType::tragedy);
Play aslike("As you like it", playType::comedy);
Play othello("Othello", playType::tragedy);

struct Plays {
	std::unordered_map<std::string, Play> m_plays;
	Plays(std::unordered_map<std::string, Play> plays) : m_plays(plays) {}
};
Plays plays({ {"hamlet", hamlet}, {"as-like", aslike}, {"othello", othello} });