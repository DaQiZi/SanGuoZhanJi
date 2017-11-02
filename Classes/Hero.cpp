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


	//给目标添加观察者
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
	
	//根据摇杆的方向来确定，人物的朝向  人物在攻击和挨打的时候，都不可以转动方向
	if (heroDirection != run_directon&&!this->isAttack&&!this->isHurt)
	{
		heroSprite->setFlippedX(run_directon);
		heroDirection = run_directon;
		//log("gai bian fang xiang");
	}


	//英雄在走动，攻击，挨打，都要返回  
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
	//无限重复的播放动画
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);

	auto animate = Animate::create(animation);

	heroSprite->runAction(animate);



	this->isRunning = true;

}


void Hero::skillAnimation(Ref* sender)
{

	//出现bug，移动的时候按按钮，技能就不会放了
	//看stopanimation函数就知道，如果为true就停止，放技能的时候必须把isRuning设置为false
	
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

	//无限重复的播放动画
	animation->setLoops(2);          
	animation->setDelayPerUnit(0.05f);

	auto animate = Animate::create(animation);
	auto action1callfun = CallFunc::create(CC_CALLBACK_0(Hero::attackEnd, this));
	heroSprite->runAction(Sequence::create(animate, action1callfun, NULL));

	isAttack = true;
	
	
	//log("isHeroSkill");
}

//图片资源 图片的名字 ，图片的文件文字  图片的数量    运动的方向
void Hero::attackAnimation(const char *name_plist, const char *name_png,
	const char *name_each, const unsigned int num, bool run_directon)
{

	/*if (isAttackPerson)
	{
		
		attackPersonAnimation("heroAttackTwo.plist", "heroAttackTwo", 19, run_directon);
		log("isattack");
		return;
	}*/
	//在攻击后，和挨打中，不可以打
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
	//无限重复的播放动画
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

//判断英雄的位置  拿来给地图或者英雄移动的时候判断用的
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

//英雄被攻击时候的动画
void Hero::hurtAnimation(const char *name_plist,
	const char *name_each, const unsigned int num, bool run_directon)
{
	//如果已经被打或者死了
	if (isHurt || isDead)
	{
		//log("isHurt || isDead");
		return;
	}
	//被攻击的时候停掉怪物行动的操作

	//unscheduleUpdate();

	//如果是在走动或者在攻击的时候被英雄打中，英雄的攻击效果优先
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

	auto action2callfun = CallFunc::create(CC_CALLBACK_0(Hero::hurtEnd, this));
	auto animate = Animate::create(animation);

	auto sequence = Sequence::create(animate, action2callfun, NULL);
	heroSprite->runAction(sequence);

	isHurt = true;
}

void Hero::hurtEnd()
{
	isHurt = false;
	//对扣血量的判断
	int blood = rand() % 4 + 10;

	bloodProgress->setNowBlood(bloodProgress->getNowBlood() - blood);

	//飙血的一个label
	auto flyword = FlyWord::create(30, Vec2(0, 0));
	this->addChild(flyword, 2);
	flyword->flying("hurt");


	//如果血量小于0
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
	//无限重复的播放动画
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