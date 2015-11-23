
#ifndef __GameUILayoutLayer__
#define __GameUILayoutLayer__


#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

enum
{
    eUIButtonTagHomeStart,
    eUIButtonTagHomeRestore,
    eUIButtonTagHomeMore,
    eUIButtonTagHomeFav,
    eUIButtonTagHomeShop,
    eUIButtonTagBack,
    eUIButtonTagNext,
    eUIButtonTagReset,
    eUIButtonTagFav,
    eUIButtonTagEmail,
    eUIButtonTagHome,
    eUIButtonTagEatAgain,
    eUIButtonTag,
};

class GameUILayoutLayer : public Node
{
public:
    GameUILayoutLayer();
    ~GameUILayoutLayer();
    
    CREATE_FUNC(GameUILayoutLayer);
    
    virtual bool init();
    
    void showHomeUILayout(bool animate = true);
    void showMakeUILayout(bool animate = true);
    void showDecorateUILayout(bool animate = true);
    void showShareUILayout(bool animate = true);
    
    void showNextLayout(bool animate = true);
    void showBackLayout(bool animate = true);
    void showResetLayout(bool animate = true);
    
    void showEatAgainLayout(bool isDrink = false,bool animate = true);
    
    void hideNext(){
        m_pNext->setVisible(false);
        m_pNext->setEnabled(false);
    };
    
    bool eatAgainIsShow(){
        return !m_pEatAgain?false:m_pEatAgain->isVisible();
    }
    std::function<void(Button*)>onButtonClicked;
protected:
    
    Button* _createButton(std::string path);
    void _onButtonCallback(Ref* ref,Widget::TouchEventType type);
    void _showHomeButtonAnimation(Button* pButton,float duration = 1,float delay = 0);
    
//    首页
    Button* m_pHomeStart;
    Button* m_pHomeRestore;
    Button* m_pHomeMore;
    Button* m_pHomeFav;
    Button* m_pHomeShop;
    
//    Make
    Button* m_pNext;
    Button* m_pBack;
    Button* m_pReset;
    
//    share
    Button* m_pFav;
    Button* m_pEmail;
    Button* m_pHome;
    Button* m_pEatAgain;
};

#endif