#ifndef __HeroAnimation_H__
#define __HeroAnimation_H__
#include "cocos2d.h"
#include <iostream>
using namespace cocos2d;
using namespace std;
class HeroAnimation{
public:
    static Animate *setAnimate(int, int, string);
};
#endif 