#include "Type.h"
#include "modelext_info.h"
#include "emb_partition_info.h"

#define BLK_UNIT(x) ((((x)%_EMBMEM_BLK_SIZE_)==0)?((x)/_EMBMEM_BLK_SIZE_):1/0) //block alignment
//#define BLK_UNIT(x) ((((x)%_EMBMEM_BLK_SIZE_)==0)?(x):1/0) //byte alignment

#ifdef _CPU2_LINUX_
EMB_PARTITION ind_emb_partition_info_data[EMB_PARTITION_INFO_COUNT] __attribute__((section("modelext_data.emb_partition_info"))) = {
#if defined(_EMBMEM_SPI_NOR_)
	[0] = {EMBTYPE_LOADER,  0,  BLK_UNIT(0x00000000), BLK_UNIT(0x00010000), BLK_UNIT(0x00000000)},
	[1] = {EMBTYPE_MODELEXT, 0,  BLK_UNIT(0x00010000), BLK_UNIT(0x00010000), BLK_UNIT(0x00000000)},
	[2] = {EMBTYPE_UITRON,  0,  BLK_UNIT(0x00020000), BLK_UNIT(0x005A0000), BLK_UNIT(0x00000000)},
	[3] = {EMBTYPE_UBOOT,   0,  BLK_UNIT(0x005C0000), BLK_UNIT(0x00070000), BLK_UNIT(0x00000000)},
	[4] = {EMBTYPE_UENV,    0,  BLK_UNIT(0x00630000), BLK_UNIT(0x00010000), BLK_UNIT(0x00000000)},
	[5] = {EMBTYPE_LINUX,   0,  BLK_UNIT(0x00640000), BLK_UNIT(0x002C0000), BLK_UNIT(0x00000000)},
	[6] = {EMBTYPE_ROOTFS,  0,  BLK_UNIT(0x00900000), BLK_UNIT(0x00600000), BLK_UNIT(0x00000000)},
	[7] = {EMBTYPE_PSTORE,  0,  BLK_UNIT(0x00F00000), BLK_UNIT(0x00000000), BLK_UNIT(0x00000000)},
#if defined(_DSP1_NONE_)
	[8] = {EMBTYPE_DSP,     0,  BLK_UNIT(0x00F00000), BLK_UNIT(0x00000000), BLK_UNIT(0x00000000)},
	[9] = {EMBTYPE_USER0,  0,  BLK_UNIT(0x00F00000), BLK_UNIT(0x00100000), BLK_UNIT(0x00000000)},
#else
	[8] = {EMBTYPE_DSP,     0,  BLK_UNIT(0x00F00000), BLK_UNIT(0x00100000), BLK_UNIT(0x00000000)},
	[9] = {EMBTYPE_USER0,  0,  BLK_UNIT(0x01000000), BLK_UNIT(0x00000000), BLK_UNIT(0x00000000)},
#endif
	[10] = {EMBTYPE_USER1,  0,  BLK_UNIT(0x00000000), BLK_UNIT(0x00000000), BLK_UNIT(0x00000000)},
#else
	[0] = {EMBTYPE_LOADER,  0,  BLK_UNIT(0x00000000), BLK_UNIT(0x00040000), BLK_UNIT(0x00000000)},
	[1] = {EMBTYPE_MODELEXT, 0,  BLK_UNIT(0x00040000), BLK_UNIT(0x00040000), BLK_UNIT(0x00000000)},
	[2] = {EMBTYPE_UITRON,  0,  BLK_UNIT(0x00080000), BLK_UNIT(0x00880000), BLK_UNIT(0x00000000)},
	[3] = {EMBTYPE_UBOOT,   0,  BLK_UNIT(0x00900000), BLK_UNIT(0x00200000), BLK_UNIT(0x00000000)},
	[4] = {EMBTYPE_UENV,    0,  BLK_UNIT(0x00B00000), BLK_UNIT(0x00080000), BLK_UNIT(0x00000000)},
	[5] = {EMBTYPE_LINUX,   0,  BLK_UNIT(0x00B80000), BLK_UNIT(0x00400000), BLK_UNIT(0x00000000)},
	[6] = {EMBTYPE_ROOTFS,  0,  BLK_UNIT(0x00F80000), BLK_UNIT(0x057C0000), BLK_UNIT(0x00000000)},
	[7] = {EMBTYPE_PSTORE,  0,  BLK_UNIT(0x06740000), BLK_UNIT(0x00400000), BLK_UNIT(0x00100000)},
#if defined(_DSP1_NONE_)
	[8] = {EMBTYPE_DSP,     0,  BLK_UNIT(0x06B40000), BLK_UNIT(0x00000000), BLK_UNIT(0x00000000)},
#else
	[8] = {EMBTYPE_DSP,     0,  BLK_UNIT(0x06B40000), BLK_UNIT(0x00100000), BLK_UNIT(0x00000000)},
#endif
#endif  //_EMBMEM_SPI_NOR_
};

#else /* CPU2 is not Linux */
EMB_PARTITION ind_emb_partition_info_data[EMB_PARTITION_INFO_COUNT] __attribute__((section("modelext_data.emb_partition_info"))) = {
#if defined(_EMBMEM_SPI_NOR_)
 [0] = {EMBTYPE_LOADER,  0,  BLK_UNIT(0x00000000), BLK_UNIT(0x00010000), BLK_UNIT(0x00000000)},
    [1] = {EMBTYPE_MODELEXT, 0, BLK_UNIT(0x00010000), BLK_UNIT(0x00010000), BLK_UNIT(0x00000000)},
    [2] = {EMBTYPE_UITRON,  0,  BLK_UNIT(0x00020000), BLK_UNIT(0x00600000), BLK_UNIT(0x00000000)},
    [3] = {EMBTYPE_UBOOT,   0,  BLK_UNIT(0x00620000), BLK_UNIT(0x00050000), BLK_UNIT(0x00000000)},
    [4] = {EMBTYPE_PSTORE,  0,  BLK_UNIT(0x00670000), BLK_UNIT(0x00080000), BLK_UNIT(0x00000000)},
    #if 0//defined(_DSP1_NONE_)
    //[5] = {EMBTYPE_DSP,     0,  BLK_UNIT(0x00370000), BLK_UNIT(0x00000000), BLK_UNIT(0x00000000)},//0
    #if defined(_CPU2_ECOS_)
    [4] = {EMBTYPE_PSTORE,  0,  BLK_UNIT(0x00370000), BLK_UNIT(0x00460000), BLK_UNIT(0x00000000)},
    [6] = {EMBTYPE_ECOS,    0,  BLK_UNIT(0x007D0000), BLK_UNIT(0x00030000), BLK_UNIT(0x00000000)},//8M SPI
    #elif defined(_CPU2_NONE_)
    [4] = {EMBTYPE_PSTORE,  0,  BLK_UNIT(0x00360000), BLK_UNIT(0x000A0000), BLK_UNIT(0x00000000)},
    [6] = {EMBTYPE_ECOS,    0,  BLK_UNIT(0x00400000), BLK_UNIT(0x00000000), BLK_UNIT(0x00000000)},
    #endif
    #else
    [5] = {EMBTYPE_DSP,     0,  BLK_UNIT(0x006F0000), BLK_UNIT(0x00080000), BLK_UNIT(0x00000000)},
    #if defined(_CPU2_ECOS_)
    [6] = {EMBTYPE_ECOS,    0,  BLK_UNIT(0x00770000), BLK_UNIT(0x00090000), BLK_UNIT(0x00000000)},
    #endif
    #endif
#else
	[0] = {EMBTYPE_LOADER,  0,  BLK_UNIT(0x00000000), BLK_UNIT(0x00040000), BLK_UNIT(0x00000000)},
	[1] = {EMBTYPE_MODELEXT, 0, BLK_UNIT(0x00040000), BLK_UNIT(0x00040000), BLK_UNIT(0x00000000)},
	[2] = {EMBTYPE_UITRON,  0,  BLK_UNIT(0x00080000), BLK_UNIT(0x00A80000), BLK_UNIT(0x00000000)},
	[3] = {EMBTYPE_UBOOT,   0,  BLK_UNIT(0x00B00000), BLK_UNIT(0x00200000), BLK_UNIT(0x00000000)},
	[4] = {EMBTYPE_PSTORE,  0,  BLK_UNIT(0x06940000), BLK_UNIT(0x00200000), BLK_UNIT(0x00100000)},
	#if defined(_DSP1_NONE_)
	[5] = {EMBTYPE_DSP,     0,  BLK_UNIT(0x06B40000), BLK_UNIT(0x00000000), BLK_UNIT(0x00000000)},
	#if defined(_CPU2_ECOS_)
	[6] = {EMBTYPE_ECOS,	0,	BLK_UNIT(0x06B40000), BLK_UNIT(0x00200000), BLK_UNIT(0x00000000)},
	#endif
	#else
	[5] = {EMBTYPE_DSP,     0,  BLK_UNIT(0x06B40000), BLK_UNIT(0x00400000), BLK_UNIT(0x00000000)},
	#if defined(_CPU2_ECOS_)
	[6] = {EMBTYPE_ECOS,	0,	BLK_UNIT(0x06F40000), BLK_UNIT(0x00200000), BLK_UNIT(0x00000000)},
	#endif
	#endif
#endif  //_EMBMEM_SPI_NOR_
};

#endif /* _CPU2_LINUX_ */

MODELEXT_HEADER ind_emb_partition_info_header __attribute__((section("modelext_header.emb_partition_info"))) = {
	.size = sizeof(ind_emb_partition_info_data) + sizeof(MODELEXT_HEADER),
	.type = MODELEXT_TYPE_EMB_PARTITION,
	.number = sizeof(ind_emb_partition_info_data) / sizeof(EMB_PARTITION),
	.version = EMB_PARTITION_INFO_VER,
};
