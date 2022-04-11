#pragma once
#include <array>
#include <cstdint>
#include "wut_structsize.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1)

	enum FFLCreateIDFlags : uint8_t
	{
		IsWiiUMii = 0x1 | 0x4,
		IsTemporaryMii = 0x2,
		IsNormalMii = 0x8,
	};

	struct FFLCreateID
	{
		uint32_t flags : 4;

		//! Seconds since Jan 1st 2010
		uint32_t timestamp : 28;

		uint8_t deviceHash[6];
	};
	WUT_CHECK_OFFSET(FFLCreateID, 4, deviceHash);
	WUT_CHECK_SIZE(FFLCreateID, 10);

	// This structure is intentionally little-endian as the data
	//  is stored in a cross-platform manner for multiple devices.
	struct FFLiMiiDataCore
	{
		// 0x00
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
		char16_t mii_name[10];

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
	};
	WUT_CHECK_OFFSET(FFLiMiiDataCore, 0x03, mii_version);
	WUT_CHECK_OFFSET(FFLiMiiDataCore, 0x04, author_id);
	WUT_CHECK_OFFSET(FFLiMiiDataCore, 0x0C, mii_id);
	WUT_CHECK_OFFSET(FFLiMiiDataCore, 0x16, unk_0x16);
	WUT_CHECK_OFFSET(FFLiMiiDataCore, 0x1A, mii_name);
	WUT_CHECK_OFFSET(FFLiMiiDataCore, 0x2E, size);
	WUT_CHECK_OFFSET(FFLiMiiDataCore, 0x2F, fatness);
	WUT_CHECK_OFFSET(FFLiMiiDataCore, 0x33, hair_type);
	WUT_CHECK_SIZE(FFLiMiiDataCore, 0x48);

	struct FFLiMiiDataOfficial : FFLiMiiDataCore
	{
		char16_t creator_name[10];
	};
	WUT_CHECK_OFFSET(FFLiMiiDataOfficial, 0x48, creator_name);
	WUT_CHECK_SIZE(FFLiMiiDataOfficial, 0x5C);

	struct FFLStoreData : FFLiMiiDataOfficial
	{
		uint16_t unk_0x5C;
		uint16_t checksum;
	};
	WUT_CHECK_OFFSET(FFLStoreData, 0x5C, unk_0x5C);
	WUT_CHECK_OFFSET(FFLStoreData, 0x5E, checksum);
	WUT_CHECK_SIZE(FFLStoreData, 0x60);


union MiiFile {
	char mem[sizeof(FFLStoreData)];
	FFLStoreData md;
} mf;

typedef struct MiiDB {

	char header[8];

} MiiDatabase;

union MiiDBFile {
	char mem[sizeof(MiiDatabase)];
	MiiDB database;
} db;

#pragma pack(pop)

#ifdef __cplusplus
}
#endif