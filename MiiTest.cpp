#include <iostream>
#include <fstream>
#include <wchar.h>
#include "miidata.h"
#include "string.hpp"
#include <string>
using namespace std;

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
    
    wprintf(L"birth_platform: %i\n", mf.md.data.core.birth_platform);
    wprintf(L"name: %s\n", mf.md.data.core.mii_name);
    wprintf(L"creator: %s\n", mf.md.data.core.creator_name);
    
}

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

void loadDBandWrite(MiiDBFile& f, const std::string& s, const std::string& out)
{
    std::fstream input;
    std::ofstream outputf;
    input.open(s, std::fstream::in | std::fstream::binary);
    FILE* outfile;
    outfile = fopen(out.c_str(), "w");
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
        string name(string_format("%s", &arr.data.core.mii_name));
        if(name.compare(string_format("%s", out))) {
            fwrite(&arr.data.core, sizeof(arr.data.core), 1, outfile);
            fclose(outfile);
        }
    }
}

int main()
{
    FFLStoreData mii;
    MiiDBFile data;

    //loadMii(mii, "mii01miiverse01.ffsd");
    loadDBandWrite(data, "FFL_ODB.dat", "Paula");
    loadMii(mii, "Paula");
}