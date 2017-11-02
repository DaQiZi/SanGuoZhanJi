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
	//��Ϊ��ʼ��Ҫ��ͼƬ�����ԣ��������Դ���init��ֻ���Լ�дһ��������Ҳ������init�г�ʼ��ͼƬ
	static LRocker* createLRocker(const char *rockerImageName, const char *rockerBGImageName, Point position);

	//virtual bool init();

	CREATE_FUNC(LRocker);

	void rockerInit(const char *rockerImageName, const char *rockerBGImageName, Point position);

	//����ҡ��
	void stopRocker();
	void startRocker();


	int rockerDirection;//����
	bool rocker_run;//����ĳ���
	
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	//���㻡��
	float getRad(Point point1,Point point2);
	//�ɻ��ȼ������
	Point getAnglePosition(float point,float angle);

	


	void update(float dt);


	float returnAngle();
private:
	Point rockerBGPosition;//ҡ�˵�λ��
	
	float rockerBGR;//�뾶
	bool isCanMove;//�Ƿ���Բ���ҡ��
	EventListenerTouchOneByOne* listener;

	float angle;
	
};


#endif