
#include "GameDataManager.h"
#include "cocos2d.h"
#include "GameDataAdapter.h"
#include "IAPManager.h"

USING_NS_CC;

#define kIsFirstTime "IsFirstTime"
#define kBabyName "BabyName"
#define kCurLevelData "CurLevelData"
#define kCurStageData "CurStageData"
#define kCurExperienceData "CurExperienceData"
#define kTotalExperienceData "TotalExperienceData"
#define kStarData "StarData"

GameDataManager::GameDataManager()
{
    
}

GameDataManager::~GameDataManager()
{
    
}

void GameDataManager::setup()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    for (int i = 0; i<4; i++) {
        std::stringstream ostr;
        ostr<<"Shop"<<i;
        if (GameDataAdapter::getBoolValue(ostr.str())) {
            IAPManager::getInstance()->setItemBoughtWithIndex(i);
        }
    }
#endif
}
