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

bool GamePlayLayer::init()
{
	return true;
}
void GamePlayLayer::loadMap(int mapIndex){
    if (mapIndex == 0){
        pTileMap = CCTMXTiledMap::create("chibi.tmx");
        pTileMap->setTag(0);
        CCLOG("mapIndex0");
    }
    else if (mapIndex == 1){
        pTileMap = CCTMXTiledMap::create("guandu.tmx");
        pTileMap->setTag(1);
        CCLOG("mapIndex1");
    }
    else if (mapIndex == 2){
        pTileMap = CCTMXTiledMap::create("hanzhong.tmx");
        pTileMap->setTag(2);
        CCLOG("mapIndex2");
    }
    else if (mapIndex == 3){
        pTileMap = CCTMXTiledMap::create("hulaoguan.tmx");
        pTileMap->setTag(3);
        CCLOG("mapIndex3");
    }
    else if (mapIndex == 4){
        pTileMap = CCTMXTiledMap::create("xuzhou.tmx");
        pTileMap->setTag(4);
        CCLOG("mapIndex4");
    }
    else{
        pTileMap = CCTMXTiledMap::create("yiling.tmx");
        pTileMap->setTag(5);
        CCLOG("mapIndex5");
    }
    setTileMap(pTileMap);
    CCLOG("%d", pTileMap->getTag());
    // ÉèÖÃ±³¾°²ã  
    this->setBackground(_tileMap->layerNamed("background"));
    winSize = CCDirector::sharedDirector()->getWinSize();
    mapSize = pTileMap->getContentSize();
    width_diff = 214;
    height_diff = 0;
    pTileMap->setPosition(ccp(214, 0));
    this->addChild(pTileMap);
    mapSize = pTileMap->getContentSize();

    map_width = mapSize.width;
    map_height = mapSize.height;
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {return true; };
    listener->onTouchEnded = CC_CALLBACK_2(GamePlayLayer::onTouchEnded, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
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
	//±ß½ç¼ì²â
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

