#pragma once

#include "invoices.h"
#include "plays.h"


Play playFor(Performance& performance) {
	std::string playID = performance.m_playID;
	return plays.m_plays[playID];
}

class EnrichedPerformance;

/*
If we decide to add more plays, the extra logic (as currently written)
will have to go into this performance code.  This is super non-ideal.
What we want is for plays to know how to compute their own volume credits
and cost for a performance.  

We should have a Play base class which is abstract, with a playType field
(which we may end up not needing, since we're going to replace switch statements
with polymorphism).  We should have a volumeCreditsFor and amountFor type of
calculation.
*/


int volumeCreditsFor(Performance performance) {
    int result = 0;
    result += std::max(performance.m_audience - 30, 0);
    // Add extra credit for every ten comedy attendees
    Play play = playFor(performance);
    if (play.m_type == playType::comedy) {
        result += std::floor(performance.m_audience / 5);
    }
    return result;
}

int amountFor(Performance aPerformance) {
    int result = 0;
    Play aPlayData = playFor(aPerformance);
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
		amount = amountFor(performance);
        volumeCredits = volumeCreditsFor(performance);
	}
};