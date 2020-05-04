
#ifndef _UIMenuWndWiFiMobileLinkOKIcons_H
#define _UIMenuWndWiFiMobileLinkOKIcons_H
#include "UIFlow.h"
#include "Type.h"



extern void FlowMovieWifi_IconDrawMaxRecTime(VControl *pCtrl);
extern void FlowMovieWifi_IconHideMaxRecTime(VControl *pCtrl);
extern void FlowMovieWifi_IconDrawRecTime(VControl *pCtrl);
extern void FlowMovieWifi_IconDrawRec(VControl *pCtrl);
extern void FlowMovieWifi_IconHideRec(VControl *pCtrl);
extern void FlowMovieWifi_IconDrawSize(VControl *pCtrl);
extern void FlowMovieWifi_IconHideSize(VControl *pCtrl);
extern void FlowMovieWifi_IconDrawStorage(VControl *pCtrl);
extern void FlowMovieWifi_IconHideStorage(VControl *pCtrl);
extern void FlowMovieWifi_IconDrawEV(VControl *pCtrl);
extern void FlowMovieWifi_IconHideEV(VControl *pCtrl);
extern void FlowMovieWifi_IconHideRecTime(VControl *pCtrl);

extern void FlowMovieWifi_IconDrawCyclicRec(VControl *pCtrl);
extern void FlowMovieWifi_IconDrawBattery(VControl *pCtrl);
extern void FlowMovieWifi_IconHideBattery(VControl *pCtrl);
extern void FlowMovieWifi_IconDrawDateTime(void);
extern void FlowMovieWifi_IconHideDateTime(void);

extern void FlowMovieWifi_UpdateIcons(BOOL bShow);

extern void UIMenuWndWiFiMobileLinkOK_UpdateMoiveIcons(BOOL bShow,BOOL);
extern void UIMenuWndWiFiMobileLinkOK_UpdatePhotoIcons(BOOL bShow);
extern void FlowMovieWifi_IconDrawPlayMode(VControl *pCtrl);

#endif //__UIFlowWndMovieIcons_H
