#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/JUnitTestOutput.h>
#include <stdio.h>
#include "imx_usb.h"


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

TEST_GROUP(ImxDevice)
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


TEST(ImxDevice,WorksCorrectlyWhenNothingPassed)
{
    LONGS_EQUAL(NULL, imx_device(0x15a2,0x004e,NULL));
}


TEST(ImxDevice,ShouldReturnNullWhenDeviceIsNotInTheList)
{
    struct mach_id tst[] =  {
	 { &tst[1], 1, 1, "Hello" },
	 { &tst[2], 1, 1, "imx6" },
	 { NULL, 1, 1, "imx5" },
       };
	
    POINTERS_EQUAL(NULL, imx_device(0x15a2,0x004e,tst));
}

TEST(ImxDevice,ShouldReturnDeviceWhenItIsInTheList)
{
    struct mach_id tst[] =  {
	 { &tst[1], 0x15a2, 1, "Hello" },
	 { &tst[2], 0x15a2, 0x004e, "imx6" },
	 { NULL, 1, 1, "imx5" },
       };
	
    POINTERS_EQUAL(&tst[1], imx_device(0x15a2,0x004e,tst));
}


int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
