#include "CppUTest/TestHarness.h"
extern "C"
{
    #include "fat_misc.h"
    #include "fat_defs.h"
}

TEST_GROUP(fat_misc)
{

};

TEST(fat_misc, IsFileEntry)
{
    struct fat_dir_entry entry;
    entry.Attr = FILE_HEADER_BLANK;

    CHECK_EQUAL(1, fatfs_entry_is_file(&entry));
    CHECK_EQUAL(0, fatfs_entry_is_dir(&entry));
}

TEST(fat_misc, IsDirectoryEntry)
{
    struct fat_dir_entry entry;
    entry.Attr = FILE_ATTR_DIRECTORY;

    CHECK_EQUAL(0, fatfs_entry_is_file(&entry));
    CHECK_EQUAL(1, fatfs_entry_is_dir(&entry));
}
