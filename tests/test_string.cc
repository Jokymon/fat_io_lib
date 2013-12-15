#include "CppUTest/TestHarness.h"
extern "C"
{
    #include "fat_string.h"
}

TEST_GROUP(fat_string)
{

};

TEST(fat_string, TotalPathLevelsRegular)
{
    CHECK_EQUAL(1, fatfs_total_path_levels("c:\\folder\\file.zip"))
    CHECK_EQUAL(2, fatfs_total_path_levels("/dev/etc/samba.conf"))
}

TEST(fat_string, TotalPathLevelsError)
{
    CHECK_EQUAL(-1, fatfs_total_path_levels(0))
    // no relativ paths supported
    CHECK_EQUAL(-1, fatfs_total_path_levels("src/include/stdio.h"))
}

TEST(fat_string, TotalPathLevelsUnexpected)
{
    // I'm not sure these results are as expected

    CHECK_EQUAL(1, fatfs_total_path_levels("/home/user/"))
}

