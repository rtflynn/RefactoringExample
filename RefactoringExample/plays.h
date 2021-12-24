#pragma once
#include <unordered_map>
#include <string>

enum class playType {
	comedy,
	tragedy,
	none
};

struct PlayData {
	std::string m_name;
	playType m_type;
	PlayData(std::string name="", playType type=playType::none) : m_name(name), m_type(type) {}
};
PlayData hamlet("Hamlet", playType::tragedy);
PlayData aslike("As you like it", playType::comedy);
PlayData othello("Othello", playType::tragedy);

struct Plays {
	std::unordered_map<std::string, PlayData> m_plays;
	Plays(std::unordered_map<std::string, PlayData> plays) : m_plays(plays) {}
};
Plays plays({ {"hamlet", hamlet}, {"as-like", aslike}, {"othello", othello} });