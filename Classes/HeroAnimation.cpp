#include "HeroAnimation.h"

Animate* HeroAnimation::setAnimate(int begin, int end, string heroName){
    string s = "images/character/" + heroName + "/" + heroName + ".plist";
    CCLOG(s.c_str());
    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s);
    Vector<SpriteFrame* > heroArray;
    for (int index = begin; index <= end; ++index) {
        //从缓存中获取精灵帧添加到数组中
        char str[20]; 
        sprintf(str, "%s%d.png", heroName.c_str(), index);
        heroArray.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
    }  
    Animation *anima = Animation::createWithSpriteFrames(heroArray, 0.1f);
    anima->setDelayPerUnit(0.8f / 2.0f);
    Animate *attack = Animate::create(anima);
    return attack;
}