#ifndef _DEMO_H_
#define _DEMO_H_
#include "cocos2d.h"
using namespace cocos2d;

//�ӵ�� ����ļ̳���Layer����Scene
class Demo :public Layer{

//�ӵ��� Ҫдpublic Ĭ��Ϊprotected ��粻�ɷ���
public:

	static Scene* createScene();
	
	virtual bool init();

	CREATE_FUNC(Demo);

	void addSprite();


	virtual bool onTouchBegan(Touch *touch ,Event unuse_event);
};


#endif