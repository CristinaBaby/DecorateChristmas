
#ifndef __ExpandScrollView__
#define __ExpandScrollView__


#include "ui/UIScrollView.h"

USING_NS_CC;
using namespace cocos2d::ui;

class ExpandScrollView : public ui::ScrollView
{
public:
    ExpandScrollView();
    ~ExpandScrollView();
    enum{
        eBeginScroll,
        eScrolling,
        eEndedScroll,
    };
    static ExpandScrollView* create();
    
    virtual bool init();
    
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent);
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent);
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent);
    virtual void onTouchCancelled(Touch* touch, Event* event);
    
    std::function<void(ExpandScrollView* ,int)> onExpandScrollViewCallback;
    bool isScrolled(){return m_bIsScrolling;}
protected:
    bool m_bIsScrolling;
};

#endif