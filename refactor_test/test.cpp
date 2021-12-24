#include "pch.h"
#include "../RefactoringExample/refactoring_example.h"


TEST(RefactoringTest, OutputsCorrectString) {
	std::string actual = statement(example, plays);
	std::string expected = "Statement for BigCo:\nHamlet: 650.00 55 seats\nAs you like it: 580.00 35 seats\nOthello: 500.00 40 seats\nAmount owed is 1730.00\nYou earned 47 credits.\n";
  EXPECT_EQ(expected, actual);
}