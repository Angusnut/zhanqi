#ifndef __NEWGAME_H__
#define __NEWGAME_H__

#include "cocos2d.h"
#include "XMLParser.h"
#include "ChooseCharacter.h"
class NewGame : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void backFun(cocos2d::Ref* pSender);
    void fightFun(cocos2d::Ref* pSender);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(NewGame);
};

#endif // __HELLOWORLD_SCENE_H__
