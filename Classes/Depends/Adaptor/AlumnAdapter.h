

#ifndef __AlumnAdapter__
#define __AlumnAdapter__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class AlumnAdapter
{
public:
    //保存图片到相册
    static void saveToAlumn(Image* apCCImg,const std::function<void()>& callback);
    static void finished(bool isOK);
    static void saveFavFinished(bool isOK);
    
    static void loadData();
    static void deleteFavImage(int tag);
    static void saveFavData();
    static void saveToFav(Image* apCCImg,const std::function<void()>& callback);
    static void saveToFav(const char*name,Image* apCCImg,const std::function<void()>& callback);
//    static void saveToFav(const char*name,CCRenderTexture* apRT);
    static const char* getFavImagePathByID(int tag,std::string favName = "");
    static Image* getFavIconByID(int tag,std::string favName = "");
    static Image* getFavImageByID(int tag,std::string favName = "");
    static const char* getFavDataPathByID(int tag,std::string favName = "");
    static const char* getFavNameByID(int tag,std::string favName = "");
    static const char* getFavIconNameByID(int tag,std::string favName = "");

    static int getFavCount(std::string favName = "");
    
//    static std::function<void()> saveAlumnCallback;
//    static std::function<void()> saveFavCallback;
};

#endif /* defined(__AlumnAdapter__) */
