#pragma once

#include "invoices.h"
#include "plays.h"


Play* playFor(Performance& performance) {
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

Thinking on this again, it's the PlayType, not the specific play, that should
matter for this.  So we'll extend Play via this axis.
*/


int volumeCreditsFor(Performance performance) {
    Play* play = playFor(performance);
    int result = play->volumeCreditsFor(performance.m_audience);
    return result;
}

int amountFor(Performance aPerformance) {
    int result = 0;
    Play* aPlayData = playFor(aPerformance);
    result = aPlayData->amountFor(aPerformance.m_audience);
    return result;
}

class EnrichedPerformance {
public:
	std::string m_playID;
	int m_audience;
	Play* play;
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