#ifndef _FLY_WORD_H_
#define _FLY_WORD_H_

#include "cocos2d.h"
using namespace cocos2d;

class FlyWord : public Sprite{
public:

	static FlyWord* create(const int fontSize, Point begin);

	bool init(const int fontSize, Point begin);

	void flying(const char* font);
	void flyEnd();
private:
	Point location;
	Label* label;
};



#endif