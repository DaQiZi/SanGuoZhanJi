#include "GameRank.h"
#include "Player.h"
Scene* GameRank::createScene()
{
	auto scene = Scene::create();

	auto layer = GameRank::create();

	scene->addChild(layer);

	return scene;
}

bool GameRank::init()
{

	if (!Layer::init())
	{
		return false;
	}
	initData();
	
	auto bgspr = Sprite::create("rank.png");
	bgspr->setPosition(winSize.width/2,winSize.height/2);
	this->addChild(bgspr);


	auto menuitem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_0(GameRank::returnClick,this));
	menuitem->setPosition(Vec2(20,winSize.height-20));
	auto menu = Menu::create(menuitem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	int  number = UserDefault::getInstance()->getIntegerForKey("NUMBER", 0);
	Player* playerArray[5];

	for (int i = 0; i < 5; i++)
	{
		playerArray[i] = new Player();
	}


	for (int i = 0; i < number; i++)
	{
		playerArray[i]->name = UserDefault::getInstance()->getStringForKey(StringUtils::format("name%d", i).c_str(), "null");
		playerArray[i]->score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("score%d", i).c_str(), 0);
	}


	for (int i = 0; i < number;i++)
	{
		auto label1 = Label::createWithTTF(StringUtils::format("%s",playerArray[i]->name.c_str()),"fonts\\Marker Felt.ttf",35);
		label1->setPosition(Vec2(130,320-60*i));
		label1->setColor(Color3B::BLACK);


		auto label2 = Label::createWithTTF(StringUtils::format("%d", playerArray[i]->score), "fonts\\Marker Felt.ttf", 35);
		label2->setPosition(Vec2(500,320-60*i));
		label2->setColor(Color3B::BLACK);

		this->addChild(label1,1);
		this->addChild(label2,2);
	}

	for (int i = 0; i < 5; i++)
	{
		delete playerArray[i];
	}
	return true;
}


void GameRank::initData()
{
	winSize = Director::getInstance()->getVisibleSize();
}

void GameRank::returnClick()
{
	Director::getInstance()->popScene();
}