#ifndef _LROCKER_H_
#define _LROCKER_H_
#include "cocos2d.h"

using namespace cocos2d;

typedef enum{
	tag_rockerImage,
	tag_rockerBG
}tagForRcoker;

typedef enum{
	rocker_stay,
	rocker_right,
	rocker_up,
	rocker_left,
	rocker_down
}tagDirection;

class LRocker : public Layer
{
public:

	~LRocker();
	//因为初始化要传图片，所以，不能用自带的init，只能自己写一个，但是也可以在init中初始化图片
	static LRocker* createLRocker(const char *rockerImageName, const char *rockerBGImageName, Point position);

	//virtual bool init();

	CREATE_FUNC(LRocker);

	void rockerInit(const char *rockerImageName, const char *rockerBGImageName, Point position);

	//隐藏摇杆
	void stopRocker();
	void startRocker();


	int rockerDirection;//方向
	bool rocker_run;//人物的朝向
	
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	//计算弧度
	float getRad(Point point1,Point point2);
	//由弧度计算出点
	Point getAnglePosition(float point,float angle);

	


	void update(float dt);


	float returnAngle();
private:
	Point rockerBGPosition;//摇杆的位置
	
	float rockerBGR;//半径
	bool isCanMove;//是否可以操纵摇杆
	EventListenerTouchOneByOne* listener;

	float angle;
	
};


#endif