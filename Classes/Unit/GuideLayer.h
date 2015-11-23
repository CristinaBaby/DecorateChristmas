
#ifndef __GuideLayer__
#define __GuideLayer__


#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class GuideLayer : public Layer
{
public:
    GuideLayer();
    ~GuideLayer();
    
    CREATE_FUNC(GuideLayer);
    
    virtual bool init();
    
    void showGuideMove(Vec2 begin,Vec2 end);
    void showGuideTapVertical(Vec2 position);
    void showGuideTapHorizonal(Vec2 position);
    void showGuideShake(Vec2 position);
    void showGuideRotateRight(Vec2 position);
    void showGuideRotateLeft(Vec2 position);
    void showGuideMix(Vec2 position);
    void removeGuide();
    
    std::function<void(int,bool)>onItemClicked;
protected:
    Sprite* m_pGuide;
};

#endif