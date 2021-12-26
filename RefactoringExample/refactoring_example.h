#pragma once
#include <iostream>
#include "plays.h"
#include "invoices.h"
#include <format>
#include <exception> 
#include "math.h"
#include "set_precision.h"
#include "rendering_modes_enum.h"
#include "StatementData.h"
#include "enriched_performance.h"


std::string statementLineForSinglePerformance(EnrichedPerformance enriched) {
    return enriched.play.m_name + ": $" + floatToDollars(enriched.amount / 100) + " " + std::to_string(enriched.m_audience) + " seats";
}

int totalVolumeCreditsFor(StatementData data) {
    int volumeCredits = 0;
    for (Performance performance : data.performances) {
        EnrichedPerformance enriched = EnrichedPerformance(performance);
        volumeCredits += enriched.volumeCredits;
    }
    return volumeCredits;
}

int totalAmountFor(StatementData data) {
    int totalAmount = 0;
    for (Performance performance : data.performances) {
        EnrichedPerformance enriched = EnrichedPerformance(performance);
        totalAmount += enriched.amount;
    }
    return totalAmount;
}

std::string renderPlainText(StatementData data) {
    std::string result = "Statement for " + data.customer + ":\n";
    for (Performance performance : data.performances) {
        result += statementLineForSinglePerformance(performance);
        result += "\n";
    }
    int totalAmount = totalAmountFor(data);
    int volumeCredits = totalVolumeCreditsFor(data);
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

std::string renderHTML(StatementData statementData) {
    std::string result = htmlHeader(statementData);
    result += "<body>";
    for (Performance performance : statementData.performances) {
        result += "<li>";
        result += statementLineForSinglePerformance(performance);
        result += "</li>";
    }
    int totalAmount = totalAmountFor(statementData);
    int volumeCredits = totalVolumeCreditsFor(statementData);
    result += "Amount owed is $" + floatToDollars(totalAmount / 100) + "\n";
    result += "You earned " + std::to_string(volumeCredits) + " credits";
    result += "</body>";
    result += "</html>";
    return result;
}


StatementData statementDataFromInvoice(Invoice invoice) {
    StatementData statementData;
    statementData.customer = invoice.m_customer;
    for (Performance perf : invoice.m_performances) {
        statementData.performances.push_back(perf);
    }
    return statementData;
}

std::string statement(Invoice invoice,
 RenderingMode mode = RenderingMode::plaintext ) {
    StatementData statementData = statementDataFromInvoice(invoice);
    switch (mode) {
    case RenderingMode::plaintext:
        return renderPlainText(statementData);
    case RenderingMode::HTML:
        return renderHTML(statementData);
    default:
        return "Invalid mode\n";
    }
}