#include "NewGame.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* NewGame::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = NewGame::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool NewGame::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //平铺背景
    auto *bg = CCSprite::create("images/background/bg_fight.png");
    bg->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(bg, -1);

    //两种模式
    //对战模式
    string path = "images/newGame/";
    auto* fightmode = CCSprite::create(path + "fight_mode.png");
    fightmode->setScale(1.4f, 1.4f);
    auto* fightmode_selected = CCSprite::create(path + "fight_mode_selected.png");
    fightmode_selected->setScale(1.4f, 1.4f);
    auto *fightMode = CCMenuItemSprite::create(fightmode, fightmode_selected, fightmode, this, menu_selector(NewGame::fightFun));
    fightMode->setPosition(ccp(visibleSize.width / 2 - 20, visibleSize.height - 300));
    //故事模式
    auto* storymode = CCSprite::create(path + "story_mode.png");
    storymode->setScale(1.4f, 1.4f);
    auto* storymode_selected = CCSprite::create(path + "story_mode_selected.png");
    storymode_selected ->setScale(1.4f, 1.4f);
    auto *storyMode = CCMenuItemSprite::create(storymode, storymode_selected, storymode, this, menu_selector(NewGame::backFun));
    storyMode->setPosition(ccp(visibleSize.width / 2 - 20, visibleSize.height - 400));
    //退出
    auto *back = CCSprite::create("back.png");
    back->setScale(1.4f, 1.4f); 
    auto *back_selected = CCSprite::create("back_selected.png");
    back_selected->setScale(1.4f, 1.4f);
    auto *gameBack = CCMenuItemSprite::create(back, back_selected, back, this, menu_selector(NewGame::backFun));
    gameBack->setPosition(ccp(visibleSize.width - 80, 50));

    auto *menu = CCMenu::create(gameBack, NULL);
    menu->addChild(fightMode, NULL);
    menu->addChild(storyMode, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);
    
    //string str = XMLParser::parseXML("node", 5);
    //auto *ttf1 = CCLabelTTF::create(str, "【朦胧补】水黑体", 20.0, Size(320, 0), TextHAlignment::LEFT);
    //ttf1->setPosition(ccp(visibleSize.width / 2, visibleSize.height - 500));
    //this->addChild(ttf1, 2);
    return true;
}

void NewGame::fightFun(Ref* pSender){
	SimpleAudioEngine::sharedEngine()->preloadEffect("anniu.wav");
	SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav",false);//开始播放背景音效，false表示不循环
    auto scene = ChooseCharacter::createScene();
    Director::getInstance()->replaceScene(scene);
}
void NewGame::backFun(Ref* pSender){
    SimpleAudioEngine::sharedEngine()->preloadEffect("anniu.wav");
    SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav", false);//开始播放背景音效，false表示不循环
    auto scene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(scene);
}
void NewGame::menuCloseCallback(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->preloadEffect("anniu.wav");
	SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav",false);//开始播放背景音效，false表示不循环
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
