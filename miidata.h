#pragma once
#include <array>
#include <cstdint>
#include <vector>
#include "wut_structsize.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1)

	typedef enum FFLCreateIDFlags {
		FFL_CREATE_ID_FLAG_WII_U = 0x1 | 0x4,
		FFL_CREATE_ID_FLAG_TEMPORARY = 0x2,
		FFL_CREATE_ID_FLAG_NORMAL = 0x8,
	} FFLCreateIDFlags;

	typedef struct FFLCreateID {
		FFLCreateIDFlags flags : 4;

		uint32_t timestamp : 28;

		uint8_t deviceHash[6];
	} FFLCreateID;

	//Note: the endian may be wrong here
	typedef struct FFLiMiiDataCore
	{
		uint8_t birth_platform : 4;
		uint8_t unk_0x00_b4 : 4;

		// 0x01
		uint8_t unk_0x01_b0 : 4;
		uint8_t unk_0x01_b4 : 4;

		// 0x02
		uint8_t font_region : 4;
		uint8_t region_move : 2;
		uint8_t unk_0x02_b6 : 1;
		uint8_t copyable : 1;

		// 0x03
		uint8_t mii_version;

		// 0x4
		uint64_t author_id;

		// 0xC
		FFLCreateID mii_id;

		// 0x16
		uint16_t unk_0x16;

		// 0x18
		uint16_t unk_0x18_b0 : 1;
		uint16_t unk_0x18_b1 : 1;
		uint16_t color : 4;
		uint16_t birth_day : 5;
		uint16_t birth_month : 4;
		uint16_t gender : 1;

		// 0x1A
		uint16_t mii_name[10];

		// 0x2E
		uint8_t size;

		// 0x2F
		uint8_t fatness;

		// 0x30
		uint8_t blush_type : 4;
		uint8_t face_style : 4;

		// 0x31
		uint8_t face_color : 3;
		uint8_t face_type : 4;
		uint8_t local_only : 1;

		// 0x32
		uint8_t hair_mirrored : 5;
		uint8_t hair_color : 3;

		// 0x33
		uint8_t hair_type;

		// 0x34
		uint32_t eye_thickness : 3;
		uint32_t eye_scale : 4;
		uint32_t eye_color : 3;
		uint32_t eye_type : 6;
		uint32_t eye_height : 7;
		uint32_t eye_distance : 4;
		uint32_t eye_rotation : 5;

		// 0x38
		uint32_t eyebrow_thickness : 4;
		uint32_t eyebrow_scale : 4;
		uint32_t eyebrow_color : 3;
		uint32_t eyebrow_type : 5;
		uint32_t eyebrow_height : 7;
		uint32_t eyebrow_distance : 4;
		uint32_t eyebrow_rotation : 5;

		// 0x3c
		uint32_t nose_height : 7;
		uint32_t nose_scale : 4;
		uint32_t nose_type : 5;
		uint32_t mouth_thickness : 3;
		uint32_t mouth_scale : 4;
		uint32_t mouth_color : 3;
		uint32_t mouth_type : 6;

		// 0x40
		uint32_t unk_0x40 : 8;
		uint32_t mustache_type : 3;
		uint32_t mouth_height : 5;
		uint32_t mustache_height : 6;
		uint32_t mustache_scale : 4;
		uint32_t beard_color : 3;
		uint32_t beard_type : 3;

		// 0x44
		uint16_t glass_height : 5;
		uint16_t glass_scale : 4;
		uint16_t glass_color : 3;
		uint16_t glass_type : 4;

		// 0x46
		uint16_t unk_0x46_b0 : 1;
		uint16_t mole_ypos : 5;
		uint16_t mole_xpos : 5;
		uint16_t mole_scale : 4;
		uint16_t mole_enabled : 1;
	} FFLiMiiDataCore;

	typedef struct FFLiMiiDataOfficial {
		FFLiMiiDataCore core;
		char16_t creator_name[10];
	} FFLiMiiDataOfficial;

	typedef struct FFLStoreData {
		FFLiMiiDataOfficial data;
	} FFLStoreData;


union MiiFile {
	char mem[sizeof(FFLStoreData)];
	FFLStoreData md;
} mf;

typedef struct MiiDB {

	int8_t header[9];
	std::array<FFLStoreData, 4> data;

} MiiDatabase;

union MiiDBFile {
	char mem[sizeof(MiiDatabase)];
	MiiDB database;
} db;

#pragma pack(pop)

#ifdef __cplusplus
}
#endif