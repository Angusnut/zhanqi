#include "ChooseCharacter_2P.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

using namespace CocosDenshion;

Scene* ChooseCharacter_2P::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = ChooseCharacter_2P::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;

}

// on "init" you need to initialize your instance
bool ChooseCharacter_2P::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, 
            callfuncO_selector(ChooseCharacter_2P::getArray), "Message", NULL);

    string path = "images/newGame/";
    string heropath = "images/country/";

    char *heroName[40] = { "caocao", "caiwenji", "caoren", "dianwei", "guojia", "xiahoudun", "xiahouyuan",
        "xuchu", "zhangliao", "zhenbi", "sunquan", "chengpu", "daqiao", "huanggai", "lusu", "luxun", "sunce",
        "taishici", "xiaoqiao", "zhouyu", "liubei", "guanyinping", "guanyu", "huangzhong", "machao", "weiyan",
        "zhangfei", "zhangxingcai", "zhaoyun", "zhugeliang", "lvbu", "diaochan", "dongzhuo", "gongsunzan",
        "liubiao", "liuzhang", "mateng", "yuanshao", "yuanshu", "zhanglu" };
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //平铺背景
    auto *bg = CCSprite::create("images/background/bg_fight.png");
    bg->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(bg, -1);
    //标题
    auto *title = CCSprite::create(path + "character_choose.png");
    title->setPosition(ccp(visibleSize.width * 0.1, visibleSize.height * 0.9));
    this->addChild(title);
    title->setScale(1.4f, 1.4f);

    auto *player = CCSprite::create(path + "2P.png");
    player->setPosition(ccp(visibleSize.width * 0.25, visibleSize.height * 0.9));
    this->addChild(player);
    player->setScale(1.2f, 1.2f);

    string hints = XMLParser::parseXML("hintStrings", 2);
    CCLabelTTF *ttf = CCLabelTTF::create(hints, "【朦胧补】水黑体", 35);
    ttf->setPosition(ccp(visibleSize.width * 0.85, visibleSize.height * 0.9));
    this->addChild(ttf);

    //确认
    auto* back = CCSprite::create(path +  "last.png");
    back->setScale(1.4f, 1.4f);
    auto* back_selected = CCSprite::create(path +  "last_selected.png");
    back_selected->setScale(1.4f, 1.4f);
    auto *Back = CCMenuItemSprite::create(back, back_selected, back, this, menu_selector(ChooseCharacter_2P::backto));
    Back->setPosition(ccp(visibleSize.width - 240, 50));
    //退出
    auto* next = CCSprite::create(path + "next.png");
    next->setScale(1.4f, 1.4f);
    auto* next_selected = CCSprite::create(path + "next_selected.png");
    next_selected->setScale(1.4f, 1.4f);
    auto *Next = CCMenuItemSprite::create(next, next_selected, next, this, menu_selector(ChooseCharacter_2P::nextto));
    Next->setPosition(ccp(visibleSize.width - 100, 50));

    auto *menu = CCMenu::create(Next, NULL);
    menu->addChild(Back, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);

    auto *wei = CCSprite::create(path + "wei.png");
    wei->setPosition(ccp(visibleSize.width * 0.17, visibleSize.height * 0.75));
    this->addChild(wei);
    wei->setScale(3.0f, 3.0f);

    auto *shu = CCSprite::create(path + "shu.png");
    shu->setPosition(ccp(visibleSize.width * 0.61, visibleSize.height * 0.75));
    this->addChild(shu);
    shu->setScale(3.0f, 3.0f);

    auto *wu = CCSprite::create(path + "wu.png");
    wu->setPosition(ccp(visibleSize.width * 0.39, visibleSize.height * 0.75));
    this->addChild(wu);
    wu->setScale(3.0f, 3.0f);
    auto *qun = CCSprite::create(path + "qun.png");
    qun->setPosition(ccp(visibleSize.width * 0.83, visibleSize.height * 0.75));
    this->addChild(qun);
    qun->setScale(3.0f, 3.0f);
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
    for (int j = 0; j < 4; j++){
        for (int k = 0; k < 2; k++){
            for (int l = 0; l < 5; l++){
                int i = l + j * 10 + k * 5;
                auto *temp = CCSprite::create(heropath + heroName[i] + "_disable.png");
                temp->setScale(2.0f, 2.0f);
                temp->setPosition(ccp(visibleSize.width * (0.12 + 0.1*k + 0.22*j), visibleSize.height * (0.6 - 0.1*l)));
                this->addChild(temp, 0);

                hero[i] = CCMenuItemImage::create(heropath + heroName[i] + ".png", heropath + heroName[i] + "_selected.png");
                hero[i]->setScale(2.0f, 2.0f);
                hero[i]->setPosition(ccp(visibleSize.width * (0.12 + 0.1*k + 0.22*j), visibleSize.height * (0.6 - 0.1*l)));
                this->addChild(hero[i], 1);
                _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), hero[i]);
            }
        }
    }
    return true;
}
void ChooseCharacter_2P::backto(Ref* pSender){
	SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav",false);//开始播放背景音效，false表示不循环
    CCNotificationCenter::sharedNotificationCenter()->purgeNotificationCenter();
    auto scene = ChooseCharacter::createScene();
    // run
    Director::getInstance()->replaceScene(scene);
}
void ChooseCharacter_2P::getArray(CCObject* obj){

    char *heroName[40] = { "caocao", "caiwenji", "caoren", "dianwei", "guojia", "xiahoudun", "xiahouyuan",
        "xuchu", "zhangliao", "zhenbi", "sunquan", "chengpu", "daqiao", "huanggai", "lusu", "luxun", "sunce",
        "taishici", "xiaoqiao", "zhouyu", "liubei", "guanyinping", "guanyu", "huangzhong", "machao", "weiyan",
        "zhangfei", "zhangxingcai", "zhaoyun", "zhugeliang", "lvbu", "diaochan", "dongzhuo", "gongsunzan",
        "liubiao", "liuzhang", "mateng", "yuanshao", "yuanshu", "zhanglu" };
    str = static_cast<CCString*>(obj);
    s = str->getCString();
    CCLOG(s.c_str());
    for (int i = 0; i < 10; i++){
        p[i] = s[i] - '0';
        hero[p[i]]->setVisible(false);
        _eventDispatcher->removeEventListenersForTarget(hero[p[i]], true);
    }
}
void ChooseCharacter_2P::nextto(Ref* pSender){
	SimpleAudioEngine::sharedEngine()->playEffect("anniu.wav",false);//开始播放背景音效，false表示不循环

    // 定义一个弹出层，传入一张背景图片
    //MessageBox("this is content", "title");
    char *heroName[40] = { "caocao", "caiwenji", "caoren", "dianwei", "guojia", "xiahoudun", "xiahouyuan",
        "xuchu", "zhangliao", "zhenbi", "sunquan", "chengpu", "daqiao", "huanggai", "lusu", "luxun", "sunce",
        "taishici", "xiaoqiao", "zhouyu", "liubei", "guanyinping", "guanyu", "huangzhong", "machao", "weiyan",
        "zhangfei", "zhangxingcai", "zhaoyun", "zhugeliang", "lvbu", "diaochan", "dongzhuo", "gongsunzan",
        "liubiao", "liuzhang", "mateng", "yuanshao", "yuanshu", "zhanglu" };
    int count = 0;
    string p2 = "";
    for (int i = 0; i < 40; i++){
        if (hero[i]->isSelected()){
            p2 += i + '0';
            count++;
        }
    }
    if (count == 10){
        auto scene = ChooseMap::createScene();
        str = CCString::create(s+p2);
        CCNotificationCenter::sharedNotificationCenter()->postNotification("2PMessage", str);
        Director::getInstance()->replaceScene(scene);
    }
    else {
        PopScene* pop = PopScene::create();
        pop->setPosition(ccp(0, 20));
        pop->setBg("images/popup/popWindow.png", -1, -1);
        pop->setContent(1);
        pop->noButton(0);
        //this->setTouchEnabled(false)
        Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);;
        this->addChild(pop, 2);
    }
}

void ChooseCharacter_2P::menuCloseCallback(Ref* pSender)
{  
    CCNotificationCenter::sharedNotificationCenter()->purgeNotificationCenter();
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
