#pragma once

#include "performance.h"
#include "plays.h"

class EnrichedPerformance;

// We need the play associated with a performance in order to
// construct various instance variables of EnrichedPerformance.
Play* playFor(Performance& performance) {
	std::string playID = performance.m_playID;
	return plays.m_plays[playID];
}

class EnrichedPerformance {
public:
	std::string m_playID;
	int m_audience;
	Play* m_play;
	int m_amount;
    int m_volumeCredits;

	EnrichedPerformance(Performance performance) {
		m_playID = performance.m_playID;
		m_audience = performance.m_audience;
		m_play = playFor(performance);
		m_amount = m_play->amountFor(m_audience);
        m_volumeCredits = m_play->volumeCreditsFor(m_audience);
	}
};