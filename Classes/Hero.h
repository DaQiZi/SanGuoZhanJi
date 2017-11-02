#ifndef _HERO_H_
#define _HERO_H_
#include "cocos2d.h"
#include "BloodProgress.h"
using namespace cocos2d;

class Hero : public Sprite{

public :
	Hero();
	~Hero();
	void initHeroSprite(char* heroName);
	void initHeroSprite(char* heroName, char *xue_back, char* xue_fore);
	//�߶�ʱ�Ķ���
	void setAnimation(const char *name_plist, 
		const char *name_each, const unsigned int num, bool run_directon);
	//�����ܶ���
	//����ʱ�Ķ���
	void attackAnimation(const char *name_plist, const char *name_png,
		const char *name_each, const unsigned int num, bool run_directon);
	//������֮��ִ�еĶ���
	void attackPersonAnimation(const char *name_plist,
		const char *name_each, const unsigned int num, bool run_directon);


	void skillAnimation(Ref* sender);
	//�����ܶ���
	void attackEnd();
	void attackPersonEnd();

	void stopAnimation();
	//���߶�  �ֱ����Ƶ�
	bool isRunning;
	//Ӣ�۵ķ���
	bool heroDirection;
	//�ڹ���
	bool isAttack;
	//Ӣ������
	bool isDead;

	//�ж�Ӣ�۵�λ��
	bool judgeHeroPosition(Size visibleSize);

	Sprite* getSprite();

	void hurtAnimation(const char *name_plist,
		const char *name_each, const unsigned int num, bool run_directon);

	void hurtEnd();
	CREATE_FUNC(Hero);
	BloodProgress* getBloodProgress();
	bool getHurt();
	void  setAttackPerson(bool temp);
	bool getAttackPerson();

	bool isAttackPersonAgain;
	int heroAttackNum;

	bool isDoubleHit;

private:

     char *heroName;
	 Sprite* heroSprite;
	 bool isHurt;
	 BloodProgress* bloodProgress;
	 bool isAttackPerson;
	
	
};


#endif