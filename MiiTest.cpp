#include <iostream>
#include <fstream>
#include <wchar.h>
#include "miidata.h"
#include "string.hpp"
#include <string>

void loadMii(FFLStoreData& f, const std::string& s)
{
    std::fstream input;
    input.open(s, std::fstream::in | std::fstream::binary);
    if (!input.is_open())
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    wprintf(L"Size of Mii: %X\n", sizeof(MiiDB));
    wprintf(L"File opened successfully\n");

    input.read(mf.mem, sizeof(FFLStoreData));
    
    wprintf(L"birth_platform: %i\n", mf.md.data.core.birth_platform);
    wprintf(L"name: %s\n", utf16_to_utf8(std::u16string(mf.md.data.core.mii_name)).c_str());
    wprintf(L"creator: %s\n", utf16_to_utf8(std::u16string(mf.md.data.core.creator_name)).c_str());
    
}

void loadDBandWrite(MiiDBFile& f, const std::string& s, const std::string& out)
{
    std::fstream input;
    input.open(s, std::fstream::in | std::fstream::binary);
    FILE* outfile;
    outfile = fopen(out.c_str(), "wb");
    if (!input.is_open())
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    wprintf(L"Size of DB: %zX\n", sizeof(MiiDB));
    wprintf(L"File opened successfully\n");

    input.read(db.mem, sizeof(MiiDatabase));

    wprintf(L"Header: %s\n", db.database.header);
    
    for (const auto& arr : db.database.data) {
        wprintf(L"Mii name: %s\n", utf16_to_utf8(std::u16string(arr.data.core.mii_name)).c_str());
        std::string name(string_format("%s", utf16_to_utf8(std::u16string(arr.data.core.mii_name)).c_str()));
        if(name.compare(string_format("%s", out))) {
            fwrite(&arr.data.core, sizeof(arr.data.core), 1, outfile);
        }
    }
    fclose(outfile);
}

int main()
{
    FFLStoreData mii;
    MiiDBFile data;

    //loadMii(mii, "mii01miiverse01.ffsd");
    loadDBandWrite(data, "FFL_ODB.dat", "Paula");
    //loadMii(mii, "Paula");
}