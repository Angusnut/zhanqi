#include "SpriteType.h"
void SpriteType::set_position(double x_, double y_)
{
	x = x_;
	y = y_;
}

string SpriteType::get_name()
{
	return name;
}

double SpriteType::get_x()
{
	return x;
}

double SpriteType::get_y()
{
	return y;
}

double SpriteType::get_fight_type()
{
	return fight_type;
}

double SpriteType::get_life()
{
	return current_life;
}

double SpriteType::get_magic()
{
	return current_magic;
}

double SpriteType::get_D_attack()
{
	return D_attack;
}

double SpriteType::get_P_attack()
{
	return P_attack;
}

double SpriteType::get_D_defense()
{
	return D_defense;
}

double SpriteType::get_P_defense()
{
	return P_defense;
}

SpriteType::SpriteType(string name_, double fight_type_, double life_, double magic_, double D_attack_, double P_attack_, double D_defense_, double P_defense_)
{
	name = name_;
	fight_type = fight_type_;
	current_life = life_;
	max_life = life_;
	current_magic = magic_;
	max_magic = magic_;
	D_attack = D_attack_;
	P_attack = P_attack_;
	D_defense = D_defense_;
	P_defense = P_defense_;
	x = 0;
	y = 0;

	initial_D_attack = D_attack_;
	initial_P_attack = P_attack_;
	initial_D_defense = D_defense_;
	initial_P_defense = P_defense_;
}

SpriteType::SpriteType()
{
	name = "sample";
	fight_type = 0;
	current_life = 0;
	max_life = 0;
	current_magic = 0;
	max_magic = 0;
	D_attack = 0;
	P_attack = 0;
	D_defense = 0;
	P_defense = 0;
}

void SpriteType::change_life(double life_)
{
	current_life = life_;
}


void SpriteType::change_magic(double magic_)
{
	current_magic = magic_;
}


void SpriteType::change_D_attack(double D_attack_)
{
	D_attack = D_attack_;
}

void SpriteType::change_P_attack(double P_attack_)
{
	P_attack = P_attack_;
}

void SpriteType::change_D_defense(double D_defense_)
{
	D_defense = D_defense_;
}

void SpriteType::change_P_defense(double P_defense_)
{
	P_defense = P_defense_;
}

void SpriteType::change_fight_type(double fight_type_)
{
	fight_type = fight_type_;
}

void SpriteType::change_value(double percent)
{
	D_attack = initial_D_attack * percent;
	P_attack = initial_P_attack * percent;
	D_defense = initial_D_defense * percent;
	P_defense = initial_P_defense * percent;
}






