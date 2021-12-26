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

int totalAmountFor(StatementData data) {
    int totalAmount = 0;
    for (EnrichedPerformance performance : data.performances) {
        totalAmount += performance.amount;
    }
    return totalAmount;
}

int totalVolumeCreditsFor(StatementData data) {
    int volumeCredits = 0;
    for (EnrichedPerformance performance : data.performances) {
        volumeCredits += performance.volumeCredits;
    }
    return volumeCredits;
}

StatementData statementDataFromInvoice(Invoice invoice) {
    StatementData statementData;
    statementData.customer = invoice.m_customer;
    for (Performance perf : invoice.m_performances) {
        EnrichedPerformance enriched = EnrichedPerformance(perf);
        statementData.performances.push_back(enriched);
    }
    return statementData;
}