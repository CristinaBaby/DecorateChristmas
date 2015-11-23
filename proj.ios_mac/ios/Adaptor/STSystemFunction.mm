/*
 * STSystemFunction.cpp
 *
 *  Created on: 2013-9-2
 *      Author: Steven.Xc.Tian
 */
#include "STSystemFunction.h"
#include "SystemFunctionIOSWrapper.h"
//#include "AboutUsPage.h"

STSystemFunction::STSystemFunction()
{
}
STSystemFunction::~STSystemFunction()
{
}

void STSystemFunction::sendEmail(const char* subject, const char* body)
{
    [[SystemFunctionManager sharedManager]sendEmail : [NSString stringWithCString:subject encoding:NSUTF8StringEncoding]
                                             Content:[NSString stringWithCString:body encoding:NSUTF8StringEncoding]];
}

void STSystemFunction::popAlertDialog(const char* message)
{
    [[SystemFunctionManager sharedManager]popAlertDialog:[NSString stringWithCString:message encoding:NSUTF8StringEncoding]];
}

void STSystemFunction::showMoreGame()
{
    [[SystemFunctionManager sharedManager]showMorePage];
}
void STSystemFunction::rating()
{
}
void STSystemFunction::go2MarketDetail(std::string packagename)
{
}
void STSystemFunction::contactUs()
{
}

void STSystemFunction::sendEmailAndAssetPic(std::string subject, std::string message, std::string assetName)
{
}
void STSystemFunction::sendEmailAndFilePic(std::string subject, std::string message,std::string fileName)
{
    [[SystemFunctionManager sharedManager]sendEmailWithPic:[NSString stringWithCString:subject.c_str() encoding:NSUTF8StringEncoding] Content:[NSString stringWithCString:message.c_str() encoding:NSUTF8StringEncoding] Path:[NSString stringWithCString:fileName.c_str() encoding:NSUTF8StringEncoding]];
}
std::string STSystemFunction::getSdCardPath()
{
	return "";
}

bool STSystemFunction::checkNetworkAvailable()
{
    return true;
}

bool STSystemFunction::isTabletAvailable()
{
    
    CGRect frame = [[UIScreen mainScreen] applicationFrame];
    if (UIInterfaceOrientationIsLandscape([[UIApplication sharedApplication] statusBarOrientation])) {
        CGFloat width = MAX(frame.size.height, frame.size.width);
        CGFloat height = MIN(frame.size.height, frame.size.width);
        frame = CGRectMake(0, 0, width, height);
    }
    return MIN(frame.size.height, frame.size.width)>700?true:false;

}
float STSystemFunction::densityScale()
{
	return 1;
}
void STSystemFunction::makeToast(const char* message)
{
	
}

void STSystemFunction::rateUs(){
    [[SystemFunctionManager sharedManager] rateUs];
}
void STSystemFunction::dismissRateUs(){
//	SystemFunctionManager::getInstance()->dismissRateUs();
}

void STSystemFunction::saveImage(std::string fileCache,Ref* selector,CallFunction callback){
}

void STSystemFunction::saveToAlumn(cocos2d::Image *apCCImg,const std::function<void(bool)>& callback)
{
    [[SystemFunctionManager sharedManager]saveToAlbum:apCCImg withCallback:callback];
}

void STSystemFunction::goToPrivacy()
{

}

void STSystemFunction::showNewsBlast()
{
    CCLOG("%s", __func__);
    [[SystemFunctionManager sharedManager] showNewsBlast];
}


void STSystemFunction::showNewsBlast(NewsBlastMode mode){
    [[SystemFunctionManager sharedManager] showNewsBlast];
}

void STSystemFunction::endAnalytics()
{
    CCLOG("%s", __func__);
}

void STSystemFunction::refreshDCIM(std::string sFileDir)
{
    CCLOG("%s", __func__);
}
