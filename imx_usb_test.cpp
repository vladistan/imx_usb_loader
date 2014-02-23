#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/JUnitTestOutput.h>

extern "C" {
int end_of_line(char *);
}

TEST_GROUP(FirstTestGroup)
{
};


TEST(FirstTestGroup, FirstTest)
{
   STRCMP_EQUAL("hello", "hello");
   LONGS_EQUAL(1, 1);
   CHECK(true);
}

TEST_GROUP(ParsingTest)
{
};


TEST(ParsingTest,EndOfLineOnEmptyLine)
{
    LONGS_EQUAL(1,end_of_line(""));
};

TEST(ParsingTest,EndOfLineBunchOfSpaces)
{
    LONGS_EQUAL(1,end_of_line("    "));
};

TEST(ParsingTest,EndOfLineBunchOfSpacesAndComment)
{
    LONGS_EQUAL(1,end_of_line("   # Comment"));
};

TEST(ParsingTest,EndOfLineComment)
{
    LONGS_EQUAL(1,end_of_line("# Comment"));
};

TEST(ParsingTest,EndOfLineNewLine)
{
    LONGS_EQUAL(1,end_of_line("\nHello"));
};

TEST(ParsingTest,EndOfLineNewLineAndSpaces)
{
    LONGS_EQUAL(1,end_of_line("  \nHello"));
};



int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
