#include "G_Map.h"

G_Map::G_Map(int w, int h, int gw, int gh) {
	//of.open("map.log");
	cols = w;
	rows = h;
	gwid = gw;
	ghei = gh;
	width = cols * gwid;
	height = rows * ghei;
	gplayer = GamePlayLayer::create();
	width_diff = gplayer->width_diff;
	height_diff = gplayer->height_diff;
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			Point lu = Point(width_diff + i * gwid, height_diff + j * ghei);
			Point ld = Point(width_diff + i * gwid, height_diff + (j + 1) * ghei);
			Point ru = Point((width_diff + i + 1) * gwid, height_diff + j * ghei);
			Point rd = Point((width_diff + i + 1) * gwid, height_diff + (j + 1) * ghei);
			if (i == 0) {
				vector<Grid> temp;
				Grid tmp = Grid(lu, ru, ld, rd, "water");
				temp.push_back(tmp);
				grids.push_back(temp);
			}
			Grid tmp = Grid(lu, ru, ld, rd, "water");
			grids[j].push_back(tmp);
		}
	}
	//of << s << endl;
	//of.close();
	//gplayer->MAP = this;
}

G_Map::~G_Map() {
	for (int i = 0; i < grids.size(); i++) {
		grids[i].clear();
	}
	//	gplayer->~GamePlayLayer();
	//	delete gplayer;
}

bool G_Map::is_valid(Point p) {
	p.x -= width_diff;
	p.y -= height_diff;
	if (p.x >= 0 && p.x < width && p.y > 0 && p.y < height) {
		return true;
	}
	else
		return false;
}

bool G_Map::is_valid_pos(position p) {
	if (p.x >= 0 && p.x < cols && p.y >= 0 && p.y < rows) {
		return true;
	}
	else
		return false;
}

bool G_Map::is_empty() {
	if (grids.size() == 0) {
		return true;
	}
	else
		return false;
}

position G_Map::get_pos_of_point(Point p) {
	if (!is_valid(p))
		return position(-1, -1);
	p.x -= width_diff;
	p.y -= height_diff;
	int col_count = p.x / gwid;
	int row_count = p.y / ghei;
	return position(col_count, row_count);
}

Point G_Map::get_center_of_pos(position p) {
	int x = ((double)p.x + 0.5) * gwid + width_diff;
	int y = ((double)p.y + 0.5) * ghei + height_diff;
	return Point(x, y);
}

GameSprite* G_Map::get_hero_on_pos(position p) {
	GameSprite* tmp = grids[p.y][p.x].get_hero();
	return tmp;
}

bool G_Map::put_hero_on_pos(GameSprite* h, position p) {
	if (!is_valid_pos(p)) {
		//cout << "not a valid pos!" << endl;
		CCLOG("not a valid pos!");
		return false;
	}
	grids[p.y][p.x].put(h);
	gplayer->addChild(h);
	h->setPosition(((double)p.x + 0.5) * gwid + width_diff, ((double)p.y + 0.5) * ghei + height_diff);
	h->get_type().set_position(p.x, p.y);
	return true;
}

bool G_Map::move(position ps, position pe) {
	if (!is_valid_pos(ps) || !is_valid_pos(pe)) {
		int x = pe.x;
		int y = pe.y;
		CCLOG("%d %d", x, y);
		cout << "not a valid pos!" << endl;
		return false;
	}
	if (grids[ps.y][ps.x].is_empty()) {
		cout << "no hero there!" << endl;
		return false;
	}
	if (!grids[pe.y][pe.x].is_empty()) {
		cout << "already hero there!" << endl;
		return false;
	}
	grids[ps.y][ps.x].get_hero()->setPosition(get_center_of_pos(pe));
	
	grids[pe.y][pe.x].put(grids[ps.y][ps.x].get_hero());
	grids[ps.y][ps.x].remove();
	return true;
}

bool G_Map::remove(position p) {
	if (!is_valid_pos(p)) {
		cout << "not a valid pos!" << endl;
		return false;
	}
	if (grids[p.y][p.x].is_empty()) {
		cout << "no hero here!" << endl;
		return false;
	}
	grids[p.y][p.x].remove();
	return true;
}

std::string G_Map::get_terrain(position p) {
	p.y = rows - 1 - p.y;
	if (!is_valid_pos(p)) {
		cout << "not a valid pos!" << endl;
		return "";
	}
	std::string str;
	int gid = gplayer->pTileMap->getLayer("background")->getTileGIDAt(p);
	CCLOG("%d", gid);
	Value gid_value = gplayer->pTileMap->getPropertiesForGID(gid);
	ValueMap ValueMap = gid_value.asValueMap();
	if (ValueMap["terrain"].asInt() == 1){
		CCLOG("it's river");
		str = "river";
	}
	else if (ValueMap["terrain"].asInt() == 2){
		CCLOG("it's mountain");
		str = "mountain";
	}
	else if (ValueMap["terrain"].asInt() == 3){
		CCLOG("it's brick");
		str = "brick";
	}
	else if (ValueMap["terrain"].asInt() == 4){
		CCLOG("it's grass");
		str = "grass";
	}
	else if (ValueMap["terrain"].asInt() == 5){
		CCLOG("it's ground");
		str = "ground";
	}
	else
		str = "fuck";
	/*if (gid == 1){
	CCLOG("it's ground");
	str = "ground";
	}
	else if (gid == 2){
	CCLOG("it's grass");
	str = "grass";

	}
	else if (gid == 3){
	CCLOG("it's mountain");
	str = "mountain";
	}
	else if (gid == 4){
	CCLOG("it's river");
	str = "river";
	}
	else if (gid == 5){
	CCLOG("it's brick");
	str = "brick";
	}*/


	return str;
}

bool G_Map::set_terrain(position p, string t) {
	if (!is_valid_pos(p)) {
		cout << "not a valid pos!" << endl;
		return "";
	}
	return grids[p.y][p.x].set_terrain(t);
}


position G_Map::get_right_pos(position p) {
	position ans = position(p.x + 1, p.y);
	if (!is_valid_pos(ans)) {
		cout << "already edge!" << endl;
		return position(-1, -1);
	}
	return ans;
}

position G_Map::get_left_pos(position p) {
	position ans = position(p.x - 1, p.y);
	if (!is_valid_pos(ans)) {
		cout << "already edge!" << endl;
		return position(-1, -1);
	}
	return ans;
}

position G_Map::get_up_pos(position p) {
	position ans = position(p.x, p.y + 1);
	if (!is_valid_pos(ans)) {
		cout << "already edge!" << endl;
		return position(-1, -1);
	}
	return ans;
}

position G_Map::get_down_pos(position p) {
	position ans = position(p.x, p.y - 1);
	if (!is_valid_pos(ans)) {
		cout << "already edge!" << endl;
		return position(-1, -1);
	}
	return ans;
}

bool G_Map::blend_pos(position p) {
	if (!is_valid_pos(p)) {
		return false;
	}
	
	map<position, Sprite*>::iterator iter = mapper.find(p);
	if (iter != mapper.end()) {
		CCLOG("I FUCK YOU");
		mapper[p]->setVisible(true);
	}
	else {
		Sprite* n_sprite = Sprite::create("blend.png");
		gplayer->blends.push_back(n_sprite);
		n_sprite->setPosition(get_center_of_pos(p));
		BlendFunc cbl = { GL_DST_COLOR, GL_ONE };
		n_sprite->setBlendFunc(cbl);
		gplayer->addChild(n_sprite, 2);
		CCLOG("FUCK");
		mapper.insert(pair<position, Sprite* >(p, n_sprite));
		mapper[p]->setVisible(true);
	}
	return true;
}

bool G_Map::unblend_pos(position p) {
	if (!is_valid_pos(p)) {
		return false;
	}
	map<position, Sprite*>::iterator iter = mapper.find(p);
	if (iter != mapper.end()) {
		mapper[p]->setVisible(false);
		return true;
	}
	else {
		return false;
	}
}

GamePlayLayer* G_Map::get_layer() {
	return gplayer;
}


vector< vector<Grid> > G_Map:: get_grids(){

	return grids;
}