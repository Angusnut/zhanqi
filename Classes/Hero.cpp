#include "Hero.h"

Hero::Hero(string s,string f) {
	name = s;
	file = f;
	sprite = Sprite::create(f);
}
int Hero::mapindex = -1;
Hero::Hero() {
	name = "";
}