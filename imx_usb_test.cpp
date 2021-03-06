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

TEST_GROUP(ConfFileName)
{
};

TEST_GROUP(ParseImxConf)
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

TEST(ConfFileName, BasicTest) {
    const char * rv = conf_file_name("imx_usb.conf",0,NULL);
    STRCMP_EQUAL( "./imx_usb.conf", rv );
}

TEST(ParseImxConf, BasicTest){
    struct mach_id * list = parse_imx_conf("imx_usb.conf",0,NULL);

    struct mach_id * l1 = list;
    LONGS_EQUAL(list[0].vid, 0x066f );
    LONGS_EQUAL(list[0].pid, 0x3780 );

    l1 = list->next;
    LONGS_EQUAL(l1[0].vid, 0x15a2 );
    LONGS_EQUAL(l1[0].pid, 0x004f );


}

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
