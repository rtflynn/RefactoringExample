#pragma once
#include <string>
#include "plays.h"
#include <vector>
#include "enriched_performance.h"

class StatementData {
public:
	std::string customer;
	std::vector<EnrichedPerformance> performances;
};