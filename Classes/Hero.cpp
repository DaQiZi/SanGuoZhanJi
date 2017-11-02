#include "Hero.h"
#include "FlyWord.h"
Hero::Hero()
{
	isRunning = false;
	heroDirection = false;


	heroName = NULL;



	isAttack = false;


	isAttackPerson= false;
	isAttackPersonAgain = false;
	
	isDead = false;
	isHurt = false;

	bloodProgress = NULL;
	heroAttackNum = 0;

	isDoubleHit = false;
}

Hero::~Hero()
{
	NotificationCenter::getInstance()->removeObserver(this,"MessageSkill");
}


void  Hero::setAttackPerson(bool temp)
{
	isAttackPerson = temp;
	//log("= = ||");
}

bool Hero::getAttackPerson()
{
	return isAttackPerson;
}
void Hero::initHeroSprite(char* heroName)
{
	this->heroName = heroName;
	this->heroSprite = Sprite::create(heroName);
	this->addChild(heroSprite);


	//��Ŀ����ӹ۲���
	NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(Hero::skillAnimation), "MessageSkill", NULL);

}
void Hero::initHeroSprite(char* heroName, char *xue_back, char* xue_fore)
{
	initHeroSprite(heroName);


	bloodProgress = BloodProgress::create();
	//bloodProgress->setPosition(Vec2(heroSprite->getPositionX() + 25, heroSprite->getPositionY() + 50));
	//bloodProgress->setScale(2.2f);
	bloodProgress->setBackgroundTexture("xue_back.png");
	bloodProgress->setForegroundTexture("xue_fore.png");
	bloodProgress->setTotalBlood(200.0f);
	bloodProgress->setNowBlood(200.0f);
	//this->addChild(bloodProgress);
	
}
BloodProgress* Hero::getBloodProgress(){
	return bloodProgress;
}
//
void Hero::setAnimation(const char *name_plist,
	const char *name_each, const unsigned int num, bool run_directon)
{
	
	//����ҡ�˵ķ�����ȷ��������ĳ���  �����ڹ����Ͱ����ʱ�򣬶�������ת������
	if (heroDirection != run_directon&&!this->isAttack&&!this->isHurt)
	{
		heroSprite->setFlippedX(run_directon);
		heroDirection = run_directon;
		//log("gai bian fang xiang");
	}


	//Ӣ�����߶������������򣬶�Ҫ����  
	if (this->isRunning||this->isAttack||this->isHurt)
	{
		return;
	}
	
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(name_plist);

	//Array frameArray = Array::createWithCapacity(num);
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <=num;i++)
	{
		SpriteFrame* frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png",name_each,i));
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

	heroSprite->runAction(animate);



	this->isRunning = true;

}


void Hero::skillAnimation(Ref* sender)
{

	//����bug���ƶ���ʱ�򰴰�ť�����ܾͲ������
	//��stopanimation������֪�������Ϊtrue��ֹͣ���ż��ܵ�ʱ������isRuning����Ϊfalse
	
	//this->stopAnimation();
	/*attackEnd();
	attackPersonEnd();*/
	if (isDead)
	{
		return;
	}
	

	isRunning = false;
	if (isDoubleHit)
	{
		attackPersonEnd();
	}
	
	
	const char *name_plist = "heroSkillOne.plist";
	const char *name_each = "heroSkillOne";
	const unsigned int num = 16;

	heroSprite->setFlippedX(heroDirection);

	//log("skill one");
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(name_plist);
	 
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <= num; i++)
	{
		SpriteFrame* frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", name_each, i));
		frameArray.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frameArray);

	//�����ظ��Ĳ��Ŷ���
	animation->setLoops(2);          
	animation->setDelayPerUnit(0.05f);

	auto animate = Animate::create(animation);
	auto action1callfun = CallFunc::create(CC_CALLBACK_0(Hero::attackEnd, this));
	heroSprite->runAction(Sequence::create(animate, action1callfun, NULL));

	isAttack = true;
	
	
	//log("isHeroSkill");
}

//ͼƬ��Դ ͼƬ������ ��ͼƬ���ļ�����  ͼƬ������    �˶��ķ���
void Hero::attackAnimation(const char *name_plist, const char *name_png,
	const char *name_each, const unsigned int num, bool run_directon)
{

	/*if (isAttackPerson)
	{
		
		attackPersonAnimation("heroAttackTwo.plist", "heroAttackTwo", 19, run_directon);
		log("isattack");
		return;
	}*/
	//�ڹ����󣬺Ͱ����У������Դ�
	if (isAttack||this->isHurt)
	{
		return;
	}

	


	if (heroDirection!=run_directon)
	{
		heroSprite->setFlippedX(run_directon);
		heroDirection = run_directon;
	}

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(name_plist,name_png);

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
	//�����ظ��Ĳ��Ŷ���
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);

	auto animate = Animate::create(animation);
	auto action1callfun = CallFunc::create(CC_CALLBACK_0(Hero::attackEnd,this));
	heroSprite->runAction(Sequence::create(animate,action1callfun,NULL));
	 
	isAttack = true;


}

void Hero::stopAnimation()
{
	if (!isRunning)
	{
		return;
	}
	heroSprite->stopAllActions();
	this->removeChild(heroSprite,true);

	heroSprite = Sprite::create(heroName);
	heroSprite->setFlippedX(heroDirection);
	this->addChild(heroSprite);
	isRunning = false;

}

void Hero::attackEnd()
{
	this->removeChild(heroSprite,true);
	heroSprite = Sprite::create(heroName);
	heroSprite->setFlippedX(heroDirection);
	this->addChild(heroSprite);
	isAttack = false;
	/*if (isAttackPerson)
	{
		isAttackPerson = false;
	}*/

	NotificationCenter::getInstance()->postNotification("SkillCool", NULL);
}

//�ж�Ӣ�۵�λ��  ��������ͼ����Ӣ���ƶ���ʱ���ж��õ�
bool Hero::judgeHeroPosition(Size visibleSize)
{

	Point temp = this->convertToWorldSpace(Point(0,0));
	//log("the x = %f the y = %f",temp.x,temp.y);
	//log("this x = %f, this y = %f",this->getPositionX(),this->getPositionY());
	/*if (this->getPositionX()>=visibleSize.width/2)
	{
		return true;
	}
	else
	{
		return false;
	}*/

	if (temp.x >= visibleSize.width / 2)
	{
		//log("is  width/2 ");
		return true;
	}
	else
	{
		return false;
	}
}


Sprite* Hero::getSprite()
{
	return heroSprite;
}

//Ӣ�۱�����ʱ��Ķ���
void Hero::hurtAnimation(const char *name_plist,
	const char *name_each, const unsigned int num, bool run_directon)
{
	//����Ѿ������������
	if (isHurt || isDead)
	{
		//log("isHurt || isDead");
		return;
	}
	//��������ʱ��ͣ�������ж��Ĳ���

	//unscheduleUpdate();

	//��������߶������ڹ�����ʱ��Ӣ�۴��У�Ӣ�۵Ĺ���Ч������
	if (isRunning || isAttack)
	{

		heroSprite->stopAllActions();
		heroSprite->removeFromParent();
		heroSprite = Sprite::create(heroName);
		heroSprite->setFlippedX(heroDirection);
		this->addChild(heroSprite);

		isRunning = false;
		isAttack = false;

		isAttackPerson = false;
		isAttackPersonAgain = false;
		isDoubleHit = false;
		heroAttackNum = 0;


		NotificationCenter::getInstance()->postNotification("SkillCool", NULL);
		//log("debug one");
	}


	//���Ź��ﱻ���е�ͼ�񣬲����ö��������ĺ���
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
	//�����ظ��Ĳ��Ŷ���
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);
	animation->setRestoreOriginalFrame(true);

	auto action2callfun = CallFunc::create(CC_CALLBACK_0(Hero::hurtEnd, this));
	auto animate = Animate::create(animation);

	auto sequence = Sequence::create(animate, action2callfun, NULL);
	heroSprite->runAction(sequence);

	isHurt = true;
}

void Hero::hurtEnd()
{
	isHurt = false;
	//�Կ�Ѫ�����ж�
	int blood = rand() % 4 + 10;

	bloodProgress->setNowBlood(bloodProgress->getNowBlood() - blood);

	//�Ѫ��һ��label
	auto flyword = FlyWord::create(30, Vec2(0, 0));
	this->addChild(flyword, 2);
	flyword->flying("hurt");


	//���Ѫ��С��0
	if (bloodProgress->getNowBlood() <= 0)
	{
		//unschedule("updateMonster");
		//unscheduleUpdate();
		//deadAnimation("MonsterDead.plist", "monster_dead", 2, monsterDirection);


		/*log("dead");
		Director::getInstance()->pause();*/
		isDead = true;
		return;
	}
	//scheduleUpdate();
}

bool Hero::getHurt(){

	return isHurt;

}


void Hero::attackPersonAnimation(const char *name_plist,
	const char *name_each, const unsigned int num, bool run_directon)
{
	//log("attackPerson-----------------------------------");
	if (isAttack || this->isHurt||isDead)
	{
		return;
	}
	if (heroDirection != run_directon)
	{
		heroSprite->setFlippedX(run_directon);
		heroDirection = run_directon;
	}

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(name_plist);

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
	//�����ظ��Ĳ��Ŷ���
	animation->setLoops(1);
	animation->setDelayPerUnit(0.05f);

	auto animate = Animate::create(animation);
	auto action1callfun = CallFunc::create(CC_CALLBACK_0(Hero::attackPersonEnd, this));
	heroSprite->runAction(Sequence::create(animate, action1callfun, NULL));

	isAttack = true;

	isDoubleHit = true;

}


void Hero::attackPersonEnd()
{

	this->removeChild(heroSprite, true);
	heroSprite = Sprite::create(heroName);
	heroSprite->setFlippedX(heroDirection);
	this->addChild(heroSprite);
	isAttack = false;

	

	isAttackPerson = false;
	isAttackPersonAgain = false;
	heroAttackNum = 0;
	isDoubleHit = false;
}