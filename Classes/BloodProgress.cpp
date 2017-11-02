#include "BloodProgress.h"

BloodProgress::BloodProgress() :spr_bloodProgressBackground(NULL),
spr_bloodProgressForeground(NULL),
totalBlood(0.0f),
nowBlood(0.0f),
scale(1.0f)
{

}


void BloodProgress::setBackgroundTexture(const char* name)
{
	spr_bloodProgressBackground = Sprite::create(name);
	this->addChild(spr_bloodProgressBackground);
}

void BloodProgress::setForegroundTexture(const char* name)
{
	spr_bloodProgressForeground = Sprite::create(name);
	spr_bloodProgressForeground->setAnchorPoint(Vec2(0,0.5));
	spr_bloodProgressForeground->setPosition(Point(-spr_bloodProgressForeground->getContentSize().width/2,0));
	//spr_bloodProgressForeground->setPosition(Point(0,0));
	this->addChild(spr_bloodProgressForeground);
}

void BloodProgress::setTotalBlood(float blood)
{
	if (spr_bloodProgressForeground==NULL)
	{
		return;
	}
	scale = spr_bloodProgressForeground->getContentSize().width / blood;
	totalBlood = blood;
}

void BloodProgress::setNowBlood(float blood)
{
	if (spr_bloodProgressForeground==NULL)
	{
		return;
	}
	if (blood<0.0f)
	{
		blood = 0.0f;
	}
	//if (blood>nowBlood)//这局话是什么意思  就是坑你 
	//{
	//	blood = nowBlood;
	//}
	nowBlood = blood;
	float rectWidth = blood*scale;
	//log("blood =  %f  scale = %f  rectwidth %f",blood,scale,blood*scale);
	
	const Point from = spr_bloodProgressForeground->getTextureRect().origin;
	const Rect rect = Rect(from.x,from.y,rectWidth,spr_bloodProgressForeground->getContentSize().height);
	 
	spr_bloodProgressForeground->setTextureRect(rect);
	
	//log("x  = %f, y  = %f   rectwidh%f",from.x,from.y,rectWidth);

}


float  BloodProgress::getTotalBlood()
{
	return totalBlood;
}
float  BloodProgress::getNowBlood()
{
	return nowBlood;
}