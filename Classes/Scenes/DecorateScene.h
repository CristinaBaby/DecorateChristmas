
#ifndef __DecorateScene__
#define __DecorateScene__


#include "ExtensionScene.h"
#include "ItemScrollView.h"
#include "DecTypeScrollView.h"

class DecorateScene : public ExtensionScene
{
public:
    DecorateScene();
    ~DecorateScene();
    
    MY_SCENE(DecorateScene);
    CREATE_FUNC(DecorateScene);
    
    virtual bool init();
    virtual void onButtonCallback(Button* btn);
    
    void onTypeCallback(int index,std::string,bool selected);
    void onDecorationCallback(int index,DecorateConfigData Data);
protected:
    virtual void _initData();
    void _initDefaultDecorate();
    void _reset();
    
    Sprite* m_pBg;
    DecTypeScrollView* m_pTypeScrollView;
    ItemScrollView* m_pDecorationScrollView;
    int m_nPackage;
    std::string m_sCurTypeStr;
};

#endif