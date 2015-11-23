
#ifndef __LockItem__
#define __LockItem__


#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class LockItem : public Node
{
public:
    LockItem();
    ~LockItem();
    
    CREATE_FUNC(LockItem);
    
    virtual bool init();
    
    virtual bool ccTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void ccTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void ccTouchEnded(Touch *pTouch, Event *pEvent);
    virtual void ccTouchCancelled(Touch *pTouch, Event *pEvent);
    
    void initWithName(const std::string contentPath,const std::string lockPath,bool locked = false);
    std::function<void(int,bool)>onItemClicked;
    void unlock();
protected:
    bool m_bLocked;
    Sprite* m_pContentSrite;
    Sprite* m_pLock;
};

#endif