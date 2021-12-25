#pragma once
#include <iostream>
#include "plays.h"
#include "invoices.h"
#include <format>
#include <exception> 
#include "math.h"
#include "set_precision.h"
#include "rendering_modes_enum.h"

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

std::string statementLineForSinglePerformance(Plays plays, Performance aPerformance) {
    PlayData play = playFor(plays, aPerformance);
    return play.m_name + ": $" + floatToDollars(amountFor(plays, aPerformance) / 100) + " " + std::to_string(aPerformance.m_audience) + " seats";
}

int totalVolumeCreditsFor(Invoice invoice, Plays plays) {
    int volumeCredits = 0;
    for (Performance performance : invoice.m_performances) {
        PlayData play = playFor(plays, performance);
        volumeCredits += volumeCreditsFor(play, performance);
    }
    return volumeCredits;
}

int totalAmountFor(Invoice invoice, Plays plays) {
    int totalAmount = 0;
    for (Performance performance : invoice.m_performances) {
        PlayData play = playFor(plays, performance);
        int thisAmount = amountFor(plays, performance);
        totalAmount += thisAmount;
    }
    return totalAmount;
}

std::string renderPlainText(Invoice invoice, Plays plays) {
    std::string result = "Statement for " + invoice.m_customer + ":\n";
    for (Performance performance : invoice.m_performances) {
        result += statementLineForSinglePerformance(plays, performance);
        result += "\n";
    }
    /*
    Note, I'm not inlining totalAmount and volumeCredits because the
    signatures of total*For are too large to merit inlining. If we
    were to have invoice or plays or both as global variables or instance
    variables, this would change and this code would become even more succinct.
    At this point, things are clean and separated enough that we can start to
    look into adding HTML-return functionality, or various other types of
    functionality like dynamically adding plays and performances.

    For the HTML side of things, we want an intermediate representation
    that captures all the important info, from which we will populate either
    an HTML template or a non-HTML template.  This separation of concerns will
    allow us to modify the templates independently of the business logic, etc.
    */
    int totalAmount = totalAmountFor(invoice, plays);
    int volumeCredits = totalVolumeCreditsFor(invoice, plays);

    result += "Amount owed is $" + floatToDollars(totalAmount / 100) + "\n";
    result += "You earned " + std::to_string(volumeCredits) + " credits.\n";
    return result;
}

std::string htmlHeader(Invoice invoice) {
    std::string result = "<html>";
    std::string header = "Statement for " + invoice.m_customer;
    result += "<head>" + header + "</head>";
    return result;
}

std::string renderHTML(Invoice invoice, Plays plays) {
    std::string result = htmlHeader(invoice);
    result += "<body>";
    for (Performance performance : invoice.m_performances) {
        result += "<li>";
        result += statementLineForSinglePerformance(plays, performance);
        result += "</li>";
    }
    int totalAmount = totalAmountFor(invoice, plays);
    int volumeCredits = totalVolumeCreditsFor(invoice, plays);
    result += "Total: $" + floatToDollars(totalAmount / 100) + "\n";
    result += "You earned " + std::to_string(volumeCredits) + " credits";
    result += "</body>";
    result += "</html>";
    return result;
}

std::string statement(Invoice invoice, Plays plays,
    RenderingMode mode = RenderingMode::plaintext ) {
    switch (mode) {
    case RenderingMode::plaintext:
        return renderPlainText(invoice, plays);
    case RenderingMode::HTML:
        return renderHTML(invoice, plays);
    default:
        return "Invalid mode\n";
    }
}