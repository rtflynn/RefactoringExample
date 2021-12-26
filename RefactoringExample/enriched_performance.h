#pragma once

#include "invoices.h"
#include "plays.h"


Play playFor(Performance& performance) {
	std::string playID = performance.m_playID;
	return plays.m_plays[playID];
}

class EnrichedPerformance;

int volumeCreditsFor(Play play, Performance enriched) {
    int result = 0;
    result += std::max(enriched.m_audience - 30, 0);
    // Add extra credit for every ten comedy attendees
    if (play.m_type == playType::comedy) {
        result += std::floor(enriched.m_audience / 5);
    }
    return result;
}

int amountFor(Play aPlayData, Performance aPerformance) {
    int result = 0;
    switch (aPlayData.m_type) {
    case playType::tragedy:
        result = 40000;
        if (aPerformance.m_audience > 30) {
            result += 1000 * (aPerformance.m_audience - 30);
        }
        break;
    case playType::comedy:
        result = 30000;
        if (aPerformance.m_audience > 20) {
            result += 10000 + 500 * (aPerformance.m_audience - 20);
        }
        result += 300 * aPerformance.m_audience;
        break;
    default:
        throw std::invalid_argument("Unsupported playType.\n");
    }
    return result;
}

class EnrichedPerformance {
public:
	std::string m_playID;
	int m_audience;
	Play play;
	int amount;
    int volumeCredits;

	EnrichedPerformance(Performance performance) {
		m_playID = performance.m_playID;
		m_audience = performance.m_audience;
		play = playFor(performance);
		amount = amountFor(play, performance);
        volumeCredits = volumeCreditsFor(play, performance);
	}
};