
#ifndef __ShopLayer__
#define __ShopLayer__


#include "cocos2d.h"
#include "IAPItem.h"
#include "Heads.h"

USING_NS_CC;


class ShopLayer : public Layer
{
public:
    ShopLayer();
    ~ShopLayer();
    
    CREATE_FUNC(ShopLayer);
    
    virtual bool init();
    virtual void onEnter();
    
    void onItemClicked(int);
    
    void setExPath(const std::string&  path){m_sExPath = std::string(path);}
    std::string localPath(const std::string&  name){
        return m_sExPath+std::string(name);
    }
    
    std::function<void()>shopDismissed;
    int getPercent();
protected:
    virtual void _initData();
    
    void _showScrollBottom();
    void _showScrollBottomBack();
    void _dismiss();
    
//    FlowPageView* m_pPageView;
    ExpandScrollView* m_pScrollView;
    Vector<IAPItem*> m_ItemVector;
    Point m_InnerPosition;
    bool m_bIsScrolling;
    int m_nPercent;
    
    std::string m_sExPath;
};

#endif