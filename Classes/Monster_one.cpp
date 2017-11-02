#include "Monster_one.h"

MonsterOne::MonsterOne()
{
	isRunning = false;
	monsterDirection = false;
	monsterName = NULL;
	isAttack = false;
	bloodProgress = NULL;

	isDead = false;
	isHurt = false;

	   
	
}

MonsterOne::~MonsterOne()
{

}


void MonsterOne::initMonsterSprite(char* monsterName)
{
	this->monsterName = monsterName;
	this->monsterSprite = Sprite::create(monsterName);
	this->addChild(monsterSprite);
}
void MonsterOne::initMonsterSprite(char* monsterName, char *xue_back, char* xue_fore)
{
	initMonsterSprite(monsterName);


	bloodProgress = BloodProgress::create();
	bloodProgress->setPosition(Vec2(monsterSprite->getPositionX()+25,monsterSprite->getPositionY()+50));
	//bloodProgress->setScale(2.2f);
	bloodProgress->setBackgroundTexture("xue_back.png");
	bloodProgress->setForegroundTexture("xue_fore.png");
	bloodProgress->setTotalBlood(300.0f);
	bloodProgress->setNowBlood(300.0f);


	this->addChild(bloodProgress);
}


void MonsterOne::setAnimation(const char *name_plist,
	const char *name_each, const unsigned int num, bool run_directon)
{

	if (monsterDirection != run_directon)
	{
		monsterSprite->setFlippedX(run_directon);
		monsterDirection = run_directon;
	}
	if (monsterDirection)
	{
		bloodProgress->setPosition(Point(monsterSprite->getPositionX() +25, monsterSprite->getPositionY()+50));
	}
	else
	{
		bloodProgress->setPosition(Point(monsterSprite->getPositionX() -25, monsterSprite->getPositionY()+50));

	}
	if (this->isRunning)
	{
		return;
	}
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(name_plist);

	//Array frameArray = Array::createWithCapacity(num);
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <= num; i++)
	{
		SpriteFrame* frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", name_each, i));
		frameArray.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frameArray);
	/*if (this->heroDirection!=run_directon)
	{
	heroDirection = run_directon;
	}*/
	//无限重复的播放动画
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);

	auto animate = Animate::create(animation);

	monsterSprite->runAction(animate);


	this->isRunning = true;

}
//图片资源 图片的名字 ，图片的文件文字  图片的数量    运动的方向
void MonsterOne::attackAnimation(const char *name_plist, const char *name_png,
	const char *name_each, const unsigned int num, bool run_directon)
{

	if (isAttack)
	{
		return;
	}
	if (monsterDirection != run_directon)
	{
		monsterSprite->setFlippedX(run_directon);
		monsterDirection = run_directon;
	}

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(name_plist, name_png);

	Vector<SpriteFrame*> frameArray;
	for (int i = 2; i <= num; i++)
	{
		SpriteFrame* frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", name_each, i));
		frameArray.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frameArray);
	/*if (this->heroDirection!=run_directon)
	{
	heroDirection = run_directon;
	}*/

	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);

	auto animate = Animate::create(animation);
	auto action1callfun = CallFunc::create(CC_CALLBACK_0(MonsterOne::attackEnd, this));
	monsterSprite->runAction(Sequence::create(animate, action1callfun, NULL));

	isAttack = true;


}
void MonsterOne::stopAnimation()
{
	if (!isRunning)
	{
		return;
	}
	monsterSprite->stopAllActions();
	this->removeChild(monsterSprite, true);

	//恢复站立的状态
	monsterSprite = Sprite::create(monsterName);
	monsterSprite->setFlippedX(monsterDirection);
	this->addChild(monsterSprite);
	isRunning = false;

}


void MonsterOne::attackEnd()
{
	this->removeChild(monsterSprite, true);
	monsterSprite = Sprite::create(monsterName);
	monsterSprite->setFlippedX(monsterDirection);
	this->addChild(monsterSprite);
	isAttack = false;
}

//
/*
			在怪物的监视范围内的怪物移动的判断
			如果超过了300，返回
			如果<300  >100则移动怪物，直到怪物达到怪物的攻击范围
			达到攻击的范围之后，判断是否要进攻
*/
void MonsterOne::followRun(Sprite* m_hero, Sprite* m_map)
{
	//log("followRun");
	float x = m_hero->getPositionX() - (this->getPositionX() + m_map->getPositionX());

	float y = m_hero->getPositionY() - (this->getPositionY()+m_map->getPositionY());

	dis = sqrt(pow(x,2)+pow(y,2));
	//如果距离大于300
	if (dis>=300)
	{
		//this->stopAnimation();
		//isRunning = false;
		this->stopAnimation();
		return;
	}
	//距离小于100 则判断是否要攻击
	if (dis<=100)
	{
		this->stopAnimation();
		judgeAttack();
		return;
	}
	float  moveX;
	float  moveY;
	//如果怪物在英雄的前面
	if (x<-100)
	{

		monsterDirection = true;

		monsterSprite->setFlipX(monsterDirection);

		//攻击的时候，移动可能会有漂移的效果
		if (isAttack)
		{
			return;
		}
		//人物往左边走
		//this->setPosition(this->getPositionX() - 1, this->getPositionY());
		moveX = this->getPositionX() - 1;
		moveY = this->getPositionY();
		//this->setAnimation("monsterRun.plist","monster_run",6,monsterDirection);
	}
	else if (x>=100)
	{
		monsterDirection = false;

		monsterSprite->setFlipX(monsterDirection);

		//攻击的时候，移动可能会有漂移的效果
		if (isAttack)
		{
			return;
		}
		//人物往右边走
		//this->setPosition(this->getPositionX() + 1, this->getPositionY());
		moveX = this->getPositionX() + 1;
		moveY = this->getPositionY();
		//this->setAnimation("monsterRun.plist", "monster_run", 6, monsterDirection);
	}
	else if (x<=100)
	{
		//如果人物在X轴的方向上和英雄的距离相差不超过100  则判断在Y轴方向上的距离
		if (m_hero->getPositionY()>this->getPositionY())
		{

			monsterSprite->setFlipX(monsterDirection);

			//攻击的时候，移动可能会有漂移的效果
			if (isAttack)
			{
				return;
			}
			//人物往上走
			//this->setPosition(this->getPositionX() , this->getPositionY()+1);
			moveX = this->getPositionX();
			moveY = this->getPositionY() + 1;
			//this->setAnimation("monsterRun.plist", "monster_run", 6, monsterDirection);
		}
		else if (m_hero->getPositionY()<this->getPositionY())
		{

			monsterSprite->setFlipX(monsterDirection);

			//攻击的时候，移动可能会有漂移的效果
			if (isAttack)
			{
				return;
			}
			//人物往下走
			//this->setPosition(this->getPositionX(), this->getPositionY()-1);
			moveX = this->getPositionX();
			moveY = this->getPositionY() - 1;
			//this->setAnimation("monsterRun.plist", "monster_run", 6, monsterDirection);
		}
	}      
	this->setPosition(Vec2(moveX,moveY));
	this->setAnimation("monsterRun.plist", "monster_run", 6, monsterDirection);
	//isRunning = false;
}

void MonsterOne::judgeAttack()
{
	srand(time(NULL));
	int x = rand() % 100;
	if (x>90)
	{
		this->attackAnimation("monsterAttack.plist","monsterAttack.png","monster_attack",5,monsterDirection);
	}
}

/*
	根据人物的朝向来确定人物往哪边移动
*/
void MonsterOne::monsterPatrol()
{
	if (dis<300)
	{
		return;
	}
	if (isRunning)
	{
		return;
	}
	this->setAnimation("monsterRun.plist", "monster_run", 6, monsterDirection);

	MoveBy* action1mt;

	if (monsterDirection)
	{
		action1mt = MoveBy::create(2.0,Vec2(-100,0));
	}
	else{
		action1mt = MoveBy::create(2.0, Vec2(100, 0));
	}

	auto action2callfun = CallFunc::create(CC_CALLBACK_0(MonsterOne::stopAnimation,this));
	auto sequence = Sequence::create(action1mt,action2callfun,NULL);

	this->runAction(sequence);
	//CCLOG("i move le a ");
}



void MonsterOne::startListener(Sprite* m_hero, Sprite* m_map)
{
	my_hero = m_hero;
	my_map = m_map;

	schedule(CC_CALLBACK_1(MonsterOne::updateMonster,this),3.0,"updateMonster");
	scheduleUpdate();
}

//如果在怪物的监视范围之外
void MonsterOne::updateMonster(float d)
{
	float x = my_hero->getPositionX() - (this->getPositionX() + my_map->getPositionX());
	//得到两点y的距离，记得怪物的坐标要加上地图的  
	float y = my_hero->getPositionY() - (this->getPositionY() + my_map->getPositionY());
	//先计算怪物和英雄的距离  
	dis = sqrt(pow(x, 2) + pow(y, 2));

	if (dis>=300)
	{
		if (!isRunning)
		{
			//CCLOG("hahaha");
			monsterPatrol();
		}
		
	}
}
//如果怪物和英雄的距离<300  则 
void MonsterOne::update(float delta)
{
	if (dis<300)
	{
		followRun(my_hero,my_map);
	}
}

//返回怪物精灵
Sprite* MonsterOne::getSprite()
{
	return monsterSprite;
}


void MonsterOne::hurtAnimation(const char *name_plist,
	const char *name_each, const unsigned int num, bool run_directon)
{
	//如果已经被打或者死了
	if (isHurt||isDead)
	{
		return;
	}
	//被攻击的时候停掉怪物行动的操作
	unscheduleUpdate();

	//如果是在走动或者在攻击的时候被英雄打中，英雄的攻击效果优先
	if (isRunning||isAttack)
	{

		monsterSprite->stopAllActions();
		monsterSprite->removeFromParent();
		monsterSprite = Sprite::create(monsterName);
		monsterSprite->setFlippedX(monsterDirection);
		this->addChild(monsterSprite);

		isRunning = false;
		isAttack = false;
	}


	//播放怪物被打中的图像，并调用动画结束的函数
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(name_plist);

	//Array frameArray = Array::createWithCapacity(num);
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <= num; i++)
	{
		SpriteFrame* frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", name_each, i));
		frameArray.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frameArray);
	/*if (this->heroDirection!=run_directon)
	{
	heroDirection = run_directon;
	}*/
	//无限重复的播放动画
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);
	animation->setRestoreOriginalFrame(true);

	auto action2callfun = CallFunc::create(CC_CALLBACK_0(MonsterOne::hurtEnd,this));
	auto animate = Animate::create(animation);

	auto sequence = Sequence::create(animate,action2callfun,NULL);
	monsterSprite->runAction(sequence);

	isHurt = true;
}

void MonsterOne::hurtEnd()
{
	isHurt = false;
	//对扣血量的判断
	int blood = rand() % 4 + 10;

	bloodProgress->setNowBlood(bloodProgress->getNowBlood()-blood);

	//飙血的一个label
	auto flyword = FlyWord::create(30, Vec2(0, 0));
	this->addChild(flyword, 2);
	flyword->flying(StringUtils::format("-%d",blood).c_str());


	//如果血量小于0
	if (bloodProgress->getNowBlood()<=0)
	{
		unschedule("updateMonster");
		unscheduleUpdate();
		deadAnimation("MonsterDead.plist","monster_dead",2,monsterDirection);
		//log("dead");
		return;
	}
	scheduleUpdate();
}


void MonsterOne::deadAnimation(const char *name_plist,
	const char *name_each, const unsigned int num, bool run_directon)
{
	isDead = true;

	

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(name_plist);

	//Array frameArray = Array::createWithCapacity(num);
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <= num; i++)
	{
		SpriteFrame* frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", name_each, i));
		frameArray.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frameArray);
	/*if (this->heroDirection!=run_directon)
	{
	heroDirection = run_directon;
	}*/
	//无限重复的播放动画
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);
	animation->setRestoreOriginalFrame(true);

	auto action2callfun = CallFunc::create(CC_CALLBACK_0(MonsterOne::deadEnd, this));
	auto animate = Animate::create(animation);

	auto sequence = Sequence::create(animate, action2callfun, NULL);
	monsterSprite->runAction(sequence);


}


void MonsterOne::deadEnd()
{
	
	this->removeChild(monsterSprite,true);
	monsterSprite = Sprite::create("monster_dead2.png");
	monsterSprite->setFlippedX(monsterDirection);
	this->addChild(monsterSprite);

	if (bloodProgress!=NULL)
	{
		if (monsterDirection)
		{
			bloodProgress->setPosition(Vec2(monsterSprite->getPositionX() + 60, monsterSprite->getPositionY()));
		}
		else
		{
			bloodProgress->setPosition(Vec2(monsterSprite->getPositionX() - 60, monsterSprite->getPositionY()));

		}
	}

	auto action1blink = Blink::create(2,4);
	auto action2callfun = CallFunc::create(CC_CALLBACK_0(MonsterOne::blinkEnd,this));
	auto sequence = Sequence::create(action1blink,action2callfun,NULL);
	this->runAction(sequence);


}


void MonsterOne::blinkEnd()
{
	
	this->removeAllChildren();

}