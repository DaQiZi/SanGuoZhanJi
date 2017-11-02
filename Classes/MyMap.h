#ifndef __MY_MAP_H_
#define __MY_MAP_H_
#include "cocos2d.h"
using namespace cocos2d;

class MyMap : public Sprite{

public:
	MyMap();
	~MyMap();

	void initMap(const char* map_name,const Size visibleSize);
	void moveMap(Node* hero, Size visibleSize, float x);
	bool judgeMap(Node* hero, Size visibleSize);
	CREATE_FUNC(MyMap);
	Sprite* getSprite();
private:
	Sprite* spr_map;
};



#endif