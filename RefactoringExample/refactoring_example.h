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


int amountFor(Plays& plays, Performance aPerformance) {
    Play aPlayData = playFor(plays, aPerformance);
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

int volumeCreditsFor(Play play, Performance aPerformance) {
    int result = 0;
    result += std::max(aPerformance.m_audience - 30, 0);
    // Add extra credit for every ten comedy attendees
    if (play.m_type == playType::comedy) {
        result += std::floor(aPerformance.m_audience / 5);
    }
    return result;
}

std::string statementLineForSinglePerformance(Plays plays, Performance aPerformance) {
    Play play = playFor(plays, aPerformance);
    return play.m_name + ": $" + floatToDollars(amountFor(plays, aPerformance) / 100) + " " + std::to_string(aPerformance.m_audience) + " seats";
}

int totalVolumeCreditsFor(Plays plays, StatementData data) {
    int volumeCredits = 0;
    for (Performance performance : data.performances) {
        Play play = playFor(plays, performance);
        volumeCredits += volumeCreditsFor(play, performance);
    }
    return volumeCredits;
}

int totalAmountFor(Plays plays, StatementData data) {
    int totalAmount = 0;
    for (Performance performance : data.performances) {
        Play play = playFor(plays, performance);
        int thisAmount = amountFor(plays, performance);
        totalAmount += thisAmount;
    }
    return totalAmount;
}

std::string renderPlainText(Invoice invoice, Plays plays, StatementData data) {
    std::string result = "Statement for " + invoice.m_customer + ":\n";
    for (Performance performance : invoice.m_performances) {
        result += statementLineForSinglePerformance(plays, performance);
        result += "\n";
    }

    int totalAmount = totalAmountFor(plays, data);
    int volumeCredits = totalVolumeCreditsFor(plays, data);

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

std::string renderHTML(Plays plays, StatementData statementData) {
    std::string result = htmlHeader(statementData);
    result += "<body>";
    for (Performance performance : statementData.performances) {
        result += "<li>";
        result += statementLineForSinglePerformance(plays, performance);
        result += "</li>";
    }
    int totalAmount = totalAmountFor(plays, statementData);
    int volumeCredits = totalVolumeCreditsFor(plays, statementData);
    result += "Amount owed is $" + floatToDollars(totalAmount / 100) + "\n";
    result += "You earned " + std::to_string(volumeCredits) + " credits";
    result += "</body>";
    result += "</html>";
    return result;
}


StatementData statementDataFromInvoice(Invoice invoice) {
    StatementData statementData;
    statementData.customer = invoice.m_customer;
    statementData.performances = invoice.m_performances;
    return statementData;
}

std::string statement(Invoice invoice, Plays plays,
    RenderingMode mode = RenderingMode::plaintext ) {
    StatementData statementData = statementDataFromInvoice(invoice);

    switch (mode) {
    case RenderingMode::plaintext:
        return renderPlainText(invoice, plays, statementData);
    case RenderingMode::HTML:
        return renderHTML(plays, statementData);
    default:
        return "Invalid mode\n";
    }
}