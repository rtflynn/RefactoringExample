#pragma once
#include <iostream>
#include "plays.h"
#include "invoice.h"
#include <format>
#include <exception> 
#include "math.h"
#include "set_precision.h"
#include "rendering_modes_enum.h"
#include "StatementData.h"
#include "enriched_performance.h"


std::string statementLineForSinglePerformance(EnrichedPerformance enriched) {
    return enriched.m_play->m_name + ": $" + floatToDollars(enriched.m_amount / 100) +
        " " + std::to_string(enriched.m_audience) + " seats";
}

std::string renderPlainText(StatementData data) {
    std::string result = "Statement for " + data.customer + ":\n";
    for (EnrichedPerformance performance : data.performances) {
        result += statementLineForSinglePerformance(performance);
        result += "\n";
    }
    int totalAmount = data.totalAmount;
    int volumeCredits = data.totalVolumeCredits;
    result += "Amount owed is $" + floatToDollars(totalAmount / 100) + "\n";
    result += "You earned " + std::to_string(volumeCredits) + " credits.\n";
    return result;
}

std::string htmlHeader(StatementData data) {
    std::string result = "<html>";
    std::string header = "Statement for " + data.customer;
    result += "<head>" + header + "</head>";
    return result;
}

std::string renderHTML(StatementData data) {
    std::string result = htmlHeader(data);
    result += "<body>";
    for (EnrichedPerformance performance : data.performances) {
        result += "<li>";
        result += statementLineForSinglePerformance(performance);
        result += "</li>";
    }
    result += "Amount owed is $" + floatToDollars(data.totalAmount / 100) + "\n";
    result += "You earned " + std::to_string(data.totalVolumeCredits) + " credits";
    result += "</body>";
    result += "</html>";
    return result;
}

std::string statement(Invoice invoice,
 RenderingMode mode = RenderingMode::plaintext ) {
    StatementData statementData = StatementData(invoice);
    switch (mode) {
    case RenderingMode::plaintext:
        return renderPlainText(statementData);
    case RenderingMode::HTML:
        return renderHTML(statementData);
    default:
        return "Invalid mode\n";
    }
}