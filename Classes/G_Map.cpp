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
	gplayer->removeFromParentAndCleanup(true);
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
	if (!is_valid_pos(p)) {
		return new GameSprite();
	}
	GameSprite* tmp = grids[p.y][p.x].get_hero();
	return tmp;
}
bool tflag = false;
bool G_Map::put_hero_on_pos(GameSprite* h, position p) {
	if (!is_valid_pos(p)) {
		//cout << "not a valid pos!" << endl;
		CCLOG("not a valid pos!");
		return false;
	}
	grids[p.y][p.x].put(h);
	h->setName(h->get_type().get_name());
	gplayer->addChild(h);
	h->setPosition(((double)p.x + 0.5) * gwid + width_diff, ((double)p.y + 0.5) * ghei + height_diff);
	h->get_type().set_position(p.x, p.y);
	BloodProgress* blood = new BloodProgress();
	blood->setBackgroundTexture("bloodback.png");
	if (h->getTag() >= 10) {
		blood->setForegroundTexture("bloodfore2p.png");
	}
	else {
		blood->setForegroundTexture("bloodfore.png");
	}
	blood->setTotalProgress(1200);
	blood->setCurrentProgress(h->get_type().get_life());
	blood->setPosition(h->getPositionX(), h->getPositionY() + 30);
	gplayer->addChild(blood);
	bloods.insert(pair<int, BloodProgress* > (h->getTag(), blood));
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
	GameSprite* hero = grids[ps.y][ps.x].get_hero();
	hero->setPosition(get_center_of_pos(pe));
	hero->get_type().set_position(pe.x, pe.y);
	bloods[hero->getTag()]->setPosition(hero->getPositionX(), hero->getPositionY() + 30);
//	hero->get_blood()->setPosition(get_center_of_pos(pe).x, get_center_of_pos(pe).y + 40);
	grids[pe.y][pe.x].put(hero);
	grids[ps.y][ps.x].remove();
	if (get_terrain(pe) == "ground") {//-----ground, knight have been powered up
		hero->change_attribute(1);
	}
	if (get_terrain(pe) == "grass") {//-------grass, soldier have been powered up
		hero->change_attribute(2);
	}
	if (get_terrain(pe) == "mountain") {//-------mountain, archer have been powered up, knight down
		hero->change_attribute(3);
	}
	if (get_terrain(pe) == "river") {//-------river, soldier have been powered down, knight down
		hero->change_attribute(4);
	}
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
		//CCLOG("it's river");
		str = "river";
	}
	else if (ValueMap["terrain"].asInt() == 2){
		//CCLOG("it's mountain");
		str = "mountain";
	}
	else if (ValueMap["terrain"].asInt() == 3){
		//CCLOG("it's brick");
		str = "brick";
	}
	else if (ValueMap["terrain"].asInt() == 4){
		str = "grass";
	}
	else if (ValueMap["terrain"].asInt() == 5){
		str = "ground";
	}
	else
		str = "error";
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
		mapper[p]->setVisible(true);
	}
	else {
		Sprite* n_sprite = Sprite::create("blend.png");
		gplayer->blends.push_back(n_sprite);
		n_sprite->setPosition(get_center_of_pos(p));
		BlendFunc cbl = { GL_DST_COLOR, GL_ONE };
		n_sprite->setBlendFunc(cbl);
		gplayer->addChild(n_sprite, 2);
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

bool G_Map::a_blend_pos(position p) {
	if (!is_valid_pos(p)) {
		return false;
	}

	map<position, Sprite*>::iterator iter = a_mapper.find(p);
	if (iter != a_mapper.end()) {
		a_mapper[p]->setVisible(true);
	}
	else {
		Sprite* n_sprite = Sprite::create("ablend.png");
		gplayer->blends.push_back(n_sprite);
		n_sprite->setPosition(get_center_of_pos(p));
		BlendFunc cbl = { GL_DST_COLOR, GL_ONE };
		n_sprite->setBlendFunc(cbl);
		gplayer->addChild(n_sprite, 2);
		a_mapper.insert(pair<position, Sprite* >(p, n_sprite));
		a_mapper[p]->setVisible(true);
	}
	return true;
}

bool G_Map::a_unblend_pos(position p) {
	if (!is_valid_pos(p)) {
		return false;
	}
	map<position, Sprite*>::iterator iter = a_mapper.find(p);
	if (iter != a_mapper.end()) {
		a_mapper[p]->setVisible(false);
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

bool G_Map::is_pos_empty(position p) {
	if (!is_valid_pos(p)) {
		CCLOG("not a valid pos");
		return false;
	}
	return grids[p.y][p.x].is_empty();
}

vector<position> G_Map::get_movable_pos(position p) {
	vector<position> answer;
	if (is_pos_empty(p)) {
		CCLOG("No Hero Here");
		return answer;
	}
	GameSprite* hero = get_hero_on_pos(p);
	if (hero->get_type().get_fight_type() == 2) {
		search_pos(p, answer);
		return answer;
	}
	else {
		search_pos(p, answer, 1);
		return answer;
	}
}

void G_Map::search_pos(position p, vector<position>& answer, int depth, bool init) {
	if (depth == -1) {
		return;
	}
	if (p == position(-1, -1)){
		return;
	}
	if (get_terrain(p) == "brick") {
		return;
	}
	if (is_searched[p] == true) {  //searched
		return;
	}
	if (!is_pos_empty(p) && init) {
		is_searched.clear();
		return;
	}
	answer.push_back(p);
	is_searched.insert(pair<position, bool> (p, true));
	search_pos(get_up_pos(p), answer, depth - 1, true);
	search_pos(get_down_pos(p), answer, depth - 1, true);
	search_pos(get_left_pos(p), answer, depth - 1, true);
	search_pos(get_right_pos(p), answer, depth - 1, true);
}

void G_Map::search_a_pos(position p, vector<position>& answer, int depth, bool init) {
	if (depth == -1) {
		return;
	}
	if (p == position(-1, -1)) {
		return;
	}
	for (int i = -depth; i <= 0; i++) {
		for (int j = -(i + depth); j <= i + depth; j++) {
			position pt = position(p.x + i, p.y + j);
			if (is_valid_pos(pt)); {
				answer.push_back(pt);
			}
		}
	}
	for (int i = 1; i <= depth; i++) {
		for (int j = -(depth - i); j <= depth - i ; j++) {
			position pt = position(p.x + i, p.y + j);
			if (is_valid_pos(pt)); {
				answer.push_back(pt);
			}
		}
	}
}

vector<position> G_Map::get_attackable_pos(position p) {
	vector<position> answer;
	if (is_pos_empty(p)) {
		CCLOG("No Hero Here");
		return answer;
	}
	GameSprite* hero = get_hero_on_pos(p);
	if (hero->get_type().get_fight_type() == 3) {
		search_a_pos(p, answer);
		return answer;
	}
	else {
		search_a_pos(p, answer, 1);
		return answer;
	}
}

bool G_Map::attack(position ps, position pe) {
	if (!is_valid_pos(ps) || !is_valid_pos(pe)) {
		return false;
	}
	if (is_pos_empty(ps) || is_pos_empty(pe)) {
		return false;
	}
    int flag;
    if (ps.y > pe.y){
        flag = 0;              //¹¥ÉÏ·ÀÏÂ
    }
    else if(ps.x > pe.x){
        flag = 1;              //¹¥ÓÒ·À×ó
    }
    else if (ps.x < pe.x){
        flag = 2;              //¹¥×ó·ÀÓÒ
    }
    else {
        flag = 3;              //¹¥ÏÂ·ÀÉÏ
    }
	int x1 = ps.x;
	int y1 = ps.y;
	int x2 = pe.x;
	int y2 = pe.y;
	GameSprite* ahero = get_hero_on_pos(ps);
	ahero->get_type().set_position(x1, y1);
	GameSprite* dhero = get_hero_on_pos(pe);
	dhero->get_type().set_position(x2, y2);
	int damage = ahero->get_type().get_D_attack() - 0.2 * dhero->get_type().get_D_defense();
	dhero->get_type().change_life(dhero->get_type().get_life() - damage);
	ahero->get_type().change_magic(dhero->get_type().get_magic() * 0.9);
    ahero->attackAnimation(ahero->getTag() / 10 + 1, flag);
	bloods[dhero->getTag()]->setCurrentProgress(dhero->get_type().get_life());
	if (dhero->get_type().get_life() <= 0) {
        string str = get_terrain(pe);
		dhero->deadAnimation(str);
		CCLOG("DEAD!!!!");
		//Sleep(1000);
		bloods[dhero->getTag()]->setVisible(false);
		CCLOG("REMOVE!!!!");
		remove(pe);
	}
	return true;
}

int G_Map::get_width() {
	return cols;
}

int G_Map::get_height() {
	return rows;
}