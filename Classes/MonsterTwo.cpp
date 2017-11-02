#include "MonsterTwo.h"

MonsterTwo::MonsterTwo()
{
	isRunning = false;
	monsterDirection = false;
	monsterName = NULL;
	isAttack = false;
	bloodProgress = NULL;

	isDead = false;
	isHurt = false;

	lastdis = 0;
	dis = 0;

	personinformation = NULL;
	
}

MonsterTwo::~MonsterTwo()
{

}


void MonsterTwo::initMonsterSprite( char* monsterName)
{
	this->monsterName = monsterName;
	this->monsterSprite = Sprite::create(monsterName);
	this->addChild(monsterSprite);
}
void MonsterTwo::initMonsterSprite(  char *xue_back, char* xue_fore)
{


	//initMonsterSprite(monsterName);
	initMonsterSprite(personinformation->personName);

	bloodProgress = BloodProgress::create();
	bloodProgress->setPosition(Vec2(monsterSprite->getPositionX()+25,monsterSprite->getPositionY()+50));
	//bloodProgress->setScale(2.2f);
	bloodProgress->setBackgroundTexture("xue_back.png");
	bloodProgress->setForegroundTexture("xue_fore.png");
	bloodProgress->setTotalBlood(300.0f);
	bloodProgress->setNowBlood(300.0f);


	this->addChild(bloodProgress);
}


void MonsterTwo::setAnimation( bool run_directon)
{

	if (monsterDirection != run_directon)
	{
		
		monsterDirection = run_directon;
	}
	monsterSprite->setFlippedX(monsterDirection);
	if (monsterDirection)
	{
		bloodProgress->setPosition(Point(monsterSprite->getPositionX()-25, monsterSprite->getPositionY()+50));
	}
	else
	{
		bloodProgress->setPosition(Point(monsterSprite->getPositionX() +25, monsterSprite->getPositionY()+50));

	}
	if (this->isRunning)
	{
		return;
	}
	auto cache = SpriteFrameCache::getInstance();
	//cache->addSpriteFramesWithFile(name_plist);
	cache->addSpriteFramesWithFile(personinformation->movePlist);
	//Array frameArray = Array::createWithCapacity(num);
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <= personinformation->moveNum; i++)
	{
		SpriteFrame* frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", personinformation->moveEachName, i));
		frameArray.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frameArray);
	/*if (this->heroDirection!=run_directon)
	{
	heroDirection = run_directon;
	}*/
	//�����ظ��Ĳ��Ŷ���
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);

	auto animate = Animate::create(animation);

	monsterSprite->runAction(animate);


	this->isRunning = true;

}
//ͼƬ��Դ ͼƬ������ ��ͼƬ���ļ�����  ͼƬ������    �˶��ķ���
void MonsterTwo::attackAnimation(bool run_directon)
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
	cache->addSpriteFramesWithFile(personinformation->attackPlist);

	Vector<SpriteFrame*> frameArray;
	for (int i = 2; i <= personinformation->attackNum; i++)
	{
		SpriteFrame* frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", personinformation->attackEachName, i));
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
	auto action1callfun = CallFunc::create(CC_CALLBACK_0(MonsterTwo::attackEnd, this));
	monsterSprite->runAction(Sequence::create(animate, action1callfun, NULL));

	isAttack = true;


}
void MonsterTwo::stopAnimation()
{
	if (!isRunning)
	{
		return;
	}



	this->stopAllActions();
	monsterSprite->stopAllActions();
	this->removeChild(monsterSprite, true);

	//�ָ�վ����״̬
	monsterSprite = Sprite::create(monsterName);
	monsterSprite->setFlippedX(monsterDirection);
	this->addChild(monsterSprite);
	isRunning = false;


	if (monsterDirection)
	{
		bloodProgress->setPosition(Point(monsterSprite->getPositionX() + 25, monsterSprite->getPositionY() + 50));
	}
	else
	{
		bloodProgress->setPosition(Point(monsterSprite->getPositionX() - 25, monsterSprite->getPositionY() + 50));

	}
}


void MonsterTwo::attackEnd()
{
	this->removeChild(monsterSprite, true);
	monsterSprite = Sprite::create(monsterName);
	monsterSprite->setFlippedX(monsterDirection);
	this->addChild(monsterSprite);
	isAttack = false;
}

//
/*
			�ڹ���ļ��ӷ�Χ�ڵĹ����ƶ����ж�
			���������300������
			���<300  >100���ƶ����ֱ������ﵽ����Ĺ�����Χ
			�ﵽ�����ķ�Χ֮���ж��Ƿ�Ҫ����
*/
void MonsterTwo::followRun(Sprite* m_hero, Sprite* m_map)
{
	
	//log("followRun");
	/*float x = m_hero->getPositionX() - (this->getPositionX() + m_map->getPositionX());

	float y = m_hero->getPositionY() - (this->getPositionY()+m_map->getPositionY());*/


	float x = m_hero->getPositionX() - this->getPositionX();

	float y = m_hero->getPositionY() - this->getPositionY();

	lastdis = dis;
	dis = sqrt(pow(x,2)+pow(y,2));


	//����������300
	if (dis>=300)
	{    
		this->stopAnimation();
		//isRunning = false;
		//this->stopAnimation();
		return;
	}


	//����С��100 ���ж��Ƿ�Ҫ����
	if (dis<=100)
	{
		this->stopAnimation();
		judgeAttack();
		return;
	}


	float  moveX;
	float  moveY;
	//���������Ӣ�۵�ǰ��
	if (x<-100)
	{

		monsterDirection = true;

		monsterSprite->setFlipX(monsterDirection);

		//������ʱ���ƶ����ܻ���Ư�Ƶ�Ч��
		if (isAttack)
		{
			return;
		}
		//�����������
		//this->setPosition(this->getPositionX() - 1, this->getPositionY());
		moveX = this->getPositionX() - 1;
		moveY = this->getPositionY();
		//this->setAnimation("monsterRun.plist","monster_run",6,monsterDirection);
	}
	else if (x>=100)
	{
		monsterDirection = false;

		monsterSprite->setFlipX(monsterDirection);

		//������ʱ���ƶ����ܻ���Ư�Ƶ�Ч��
		if (isAttack)
		{
			return;
		}
		//�������ұ���
		//this->setPosition(this->getPositionX() + 1, this->getPositionY());
		moveX = this->getPositionX() + 1;
		moveY = this->getPositionY();
		//this->setAnimation("monsterRun.plist", "monster_run", 6, monsterDirection);
	}
	else if (x<=100)
	{
		//���������X��ķ����Ϻ�Ӣ�۵ľ���������100  ���ж���Y�᷽���ϵľ���
		if (m_hero->getPositionY()>this->getPositionY())
		{

			monsterSprite->setFlipX(monsterDirection);

			//������ʱ���ƶ����ܻ���Ư�Ƶ�Ч��
			if (isAttack)
			{
				return;
			}
			//����������
			//this->setPosition(this->getPositionX() , this->getPositionY()+1);
			moveX = this->getPositionX();
			moveY = this->getPositionY() + 1;
			//this->setAnimation("monsterRun.plist", "monster_run", 6, monsterDirection);
		}
		else if (m_hero->getPositionY()<this->getPositionY())
		{

			monsterSprite->setFlipX(monsterDirection);

			//������ʱ���ƶ����ܻ���Ư�Ƶ�Ч��
			if (isAttack)
			{
				return;
			}
			//����������
			//this->setPosition(this->getPositionX(), this->getPositionY()-1);
			moveX = this->getPositionX();
			moveY = this->getPositionY() - 1;
			//this->setAnimation("monsterRun.plist", "monster_run", 6, monsterDirection);
		}
	}      

	this->setPosition(Vec2(moveX,moveY));
	this->setAnimation(monsterDirection);


	//isRunning = false;
}

void MonsterTwo::judgeAttack()
{
	int x = u(e) % 200;
	if (x>197)
	{
		this->attackAnimation(monsterDirection);
	}
}

/*
	��������ĳ�����ȷ���������ı��ƶ�
*/
void MonsterTwo::monsterPatrol()
{
	if (dis<300)
	{
		return;
	}


	if (isRunning)
	{
		return;
	}


	if (lastdis<dis)
	{
		monsterDirection = !monsterDirection;
	}


	this->setAnimation(monsterDirection);
	//���Խ��ԽԶ��ô��ͷ��
	MoveBy* action1mt;
	//�����Լ��ĳ����߶�
	int speed = 50;
	int distanceX = u(e)%500;
	int distanceY = u(e) % 200;
	int temp = u(e) % 2;
	if (temp ==0)
	{
		distanceY = -distanceY;
	}

	float time =sqrt(pow(distanceX,2)+pow(distanceY,2)) / speed;

	if (monsterDirection)
	{

		action1mt = MoveBy::create(time, Vec2(-distanceX,-distanceY));
	}
	else{

		action1mt = MoveBy::create(time, Vec2(distanceX, distanceY));

	}

	auto action2callfun = CallFunc::create(CC_CALLBACK_0(MonsterTwo::stopAnimation,this));
	auto sequence = Sequence::create(action1mt,action2callfun,NULL);

	this->runAction(sequence);
	//CCLOG("i move le a ");
}



void MonsterTwo::startListener(Sprite* m_hero, Sprite* m_map)
{
	my_hero = m_hero;
	my_map = m_map;
	//Ѳ�ߵ�·��ÿ��������ж�һ��
	schedule(CC_CALLBACK_1(MonsterTwo::updateMonster,this),3.0,"updateMonster");
	//���������ӷ�Χ��ÿ�붼���ж�
	scheduleUpdate();
}

//����ڹ���ļ��ӷ�Χ֮��
void MonsterTwo::updateMonster(float d)
{
	//float x = my_hero->getPositionX() - (this->getPositionX() + my_map->getPositionX());
	////�õ�����y�ľ��룬�ǵù��������Ҫ���ϵ�ͼ��  
	//float y = my_hero->getPositionY() - (this->getPositionY() + my_map->getPositionY());
	//�ȼ�������Ӣ�۵ľ���  

	float x = my_hero->getPositionX() - this->getPositionX();

	float y = my_hero->getPositionY() - this->getPositionY();

	lastdis = dis;
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
//��������Ӣ�۵ľ���<300  �� 
void MonsterTwo::update(float delta)
{

	//�����ÿһ��Ĳ��Ծ��룬���᲻�����Ư��
	


	if (dis<300)
	{
		followRun(my_hero,my_map);
	}
}

//���ع��ﾫ��
Sprite* MonsterTwo::getSprite()
{
	return monsterSprite;
}


void MonsterTwo::hurtAnimation(bool run_directon)
{
	//����Ѿ������������
	if (isHurt||isDead)
	{
		return;
	}
	//��������ʱ��ͣ�������ж��Ĳ���
	unscheduleUpdate();

	//��������߶������ڹ�����ʱ��Ӣ�۴��У�Ӣ�۵Ĺ���Ч������
	if (isRunning||isAttack)
	{

		this->stopAllActions();
		monsterSprite->stopAllActions();
		monsterSprite->removeFromParent();
		monsterSprite = Sprite::create(monsterName);
		monsterSprite->setFlippedX(monsterDirection);
		this->addChild(monsterSprite);

		isRunning = false;
		isAttack = false;
	}


	//���Ź��ﱻ���е�ͼ�񣬲����ö��������ĺ���
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(personinformation->hurtPlist);

	//Array frameArray = Array::createWithCapacity(num);
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <= personinformation->hurtNum; i++)
	{
		SpriteFrame* frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", personinformation->hurtEachName, i));
		frameArray.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frameArray);
	/*if (this->heroDirection!=run_directon)
	{
	heroDirection = run_directon;
	}*/
	//�����ظ��Ĳ��Ŷ���
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);
	animation->setRestoreOriginalFrame(true);

	auto action2callfun = CallFunc::create(CC_CALLBACK_0(MonsterTwo::hurtEnd,this));
	auto animate = Animate::create(animation);

	auto sequence = Sequence::create(animate,action2callfun,NULL);
	monsterSprite->runAction(sequence);

	isHurt = true;
}

void MonsterTwo::hurtEnd()
{
	isHurt = false;
	//�Կ�Ѫ�����ж�
	int blood = rand() % 10 + 15 ;

	bloodProgress->setNowBlood(bloodProgress->getNowBlood()-blood);

	//�Ѫ��һ��label
	auto flyword = FlyWord::create(30, Vec2(0, 0));
	this->addChild(flyword, 2);
	flyword->flying(StringUtils::format("-%d",blood).c_str());


	//���Ѫ��С��0
	if (bloodProgress->getNowBlood()<=0)
	{
		unschedule("updateMonster");
		unscheduleUpdate();
		deadAnimation(monsterDirection);
		//log("dead");
		return;
	}
	scheduleUpdate();
}


void MonsterTwo::deadAnimation(bool run_directon)
{
	isDead = true;

	

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(personinformation->deadPlist);

	//Array frameArray = Array::createWithCapacity(num);
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <= personinformation->deadNum; i++)
	{
		SpriteFrame* frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", personinformation->deadEachName, i));
		frameArray.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frameArray);
	/*if (this->heroDirection!=run_directon)
	{
	heroDirection = run_directon;
	}*/
	//�����ظ��Ĳ��Ŷ���
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);
	animation->setRestoreOriginalFrame(true);

	auto action2callfun = CallFunc::create(CC_CALLBACK_0(MonsterTwo::deadEnd, this));
	auto animate = Animate::create(animation);

	auto sequence = Sequence::create(animate, action2callfun, NULL);
	monsterSprite->runAction(sequence);


}


void MonsterTwo::deadEnd()
{
	
	this->removeChild(monsterSprite,true);
	monsterSprite = Sprite::create(personinformation->personDeadName);
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
	auto action2callfun = CallFunc::create(CC_CALLBACK_0(MonsterTwo::blinkEnd,this));
	auto sequence = Sequence::create(action1blink,action2callfun,NULL);
	this->runAction(sequence);


}


void MonsterTwo::blinkEnd()
{
	
	this->removeAllChildren();

}