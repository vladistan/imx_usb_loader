#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/JUnitTestOutput.h>
#include <stdio.h>

extern "C" {
int end_of_line(char *);
int get_file_size(FILE *);
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

TEST_GROUP(FileRoutines)
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

TEST(ParsingTest,EndOfLineCRAndSpaces)
{
    LONGS_EQUAL(1,end_of_line("  \rHello"));
};

TEST(ParsingTest,EndOfLineNegative)
{
    LONGS_EQUAL(0, end_of_line("Hello  \rHello"));
};


TEST(FileRoutines,FileSize)
{
    FILE * f = fopen("test_data/bFile.test","rb");
    LONGS_EQUAL(45451, get_file_size(f));
};



int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
