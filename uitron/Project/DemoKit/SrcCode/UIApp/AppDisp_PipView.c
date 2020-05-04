#include "Color.h"
#include <stdio.h>
#include "SysCfg.h"
#include "UIInfo.h"
#include "AppDisp_PipView.h"
#include "nvtmpp.h"
#include "UIAppMovie.h"

#define THIS_DBGLVL         2       // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
#define __MODULE__          Pip
#define __DBGLVL__          THIS_DBGLVL
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include "DebugModule.h"

#if (SENSOR_CAPS_COUNT == 2)
static APPDISP_VIEW_INFO   pip_view_info={
							 0x00010001, 0x00010001 , // w 1/1    h 1/1
					  		 0x00010002, 0x00010002 , // w 1/2    h 1/2
							 0x00010002, 0x00010002 , // w 1/2    h 1/2
							 0x00010002, 0x00010002 , // w 1/2    h 1/2
};
#elif (SENSOR_CAPS_COUNT == 3)
static APPDISP_VIEW_INFO   pip_view_info={
							 0x00010002, 0x00010002 , // w 1/2    h 1/2
							 0x00010002, 0x00010002 , // w 1/2    h 1/2
					  		 0x00010002, 0x00010002 , // w 1/2    h 1/2
							 0x00010002, 0x00010002 , // w 1/2    h 1/2
};
#else
static APPDISP_VIEW_INFO   pip_view_info={
							 0x00010002, 0x00010002 , // w 1/2    h 1/2
					  		 0x00010002, 0x00010002 , // w 1/2    h 1/2
					  		 0x00010002, 0x00010002 , // w 1/2    h 1/2
							 0x00010002, 0x00010002 , // w 1/2    h 1/2
};
#endif

#if (DUALCAM_PIP_BEHIND_FLIP == ENABLE)
static NVTMPP_VB_POOL g_PipViewBflip_Pool = NVTMPP_VB_INVALID_POOL;
static UINT32 g_PipViewBflip_PoolAddr = 0, g_PipViewBflip_PoolSize = 0;
UINT32 PipView_BFLIP_GetBufAddr(UINT32 blk_size)
{
        UINT32 uiAddr = 0;
        NVTMPP_VB_BLK  blk=0;
        CHAR pool_name[20] ={0};


        if(g_PipViewBflip_Pool == NVTMPP_VB_INVALID_POOL)  {
            sprintf(pool_name,"PipView");
            g_PipViewBflip_Pool = nvtmpp_vb_create_pool(pool_name, blk_size , 1, NVTMPP_DDR_1);
            if (NVTMPP_VB_INVALID_POOL == g_PipViewBflip_Pool)	{
        		DBG_ERR("create private pool err\r\n");
        		return 0;
            }

            blk = nvtmpp_vb_get_block(0, g_PipViewBflip_Pool, blk_size, NVTMPP_DDR_1);
            if (NVTMPP_VB_INVALID_BLK == blk) {
        		DBG_ERR("get vb block err\r\n");
                	return 0;
            }
            uiAddr = nvtmpp_vb_block2addr(blk);
        }
        if(uiAddr == 0)
    		DBG_ERR("get buf addr err\r\n");
        return uiAddr;
}

void PipView_BFLIP_DestroyBuff(void)
{
	INT32 ret;

	if(g_PipViewBflip_Pool != NVTMPP_VB_INVALID_POOL) {
		ret = nvtmpp_vb_destroy_pool(g_PipViewBflip_Pool);
		if (NVTMPP_ER_OK != ret) {
			DBG_ERR("destory pool error pool 0x%x   ret=%d\r\n", g_PipViewBflip_Pool, ret);
		}
		g_PipViewBflip_Pool = NVTMPP_VB_INVALID_POOL;
		g_PipViewBflip_PoolAddr = g_PipViewBflip_PoolSize = 0;
	}
}

void PipView_BFLIP_SetBuffer(UINT32 uiAddr, UINT32 uiSize)
{
    if(!uiAddr || !uiSize) {
        DBG_ERR("Buf invalid!\r\n");
    } else {
        g_PipViewBflip_PoolAddr = uiAddr;
        g_PipViewBflip_PoolSize = uiSize;
    }
}
#endif

#if 0 //(SBS_VIEW_FUNC == ENABLE)
static void PipLRView_SetStyle(UINT32 uiStyle)
{
	pip_scale_info_4sensor.scale[0].w = 0x00010002;
	pip_scale_info_4sensor.scale[0].h = 0x00010001;
	pip_scale_info_4sensor.scale[1].w = 0x00010002; // w 1/2
	pip_scale_info_4sensor.scale[1].h = 0x00010001; // h 1/1
}

static INT32 PipLRView_OnDraw_2sensor(PIP_DRAW *pDraw) //PIP = Picture In Picture
{
	IPOINT dstLos = {0, 0};
	//IRECT            dst_region;

    #if 1
    {
        static BOOL isSave = FALSE;

		if (!isSave && pDraw->p_src_img[0]->Width > 1000) {
			GxImg_DumpBuf("A:\\src1.yuv", pDraw->p_src_img[0], GX_IMAGE_DUMP_ALL);
			GxImg_DumpBuf("A:\\src2.yuv", pDraw->p_src_img[1], GX_IMAGE_DUMP_ALL);
			DBG_DUMP("Saved\r\n");
			isSave = TRUE;
		}
    }
	#endif

    //GxImg_FillData(pDraw->p_dst_img, REGION_MATCH_IMG, COLOR_YUV_BLACK);
	// img1
	//dst_region.x = 0;
	//dst_region.y = pDraw->p_dst_img->Height /4;
	//dst_region.w = pDraw->p_dst_img->Width / 2;
	//dst_region.h = pDraw->p_dst_img->Height / 2;
	GxImg_CopyData(pDraw->p_src_img[0], REGION_MATCH_IMG, pDraw->p_dst_img, &dstLos);

    // img2
    //dst_region.x = pDraw->p_dst_img->Width / 2;
	//dst_region.y = pDraw->p_dst_img->Height / 4;
	dstLos.x = pDraw->p_dst_img->Width / 2;
	GxImg_CopyData(pDraw->p_src_img[1], REGION_MATCH_IMG, pDraw->p_dst_img, &dstLos);

	return E_OK;
}
#endif



void PipView_SetImg(ISIZE *pImgSize, USIZE *pAspectRatio)
{

}

void PipView_SetStyle(UINT32 uiStyle)
{

	#if (SENSOR_CAPS_COUNT == 2)
	pip_view_info.scale[0].w = 0x00010001;
	pip_view_info.scale[0].h = 0x00010001;
	pip_view_info.scale[1].w = 0x00010002; // w 1/2
	pip_view_info.scale[1].h = 0x00010002; // h 1/2
	#else

	#endif

}

INT32 PipView_GetInfo(APPDISP_VIEW_INFO *info)
{
	if (!info){
		return E_PAR;
	}
	*info = pip_view_info;
	return E_OK;
}

#if (SENSOR_CAPS_COUNT == 2)
static INT32 PipView_OnDraw_2sensor(APPDISP_VIEW_DRAW *pDraw) //PIP = Picture In Picture
{
	IRECT	dst_region;
	UINT32	dual_cam;

	if (pDraw->viewcnt == 2)
	{
		dual_cam = UI_GetData(FL_DUAL_CAM);
		GxImg_FillData(pDraw->p_dst_img, NULL, COLOR_YUV_BLACK);

		if (dual_cam == DUALCAM_FRONT)
		{
			// img1
			if (pDraw->p_src_img[0]) {
				dst_region.x = 0;
				dst_region.y = 0;
				dst_region.w = pDraw->p_dst_img->Width;
				dst_region.h = pDraw->p_dst_img->Height;
				GxImg_ScaleData(pDraw->p_src_img[0], REGION_MATCH_IMG, pDraw->p_dst_img, &dst_region);
			}
		}
		else if (dual_cam == DUALCAM_BEHIND)
		{
			// img2
			if (pDraw->p_src_img[1]) {
				dst_region.x = 0;
				dst_region.y = 0;
				dst_region.w = pDraw->p_dst_img->Width;
				dst_region.h = pDraw->p_dst_img->Height;

				#if (DUALCAM_PIP_BEHIND_FLIP == DISABLE)
					GxImg_ScaleData(pDraw->p_src_img[1], REGION_MATCH_IMG, pDraw->p_dst_img, &dst_region);
				#else
					// flip rear image to destination buffer
					IPOINT	dstLocation = {0, 0};
					GxImg_RotatePasteData(pDraw->p_src_img[1], &dst_region, pDraw->p_dst_img, &dstLocation, GX_IMAGE_ROTATE_HRZ, GX_IMAGE_ROTATE_ENG2);
				#endif
			}
		}
		else if (dual_cam == DUALCAM_BOTH2)
		{
			// rear image is bigger
			if (pDraw->p_src_img[1]) {
				dst_region.x = 0;
				dst_region.y = 0;
				dst_region.w = pDraw->p_dst_img->Width;
				dst_region.h = pDraw->p_dst_img->Height;

				#if (DUALCAM_PIP_BEHIND_FLIP == DISABLE)
					GxImg_ScaleData(pDraw->p_src_img[1], REGION_MATCH_IMG, pDraw->p_dst_img, &dst_region);
				#else
					// flip rear image to destination buffer
					IPOINT	dstLocation = {0, 0};
					GxImg_RotatePasteData(pDraw->p_src_img[1], &dst_region, pDraw->p_dst_img, &dstLocation, GX_IMAGE_ROTATE_HRZ, GX_IMAGE_ROTATE_ENG2);
				#endif
			}

			// front image is smaller
			if (pDraw->p_src_img[0]) {
				dst_region.x = 0;
				dst_region.y = 0;
				dst_region.w = pDraw->p_dst_img->Width / 2;
				dst_region.h = pDraw->p_dst_img->Height / 2;
				GxImg_ScaleData(pDraw->p_src_img[0], REGION_MATCH_IMG, pDraw->p_dst_img, &dst_region);
			}
		}
		else if (dual_cam == DUALCAM_BOTH)
		{
			// front image is bigger
			if (pDraw->p_src_img[0]) {
				dst_region.x = 0;
				dst_region.y = 0;
				dst_region.w = pDraw->p_dst_img->Width;
				dst_region.h = pDraw->p_dst_img->Height;
				GxImg_ScaleData(pDraw->p_src_img[0], REGION_MATCH_IMG, pDraw->p_dst_img, &dst_region);
			}

			// rear image is smaller
			if (pDraw->p_src_img[1]) {
				dst_region.x = 0;
				dst_region.y = 0;
				dst_region.w = pDraw->p_dst_img->Width / 2;
				dst_region.h = pDraw->p_dst_img->Height / 2;

				#if (DUALCAM_PIP_BEHIND_FLIP == DISABLE)
					GxImg_ScaleData(pDraw->p_src_img[1], REGION_MATCH_IMG, pDraw->p_dst_img, &dst_region);
				#else
					// flip rear image to destination buffer
					IRECT		dstRegion;
					IPOINT		dstLocation;

					// scale rear image to top-right corner of destination buffer (size 1/4)
					dstRegion.x = pDraw->p_dst_img->Width / 2;
					dstRegion.y = 0;
					dstRegion.w = ALIGN_CEIL_4(pDraw->p_dst_img->Width / 2);
					dstRegion.h = ALIGN_CEIL_4(pDraw->p_dst_img->Height / 2);
					GxImg_ScaleData(pDraw->p_src_img[1], REGION_MATCH_IMG, pDraw->p_dst_img, &dstRegion);

					// flip and paste scaled image from top-right to top-left of destination buffer
					dstLocation.x = 0;
					dstLocation.y = 0;
					GxImg_RotatePasteData(pDraw->p_dst_img, &dstRegion, pDraw->p_dst_img, &dstLocation, GX_IMAGE_ROTATE_HRZ, GX_IMAGE_ROTATE_ENG2);

					// paste top-right of front image to destination buffer
					if (pDraw->p_src_img[0]) {
						GxImg_ScaleData(pDraw->p_src_img[0], &dstRegion, pDraw->p_dst_img, &dstRegion);
					}
				#endif
			}
		}
#if IMG_FULL_DISP
		else if (dual_cam == DUALCAM_LR_FULL)
		{
			ISIZE	img_ratio;
			USIZE	disp_aspect_ratio = GxVideo_GetDeviceAspect(DOUT1);
			IRECT	src_region;
			IPOINT	dstLocation;

			MovieExe_GetRecSize(0, &img_ratio);

			if ((img_ratio.w * disp_aspect_ratio.h) > (disp_aspect_ratio.w * img_ratio.h) ||
				(img_ratio.w * disp_aspect_ratio.h * 2) > (disp_aspect_ratio.w * img_ratio.h)) {

				if (pDraw->p_src_img[1]) {
					#if (DUALCAM_PIP_BEHIND_FLIP == DISABLE)
						// crop rear image and copy to right of destination buffer
						src_region.w = pDraw->p_dst_img->Width / 2;
						src_region.h = pDraw->p_dst_img->Height;
						src_region.x = ALIGN_CEIL_4((pDraw->p_src_img[1]->Width - src_region.w) / 2);
						src_region.y = 0;
						dst_region.w = pDraw->p_dst_img->Width / 2;
						dst_region.h = pDraw->p_dst_img->Height;
						dst_region.x = pDraw->p_dst_img->Width / 2;
						dst_region.y = 0;
						GxImg_ScaleData(pDraw->p_src_img[1], &src_region, pDraw->p_dst_img, &dst_region);
					#else
						// crop rear image and copy to left of destination buffer
						src_region.w = pDraw->p_dst_img->Width / 2;
						src_region.h = pDraw->p_dst_img->Height;
						src_region.x = ALIGN_CEIL_4((pDraw->p_src_img[1]->Width - src_region.w) / 2);
						src_region.y = 0;
						dst_region.w = pDraw->p_dst_img->Width / 2;
						dst_region.h = pDraw->p_dst_img->Height;
						dst_region.x = 0;
						dst_region.y = 0;
						GxImg_ScaleData(pDraw->p_src_img[1], &src_region, pDraw->p_dst_img, &dst_region);

						// flip and paste cropped rear image from left to right of destination buffer
						dstLocation.x = pDraw->p_dst_img->Width / 2;
						dstLocation.y = 0;
						GxImg_RotatePasteData(pDraw->p_dst_img, &dst_region, pDraw->p_dst_img, &dstLocation, GX_IMAGE_ROTATE_HRZ, GX_IMAGE_ROTATE_ENG2);
					#endif
				}

				if (pDraw->p_src_img[0]) {
					// crop front image and copy to left of destination buffer
					src_region.w = pDraw->p_dst_img->Width / 2;
					src_region.h = pDraw->p_dst_img->Height;
					src_region.x = ALIGN_CEIL_4((pDraw->p_src_img[0]->Width - src_region.w) / 2);
					src_region.y = 0;
					dst_region.w = pDraw->p_dst_img->Width / 2;
					dst_region.h = pDraw->p_dst_img->Height;
					dst_region.x = 0;
					dst_region.y = 0;
					GxImg_ScaleData(pDraw->p_src_img[0], &src_region, pDraw->p_dst_img, &dst_region);
				}
			} else {

				if (pDraw->p_src_img[1]) {
					#if (DUALCAM_PIP_BEHIND_FLIP == DISABLE)
						// crop rear image and copy to right of destination buffer
						src_region.w = pDraw->p_dst_img->Width / 2;
						src_region.h = pDraw->p_dst_img->Height;
						src_region.x = 0;
						src_region.y = ALIGN_CEIL_4((pDraw->p_src_img[1]->Height - src_region.h) / 2);
						dst_region.w = pDraw->p_dst_img->Width / 2;
						dst_region.h = pDraw->p_dst_img->Height;
						dst_region.x = pDraw->p_dst_img->Width / 2;
						dst_region.y = 0;
						GxImg_ScaleData(pDraw->p_src_img[1], &src_region, pDraw->p_dst_img, &dst_region);
					#else
						// crop rear image and copy to left of destination buffer
						src_region.w = pDraw->p_dst_img->Width / 2;
						src_region.h = pDraw->p_dst_img->Height;
						src_region.x = 0;
						src_region.y = ALIGN_CEIL_4((pDraw->p_src_img[1]->Height - src_region.h) / 2);
						dst_region.w = pDraw->p_dst_img->Width / 2;
						dst_region.h = pDraw->p_dst_img->Height;
						dst_region.x = 0;
						dst_region.y = 0;
						GxImg_ScaleData(pDraw->p_src_img[1], &src_region, pDraw->p_dst_img, &dst_region);

						// flip and paste cropped rear image from left to right of destination buffer
						dstLocation.x = pDraw->p_dst_img->Width / 2;
						dstLocation.y = 0;
						GxImg_RotatePasteData(pDraw->p_dst_img, &dst_region, pDraw->p_dst_img, &dstLocation, GX_IMAGE_ROTATE_HRZ, GX_IMAGE_ROTATE_ENG2);
					#endif
				}

				if (pDraw->p_src_img[0]) {
					// crop front image and copy to left of destination buffer
					src_region.w = pDraw->p_dst_img->Width / 2;
					src_region.h = pDraw->p_dst_img->Height;
					src_region.x = 0;
					src_region.y = ALIGN_CEIL_4((pDraw->p_src_img[0]->Height - src_region.h) / 2);
					dst_region.w = pDraw->p_dst_img->Width / 2;
					dst_region.h = pDraw->p_dst_img->Height;
					dst_region.x = 0;
					dst_region.y = 0;
					GxImg_ScaleData(pDraw->p_src_img[0], &src_region, pDraw->p_dst_img, &dst_region);
				}
			}
		}
#endif
	}

	return E_OK;
}
#elif (SENSOR_CAPS_COUNT == 3)
static INT32 PipView_OnDraw_3sensor(APPDISP_VIEW_DRAW *pDraw) //PIP = Picture In Picture
{
	IRECT            dst_region;

	GxImg_FillData(pDraw->p_dst_img, NULL, COLOR_YUV_BLACK) ;

	// img1
	dst_region.x = 0;
	dst_region.y = 0;
	dst_region.w = pDraw->p_dst_img->Width / 2;
	dst_region.h = pDraw->p_dst_img->Height / 2;
	if(pDraw->p_src_img[0]){
		GxImg_ScaleData(pDraw->p_src_img[0], REGION_MATCH_IMG, pDraw->p_dst_img, &dst_region);
	}
	// img2
	dst_region.x = pDraw->p_dst_img->Width / 2;
	dst_region.y = 0;
	if(pDraw->p_src_img[1]){
		GxImg_ScaleData(pDraw->p_src_img[1], REGION_MATCH_IMG, pDraw->p_dst_img, &dst_region);
	}
	// img3
	dst_region.x = 0;
	dst_region.y = pDraw->p_dst_img->Height / 2;
	if(pDraw->p_src_img[2]){
		GxImg_ScaleData(pDraw->p_src_img[2], REGION_MATCH_IMG, pDraw->p_dst_img, &dst_region);
	}
	return E_OK;
}
#elif (SENSOR_CAPS_COUNT == 4)

static INT32 PipView_OnDraw_4sensor_2view(APPDISP_VIEW_DRAW *pDraw) //PIP = Picture In Picture
{
	IRECT            dst_region;

    // img2
	dst_region.x = 0;
	dst_region.y = 0;
	dst_region.w = pDraw->p_dst_img->Width / 2;
	dst_region.h = pDraw->p_dst_img->Height / 2;
	if(pDraw->p_src_img[1]){
		GxImg_ScaleData(pDraw->p_src_img[1], REGION_MATCH_IMG, pDraw->p_dst_img, &dst_region);
	}
	return E_OK;
}

static INT32 PipView_OnDraw_4sensor(APPDISP_VIEW_DRAW *pDraw) //PIP = Picture In Picture
{
	IRECT            dst_region;
	GxImg_FillData(pDraw->p_dst_img, NULL, COLOR_YUV_BLACK) ;

	// img1
	dst_region.x = 0;
	dst_region.y = 0;
	dst_region.w = pDraw->p_dst_img->Width / 2;
	dst_region.h = pDraw->p_dst_img->Height / 2;
	if(pDraw->p_src_img[0]){
		GxImg_ScaleData(pDraw->p_src_img[0], REGION_MATCH_IMG, pDraw->p_dst_img, &dst_region);
	}
	// img2
	dst_region.x = pDraw->p_dst_img->Width / 2;
	dst_region.y = 0;
	if(pDraw->p_src_img[1]){
		GxImg_ScaleData(pDraw->p_src_img[1], REGION_MATCH_IMG, pDraw->p_dst_img, &dst_region);
	}
	// img3
	dst_region.x = 0;
	dst_region.y = pDraw->p_dst_img->Height / 2;
	if(pDraw->p_src_img[2]){
		GxImg_ScaleData(pDraw->p_src_img[2], REGION_MATCH_IMG, pDraw->p_dst_img, &dst_region);
	}
	// img4
	dst_region.x = pDraw->p_dst_img->Width / 2;
	dst_region.y = pDraw->p_dst_img->Height / 2;
	if(pDraw->p_src_img[3]){
		GxImg_ScaleData(pDraw->p_src_img[3], REGION_MATCH_IMG, pDraw->p_dst_img, &dst_region);
	}
	return E_OK;
}
#endif



INT32 PipView_OnDraw(APPDISP_VIEW_DRAW *pDraw) //PIP = Picture In Picture
{
#if (SENSOR_CAPS_COUNT == 4)
    if (pDraw->viewcnt == 2){
        PipView_OnDraw_4sensor_2view(pDraw);
    } else{
        PipView_OnDraw_4sensor(pDraw);
    }
#elif (SENSOR_CAPS_COUNT == 3)
    PipView_OnDraw_3sensor(pDraw);
#elif (SENSOR_CAPS_COUNT == 2)
    PipView_OnDraw_2sensor(pDraw);
#else
    DBG_ERR("Not Support %d sensor\r\n",SENSOR_CAPS_COUNT);
#endif
    return E_OK;
}




