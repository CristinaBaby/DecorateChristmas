
#ifndef __DecorateManager__
#define __DecorateManager__


#include "MakeEatLayer.h"
#include "cocos2d.h"

USING_NS_CC;

enum{
    eDecorateTypeFood,
    eDecorateTypeDrink,
    eDecorateTypeBoth,
};

enum{
    eDecorationLayerFoodBack,
    eDecorationLayerFood,
    eDecorationLayerFoodFront,
    eDecorationLayerDrinkBack,
    eDecorationLayerDrink,
    eDecorationLayerDrinkFood,
    eDecorationLayerDrinkFront,
    eDecorationLayerAllFront,
};
/*分为3类
 1 food类
 分为最下面一层的不可吃的
 中间一层的可吃的
 最上面一层的不可吃的
 
 2 drink类
 分为最下面一层的不可吃的
 中间一层的喝的
 最上面一层的不可吃的
 
 3 food&drink类
 food类和drink类同时有
 */
class DecorateManager : public Node
{
public:
    DecorateManager();
    ~DecorateManager();
    
    static DecorateManager* getInstance()
    {
        static DecorateManager* ret = nullptr;
        if(!ret){
            ret = new DecorateManager();
        }
        return ret;
    }
    void initWithParent(Node* parent,int type);
    void reset();
    void reDecorate();
    void addDecoration(Node* pUnit,int layerFlag,const std::string singleName = "",Vec2 position = Vec2::ZERO,int zOrder = 0);
    void setDrinkMaskSprite(Sprite* pMask);
    void doDrink();
    void stopDrink();
    void doEat(Vec2 location);
    
    void saveEatLayer();
    
    void showFinishedFood(Node* pParent){
//        不可吃的back （如杯子后部）
        Layer* pUneatableLayer = getUneatableLayer();
        if (pUneatableLayer) {
            pParent->addChild(pUneatableLayer);
        }
        if(m_pDrinkLayer){
            m_pEatableLayer = (MakeEatLayer*)getEatableLayer();
            if (m_pEatableLayer) {
                pParent->addChild(m_pEatableLayer);
            }
        }
//        喝的
        RenderTexture* drinkRenderTexture = getDrinkRenderTexture();
        if (drinkRenderTexture) {
            if (drinkRenderTexture->getParent()) {
                drinkRenderTexture->removeFromParent();
            }
            pParent->addChild(drinkRenderTexture);
            _showDrink(100);
        }
//        可吃的中部的
        if(!m_pDrinkLayer){
            m_pEatableLayer = (MakeEatLayer*)getEatableLayer();
            if (m_pEatableLayer) {
                pParent->addChild(m_pEatableLayer);
            }
        }
//        不可吃的前部 （如杯子前部）
        Layer* pFoodFrontLayer = getFoodFrontLayer();
        if (pFoodFrontLayer) {
            pParent->addChild(pFoodFrontLayer);
        }
        Layer* pDrinkFrontLayer = getDrinkFrontLayer();
        if (pDrinkFrontLayer) {
            pParent->addChild(pDrinkFrontLayer);
        }
        //        可吃的前部的
        m_pEatableFrontLayer = (MakeEatLayer*)getEatableFrontLayer();
        if (m_pEatableFrontLayer) {
            pParent->addChild(m_pEatableFrontLayer);
        }
        m_bFinishedEat = false;
        DecorateManager::getInstance()->m_nDrinkPercent = 100;
    }
    Layer* getUneatableLayer();
    MakeEatLayer* getEatableLayer();
    MakeEatLayer* getEatableFrontLayer();
    Layer* getFoodFrontLayer();
    Layer* getDrinkFrontLayer();
    RenderTexture* getDrinkRenderTexture();
    
    bool finishedEat(){return m_bFinishedEat;}
protected:
    void _initFoodLayer();
    void _initDrinkLayer();
    Layer* _initLayer(Layer *pLayer);
    
    void _updateDrink(float dt = 0.1f);
    void _showDrink(int percent);
    void _updateFinishedPercent();
    
    Layer* m_pFoodUneatableBackLayer;
    Layer* m_pFoodUneatableFrontLayer;
    Layer* m_pDrinkUneatableBackLayer;
    Layer* m_pDrinkUneatableFrontLayer;
    Layer* m_pFoodLayer;
    Layer* m_pDrinkLayer;
    Layer* m_pDrinkFoodLayer;
    Layer* m_pAllFrontLayer;
    RenderTexture* m_pDrinkDecRT;
    Sprite* m_pStraw;
    
    Node* m_pParent;
    
//    eat 相关
    Layer* m_pUneatableLayer;
    MakeEatLayer* m_pEatableLayer;
    MakeEatLayer* m_pEatableFrontLayer;
    RenderTexture* m_pDrinkRT;
    Sprite* m_pDrinkMaskSprite;
    Sprite* m_pDrinkSprite;
    
    
    Size m_DrinkSize;
    int m_nDrinkPercent;
    bool m_bFinishedEat;
};

#endif