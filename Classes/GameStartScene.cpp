#include "GameStartScene.h"
USING_NS_CC;

#define DIV0 100

unsigned int flag = 0;//0----wait for click hero, 1----clicked hero,wait for move, 2-----moved hero, wait for attack
position last_touch;
bool isempty;
vector<position> enemy_pos;
int AIflag = 0;//-1----no AI, 0----AI player1, 1---AI player2, 2---both AI
int win = 0; //1----player1 win, 2----player2 win
vector<position> last_pos;
vector<position> last_a_pos;
bool moved[10] = {false}; //if a hero has been moved in this round
int player = 0; //----------0 for player1, 1 for player2
int count_1 = 10, count_2 = 10; //----------count of heroes of player1 and 2
int AICount = 0;
int death_flag = 0;
int updateCount = 0;
string GameStartScene::restart = ""; 
string path = "images/fightstart/";
char *heroName[40] = { "caocao", "caiwenji", "caoren", "dianwei", "guojia", "xiahoudun", "xiahouyuan",
"xuchu", "zhangliao", "zhenbi", "sunquan", "chengpu", "daqiao", "huanggai", "lusu", "luxun", "sunce",
"taishici", "xiaoqiao", "zhouyu", "liubei", "guanyinping", "guanyu", "huangzhong", "machao", "weiyan",
"zhangfei", "zhangxingcai", "zhaoyun", "zhugeliang", "lvbu", "diaochan", "dongzhuo", "gongsunzan",
"liubiao", "liuzhang", "mateng", "yuanshao", "yuanshu", "zhanglu" };
GameStartScene::~GameStartScene(){
    MAP->~G_Map();
}
bool GameStartScene::init()
{
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("battle.wma");
	//开始播放背景音乐，true表示循环
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("battle.wma", true);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
        callfuncO_selector(GameStartScene::getArray), "StartMessage", NULL);
    //边栏背景
    auto *side = CCSprite::create(path + "side.png");
    side->setPosition(ccp(107, visibleSize.height / 2));
    this->addChild(side);

    auto *sprite1 = CCSprite::create(path + "cundang.png");
    auto *sprite1_1 = CCSprite::create(path + "cundang_selected.png");
    auto * sprite2 = CCSprite::create(path + "dudang.png");
    auto * sprite2_1 = CCSprite::create(path + "dudang_selected.png");
    auto *sprite3 = CCSprite::create(path + "bangzhu.png");
    auto *sprite3_1 = CCSprite::create(path + "bangzhu_selected.png");
    auto *sprite4 = CCSprite::create(path + "zhucaidan.png");
    auto *sprite4_1 = CCSprite::create(path + "zhucaidan_selected.png");
	auto *spriteJ = CCSprite::create(path + "jieshuhuihe.png");
	auto *spriteJ_1 = CCSprite::create(path + "jieshuhuiheselected.png");

    auto *cundang = CCMenuItemSprite::create(sprite1, sprite1_1, sprite1, this, menu_selector(GameStartScene::saveGame));
    auto *dudang = CCMenuItemSprite::create(sprite2, sprite2_1, sprite2, this, menu_selector(GameStartScene::loadGame));
    auto *bangzhu = CCMenuItemSprite::create(sprite3, sprite3_1, sprite3, this, menu_selector(GameStartScene::help));
    auto *zhucaidan = CCMenuItemSprite::create(sprite4, sprite4_1, sprite4, this, menu_selector(GameStartScene::backToMenu));
	auto *jieshuhuihe = CCMenuItemSprite::create(spriteJ, spriteJ_1, spriteJ, this, menu_selector(GameStartScene::switchPlayer));
    cundang->setScale(0.4f, 0.4f);
    dudang->setScale(0.4f, 0.4f);
    bangzhu->setScale(0.4f, 0.4f);
    zhucaidan->setScale(0.4f, 0.4f);

    cundang->setPosition(ccp(44, 150));
    dudang->setPosition(ccp(88, 150));
    bangzhu->setPosition(ccp(132, 150));
    zhucaidan->setPosition(ccp(176, 150));
	jieshuhuihe->setPosition(ccp(110, 300));
    CCMenu *menu = CCMenu::create(cundang, NULL);
    menu->addChild(dudang, NULL);
    menu->addChild(bangzhu, NULL);
    menu->addChild(zhucaidan, NULL);
	CCMenu *menu_J = CCMenu::create(jieshuhuihe, NULL);
	menu_J->setPosition(Point::ZERO);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
	this->addChild(menu_J, 1);

    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = [](Touch* touch, Event* event)->bool{
       // CCLOG("listener1 onTouchBegan");
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
    return loadMap();
}
bool doubleClick = false;
bool doubleClicked = false;
bool GameStartScene::loadMap(){
    MAP = new G_Map(18, 12, 64, 64);
    bool bRct = false;
    do
    {
        //CC_BREAK_IF(!CCScene::init());
        GamePlayLayer *pGamePlatLayer = GamePlayLayer::create(); 
        pGamePlatLayer->loadMap(mapIndex);

        CC_BREAK_IF(!MAP->get_layer());

        this->addChild(MAP->get_layer(), 1);

        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(GameStartScene::onTouchBegan, this);
        //	listener->onTouchEnded = CC_CALLBACK_2(GameStartScene::onTouchEnded, this);
        this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        bRct = true;
    } while (0);
    initGlobal();
    scheduleUpdate();
    return bRct;
}
bool GameStartScene::onTouchBegan(Touch *touch, Event *unused_event)
{
    auto touch_location = touch->getLocation();
    p1 = MAP->get_pos_of_point(Point(touch_location.x, touch_location.y));
    //CCLOG("%d %d", x, y);
	isempty = MAP->is_pos_empty(p1);
    if (doubleClick && !isempty){
		removeExistTag();
		popHeroTag(touch_location);
    }
	else if (!doubleClick && !doubleClicked) {
		removeExistTag();
        doubleClick = true;
        scheduleOnce(schedule_selector(GameStartScene::gameControl), 0.3f);
    }
    return true;
}
void GameStartScene::gameControl(float delay){
	doubleClick = false;
	if (doubleClicked){
		doubleClicked = false;
		return;
	}
	if (AIflag == player || AIflag == 2) {
		return;
	}
	doubleClicked = false;
	if (flag == 0) {       //wait for click hero
		if (isempty) {               //click a empty position, return wait for another right click
			return;
		}
		if (MAP->get_hero_on_pos(p1)->getTag() / 10 != player) {  //click a hero that is not a hero of this player, return wait for another right click
			return;
		}
		if (moved[MAP->get_hero_on_pos(p1)->getTag() % 10]) {          //click a hero already moved, return wait for another right click
			return;
		}
		if (!isempty) {           //click a hero, wait for move
			clickedHero();
			flag = 1;
			return;
		}
		else {
			return;
		}
	}


	if (flag == 1) {                          //already clicked hero  
		if (isempty) {                      //click a empty grid, move, flag = 2 wait for select attack
			if (moveHero()) {
				flag = 2;
			}
			else {                          //cannot move, cancel the click
				cancel();
				return;
			}
		}
		if (!isempty) {                      //click a not empty grid
			if (moved[MAP->get_hero_on_pos(p1)->getTag() % 10])  {    //click a hero that already moved, wrong click,skip
				return;
			}
			else if (p1 == last_touch) {                           //click self, just go straight
				flag = 2;
				unblendLastTouch();
			}
			else if (MAP->get_hero_on_pos(p1)->getTag() / 10 != player) {  //click a hero that is not a hero of this player, skip
				return;
			}
			else {                   //clicked another hero, exec anotherClick()
				anotherClick();
				return;
			}                      
		}
    }


	if (flag == 2) {                      //choose to attack or not
		if (chooseAttack()) {                  //choose a attack, change flag to 3, wait for attack
			flag = 3;
			return;
		}
		else {                             //give up attack or cannot attack, end move
			flag = 0;
			moved[MAP->get_hero_on_pos(p1)->getTag() % 10] = true;
			return;
		}
	}


	if (flag == 3) {                      //attack
		if (attack()) {                    //if attack successed, end this round of this hero
			flag = 0;
			moved[MAP->get_hero_on_pos(last_touch)->getTag() % 10] = true;
			unblendLastAPos();
		}
		else {                           //attack failed, wait for successful attack
			if (p1 == last_touch) {
				moved[MAP->get_hero_on_pos(last_touch)->getTag() % 10] = true;
				unblendLastAPos();
				flag = 0;
			}
		}
	}
	judgeWin();                       //judge if end
	if (win) {                       //end, exec winner event of player
		gameWonByPlayer(win);
	}
	return;
}
void GameStartScene::getArray(CCObject* obj){
    CCString *para = static_cast<CCString*>(obj);
    s = para->getCString();
    if (s.size() < 20){
        string heros;
        if (s[0] == '0'){
            heros = "0123456789:;=>CDFJLM";
        }
        else if (s[0] == '1'){
            heros = "0123456789NOPQRSTUVW";
        }
        else if (s[0] == '2'){
            heros = "0W23456789DEFGHIJKLM";
        }
        else if (s[0] == '3'){
            heros = "DFJ056@A=UQOPN8RSTVW";
        }
        else if (s[0] == '4'){
            heros = "0234567DFJ8OPN<B:A>?";
        }
        else if (s[0] == '5'){
            heros = "DEFGHIJKLM:;<=>?@ABC";
        }
        s = heros + s;
        AIflag = -1;
    }
    restart = s;
    addSprite(s);
}
void GameStartScene::addSprite(string s){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    char *mapNameList[6] = { "chibi", "guandu", "hanzhong", "hulaoguan", "xuzhou", "yiling" };
    int index = s[20] - '0';
    mapName = mapNameList[index];
    mapIndex = index;
    auto *name = CCSprite::create(path + mapName + "_column.png");
    name->setPosition(ccp(107, visibleSize.height - 200));
    this->addChild(name);
    for (int i = 0; i < 10; i++){
        string heroname = heroName[s[i] - '0'];
        GameSprite* s = GameSprite::create(heroname, 1);
        s->setTag(i);
        herolist_1.push_back(s);
        MAP->put_hero_on_pos(s, position(1, i + 1));
    }
    for (int j = 0; j < 10; j++){
        string heroname = heroName[s[j + 10] - '0'];
        GameSprite* s = GameSprite::create(heroname, 2);
        s->setTag(j + 10);
        herolist_2.push_back(s);
        MAP->put_hero_on_pos(s, position(16, j + 1));
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
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("battle.wma");
	//开始播放背景音乐，true表示循环
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("battle.wma", true);
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
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);
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
void GameStartScene::switchPlayer(Ref* pSender) {
	if (player == 0) {
		player = 1;
	}
	else if (player == 1) {
		player = 0;
	}
	for (int i = 0; i < 10; i++) {
		moved[i] = false;
	}
	unblendLastAPos();
	unblendLastTouch();
	flag = 0;
	AICount = 0;
}


void GameStartScene::clickedHero() {
	vector<position> movable_pos = MAP->get_movable_pos(p1);
	for (int i = 0; i < movable_pos.size(); i++) {
		MAP->blend_pos(movable_pos[i]);
	}
	last_touch = p1;
	last_pos = movable_pos;
}

void GameStartScene::anotherClick() {
	unblendLastTouch();
	clickedHero();
}

bool GameStartScene::moveHero() {
	if (find(last_pos.begin(), last_pos.end(), p1) == last_pos.end()) {//-------not movable
		return false;
	}
	MAP->move(last_touch, p1);
	unblendLastTouch();
	return true;
}

void GameStartScene::cancel() {
	flag--;
	if (flag == 0) {
		unblendLastTouch();
	}
}

bool GameStartScene::chooseAttack() {
	vector<position> poss = MAP->get_attackable_pos(p1);
	if (noEmptyPos(poss)) {
		return false;
	}
	else {
		for (int i = 0; i < poss.size(); i++) {
			MAP->a_blend_pos(poss[i]);
		}
		last_a_pos = poss;
		last_touch = p1;
		return true;
	}
}

bool GameStartScene::attack() {
	if (MAP->is_pos_empty(p1)) {
		return false;
	}
	if (MAP->get_hero_on_pos(p1)->getTag() / 10 == player) {
		return false;
	}
	if (MAP->attack(last_touch, p1)) {
		if (MAP->is_pos_empty(p1)) {
			count_1--;
		}
		return true;
	}
	return false;
}

void GameStartScene::unblendLastTouch() {
	for (int i = 0; i < last_pos.size(); i++) {
		MAP->unblend_pos(last_pos[i]);
	}
}


void GameStartScene::unblendLastAPos() {
	for (int i = 0; i < last_a_pos.size(); i++) {
		MAP->a_unblend_pos(last_a_pos[i]);
	}
}

bool GameStartScene::noEmptyPos(vector<position> ps) {
	bool tflag = true;
	for (int i = 0; i < ps.size(); i++) {
		if (!MAP->is_pos_empty(ps[i])) {
			CCLOG("his tag %d", MAP->get_hero_on_pos(ps[i])->getTag());
			if (MAP->get_hero_on_pos(ps[i])->getTag() / 10 != player)  {
				CCLOG("should out like this");
				tflag = false;
				break;
			}
		}
	}
	return tflag;
}

void GameStartScene::popHeroTag(Point touch_location) {
	CCLOG("showing tag");
	PopScene* pops = PopScene::create();
	doubleClick = false;
	doubleClicked = true;
	Size visibleSize = Director::getInstance()->getVisibleSize();
    int x, y;
    if (int(touch_location.x) < visibleSize.width - 128){
        int a = touch_location.x - 214;
        x = (a / 64 + 1) * 64 + 263;
    }
    else {
        int a = touch_location.x - 214;
        x = (a / 64) * 64 + 165;
    }
    if (touch_location.y > 64){
        y = (int(touch_location.y) / 64) * 64;
    }
    else {
        y = 64;
    }
    pops->setBg(path+"hero_popup.png", x, y);
	pops->setName("popwin");
	int tag = MAP->get_hero_on_pos(p1)->getTag();
	string name;
	char lifes[100] = { 0 };
	char magic[100] = { 0 };
	char attack[100] = { 0 };
	char defence[100] = { 0 };
    pops->setContent(XMLParser::parseXML("popuwindow", 1), x - 20, y + 20);
    pops->setContent(XMLParser::parseXML("popuwindow", 2), x - 20, y);
    pops->setContent(XMLParser::parseXML("popuwindow", 3), x - 20, y - 20);
    pops->setContent(XMLParser::parseXML("popuwindow", 4), x - 20, y - 40);
	if (tag < 10) {
        name = XMLParser::parseXML(herolist_1[tag]->get_type().get_name().c_str(), 1);
		//name = herolist_1[tag]->get_type().get_name();
        sprintf(lifes, "%.0lf", herolist_1[tag]->get_type().get_life());
		sprintf(magic, "%.0lf", herolist_1[tag]->get_type().get_magic());
		sprintf(attack, "%.0lf", herolist_1[tag]->get_type().get_D_attack());
		sprintf(defence, "%.0lf", herolist_1[tag]->get_type().get_D_defense());
	}
    else {
        name = XMLParser::parseXML(herolist_2[tag - 10]->get_type().get_name().c_str(), 1);
        sprintf(lifes, "%.0lf", herolist_2[tag - 10]->get_type().get_life());
        sprintf(magic, "%.0lf", herolist_2[tag - 10]->get_type().get_magic());
        sprintf(attack, "%.0lf", herolist_2[tag - 10]->get_type().get_D_attack());
        sprintf(defence, "%.0lf", herolist_2[tag - 10]->get_type().get_D_defense());
    }
	pops->setContent(name, x, y + 40);
    pops->setContent(lifes, x + 20, y + 20);
    pops->setContent(magic, x + 20, y);
    pops->setContent(attack, x + 20, y - 20);
    pops->setContent(defence, x + 20, y - 40);
	this->addChild(pops, 2);
}

void GameStartScene::removeExistTag() {
	if (getChildByName("popwin")){
		this->removeChildByName("popwin");
	}
}

void GameStartScene::AI() {
	enemy_pos.clear();
	for (int i = 0; i < MAP->get_width(); i++) {
		for (int j = 0; j < MAP->get_height(); j++) {
			position pos = position(i, j);
			if (!MAP->is_pos_empty(pos)) {
				if (MAP->get_hero_on_pos(pos)->getTag() / 10 != player) {
					enemy_pos.push_back(pos);
				}
			}
		}
	}
	for (int i = 0; i < MAP->get_width(); i++) {
		for (int j = 0; j < MAP->get_height(); j++) {
			position pos = position(i, j);
			if (MAP->is_valid_pos(pos) && !MAP->is_pos_empty(pos)) {
				if (MAP->get_hero_on_pos(pos)->getTag() / 10 == player && !moved[MAP->get_hero_on_pos(pos)->getTag() % 10]) {
					p1 = pos;
					CCLOG("startAI");
				}
			}
		}
	}
	endAI();
}

void GameStartScene::judgeWin() {
	if (count_1 == 0) {
		win = 2;
	}
	if (count_2 == 0) {
		win = 1;
	}
}
 
void GameStartScene::gameWonByPlayer(int player) {
	//do something
	CCLOG("gameWonByPlayer%d", player);
    if (getChildByName("popwins")){
        return;
    }
    //Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);
    PopScene* pops = PopScene::create();
    pops->setBg(path+"resultBg.png", -1, -1);
    pops->setScale(0.8f, 0.8f);
    pops->setName("popwins");
    if (player == 1){
        pops->setAnimation("left");
    }
    else {
        pops->setAnimation("right");
    }
    pops->yesButton(2);
    pops->yesButton(3);
    this->addChild(pops, 3);
}
void GameStartScene::AIStart(position p, vector<position> enemies) {
	last_touch = p;
	moved[MAP->get_hero_on_pos(last_touch)->getTag() % 10] = true;
	AIMove(p, enemies);
	//Sleep(10000);
	AIAttack(p1);
	AICount++;
}

void GameStartScene::AIMove(position p, vector<position> enemies) {
	p1 = getAIMovePos(p, enemies);
	MAP->move(last_touch, p1);
}

void GameStartScene::AIAttack(position p) {
	//do something
	CCLOG("begin attack");
	vector<position> attack_pos = MAP->get_attackable_pos(p);
	CCLOG("vector size: %d", attack_pos.size());
	position a_pos = position(-1, -1);
	int life_left = 9999;
	for (int i = 0; i < attack_pos.size(); i++) {
		if (MAP->is_valid_pos(attack_pos[i])) {
			if (!MAP->is_pos_empty(attack_pos[i])) {
				if (MAP->get_hero_on_pos(attack_pos[i])->getTag() / 10 != player) {
					if (MAP->get_hero_on_pos(attack_pos[i])->get_type().get_life() < life_left) {
						life_left = MAP->get_hero_on_pos(attack_pos[i])->get_type().get_life();
						a_pos = attack_pos[i];
					}
				}
			}
		}
	}
	int x = a_pos.x;
	int y = a_pos.y;
	CCLOG("attacking pos x: %d y: %d", x, y);
	if (a_pos == position(-1, -1)) {
		return;
	}
	else { 
		last_touch = p;
		p1 = a_pos;
		MAP->attack(last_touch, p1);
		if (MAP->is_pos_empty(p1)) {
			if (player == 0) {
				count_2--;
			}
			else {
				count_1--;
			}
		}
	}
}

void GameStartScene::endAI() {
	if (player == 0) {
		player = 1;
	}
	else if (player == 1) {
		player = 0;
	}
	for (int i = 0; i < 10; i++) {
		moved[i] = false;
	}
	AICount = 0;
}

position GameStartScene::getAIMovePos(position p, vector<position> enemies) {
	vector<position> move_pos = MAP->get_movable_pos(p);
	int max_attackable = 0, max_fix = 0, min_attackable = 99, min_fix = 0, min_life_left = 99999;
	for (int i = 0; i < move_pos.size(); i++) {
		int life = 99999;
		int attackable_count = attackableCount(move_pos[i], life);           //-----------------------get the attackable position after move
		if (attackable_count > max_attackable) {
			max_attackable = attackable_count;
			max_fix = i;
		}
		if (attackable_count != 0 && attackable_count < min_attackable) {
			min_attackable = attackable_count;
			min_fix = i;
		}
		else if (attackable_count == min_attackable && life < min_life_left) {  //-------------move to this can easily attack a deadly one
			min_fix = i;
		}
	}
	if (max_attackable == 0) {  //-------cannot attack anyone after move, move more efficient
		return AIMoveMostEfficient(p, enemies);
	}
	if (max_attackable > 0) {                            //------------can attack someone, then we move to the grid can attack as less as possible
		return move_pos[min_fix];
	}
}

int GameStartScene::attackableCount(position p, int& life_left) {
	int count = 0;
	if (p != last_touch) {                   //notice p can be itself
		MAP->move(last_touch, p);
	}
	vector<position> attack_pos = MAP->get_attackable_pos(p);
	for (int i = 0; i < attack_pos.size(); i++) {
		if (MAP->is_valid_pos(attack_pos[i]) && !MAP->is_pos_empty(attack_pos[i])) {
			if (MAP->get_hero_on_pos(attack_pos[i])->getTag() / 10 != player) {
				count++;
				if (life_left > MAP->get_hero_on_pos(attack_pos[i])->get_type().get_life()) {
					life_left = MAP->get_hero_on_pos(attack_pos[i])->get_type().get_life();
				}
			}
		}
	}
	if (p != last_touch) {
		MAP->move(p, last_touch);
	}
	return count;
}

position GameStartScene::AIMoveMostEfficient(position p, vector<position> enemies) {
	vector<position> move_pos = MAP->get_movable_pos(p);
	Point k0 = calVec(p, enemies);
	//k0.normalize();
	int x = k0.x;
	int y = k0.y;
	CCLOG("look at x: %d y: %d", x, y);
	int max = -1;
	int max_fix = 0;
	for (int i = 0; i < move_pos.size(); i++) {
		if (move_pos[i] == p) {
			continue;
		}
		Point k = move_pos[i] - p;
		//k.normalize();
		if (k0.dot(k) >= max) {
			int x1 = k.x;
			int y1 = k.y;
			CCLOG("look at x1: %d y1: %d", x1, y1);
			max = k0.dot(k);
			max_fix = i;
		}
	}
	return move_pos[max_fix];
}

Point GameStartScene::calVec(position p, vector<position> enemies) {
	int up = 0, right = 0;
	for (int i = 0; i < enemies.size(); i++) {
		up += enemies[i].y - p.y;
		right += enemies[i].x - p.x;
	}
	return Point(right, up);
}

void GameStartScene::update(float delta) {
	if (updateCount != 10) {
		updateCount++;
		return;
	}
	updateCount %= 10;
	if (death_flag > 0) {
		death_flag--;
		return;
	}
	if (player == AIflag || AIflag == 2) {
		initAI(AICount);
		judgeWin();
		if (win) {
			gameWonByPlayer(win);
		}
	}
	else {
		return;
	}
}

void GameStartScene::initAI(int count) {
	if (count == 0) {      //-----init enemy pos
		enemy_pos.clear();
		for (int i = 0; i < MAP->get_width(); i++) {
			for (int j = 0; j < MAP->get_height(); j++) {
				position pos = position(i, j);
				if (!MAP->is_pos_empty(pos)) {
					if (MAP->get_hero_on_pos(pos)->getTag() / 10 != player) {
						enemy_pos.push_back(pos);
					}
				}
			}
		}
	}
	for (int i = 0; i < MAP->get_width(); i++) {
		for (int j = 0; j < MAP->get_height(); j++) {
			position pos = position(i, j);
			if (MAP->is_valid_pos(pos) && !MAP->is_pos_empty(pos)) {
				if (MAP->get_hero_on_pos(pos)->getTag() / 10 == player && !moved[MAP->get_hero_on_pos(pos)->getTag() % 10]) {
					CCLOG("startAI TAG %d", MAP->get_hero_on_pos(pos)->getTag());
					AIStart(pos, enemy_pos);
					break;
				}
			}
		}
	}
	if (AICount == count_1 && player == 0) {
		endAI();
	}
	else if (AICount == count_2 && player == 1) {
		endAI();
	}
	return;
}

void GameStartScene::initGlobal() {
	flag = 0;//0----wait for click hero, 1----clicked hero,wait for move, 2-----moved hero, wait for attack
	enemy_pos.clear();
	//AIflag = -1;//-1----no AI, 0----AI player1, 1---AI player2, 2---both AI
	win = 0; //1----player1 win, 2----player2 win
	last_pos.clear();
	last_a_pos.clear();
	for (int i = 0; i < 10; i++) {
		moved[i] = false;
	}
	player = 0; //----------0 for player1, 1 for player2
	count_1 = 10;
	count_2 = 10; //----------count of heroes of player1 and 2
	AICount = 0;
	death_flag = 0;
	updateCount = 0;
}