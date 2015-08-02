#ifndef __CHOOSEMAP_H__
#define __CHOOSEMAP_H__

#include "cocos2d.h"
#include "XMLParser.h"
#include "ChooseCharacter.h"
#include "PopScene.h"
#include "GameStartScene.h"
class ChooseMap : public cocos2d::Layer
{
private:
	cocos2d::CCMenuItemImage *map[6];
    string s;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    void backto(cocos2d::Ref* pSender);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void getArray(cocos2d::CCObject* obj);
    void storymode(cocos2d::CCObject* obj);
    void startGame(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(ChooseMap);
};

#endif // __HELLOWORLD_SCENE_H__
