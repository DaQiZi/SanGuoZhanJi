#include "FlyWord.h"


FlyWord* FlyWord::create( const int fontSize, Point begin)
{
	FlyWord* flyword = new FlyWord();

	if (flyword&&flyword->init(fontSize,begin))
	{
		flyword->autorelease();
		return flyword;
	}
	
	CC_SAFE_DELETE(flyword);

	return nullptr;
}



bool FlyWord::init( const int fontSize, Point begin)
{
	if (!Sprite::init())
	{
		return false;
	}
	location = begin;

	label = Label::createWithTTF("","fonts\\Marker Felt.ttf",fontSize);
	label->setColor(Color3B::RED);
	this->addChild(label);
	this->setPosition(Vec2(begin
		.x,begin.y));

	this->setVisible(false);

	return true;


}


void FlyWord::flying(const char* font)
{
	label->setString(font);
	auto action1mb = MoveBy::create(0.5,Vec2(0,70));
	auto action2callfun = CallFunc::create(CC_CALLBACK_0(FlyWord::flyEnd,this));
	auto sequence = Sequence::create(action1mb,action2callfun,NULL);
	this->setVisible(true);
	this->runAction(sequence);
}

void FlyWord::flyEnd()
{
	//this->setVisible(false);

	//this->setPosition(Vec2(location.x,location.y));

	this->removeFromParent();
}
