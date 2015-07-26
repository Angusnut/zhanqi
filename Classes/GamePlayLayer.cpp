#include "GamePlayLayer.h"
using namespace std;
//#include "GameOverScene.h"
USING_NS_CC;
int GamePlayLayer::object_id = 0;
float map_width;
float map_height;
float scale;
CCSize winSize;
CCSize mapSize;
GamePlayLayer::GamePlayLayer(void)
	: _tileMap(NULL), _background(NULL)
{
}


GamePlayLayer::~GamePlayLayer(void)
{
}

bool GamePlayLayer::init()
{
	bool bRct = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		// 1、地图
		// 设置地图
		pTileMap = CCTMXTiledMap::create("map.tmx");
		CC_BREAK_IF(!pTileMap);
		setTileMap(pTileMap);
		// 设置背景层  
	    this->setBackground(_tileMap->layerNamed("background"));

        CC_BREAK_IF(!_background);

		//this->setBackground(_tileap->layerNamed("mask"));
		//CC_BREAK_IF(!_mask);

		//this->setBackground(_tileMap->layerNamed("foreground"));
		//CC_BREAK_IF(!_foreground);
		//blend->setColor(ccWHITE);
		//blend->setPosition(300, 300);


		 winSize = CCDirector::sharedDirector()->getWinSize();
		 mapSize =pTileMap->getContentSize();

			//缩放地图到合适屏幕大小
			//scale = winSize.height / pTileMap->getContentSize().height;
			//pTileMap->setScale(scale);

			//将地图放到屏幕中间
			width_diff = 216;
			height_diff = 0;
			pTileMap->setPosition(ccp(216,0));
			this->addChild(pTileMap);
			mapSize = pTileMap->getContentSize();

			map_width = mapSize.width;
			map_height = mapSize.height;
		bRct = true;
		//2、创建和显示玩家精灵
		// 创建精灵1
		/*CCSprite *pSpritePlayer = CCSprite::create("rev1.png");
		CC_BREAK_IF(!pSpritePlayer);
		this->setPlayerSprite(pSpritePlayer);
		_pPlayerSprite->setPosition(ccp(550, 200));
		// 将玩家精灵添加至图层
		this->addChild(_pPlayerSprite);
	//	setViewPointCenter(_pPlayerSprite->getPosition());
		//创建精灵2
		CCSprite *pSpritePlayer2 = CCSprite::create("rev3.png");
		CC_BREAK_IF(!pSpritePlayer2);
		this->setPlayerSprite(pSpritePlayer2);
		pSpritePlayer2->setPosition(ccp(600, 200));
		// 将玩家精灵添加至图层
		this->addChild(pSpritePlayer2);*/

		
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {return true; };
		listener->onTouchEnded = CC_CALLBACK_2(GamePlayLayer::onTouchEnded, this);
		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);




	} while (0);

	return bRct;
}
/*
void GamePlayLayer::setViewPointCenter(Point position) {
	auto winSize = Director::getInstance()->getWinSize();


	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	auto actualPosition = Point(x, y);


	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;
	//this->setPosition(viewPoint);
}
*/
void GamePlayLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	auto actionTo1 = RotateTo::create(0, 0, 180);
	auto actionTo2 = RotateTo::create(0, 0, 0);
	auto touchLocation = touch->getLocation();
	CCLOG("%d %d", touchLocation.x, touchLocation.y);
	touchLocation = this->convertToNodeSpace(touchLocation);


	//auto playerPos = _pPlayerSprite->getPosition();
	//auto diff = touchLocation - playerPos;
	//playerPos.x = touchLocation.x;
	//playerPos.y = touchLocation.y;
	//边界检测
	if (
		touchLocation.x >= ((winSize.width - mapSize.width *scale) / 2) && touchLocation.x<(winSize.width-((winSize.width - mapSize.width *scale) / 2)) &&
		touchLocation.y >= ((winSize.height - mapSize.height *scale) / 2) && touchLocation.y< (winSize.height - ((winSize.height - mapSize.height *scale) / 2)))
	{
		
		//if (object_id == 3 || object_id == 4)
		//this->setPlayerPosition(playerPos);
		//object_id = 0;
	}


	//this->setViewPointCenter(_pPlayerSprite->getPosition());
}

