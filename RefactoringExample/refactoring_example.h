#pragma once
#include <iostream>
#include "plays.h"
#include "invoices.h"
#include <format>
#include <exception> 
#include "math.h"
#include "set_precision.h"


PlayData playFor(Plays& plays, Performance& performance) {
    std::string playID = performance.m_playID;
    return plays.m_plays[playID];
}

int amountFor(Plays& plays, Performance aPerformance) {
    PlayData aPlayData = playFor(plays, aPerformance);
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

int volumeCreditsFor(PlayData play, Performance aPerformance) {
    int result = 0;
    result += std::max(aPerformance.m_audience - 30, 0);
    // Add extra credit for every ten comedy attendees
    if (play.m_type == playType::comedy) {
        result += std::floor(aPerformance.m_audience / 5);
    }
    return result;
}

std::string statementLineForSinglePerformance(PlayData play, Performance aPerformance, int amount) {
    return play.m_name + ": $" + floatToDollars(amount / 100) + " " + std::to_string(aPerformance.m_audience) + " seats\n";

}

int totalVolumeCreditsFor(Invoice invoice, Plays plays) {
    int volumeCredits = 0;
    for (Performance performance : invoice.m_performances) {
        PlayData play = playFor(plays, performance);
        volumeCredits += volumeCreditsFor(play, performance);
    }
    return volumeCredits;
}

std::string statement(Invoice invoice, Plays plays) {
    std::string ret = "Statement for " + invoice.m_customer + ":\n";

    int totalAmount = 0;
    for (Performance performance : invoice.m_performances) {
        PlayData play = playFor(plays, performance);
        int thisAmount = amountFor(plays, performance);
        ret += statementLineForSinglePerformance(play, performance, thisAmount);
        totalAmount += thisAmount;
    }
    int volumeCredits = totalVolumeCreditsFor(invoice, plays);

    ret += "Amount owed is $" + floatToDollars(totalAmount / 100) + "\n";
    ret += "You earned " + std::to_string(volumeCredits) + " credits.\n";
    return ret;
}