#include "GameStartScene.h"
USING_NS_CC;
bool flag = false;
position last_touch;
bool isempty;
GameStartScene::GameStartScene(void)
{
}
GameStartScene::~GameStartScene(void)
{
	MAP.~G_Map();
	exit(0);
}
bool GameStartScene::init()
{
	bool bRct = false;
    string path = "images/fightstart/";
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
        callfuncO_selector(GameStartScene::getArray), "StartMessage", NULL);
	do
	{
		CC_BREAK_IF(!CCScene::init());

		GamePlayLayer *pGamePlatLayer = GamePlayLayer::create();
		CC_BREAK_IF(!MAP.get_layer());

		this->addChild(MAP.get_layer(), 1);

        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(GameStartScene::onTouchBegan, this);
        //	listener->onTouchEnded = CC_CALLBACK_2(GameStartScene::onTouchEnded, this);
        this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		bRct = true;
	} while (0);
    //边栏背景
    auto *side = CCSprite::create(path + "side.png");
    side->setPosition(ccp(108, visibleSize.height / 2));
    this->addChild(side);

    auto *sprite1 = CCSprite::create(path + "cundang.png");
    auto *sprite1_1 = CCSprite::create(path + "cundang_selected.png");
    auto * sprite2 = CCSprite::create(path + "dudang.png");
    auto * sprite2_1 = CCSprite::create(path + "dudang_selected.png");
    auto *sprite3 = CCSprite::create(path + "bangzhu.png");
    auto *sprite3_1 = CCSprite::create(path + "bangzhu_selected.png");
    auto *sprite4 = CCSprite::create(path + "zhucaidan.png");
    auto *sprite4_1 = CCSprite::create(path + "zhucaidan_selected.png");

    auto *cundang = CCMenuItemSprite::create(sprite1, sprite1_1, sprite1, this, menu_selector(GameStartScene::saveGame));
    auto *dudang = CCMenuItemSprite::create(sprite2, sprite2_1, sprite2, this, menu_selector(GameStartScene::loadGame));
    auto *bangzhu = CCMenuItemSprite::create(sprite3, sprite3_1, sprite3, this, menu_selector(GameStartScene::help));
    auto *zhucaidan = CCMenuItemSprite::create(sprite4, sprite4_1, sprite4, this, menu_selector(GameStartScene::backToMenu));

    cundang->setScale(0.4f, 0.4f);
    dudang->setScale(0.4f, 0.4f);
    bangzhu->setScale(0.4f, 0.4f);
    zhucaidan->setScale(0.4f, 0.4f);

    cundang->setPosition(ccp(44, 150));
    dudang->setPosition(ccp(88, 150));
    bangzhu->setPosition(ccp(132, 150));
    zhucaidan->setPosition(ccp(176, 150));
    CCMenu *menu = CCMenu::create(cundang, NULL);
    menu->addChild(dudang, NULL);
    menu->addChild(bangzhu, NULL);
    menu->addChild(zhucaidan, NULL);
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
    music->setPosition(ccp(170, 50));
    this->addChild(music, 1);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), music);

	return bRct; 
}
bool doubleClick = false;
bool doubleClicked = false;
bool GameStartScene::onTouchBegan(Touch *touch, Event *unused_event)
{
    auto touch_location = touch->getLocation();
    p1 = MAP.get_pos_of_point(Point(touch_location.x, touch_location.y));
    int x = p1.x;
    int y = p1.y;
    CCLOG("%d %d", x, y);

    isempty = MAP.get_grids()[p1.y][p1.x].is_empty();
    if (doubleClick && !isempty){
        if (getChildByName("popwin")){
            this->removeChildByName("popwin");
        }
        PopScene* pops = PopScene::create();
        doubleClick = false;   
        doubleClicked = true;
        Size visibleSize = Director::getInstance()->getVisibleSize();
        pops->setBg("images/fightstart/heropopup.png", touch_location.x + 64, touch_location.y - 80);
        pops->setName("popwin");
        int tag = MAP.get_hero_on_pos(p1)->getTag();
        string name = herolist[tag]->get_type().get_name();
        pops->setContent(name, touch_location.x + 64, touch_location.y - 25);
        char lifes[100] = { 0 };
        sprintf(lifes, "HP: %.0lf", herolist[tag]->get_type().get_life());
        pops->setContent(lifes, touch_location.x + 64, touch_location.y - 50);
        char magic[100] = { 0 };
        sprintf(magic, "MP: %.0lf", herolist[tag]->get_type().get_magic());
        pops->setContent(magic, touch_location.x + 64, touch_location.y - 75);
        char attack[100] = { 0 };
        sprintf(attack, "Attack: %.0lf", herolist[tag]->get_type().get_D_attack());
        pops->setContent(attack, touch_location.x + 64, touch_location.y - 100);
        char defence[100] = { 0 };
        sprintf(defence, "Defence: %.0lf", herolist[tag]->get_type().get_D_defense());
        pops->setContent(defence, touch_location.x + 64, touch_location.y - 125);
        this->addChild(pops, 2);
    }
    if (!doubleClick && !doubleClicked) {
        if (getChildByName("popwin")){
            this->removeChildByName("popwin");
        }
        doubleClick = true;
        scheduleOnce(schedule_selector(GameStartScene::clickHero), 0.3f);
    }
    doubleClicked = false;
    return true;
}
void GameStartScene::clickHero(float delay){
    doubleClick = false;
    if (!isempty){
        position up = MAP.get_up_pos(p1);
        position down = MAP.get_down_pos(p1);
        position left = MAP.get_left_pos(p1);
        position right = MAP.get_right_pos(p1);
        if (up.x != -1 && up.y != -1){
            MAP.blend_pos(up);
        }
        if (down.x != -1 && down.y != -1){
            MAP.blend_pos(down);
        }
        if (left.x != -1 && left.y != -1){
            MAP.blend_pos(left);
        }
        if (right.x != -1 && right.y != -1){
            MAP.blend_pos(right);
        }
        last_touch = p1;
        flag = true;
        CCLOG("I can be move");
    }
    if (isempty && flag == true){
        position up = MAP.get_up_pos(last_touch);
        position down = MAP.get_down_pos(last_touch);
        position left = MAP.get_left_pos(last_touch);
        position right = MAP.get_right_pos(last_touch);
        CCLOG("I have to move");
        flag = false;
        MAP.move(last_touch, p1);
        MAP.unblend_pos(last_touch);
        MAP.unblend_pos(up);
        MAP.unblend_pos(down);
        MAP.unblend_pos(left);
        MAP.unblend_pos(right);
    }
}
void GameStartScene::getArray(CCObject* obj){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    CCString *para = static_cast<CCString*>(obj);
    s = para->getCString();
    int index = s[20] - '0';
    char *heroName[40] = { "caocao", "caiwenji", "caoren", "dianwei", "guojia", "xiahoudun", "xiahouyuan",
        "xuchu", "zhangliao", "zhenbi", "sunquan", "chengpu", "daqiao", "huanggai", "lusu", "luxun", "sunce",
        "taishici", "xiaoqiao", "zhouyu", "liubei", "guanyinping", "guanyu", "huangzhong", "machao", "weiyan",
        "zhangfei", "zhangxingcai", "zhaoyun", "zhugeliang", "lvbu", "diaochan", "dongzhuo", "gongsunzan",
        "liubiao", "liuzhang", "mateng", "yuanshao", "yuanshu", "zhanglu" };
    char *mapNameList[6] = { "chibi", "guandu", "hanzhong", "hulaoguan", "xuzhou", "yiling" };
    mapName = mapNameList[index];
    auto *name = CCSprite::create("images/fightstart/"+mapName+"_column.png");
    name->setPosition(ccp(108, visibleSize.height - 200));
    this->addChild(name);
    for (int i = 0; i < 10; i++){
        string heroname = heroName[s[i] - '0'];
        GameSprite* s = GameSprite::create(heroname, 1);
        s->setTag(i);
        herolist.push_back(s);
        MAP.put_hero_on_pos(s, position(1, i+1));
    }
    for (int j = 0; j < 10; j++){
        string heroname = heroName[s[j+10] - '0'];
        GameSprite* s = GameSprite::create(heroname, 2);
        s->setTag(j + 10);
        herolist.push_back(s);
        MAP.put_hero_on_pos(s, position(16, j + 1));
    }
}
void GameStartScene::saveGame(Ref* pSender){
    SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav", false);//开始播放背景音效，false表示不循环
}
void GameStartScene::loadGame(Ref* pSender){
    SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav", false);//开始播放背景音效，false表示不循环
}
void GameStartScene::help(Ref* pSender){
    SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav", false);//开始播放背景音效，false表示不循环
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto scene = Help::create();
    auto s = CCString::create("fight");
    CCNotificationCenter::sharedNotificationCenter()->postNotification("HelpMessage", s);
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);;
    this->addChild(scene, 5);
}
void GameStartScene::backToMenu(Ref* pSender){
    CCNotificationCenter::sharedNotificationCenter()->purgeNotificationCenter();
    SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav", false);//开始播放背景音效，false表示不循环
    PopScene* pop = PopScene::create();
    pop->setBg("images/popup/popWindow.png", -1, -1);
    pop->setPosition(ccp(0, 20));
    pop->setContent(5);
    pop->noButton(1);
    pop->yesButton(0);
    //this->setTouchEnabled(false)
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);;
    this->addChild(pop, 6);
}
void GameStartScene::menuCloseCallback(Ref* pSender)
{
    CCNotificationCenter::sharedNotificationCenter()->purgeNotificationCenter();
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
