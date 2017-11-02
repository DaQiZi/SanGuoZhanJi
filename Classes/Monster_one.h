#ifndef _MONSTER_ONE_H_
#define _MONSTER_ONE_H_
#include "cocos2d.h"
#include "BloodProgress.h"
#include "FlyWord.h"
using namespace cocos2d;
class MonsterOne : public Sprite{
public:

	MonsterOne();
	~MonsterOne();
	void initMonsterSprite(char* monsterName);
	void initMonsterSprite(char* monsterName, char *xue_back, char* xue_fore);
	//�߶�ʱ�Ķ���
	void setAnimation(const char *name_plist,
		const char *name_each, const unsigned int num, bool run_directon);
	//�����ܶ���
	//����ʱ�Ķ���
	void attackAnimation(const char *name_plist, const char *name_png,
		const char *name_each, const unsigned int num, bool run_directon);
	void attackEnd();

	void stopAnimation();
	//���߶�  
	bool isRunning;
	//���﷽��
	bool monsterDirection;
	//�ڹ���
	bool isAttack;

	
	CREATE_FUNC(MonsterOne);


	//�ж�Ӣ�ۺ͹����λ��
	void followRun(Sprite* m_hero,Sprite* m_map);

	//�жϹ���
	void judgeAttack();

	//�����Ѳ��·��
	void monsterPatrol();

	//��ʼ����ļ���
	void startListener(Sprite* m_hero, Sprite* m_map);

	//Ӣ�ۺ͹���ľ���
	void updateMonster(float d);
	//���Ӣ���ڹ���Ŀ��ӷ�Χ�ڵ�ʱ��
	void update(float delta);
	//���ع��ﾫ��
	Sprite* getSprite();


	void hurtAnimation(const char *name_plist,
		const char *name_each, const unsigned int num, bool run_directon);
	
	void hurtEnd();
	bool isHurt;

	void deadAnimation(const char *name_plist,
		const char *name_each, const unsigned int num, bool run_directon);



	void deadEnd();
	
	bool isDead;

	void blinkEnd();

	
private:

	char *monsterName;
	Sprite* monsterSprite;
	BloodProgress* bloodProgress;

	Sprite* my_hero;
	Sprite* my_map;
	float dis;


	
	
	//FlyWord* flyword;
};


#endif