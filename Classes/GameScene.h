#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "LRocker.h"
#include "Hero.h"
#include "MyControlButton.h"
#include "MyMap.h"
#include "BloodProgress.h"
#include "Monster_one.h"
#include "SkillButton.h"
#include "MonsterTwo.h"
#include "PersonAnimation.h"

using namespace cocos2d;


class GameScene : public cocos2d::Layer
{
public:


    static cocos2d::Scene* createScene();

    virtual bool init();
    // implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	Size winSize;

	void initData();

	virtual void update(float delta);
	//bool isRectCollision(Rect rect1, Rect rect2);

	void menuPauseClick();

	void runMenuGameDefeat();

	void judgeMenuGameWin();
	void runMenuGameWin(float d);

	void judgeMonsterPosition();
	void judgePersonPosition();
	void judgePersonDistance();


	void initPersonAnimationArray();

	void changScoreLabel(bool isSkill);

	void heroAttackJudge();
private:
	Hero * hero;
	LRocker* rocker;
	MyControlButton *button;
	MyMap *myMap;
	BloodProgress* bloodRrogress;
	//MonsterOne* monster1;

	DrawNode* draw;

	SkillButton* skillButton;
	Vector<MonsterTwo*> monsterArray;
	Vector<Node*> personArray;
	Vector<PersonAnimation*>personAnimationArray;

	Label* scorelabel;
	int score;
};




#endif //
