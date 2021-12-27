#include "pch.h"
#include "../RefactoringExample/refactoring_example.h"

TEST(RefactoringTest, OutputsCorrectString) {
	std::string actual = statement(example, RenderingMode::plaintext);
	const char* expected_raw_text = 
		"Statement for BigCo:\nHamlet: $650.00 55 seats\nAs you like it: "
		"$580.00 35 seats\nOthello: $500.00 40 seats\nAmount owed is "
		"$1730.00\nYou earned 47 credits.\n";
	std::string expected = std::string(expected_raw_text);
  EXPECT_EQ(expected, actual);
}

TEST(RefactoringTest, OutputCorrectHTMLString) {
	std::string actual = statement(example, RenderingMode::HTML);
	const char* expected_html_test =
		"<html>"
		"<head>"
		"Statement for BigCo"
		"</head>"
		"<body>"
		"<li>Hamlet: $650.00 55 seats</li>"
		"<li>As you like it: $580.00 35 seats</li>"
		"<li>Othello: $500.00 40 seats</li>"
		"Amount owed is $1730.00\nYou earned 47 credits"
		"</body>"
		"</html>";
	std::string expected = std::string(expected_html_test);
	EXPECT_EQ(expected, actual);
}

TEST(RefactoringTest, ChildrensPlayPerformance) {
	std::string actual = statement(barneyTestInvoice, RenderingMode::plaintext);
	const char* expected_chars = 
		"Statement for BarneyTest:\nBarney On Ice: $300.00 60 seats\n"
		"Amount owed is $300.00\nYou earned 60 credits.\n";
	std::string expected(expected_chars);
	EXPECT_EQ(expected, actual);

}