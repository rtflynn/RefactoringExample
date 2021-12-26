#pragma once

#include "invoices.h"
#include "plays.h"


Play playFor(Performance& performance) {
	std::string playID = performance.m_playID;
	return plays.m_plays[playID];
}

class EnrichedPerformance {
	std::string m_playID;
	int m_audience;
	Play play;

	EnrichedPerformance(Performance performance) {
		m_playID = performance.m_playID;
		m_audience = performance.m_audience;
		play = playFor(performance);
	}
};