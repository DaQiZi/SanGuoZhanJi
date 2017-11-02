#include "SkillButton.h"

SkillButton* SkillButton::create(const char* fore_name, const char* back_name){

	SkillButton* sprSkill = new SkillButton();

	if (sprSkill&&sprSkill->init(fore_name,back_name))
	{
		sprSkill->autorelease();
		return sprSkill;
	}
	CC_SAFE_DELETE(sprSkill);
	return nullptr;
}
SkillButton::~SkillButton()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

	NotificationCenter::getInstance()->removeObserver(this,"SkillCool");


	//log("~~Skill Button");
}

bool SkillButton::init(const char* fore_name, const char* back_name)
{
	if (!Layer::init())
	{
		return false;
	}

	isSkillCool = true;
	isSkill = false;
	isCanClick = false;

	this->setTouchEnabled(true);

	sprFore = Sprite::create(fore_name);
	
	this->addChild(sprFore,1);

	sprBack = Sprite::create(back_name);
	pt = ProgressTimer::create(sprBack);
	
	pt->setPercentage(100);
	this->addChild(pt,2);

	

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SkillButton::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(SkillButton::onTouchEnded,this);


	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener,1);
	//不知道监听要不要设置向下传递
	///_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);


	//加一个观察者   
	NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(SkillButton::changeSkillEnd),
		"SkillCool",NULL);
	return true;
}


void SkillButton::changeSkillEnd(Ref* sender)
{

	isSkill = false;

}
void SkillButton::BeginSkill()
{

	pt->setPercentage(0);

	pt->setType(ProgressTimer::Type::RADIAL);
	auto action1PT = ProgressTo::create(8,100);
	auto action2callfun = CallFunc::create(CC_CALLBACK_0(SkillButton::endSkill,this));
	auto sequence = Sequence::create(action1PT,action2callfun,NULL);


	pt->setVisible(true);
	isSkill = true;
	isSkillCool = false;
	pt->runAction(sequence);
	
	NotificationCenter::getInstance()->postNotification("MessageSkill", NULL);


}


void SkillButton::endSkill(){
	//+-pt->setVisible(false);
	//isSkilling = false;
	isSkillCool = true;
	isCanClick = false;
	//pt->setPercentage(0);

}

bool SkillButton::onTouchBegan(Touch *touch, Event *unused_event){

	//CCLOG("skill is click");
	Point touchPoint = convertToNodeSpace(touch->getLocation());
	if (sprFore->boundingBox().containsPoint(touchPoint))
	{
		isCanClick = true;
	}

	return true;
}

void SkillButton::onTouchEnded(Touch *touch, Event *unused_event)
{


	if (!isSkillCool)
	{
		return;
	}

	if (isCanClick)
	{
		BeginSkill();
	}

	/*Point touchPoint = convertToNodeSpace(touch->getLocation());
	if (sprFore->boundingBox().containsPoint(touchPoint))
	{
		BeginSkill();
	}*/
}

