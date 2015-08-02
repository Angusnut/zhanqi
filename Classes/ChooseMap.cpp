#include "ChooseMap.h"
#include "SimpleAudioEngine.h"
#include "GameStartScene.h"
USING_NS_CC;

using namespace CocosDenshion;

Scene* ChooseMap::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = ChooseMap::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChooseMap::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ChooseMap::getArray), "2PMessage", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ChooseMap::storymode), "storyMessage", NULL);
    string path = "images/newGame/";
	char *mapName[6] = { "chibi", "guandu", "hanzhong", "hulaoguan", "xuzhou", "yiling"};
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //平铺背景
    auto *bg = CCSprite::create("images/background/bg_fight.png");
    bg->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(bg, -1);
    //标题
    auto *title = CCSprite::create(path + "map_choose.png");
    title->setPosition(ccp(visibleSize.width * 0.1, visibleSize.height * 0.9));
    this->addChild(title);
    title->setScale(1.4f, 1.4f);
    //hint
    string hints = XMLParser::parseXML("hintStrings", 3);
    CCLabelTTF *ttf = CCLabelTTF::create(hints, "【朦胧补】水黑体", 35);
    ttf->setPosition(ccp(visibleSize.width * 0.85, visibleSize.height * 0.87));
    this->addChild(ttf);
    //上一步
    auto* last = CCSprite::create(path+"last.png");
    last->setScale(1.4f, 1.4f);
    auto* last_selected = CCSprite::create(path + "last_selected.png");
    last_selected->setScale(1.4f, 1.4f);
    auto *Last = CCMenuItemSprite::create(last, last_selected, last, this, menu_selector(ChooseMap::backto));
    Last->setPosition(ccp(visibleSize.width - 200, 50));
    //开始游戏
    auto* begin = CCSprite::create(path + "begin.png");
    begin->setScale(1.4f, 1.4f);
    auto* begin_selected = CCSprite::create(path + "begin_selected.png");
    begin_selected->setScale(1.4f, 1.4f);
    auto *Begin = CCMenuItemSprite::create(begin, begin_selected, begin, this, menu_selector(ChooseMap::startGame));
    Begin->setPosition(ccp(visibleSize.width - 80, 50));

    auto *menu = CCMenu::create(Begin, NULL);
    menu->addChild(Last, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);

	auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event)->bool{
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
    listener->onTouchMoved = [](Touch* touch, Event* event){CCLOG("listener1 onTouchMoved"); };
    listener->onTouchEnded = [](Touch* touch, Event* event){
        CCMenuItemImage *target = static_cast< CCMenuItemImage*>(event->getCurrentTarget());
        if (target->isSelected()){
            target->unselected();
        }
        else {
	        SimpleAudioEngine::sharedEngine()->playEffect("select.wav",false);//开始播放背景音效，false表示不循环
            target->selected();
        }
    };
    for (int j = 0; j < 3; j++){
        for (int k = 0; k < 2; k++){
			int i = 3 * k + j;
            map[i] = CCMenuItemImage::create(path + mapName[i] + ".png", path + mapName[i] + "_selected.png");
            map[i]->setScale(0.5f, 0.5f);
            map[i]->setPosition(ccp(visibleSize.width * 0.25 * (j + 1), visibleSize.height * 0.32 * (2 - k)));
            this->addChild(map[i], 1);
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), map[i]);
        }
    }
    return true;
}  
void ChooseMap::getArray(CCObject* obj){
    CCString *para = static_cast<CCString*>(obj);
    s = para->getCString();
}
void ChooseMap::storymode(CCObject* obj){
    s = "";
}
void ChooseMap::startGame(Ref* pSender){
	SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav",false);//开始播放背景音效，false表示不循环
    int count = 0;
    string p = "";
    for (int i = 0; i < 6; i++){
        if (map[i]->isSelected()){
            p += i + '0';
            count++;
        }
    }
    if (count == 1){
        auto scene = GameStartScene::create();
        CCString *str = CCString::create(s + p);
        CCNotificationCenter::sharedNotificationCenter()->postNotification("StartMessage", str);
        Director::getInstance()->replaceScene(scene);
    }
    else {
        PopScene* pop = PopScene::create();
        pop->setPosition(ccp(0, 20));
        pop->setBg("images/popup/popWindow.png", -1, -1);
        pop->setContent(4);
        pop->noButton(0);
        //this->setTouchEnabled(false)
        Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);;
        this->addChild(pop, 2);
    }
}
void ChooseMap::backto(Ref* pSender){
	SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav",false);//开始播放背景音效，false表示不循环
    CCNotificationCenter::sharedNotificationCenter()->purgeNotificationCenter();
    if (s.size() > 1){
        auto scene = ChooseCharacter_2P::createScene();
        string substr = "";
        for (int i = 0; i < 10; i++){
            substr += s[i];
        }
        CCString *str = CCString::create(substr);
        CCNotificationCenter::sharedNotificationCenter()->postNotification("Message", str);
        // run
        Director::getInstance()->replaceScene(scene);
    }
    else {
        auto scene = ChooseMap::createScene();
        // run
        Director::getInstance()->replaceScene(scene);
    }
}

void ChooseMap::menuCloseCallback(Ref* pSender)
{
    CCNotificationCenter::sharedNotificationCenter()->purgeNotificationCenter();
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
