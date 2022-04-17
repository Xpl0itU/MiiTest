#include <iostream>
#include <fstream>
#include <wchar.h>
#include "miidata.h"
#include <string>
using namespace std;

/*
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
    
    wprintf(L"birth_platform: %i\n", mf.md.birth_platform);
    wprintf(L"name: %s\n", mf.md.mii_name);
    wprintf(L"creator: %s\n", mf.md.creator_name);
    printf("checksum: %u\n", mf.md.checksum);
    
}
*/

void loadDB(MiiDBFile& f, const std::string& s)
{
    std::fstream input;
    input.open(s, std::fstream::in | std::fstream::binary);
    if (!input.is_open())
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    printf("Size of DB: %zX\n", sizeof(MiiDB));
    printf("File opened successfully\n");

    input.read(db.mem, sizeof(MiiDatabase));

    printf("Header: %s\n", db.database.header);
    for (const auto& arr : db.database.data) {
        wprintf(L"Mii name: %s\n", &arr.data.core.mii_name);
    }
}

int main()
{
    //FFLStoreData mii;
    MiiDBFile data;

    //loadMii(mii, "mii01miiverse01.ffsd");
    //loadMii(mii, "mii.ffsd");
    
    loadDB(data, "FFL_ODB.dat");
}