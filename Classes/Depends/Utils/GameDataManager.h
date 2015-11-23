
#ifndef __GameDataManager__
#define __GameDataManager__


#include "SingleTon.h"
#include "DressUpData.h"

enum{
    ePackageLemonade,
    ePackageHotdog,
    ePackageFrenchFries,
    ePackageSnowCone,
    ePackageChurro,
    ePackageBurrito,
    ePackageFunnelCake,
    ePackageFryBread,
};

class GameDataManager : public SingleTon<GameDataManager>
{
public:
    GameDataManager();
    ~GameDataManager();
    
    void setup();
    
    
//    lemonade
//    口味（下标0开始）
    int m_nLemonadeFlavor = 0;
    
    
    int m_nFunnelCakeFlavor = 0;
    
    int m_nHotdogStick = 0;
    
    int m_nChurroFlavor = 0;
    
    int m_nSnowconeFlavor = 0;
    
    int m_nPackage = 0;
    
    int m_nBgIndex = -1;
protected:
    
};

#endif