#include "LoadingScene.h"
#include "CMVisibleRect.h"
#include "SceneManager.h"
#include "cocostudio/CCArmature.h"

USING_NS_CC;
using namespace cocostudio;

Scene* LoadingScene::scene(){
    Scene* scene = Scene::create();
    LoadingScene* layer = LoadingScene::create();
    scene->addChild(layer);
    return scene;
}

bool LoadingScene::init(){
    if (!LayerColor::init()) {
        return false;
    }
    Size size = Director::getInstance()->getVisibleSize();
    Sprite* bg = Sprite::create("loading/bg.jpg");
    bg->setPosition(Point(size.width/2, size.height/2));
    this->addChild(bg);
    
    this->runAction(Sequence::create(DelayTime::create(3),
                                     CallFunc::create([=]()
                                                      {
                                                          STSystemFunction st;
                                                          st.showNewsBlast();
                                                          SceneManager::replaceTheScene<HomeScene>();
                                                      }),
                                     NULL));
    
    return true;
}