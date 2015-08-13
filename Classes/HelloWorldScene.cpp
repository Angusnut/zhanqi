#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	//预加载背景音乐
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("game.wma");
   //开始播放背景音乐，true表示循环
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("game.wma",true);
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
	// 先默认播放背景音乐


    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //平铺背景 
    //CCTexture2D *texture = Director::getInstance()->getTextureCache()->addImage("background.png");
    //CCTexture2D::TexParams tp = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
    //texture->setTexParameters(tp);
    //auto sprite = Sprite::createWithTexture(texture, Rect(0, 0, visibleSize.width, visibleSize.height));
    //sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    //this->addChild(sprite, 0);
    auto *bg = CCSprite::create("images/background/bg_mainMenu.png");
    bg->setPosition(ccp(visibleSize.width / 2, visibleSize.height/2));
    this->addChild(bg, -1);
    //游戏名  
    auto *title = CCSprite::create("gameName.png");
    title->setPosition(ccp(visibleSize.width / 2 - 10, visibleSize.height - 250));
    this->addChild(title);
    title->setScale(1.4f, 1.4f);

    //游戏菜单
    string path = "images/mainMenu/";
    auto *sprite1 = CCSprite::create(path + "newGame.png");
    sprite1->setScale(1.3f, 1.3f);
    auto *sprite1_1 = CCSprite::create(path + "newGame_selected.png");
    sprite1_1->setScale(1.3f, 1.3f);
    auto * sprite2 = CCSprite::create(path + "loadGame.png");
    sprite2->setScale(1.3f, 1.3f);
    auto * sprite2_1 = CCSprite::create(path + "loadGame_selected.png");
    sprite2_1->setScale(1.3f, 1.3f);
    auto *sprite3 = CCSprite::create(path + "help.png");
    sprite3->setScale(1.3f, 1.3f);
    auto *sprite3_1 = CCSprite::create(path + "help_selected.png");
    sprite3_1->setScale(1.3f, 1.3f);
    auto *sprite4 = CCSprite::create(path + "exitGame.png");
    sprite4->setScale(1.3f, 1.3f);
    auto *sprite4_1 = CCSprite::create(path + "exitGame_selected.png");
    sprite4_1->setScale(1.3f, 1.3f);

    auto *newGame = CCMenuItemSprite::create(sprite1, sprite1_1, sprite1, this, menu_selector(HelloWorld::newFun));
    auto *loadGame = CCMenuItemSprite::create(sprite2, sprite2_1, sprite2, this, menu_selector(HelloWorld::loadFun));
    auto *helpGame = CCMenuItemSprite::create(sprite3, sprite3_1, sprite3, this, menu_selector(HelloWorld::helpFun));
    auto *exitGame = CCMenuItemSprite::create(sprite4, sprite4_1, sprite4, this, menu_selector(HelloWorld::quitFun));
    newGame->setPosition(ccp(visibleSize.width / 2 - 20, visibleSize.height - 400));
    loadGame->setPosition(ccp(visibleSize.width / 2 - 20, visibleSize.height - 460));
    helpGame->setPosition(ccp(visibleSize.width / 2 - 20, visibleSize.height - 520));
    exitGame->setPosition(ccp(visibleSize.width / 2 - 20, visibleSize.height - 580));
    CCMenu *menu = CCMenu::create(newGame, NULL);
    menu->addChild(loadGame, NULL);
    menu->addChild(helpGame, NULL);
    menu->addChild(exitGame, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

	auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = [](Touch* touch, Event* event)->bool{
        CCLOG("listener1 onTouchBegan");
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        if (rect.containsPoint(locationInNode)){//判断触摸点是否在目标的范围内
            return true;
        }
        else
            return false;
    };

	listener1->onTouchMoved = [](Touch* touch, Event* event){CCLOG("listener1 onTouchMoved"); };
    listener1->onTouchEnded = [](Touch* touch, Event* event){
        CCMenuItemImage *target = static_cast< CCMenuItemImage*>(event->getCurrentTarget());
        if (target->isSelected()){
            target->unselected();
			SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();//暂停背景音乐
        }
        else {
            target->selected();
			SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();//继续背景音乐
		}
    };
    auto *music = CCMenuItemImage::create(path + "openVolice.png", path + "closeVolice.png");
    music->setPosition(ccp(visibleSize.width * 0.95, visibleSize.height * 0.12));
	this->addChild(music, 1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), music);
    //     
      
    //Animate *attack = HeroAnimation::setAnimate(5, 8, "huangzhong");
    //auto heard_sp = Sprite::create("singlePoint.png");
    //heard_sp->setPosition(Point(visibleSize.width / 2, visibleSize.height - 200));
    //heard_sp->runAction(RepeatForever::create(attack));//播放动画
    //this->addChild(heard_sp, 2);

    //
    //会动的小人
    for (int k = 0; k < 2; k++){
        char s[100] = { 0 };
        int l;
        if (k == 0){
            sprintf(s, "images/character/caocao/run");
            l = visibleSize.height*0.05;
        }
        else{
            sprintf(s, "images/character/caocao/rev");
            l = visibleSize.height*0.95;
        }
        for (int i = 1; i < visibleSize.width; i += 50){
            char str[100] = { 0 };
            sprintf(str, "%s1.png", s);
            CCSprite* player = CCSprite::create(str);
            player->setPosition(ccp(i + 25, l));
            this->addChild(player);
            auto animation = Animation::create();
            for (int j = 1; j <= 4; j++)
            {
                char szName[100] = { 0 };
                sprintf(szName, "%s%d.png", s, j);
                animation->addSpriteFrameWithFile(szName);
            }
            animation->setDelayPerUnit(0.8f / 4.0f);
            animation->setRestoreOriginalFrame(true);
            auto action = Animate::create(animation);
            player->runAction(CCRepeatForever::create(action));
        }
    }
    return true;
}
void HelloWorld::newFun(cocos2d::Ref* pSender){
	SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav",false);//开始播放背景音效，false表示不循环
    auto scene = NewGame::createScene();
    // run
    Director::getInstance()->replaceScene(scene);
};
void HelloWorld::helpFun(cocos2d::Ref* pSender){
	SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav",false);//开始播放背景音效，false表示不循环
    auto scene = Help::createScene();
    auto s = CCString::create("main");
    CCNotificationCenter::sharedNotificationCenter()->postNotification("HelpMessage", s);
    // run
    Director::getInstance()->replaceScene(scene);

};
void HelloWorld::loadFun(cocos2d::Ref* pSender){
	SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav",false);//开始播放背景音效，false表示不循环
    //auto scene = GameStartScene::create();
    // run
   // Director::getInstance()->replaceScene(scene);

	PopScene* pop = PopScene::create();
	pop->setBg("images/popup/popWindow.png", -1, -1);
	pop->setPosition(ccp(0, 20));
	pop->setContent(9);
	pop->noButton(1);
	pop->yesButton(4);
	//this->setTouchEnabled(false)
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);
	this->addChild(pop, 6);
};

void HelloWorld::quitFun(cocos2d::Ref* pSender){
    CCNotificationCenter::sharedNotificationCenter()->purgeNotificationCenter();
    SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav", false);//开始播放背景音效，false表示不循环
    PopScene* pop = PopScene::create();
    pop->setPosition(ccp(0, 20));
    pop->setBg("images/popup/popWindow.png", -1, -1);
    pop->setContent(7);
    pop->noButton(1);
    pop->yesButton(1);
    //this->setTouchEnabled(false)
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);;
    this->addChild(pop, 6);
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav",false);//开始播放背景音效，false表示不循环
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
