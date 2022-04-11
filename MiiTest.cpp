#include <iostream>
#include <fstream>
#include "miidata.h"

void loadMii(FFLStoreData& f, const std::string& s)
{
    std::fstream input;
    input.open(s, std::fstream::in | std::fstream::binary);
    if (!input.is_open())
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    printf("Size of Mii: %X\n", sizeof(MiiDB));
    printf("File opened successfully\n");

    input.read(mf.mem, sizeof(FFLStoreData));

    printf("birth_platform: %i\n", mf.md.birth_platform);
    printf("name: %s\n", mf.md.mii_name);
    printf("checksum: %u\n", mf.md.checksum);
}

void loadDB(MiiDB& f, const std::string& s)
{
    std::fstream input;
    input.open(s, std::fstream::in | std::fstream::binary);
    if (!input.is_open())
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    printf("Size of DB: %X\n", sizeof(MiiDB));
    printf("File opened successfully\n");

    input.read(db.mem, sizeof(MiiDatabase));

    printf("Header: %s\n", db.database.header);
}

int main()
{
    FFLStoreData mii;
    MiiDB data;

    loadMii(mii, "mii01miiverse01.ffsd");
    
    //loadDB(data, "FFL_ODB.dat");
}