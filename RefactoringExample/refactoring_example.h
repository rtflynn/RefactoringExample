#pragma once
#include <iostream>
#include "plays.h"
#include "invoices.h"
#include <format>
#include <exception> 
#include "math.h""
#include "set_precision.h"

int amountFor(PlayData aPlayData, Performance aPerformance) {
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

std::string statement(Invoice invoice, Plays plays) {
    int totalAmount = 0;
    int volumeCredits = 0;
    std::string ret = "Statement for " + invoice.m_customer + ":\n";
    // Some formatting stuff here.  Don't think I really need it.
    for (Performance performance : invoice.m_performances) {
        PlayData play = plays.m_plays[performance.m_playID];
        int thisAmount = amountFor(play, performance);
        // Add volume credits
        volumeCredits += std::max(performance.m_audience - 30, 0);
        // Add extra credit for every ten comedy attendees
        if (play.m_type == playType::comedy) {
            volumeCredits += std::floor(performance.m_audience / 5);
        }
        // print line for this order
        ret += play.m_name + ": " + floatToDollars(thisAmount / 100) + " " + std::to_string(performance.m_audience) + " seats\n";
        totalAmount += thisAmount;
    }

    ret += "Amount owed is " + floatToDollars(totalAmount / 100) + "\n";
    ret += "You earned " + std::to_string(volumeCredits) + " credits.\n";
    return ret;
}