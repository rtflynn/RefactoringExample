#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include "performance.h"

struct Invoice {
	std::string m_customer;
	std::vector<Performance> m_performances;
	Invoice(std::string customer, std::vector<Performance> performances) :
		m_customer(customer), m_performances(performances) {}
};

Performance first("hamlet", 55);
Performance second("as-like", 35);
Performance third("othello", 40);
Performance fourth("barney", 60);

std::vector<Performance> performances = { first, second, third };
Invoice example("BigCo", performances);

std::vector<Performance> barneyPerformances = { fourth };
Invoice barneyTestInvoice("BarneyTest", barneyPerformances);