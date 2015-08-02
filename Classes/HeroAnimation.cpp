#include "HeroAnimation.h"

Animate* HeroAnimation::setAnimate(int begin, int end, string heroName){
    string s = "images/character/" + heroName + "/" + heroName + ".plist";
    CCLOG(s.c_str());
    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s);
    Vector<SpriteFrame* > heroArray;
    for (int index = begin; index <= end; ++index) {
        //从缓存中获取精灵帧添加到数组中
        char str[100];
        sprintf(str, "%s%d.png", heroName.c_str(), index);
        heroArray.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
    }
    Animation *anima = Animation::createWithSpriteFrames(heroArray, 0.1f);
    anima->setLoops(-1);
    anima->setDelayPerUnit(0.8f / 2.0f);
    Animate *attack = Animate::create(anima);
    CCLOG(s.c_str());
    return attack;
}
Animate* HeroAnimation::setAnimate(int begin, int end, string heroName, string type){
    string s;
    if (type == "attack"){
        s = "images/character/" + heroName + "/" + heroName + "_melee.plist";
        heroName = heroName + "_melee";
    }
    else if (type == "dead"){
        s = "images/character/" + heroName + "/" + heroName + "_dead.plist";
        heroName = heroName + "_dead";
    }
    CCLOG(s.c_str());
    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s);
    Vector<SpriteFrame* > heroArray;
    for (int index = begin; index <= end; ++index) {
        //从缓存中获取精灵帧添加到数组中
        char str[100];
        sprintf(str, "%s%d.png", heroName.c_str(), index);
        heroArray.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
    }
    Animation *anima = Animation::createWithSpriteFrames(heroArray, 0.1f);
    anima->setDelayPerUnit(0.8f / 4.0f);
    Animate *attack = Animate::create(anima);
    return attack;
}
Animate* HeroAnimation::setUIAnimate(int begin, int end, string name){
    string s = "images/fightstart/" + name+".plist";
    CCLOG(s.c_str());
    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s);
    Vector<SpriteFrame* > array;
    for (int index = begin; index <= end; ++index) {
        //从缓存中获取精灵帧添加到数组中
        char str[100];
        sprintf(str, "%s%d.png", name.c_str(), index);
        array.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
    }
    Animation *anima = Animation::createWithSpriteFrames(array, 0.1f);
    anima->setDelayPerUnit(0.8f / 8.0f);
    Animate *attack = Animate::create(anima);
    CCLOG(s.c_str());
    return attack;
}