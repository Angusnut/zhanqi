#include "Help.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

using namespace CocosDenshion;

Scene* Help::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = Help::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance


bool Help::init()
{

    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, 
        callfuncO_selector(Help::getArray), "HelpMessage", NULL);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //背景
    auto *bg = CCSprite::create("images/background/bg_help.png");
    bg->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(bg, -1);
    
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("help.wma");
   //开始播放背景音乐，true表示循环
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("help.wma",true);
	//游戏规则
    string path = "images/help/";
    //string ssssss = path + "game_rules.png";
    //CCLOG("cao");
    auto* rules = CCSprite::create(path + "game_rules.png");
    auto* rules_selected = CCSprite::create(path + "game_rules_selected.png");
    auto* characters = CCSprite::create(path + "character_introduction.png");
    auto* characters_selected = CCSprite::create(path + "character_introduction_selected.png");
    auto* skills = CCSprite::create(path + "skill_introduction.png");
    auto* skills_selected = CCSprite::create(path + "skill_introduction_selected.png");
    auto* maps = CCSprite::create(path + "map_introduction.png");
    auto* maps_selected = CCSprite::create(path + "map_introduction_selected.png");
    auto* backs = CCSprite::create("back.png");
    auto* backs_selected = CCSprite::create("back_selected.png");
	//游戏规则监听器
    auto *gameRule = CCMenuItemSprite::create(rules, rules_selected, rules, this, menu_selector(Help::ruleFun));
    auto *gameChar = CCMenuItemSprite::create(characters, characters_selected, characters, this, menu_selector(Help::characterFun));
    auto *gameSkill = CCMenuItemSprite::create(skills, skills_selected, skills, this, menu_selector(Help::skillFun));
    auto *gameMap = CCMenuItemSprite::create(maps, maps_selected, maps, this, menu_selector(Help::mapFun));
    auto *gameBack = CCMenuItemSprite::create(backs, backs_selected, backs, this, menu_selector(Help::backto));
    gameRule->setScale(1.4f, 1.4f);
    gameChar->setScale(1.4f, 1.4f);
    gameSkill->setScale(1.4f, 1.4f);
    gameMap->setScale(1.4f, 1.4f);
    gameBack->setScale(1.4f, 1.4f);
    gameRule->setPosition(ccp(visibleSize.width / 2 - 20, visibleSize.height - 200));
    gameChar->setPosition(ccp(visibleSize.width / 2 - 20, visibleSize.height - 300));
    gameSkill->setPosition(ccp(visibleSize.width / 2 - 20, visibleSize.height - 400));
    gameMap->setPosition(ccp(visibleSize.width / 2 - 20, visibleSize.height - 500));
    gameBack->setPosition(ccp(visibleSize.width - 80, 50));
    auto *menu = CCMenu::create(gameRule, NULL);
    menu->addChild(gameChar, NULL);
    menu->addChild(gameSkill, NULL);
    menu->addChild(gameMap, NULL);
    menu->addChild(gameBack, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);
    return true;
}
void Help::getArray(cocos2d::CCObject* obj){
    CCString *str = static_cast<CCString*>(obj);
    s = str->getCString();  
}
void Help::ruleFun(cocos2d::Ref* pSender){
	SimpleAudioEngine::sharedEngine()->preloadEffect("anniu.wav");
	SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav",false);//开始播放背景音效，false表示不循环
    Helpscene::flag = 1;
    auto scene = Helpscene::create();
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);;
    this->addChild(scene, 5);
}

void Help::characterFun(cocos2d::Ref* pSender){
	SimpleAudioEngine::sharedEngine()->preloadEffect("anniu.wav");
	SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav",false);//开始播放背景音效，false表示不循环
    Helpscene::flag = 2;
    auto scene = Helpscene::create();
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);;
    this->addChild(scene, 5);
}
void Help::skillFun(cocos2d::Ref* pSender){
	SimpleAudioEngine::sharedEngine()->preloadEffect("anniu.wav");
	SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav",false);//开始播放背景音效，false表示不循环
    Helpscene::flag = 3;
    auto scene = Helpscene::create();
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);;
    this->addChild(scene, 5);
}
void Help::mapFun(cocos2d::Ref* pSender){
	SimpleAudioEngine::sharedEngine()->preloadEffect("anniu.wav");
	SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav",false);//开始播放背景音效，false表示不循环
    Helpscene::flag = 4;
    auto scene = Helpscene::create();
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);;
    this->addChild(scene, 5);
}
void Help::backto(cocos2d::Ref* pSender){
    CCNotificationCenter::sharedNotificationCenter()->purgeNotificationCenter();
    SimpleAudioEngine::sharedEngine()->preloadEffect("anniu.wav");
    SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav", false);//开始播放背景音效，false表示不循环
    if (s == "main"){
        auto scene = HelloWorld::createScene();
        Director::getInstance()->replaceScene(scene);
    }
    else {
        Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent(), true);
        this->removeFromParentAndCleanup(true);
    }
    // run

};
void Help::menuCloseCallback(Ref* pSender)
{
    CCNotificationCenter::sharedNotificationCenter()->purgeNotificationCenter();
	SimpleAudioEngine::sharedEngine()->preloadEffect("anniu.wav");
	SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav",false);//开始播放背景音效，false表示不循环
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
