#pragma once
#include <string>
#include "plays.h"
#include <vector>
#include "enriched_performance.h"

class StatementData {
public:
    std::string customer;
    std::vector<EnrichedPerformance> performances;
    int totalAmount;
    int totalVolumeCredits;
    StatementData(Invoice invoice) {
        customer = invoice.m_customer;
        totalAmount = 0;
        totalVolumeCredits = 0;
        for (Performance perf : invoice.m_performances) {
            EnrichedPerformance enriched = EnrichedPerformance(perf);
            performances.push_back(enriched);
            totalAmount += enriched.m_amount;
            totalVolumeCredits += enriched.m_volumeCredits;
        }
    }
};