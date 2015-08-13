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
    int flag = 0;
    if (width > 10000){
        flag = 1;
        width /= 10000;
    }
    mSize = CCDirector::sharedDirector()->getWinSize();
    mBg = CCSprite::create(s);
    if (width == -1){
        mBg->setPosition(ccp(mSize.width / 2, mSize.height / 2));
    }
    else {
        mBg->setPosition(ccp(width, height));
    }
    this->addChild(mBg);
    if (flag == 1){
        return;
    }
    CCSequence *popupActions = CCSequence::create(
        CCScaleTo::create(0.0, 0.0),
        CCScaleTo::create(0.06, 1.05),
        CCScaleTo::create(0.08, 0.95),
        CCScaleTo::create(0.08, 1.0), NULL);
    this->runAction(popupActions);
}
void registerWithTouchDispatcher(void){
    //使用int最小值做最高优先级  
    //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN, true);
}

void PopScene::setContent(int flag){
    string rules = XMLParser::parseXML("hintStrings", flag);
    CCLabelTTF* pLabel = CCLabelTTF::create(rules, "【朦胧补】水黑体", 20);
    pLabel->setPosition(ccp(mSize.width / 2, mSize.height / 2 + 40));
    pLabel->setTag(1);
    this->addChild(pLabel);
}
void PopScene::setContent(string s, int w, int h){
    CCLabelTTF* pLabel = CCLabelTTF::create(s, "【朦胧补】水黑体", 15);
    pLabel->setPosition(ccp(w, h));
    pLabel->setTag(1);
    this->addChild(pLabel);
}
void PopScene::removeContent(){
    this->removeChildByTag(1);
}
void PopScene::yesButton(int flag){
    CCMenuItemImage *pMenuItem;
    int b = 60;
    int c = 100;
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
    if (flag == 2){
        pMenuItem = CCMenuItemImage::create(
            "images/fightstart/backto.png",
            "images/fightstart/backto_selected.png",
            this,
            menu_selector(PopScene::onBack));
        c = -120;
        b = 120;
    }
    if (flag == 3){
        pMenuItem = CCMenuItemImage::create(
            "images/fightstart/restart.png",
            "images/fightstart/restart_selected.png",
            this,
            menu_selector(PopScene::onStart));
        SimpleAudioEngine::sharedEngine()->preloadEffect("voice/end.wav");
        SimpleAudioEngine::sharedEngine()->playEffect("voice/end.wav", false);
        c = 120;
        b = 120;
    }

	if (flag == 4){
		pMenuItem = CCMenuItemImage::create(
			"images/popup/yesbutton.png",
			"images/popup/yesbutton_selected.png",
			this,
			menu_selector(PopScene::onLoad));
	}

    pMenuItem->setPosition(ccp(mSize.width / 2 - c, mSize.height / 2 - b));
    CCMenu* pMenu = CCMenu::create(pMenuItem, NULL);
    pMenu->setPosition(Point::ZERO);
    this->addChild(pMenu);
}
void PopScene::setAnimation(string s){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite *sprite = Sprite::create("singlePoint.png");
    sprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    Animate *animation = HeroAnimation::setUIAnimate(1, 5, s);
    sprite->runAction(animation);
    this->addChild(sprite, 4);
}
void PopScene::noButton(int flag){
    CCMenuItemImage *pMenuItem = CCMenuItemImage::create(
        "images/popup/nobutton.png",
        "images/popup/nobutton_selected.png",
        this,
        menu_selector(PopScene::onOK));
    if (flag == 2){
        pMenuItem = CCMenuItemImage::create(
            "images/popup/yesbutton.png",
            "images/popup/yesbutton_selected.png",
            this,
            menu_selector(PopScene::onOK));
    };
    if (flag == 0 || flag == 2){
        pMenuItem->setPosition(ccp(mSize.width / 2, mSize.height / 2 - 60));
    }
    else if (flag == 1){
        pMenuItem->setPosition(ccp(mSize.width / 2 + 100, mSize.height / 2 - 60));
    }
    CCMenu* pMenu = CCMenu::create(pMenuItem, NULL);
    pMenu->setPosition(Point::ZERO);
    this->addChild(pMenu);
    myflag = 0;
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
    //CCNotificationCenter::sharedNotificationCenter()->postNotification("backMessage", NULL);
    //this->release();
    auto scene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(scene);
    this->removeFromParentAndCleanup(true);
}
void PopScene::onStart(CCObject* pSender)
{
    CCNotificationCenter::sharedNotificationCenter()->purgeNotificationCenter();
    SimpleAudioEngine::sharedEngine()->preloadEffect("anniu.wav");
    SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav", false);//开始播放背景音效，false表示不循环
    Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent(), true);
    //CCNotificationCenter::sharedNotificationCenter()->postNotification("backMessage", NULL);
    //this->release();
    CCString *str = CCString::create(GameStartScene::restart);
    auto scene = GameStartScene::create();
   // CCNotificationCenter::sharedNotificationCenter()->postNotification("2PMessage", str);
	scene->addSprite(GameStartScene::restart);
    Director::getInstance()->replaceScene(scene);
    this->removeFromParentAndCleanup(true);
}

void PopScene::onLoad(CCObject* pSender)
{
	CCNotificationCenter::sharedNotificationCenter()->purgeNotificationCenter();
	SimpleAudioEngine::sharedEngine()->preloadEffect("anniu.wav");
	SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav", false);//开始播放背景音效，false表示不循环
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent(), true);
	//CCNotificationCenter::sharedNotificationCenter()->postNotification("backMessage", NULL);
	//this->release();
	//CCString *str = CCString::create(GameStartScene::restart);
    archive::open_archive(0);
    XMLParser::map_id = archive::get_map();
    //CCLOG("map_id :::::: %d", x.get_map());
	auto scene = GameStartScene::create();
	// CCNotificationCenter::sharedNotificationCenter()->postNotification("2PMessage", str);
	scene->new_addSprite();
	Director::getInstance()->replaceScene(scene);
	this->removeFromParentAndCleanup(true);
}

PopScene:: ~PopScene(){
}
void PopScene::onExit(CCObject* pSender)
{
    Director::getInstance()->end();
}