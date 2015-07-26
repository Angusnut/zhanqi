#include "Help.h"
#include "HelloWorldScene.h"
#include "XMLParser.h"
#include "Helpscene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

using namespace CocosDenshion;

int Helpscene::flag = 0;
Scene* Helpscene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = Helpscene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance


bool Helpscene::init()
{

    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //背景
    auto *bg = CCSprite::create("images/background/bg_help.png");
    bg->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(bg, -1);
     
	string rules = XMLParser::parseXML("introduction", flag);
	CCLabelTTF *ttf = CCLabelTTF::create("", "【朦胧补】水黑体", 40, CCSizeMake(visibleSize.width - 50, visibleSize.height - 50), kCCTextAlignmentLeft);
	ttf->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(ttf, 1); 
	ttf->setString(rules);

    //返回
    auto* back = CCSprite::create("back.png");
    back->setScale(1.4f, 1.4f);
    auto* back_selected = CCSprite::create("back_selected.png");
    back_selected->setScale(1.4f, 1.4f);
    auto *gameBack = CCMenuItemSprite::create(back, back_selected, back, this, menu_selector(Helpscene::backto));
    gameBack->setPosition(ccp(visibleSize.width - 80, 50));
    auto *menu = CCMenu::create(gameBack, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);
    return true;
}

void Helpscene::backto(Ref* pSender){
	SimpleAudioEngine::sharedEngine()->preloadEffect("anniu.wav");
	SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav",false);//开始播放背景音效，false表示不循环
    Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent(), true);
    this->removeFromParentAndCleanup(true);
}

void Helpscene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
