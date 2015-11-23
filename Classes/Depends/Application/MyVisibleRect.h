
#ifndef __MyVisibleRect__
#define __MyVisibleRect__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

typedef enum {
    eXNearestTypeNone = 0,
    eXNearestTypeLeft,
    eXNearestTypeRight,
    eXNearestTypeCenter,
}eXNearestType;

typedef enum {
    eYNearestTypeNone = 0,
    eYNearestTypeTop,
    eYNearestTypeBottom,
    eYNearestTypeMiddle,
}eYNearestType;

class MyVisibleRect
{
public:
    static void setup();
    static void setupVisibleRect(const Size& frameSize, const Size& designSize);
    
    static void setPosition(Node* pNode, float x, float y, eXNearestType xType, eYNearestType yType);
    static Point getPosition(float x, float y, eXNearestType xType, eYNearestType yType);
    
    static Size getDesignSize();
    static Size getFrameSize();
    static Size getRealDesignSize();
    static float getRealContentFactor();
    
    static Point getDesignOffset();
    static Point getWoldOrigin();
    static float getRealDesignScale();
    
protected:
    static Size ms_cFrameSize;
    static Size ms_cDesignSize;
    static Size ms_cRealDesignSize;
    
    static Point ms_cWorldOrigin;
    static Point ms_cDesignOffset;
    static Size ms_cVisibleSize;
    static Point ms_cVisibleOrigin;
    static float ms_fRealDesignScale;
    static float ms_fRealContentFactor;
};

#endif /* defined(__MyVisibleRect__) */
