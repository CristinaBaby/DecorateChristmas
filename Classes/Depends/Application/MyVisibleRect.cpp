
#include "MyVisibleRect.h"

Size MyVisibleRect::ms_cFrameSize = Size(0, 0);
Size MyVisibleRect::ms_cDesignSize = Size(0, 0);
Size MyVisibleRect::ms_cRealDesignSize = Size(0, 0);
Size MyVisibleRect::ms_cVisibleSize = Size(0, 0);

Point MyVisibleRect::ms_cDesignOffset = Point(0, 0);
Point MyVisibleRect::ms_cVisibleOrigin = Point(0, 0);
Point MyVisibleRect::ms_cWorldOrigin = Point(0, 0);

float MyVisibleRect::ms_fRealDesignScale = 0.0f;
float MyVisibleRect::ms_fRealContentFactor = 0.0f;

void MyVisibleRect::setup()
{
    
    ms_cVisibleSize = CCDirector::getInstance()->getVisibleSize();
    ms_cVisibleOrigin = CCDirector::getInstance()->getVisibleOrigin();
}
void MyVisibleRect::setupVisibleRect(const Size& frameSize, const Size& designSize)
{
    ms_cDesignSize = designSize;
    ms_cFrameSize = frameSize;
    
    float scaleX = frameSize.width / designSize.width;
    float scaleY = frameSize.height / designSize.height;
    float scale = MIN(scaleX, scaleY);
    
    ms_cRealDesignSize = Size(frameSize.width / scale, frameSize.height / scale);
    ms_fRealContentFactor = MAX(scaleX, scaleY);
    
    ms_cDesignOffset = Point( fabs(ms_cRealDesignSize.width - designSize.width)/2.0 ,
                             fabs(ms_cRealDesignSize.height - designSize.height)/2.0 );
    ms_fRealDesignScale = scale;
    ms_cWorldOrigin = Point((CCDirector::getInstance()->getWinSize().width-frameSize.width)*0.5, (CCDirector::getInstance()->getWinSize().height-frameSize.height)*0.5);
    log("%f,%f",CCDirector::getInstance()->getWinSize().width,CCDirector::getInstance()->getWinSize().height);
    log("%f,%f",ms_cVisibleSize.width,ms_cVisibleSize.height);
    log("%f,%f",ms_cRealDesignSize.width,ms_cRealDesignSize.height);
}

void MyVisibleRect::setPosition(Node* pNode, float x, float y, eXNearestType xType, eYNearestType yType)
{
    
    ms_cVisibleSize = CCDirector::getInstance()->getVisibleSize();
    ms_cVisibleOrigin = CCDirector::getInstance()->getVisibleOrigin();
    log("%f,%f",ms_cDesignOffset.x,ms_cDesignOffset.y);
    log("%f,%f",ms_cVisibleSize.width,ms_cVisibleSize.height);
    float posX = 0;
    float posY = 0;
    
    // 设置x坐标
    switch (xType) {
        case eXNearestTypeNone:
        {
            posX = x;
        }
            break;
            
        case eXNearestTypeLeft:
        {
            posX = ms_cVisibleOrigin.x + x;
        }
            break;
            
        case eXNearestTypeRight:
        {
            posX = ms_cVisibleOrigin.x + ms_cVisibleSize.width - x;
        }
            break;
            
        case eXNearestTypeCenter:
        {
            posX = x + ms_cDesignOffset.x;
        }
            break;
            
        default:
            break;
    }
    
    // 设置y坐标
    switch (yType) {
        case eYNearestTypeNone:
        {
            posY = y;
        }
            break;
            
        case eYNearestTypeTop:
        {
            posY = ms_cVisibleOrigin.y + ms_cVisibleSize.height - y;
        }
            break;
            
        case eYNearestTypeBottom:
        {
            posY = ms_cVisibleOrigin.y + y;
        }
            break;
            
        case eYNearestTypeMiddle:
        {
            posY = y + ms_cDesignOffset.y;
        }
            break;
            
        default:
            break;
    }
    
    pNode->setPosition(Point(posX, posY));
    log("%f,%f",posX,posY);
}

Point MyVisibleRect::getPosition(float x, float y, eXNearestType xType, eYNearestType yType)
{
    
    ms_cVisibleSize = CCDirector::getInstance()->getVisibleSize();
    ms_cVisibleOrigin = CCDirector::getInstance()->getVisibleOrigin();
    log("%f,%f",ms_cDesignOffset.x,ms_cDesignOffset.y);
    log("%f,%f",ms_cVisibleSize.width,ms_cVisibleSize.height);
    float posX = 0;
    float posY = 0;
    
    // 设置x坐标
    switch (xType) {
        case eXNearestTypeNone:
        {
            posX = x;
        }
            break;
            
        case eXNearestTypeLeft:
        {
            posX = ms_cVisibleOrigin.x + x;
        }
            break;
            
        case eXNearestTypeRight:
        {
            posX = ms_cVisibleOrigin.x + ms_cVisibleSize.width - x;
        }
            break;
            
        case eXNearestTypeCenter:
        {
            posX = x + ms_cDesignOffset.x;
        }
            break;
            
        default:
            break;
    }
    
    // 设置y坐标
    switch (yType) {
        case eYNearestTypeNone:
        {
            posY = y;
        }
            break;
            
        case eYNearestTypeTop:
        {
            posY = ms_cVisibleOrigin.y + ms_cVisibleSize.height - y;
        }
            break;
            
        case eYNearestTypeBottom:
        {
            posY = ms_cVisibleOrigin.y + y;
        }
            break;
            
        case eYNearestTypeMiddle:
        {
            posY = y + ms_cDesignOffset.y;
        }
            break;
            
        default:
            break;
    }
    
    log("%f,%f",posX,posY);
    return Point(posX, posY);
}

Size MyVisibleRect::getDesignSize()
{
    return ms_cDesignSize;
}

Size MyVisibleRect::getFrameSize()
{
    return ms_cFrameSize;
}

Size MyVisibleRect::getRealDesignSize()
{
    return ms_cRealDesignSize;
}

float MyVisibleRect::getRealContentFactor()
{
    return ms_fRealContentFactor;
}

Point MyVisibleRect::getDesignOffset()
{
    return ms_cDesignOffset;
}

Point MyVisibleRect::getWoldOrigin()
{
    return ms_cWorldOrigin;
}
float MyVisibleRect::getRealDesignScale()
{
    return ms_fRealDesignScale;
}


