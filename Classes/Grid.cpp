#include "Grid.h"

Grid::Grid(Point lu_, Point ru_, Point ld_, Point rd_, string t) {
	lu = lu_;
	ru = ru_;
	ld = ld_;
	rd = rd_;
	terrain = t;
	hero = new GameSprite();
}

bool Grid::put(GameSprite* h_) {
	hero = h_;
	return true;
}

bool Grid::remove() {
	if (hero->get_type().get_name() == "sample") {
		cout << "no hero here!" << endl;
		return false;
	}
	else {
		hero = new GameSprite();
	}
	return true;
}

bool Grid::is_empty() {
	if (hero->get_type().get_name() == "sample") {
		return true;
	}
	else
		return false;
}

GameSprite* Grid::get_hero() {
	if (is_empty()) {
		cout << "no hero here!" << endl;
	}
	else
		return hero;
}

string Grid::get_terrain() {
	return terrain;
}

bool Grid::set_terrain(string s) {
	terrain = s;
	return true;
}

bool Grid::in_this_grid(Point p) {
	if (p.x >= lu.x && p.x < ru.x && p.y >= lu.y && p.y < ld.y)
		return true;
	return false;
}

Point Grid::get_left_up() {
	return lu;
}

Point Grid::get_left_down() {
	return ld;
}

Point Grid::get_right_up() {
	return ru;
}

Point Grid::get_right_down() {
	return rd;
}