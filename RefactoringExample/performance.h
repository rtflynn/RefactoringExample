#pragma once

#include <string>

struct Performance {
	std::string m_playID;
	int m_audience;
	Performance(std::string playID, int audience) : m_playID(playID), m_audience(audience) {}
};