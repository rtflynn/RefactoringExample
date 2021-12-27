#pragma once

#include <unordered_map>
#include <vector>
#include <string>

struct Performance {
	std::string m_playID;
	int m_audience;
	Performance(std::string playID, int audience) : m_playID(playID), m_audience(audience) {}
};

struct Invoice {
	std::string m_customer;
	std::vector<Performance> m_performances;
	Invoice(std::string customer, std::vector<Performance> performances) :
		m_customer(customer), m_performances(performances) {}
};

Performance first("hamlet", 55);
Performance second("as-like", 35);
Performance third("othello", 40);

std::vector<Performance> performances = { first, second, third };
Invoice example("BigCo", performances);