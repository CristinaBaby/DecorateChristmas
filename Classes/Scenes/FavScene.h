//
//  FavScene.h
//  FMAKER033
//
//  Created by wuguiling on 9/11/14.
//
//

#ifndef __FMAKER033__FavScene__
#define __FMAKER033__FavScene__

#include <iostream>
#include "cocos2d.h"
#include "Heads.h"
#include "ExtensionScene.h"
#include "FlowPageView.h"

USING_NS_CC;
USING_NS_CC_EXT;

class FavScene:public ExtensionScene{
    
    
public:
    MY_SCENE(FavScene);
    CREATE_FUNC(FavScene);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void FlowPageWillScroll();
    virtual void FLowPageDidEndScroll(int tag);
    
//    virtual void alertViewDidDismissWithButtonIndex(int aInx);
    virtual void onNegativeClick(void*);
    virtual void onPositiveClick(void*);
    
    virtual void onKeyBackClicked();
    
    void _onMenuItemCallback(MenuItemSprite* item);
    void _setMenuEnable(){m_pMenu->setEnabled(true);}
protected:
    Menu* m_pMenu;
    
    MenuItemSprite* m_pBackItemSprite;
    MenuItemSprite* m_pDeleteItemSprite;
    FlowPageView* m_pFlowLayer;
    
    int m_nCurFavTag;
};
#endif /* defined(__FMAKER033__FavScene__) */
