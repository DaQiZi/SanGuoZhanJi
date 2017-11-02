#include "MyMap.h"

MyMap::MyMap() :spr_map(NULL)
{

}

MyMap::~MyMap()
{

}

void MyMap::initMap(const char* map_name, const Size visibleSize)
{
	this->spr_map = Sprite::create(map_name);
	spr_map->setAnchorPoint(Point::ZERO);
	spr_map->setPosition(Point::ZERO);
	this->addChild(spr_map);

}


void MyMap::moveMap(Node* hero, Size visibleSize, float x)
{
	//Ӣ�۵����е�ſ�ʼ�ƶ�

	Point temp = hero->convertToWorldSpace(Point(0,0));
	if (temp.x>=visibleSize.width/2)
	{
		//ע���ͼ�ĵ㣬ֻ�е�ͼ��Xֵһֱ���ſ�����ɵ�ͼ����ǰ�ƶ��ĸо�
		if (this->getPositionX()>-(spr_map->getContentSize().width-visibleSize.width))
		{

			this->setPosition(Point(this->getPositionX()-x,this->getPositionY()));

		}
	}
	else
	{
		log("no move map");
	}
}


bool MyMap::judgeMap(Node* hero, Size visibleSize)
{
	//��ͼû�е����Ҳ�ı�Ե
	if (this->getPositionX()>-(spr_map->getContentSize().width-visibleSize.width))
	{
		return false;
	}
	else
	{
		//log("is map zhong jian");
		return true;
	}
}

Sprite* MyMap::getSprite()
{
	return spr_map;
}
