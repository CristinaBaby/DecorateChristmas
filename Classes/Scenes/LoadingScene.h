#ifndef __LoadingScene__
#define __LoadingScene__

#include "cocos2d.h"

USING_NS_CC;

class LoadingScene : public LayerColor{
public:
    static Scene* scene();
    
    virtual bool init();
    
    CREATE_FUNC(LoadingScene);
};

#endif /* defined(__LoadingScene__) */
