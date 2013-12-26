#include "CppUTest/TestHarness.h"
#include "string.h"
extern "C"
{
    #include "fat_access.h"
    #include "fat_misc.h"
}

static uint8_t _disk[1024];
int media_read(uint32 sector, uint8 *buffer, uint32 sector_count)
{
    memcpy(buffer, &_disk[512*sector], 512*sector_count);
    return 1;
}

int media_write(uint32 sector, uint8 *buffer, uint32 sector_count)
{
    // Not yet needed in the tests
    return 0;
}

TEST_GROUP(fat_access)
{
    struct fatfs fs;

    void setup_valid_partition()
    {
        SET_16BIT_WORD(_disk, BPB_BYTSPERSEC, FAT_SECTOR_SIZE);
        _disk[BPB_SECPERCLUS] = 4;
        SET_16BIT_WORD(_disk, BPB_RSVDSECCNT, 1);
        _disk[BPB_NUMFATS] = 1;
        SET_16BIT_WORD(_disk, BPB_ROOTENTCNT, 32);
        SET_16BIT_WORD(_disk, BPB_TOTSEC16, 18000); // right amount for a FAT16
        SET_16BIT_WORD(_disk, BPB_FATSZ16, 8);
        _disk[SIGNATURE_POSITION] = 0x55;
        _disk[SIGNATURE_POSITION+1] = 0xAA;
    }

    TEST_SETUP()
    {
        fs.disk_io.read_media = media_read;
        fs.disk_io.write_media = media_write;
        setup_valid_partition();
    }
};

TEST(fat_access, NormalInitFAT16)
{
    int result = fatfs_init(&fs);
    CHECK_EQUAL(4, fs.sectors_per_cluster);
    CHECK_EQUAL(FAT_INIT_OK, result);
    CHECK_EQUAL(FAT_TYPE_16, fs.fat_type);
}

TEST(fat_access, NotSupportedFAT12)
{
    SET_16BIT_WORD(_disk, BPB_TOTSEC16, 2000);

    int result = fatfs_init(&fs);

    CHECK_EQUAL(FAT_INIT_WRONG_FILESYS_TYPE, result);
}

TEST(fat_access, SectorsPerClusterZero)
{
    _disk[BPB_SECPERCLUS] = 0;

    int result = fatfs_init(&fs);

    CHECK_EQUAL(FAT_INIT_WRONG_FILESYS_TYPE, result);
}
