#ifndef __CHOOSECHARACTER_H__
#define __CHOOSECHARACTER_H__

#include "cocos2d.h"
#include "XMLParser.h"
#include "NewGame.h"
#include "ChooseCharacter_2P.h"
#include "PopScene.h"
#include <string>
using namespace std;
class ChooseCharacter : public cocos2d::Layer
{
private:
    cocos2d::CCMenuItemImage *hero[40];
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void backto(cocos2d::Ref* pSender);

    void nextto(cocos2d::Ref* pSender);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(ChooseCharacter);
};

#endif // __HELLOWORLD_SCENE_H__
