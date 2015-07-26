#include "PopScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
bool PopScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    return true;
}
void PopScene::setBg(string s, int width, int height){
    mSize = CCDirector::sharedDirector()->getWinSize();
    mBg = CCSprite::create(s);
    if (width == -1){
        mBg->setPosition(ccp(mSize.width / 2, mSize.height / 2));
    }
    else {
        mBg->setPosition(ccp(width, height));
    }
    this->addChild(mBg);
}
void registerWithTouchDispatcher(void){
    //使用int最小值做最高优先级  
    //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN, true);
}

void PopScene::setContent(int flag){
    string rules = XMLParser::parseXML("hintStrings", flag);
    CCLabelTTF* pLabel = CCLabelTTF::create(rules, "【朦胧补】水黑体", 20);
    pLabel->setPosition(ccp(mSize.width / 2, mSize.height / 2 + 40));
    this->addChild(pLabel);
}
void PopScene::setContent(string s, int w, int h){
    CCLabelTTF* pLabel = CCLabelTTF::create(s, "【朦胧补】水黑体", 15);
    pLabel->setPosition(ccp(w, h));
    this->addChild(pLabel);
}
void PopScene::yesButton(int flag){
    CCMenuItemImage *pMenuItem;
    if (flag == 0){
        pMenuItem = CCMenuItemImage::create(
            "images/popup/yesbutton.png",
            "images/popup/yesbutton_selected.png",
            this,
            menu_selector(PopScene::onBack));
    }
    if (flag == 1){
       pMenuItem = CCMenuItemImage::create(
            "images/popup/yesbutton.png",
            "images/popup/yesbutton_selected.png",
            this,
            menu_selector(PopScene::onExit));
    }
    pMenuItem->setPosition(ccp(mSize.width / 2 - 100, mSize.height / 2 - 60));
    CCMenu* pMenu = CCMenu::create(pMenuItem, NULL);
    pMenu->setPosition(Point::ZERO);
    this->addChild(pMenu);
}
void PopScene::noButton(int flag){
    CCMenuItemImage *pMenuItem = CCMenuItemImage::create(
        "images/popup/nobutton.png",
        "images/popup/nobutton_selected.png",
        this,
        menu_selector(PopScene::onOK));
    if (flag == 0){
        pMenuItem->setPosition(ccp(mSize.width / 2, mSize.height / 2 - 60));
    }
    else if (flag == 1){
        pMenuItem->setPosition(ccp(mSize.width / 2 + 100, mSize.height / 2 - 60));
    }
    CCMenu* pMenu = CCMenu::create(pMenuItem, NULL);
    pMenu->setPosition(Point::ZERO);
    this->addChild(pMenu);
}
void PopScene::onOK(CCObject* pSender)
{
    CCNotificationCenter::sharedNotificationCenter()->purgeNotificationCenter();
    SimpleAudioEngine::sharedEngine()->preloadEffect("anniu.wav");
    SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav", false);//开始播放背景音效，false表示不循环
    Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent(), true); 
    this->removeFromParentAndCleanup(true);
}
void PopScene::onBack(CCObject* pSender)
{
    CCNotificationCenter::sharedNotificationCenter()->purgeNotificationCenter();
    SimpleAudioEngine::sharedEngine()->preloadEffect("anniu.wav");
    SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav", false);//开始播放背景音效，false表示不循环
    Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent(), true); 
    this->removeFromParentAndCleanup(true);
    auto scene = HelloWorld::createScene();
    Director::getInstance()->pushScene(scene);
    //Director::getInstance()->replaceScene(scene);
}
void PopScene::onExit(CCObject* pSender)
{
    Director::getInstance()->end();
}