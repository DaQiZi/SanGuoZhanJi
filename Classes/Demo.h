#ifndef _DEMO_H_
#define _DEMO_H_
#include "cocos2d.h"
using namespace cocos2d;

//坑点二 这里的继承是Layer不是Scene
class Demo :public Layer{

//坑点三 要写public 默认为protected 外界不可访问
public:

	static Scene* createScene();
	
	virtual bool init();

	CREATE_FUNC(Demo);

	void addSprite();


	virtual bool onTouchBegan(Touch *touch ,Event unuse_event);
};


#endif