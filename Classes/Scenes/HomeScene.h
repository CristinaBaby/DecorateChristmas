
#ifndef __HomeScene__
#define __HomeScene__


#include "ExtensionScene.h"

class HomeScene : public ExtensionScene
{
public:
    HomeScene();
    ~HomeScene();
    
    MY_SCENE(HomeScene);
    CREATE_FUNC(HomeScene);
    
    virtual bool init();
    virtual void onEnter();
    virtual void onButtonCallback(Button* btn);
    virtual void onKeyBackClicked();
protected:
    virtual void _initData();
    void _showParticle();
    
    Sprite* m_pCup;
    Sprite* m_pCupShadow;
    Sprite* m_pLogo;
    Sprite* m_pFork;
    Sprite* m_pForkShadow;
};

#endif