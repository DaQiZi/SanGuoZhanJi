#include "GameDefeat.h"
#include "GameScene.h"
#include "GameMenuScene.h"


Scene* GameDefeat::createScene(RenderTexture* spr)
{
	auto scene = Scene::create();

	auto layer = GameDefeat::create();

	scene->addChild(layer, 1);


	Size winSize = Director::getInstance()->getVisibleSize();

	auto spr_bg = Sprite::createWithTexture(spr->getSprite()->getTexture());
	spr_bg->setPosition(winSize.width / 2, winSize.height / 2);
	spr_bg->setColor(Color3B::GRAY);
	spr_bg->setFlipY(true);
	scene->addChild(spr_bg);

	return scene;
}



bool GameDefeat::init()
{
	if (!Layer::init())
	{
		return false;
	}
	initData();


	auto menuitemRestart = MenuItemImage::create("pause_restart.png", "pause_restart.png",
		CC_CALLBACK_0(GameDefeat::menuRestartClick, this));
	menuitemRestart->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 20));

	auto menuitemReturn = MenuItemImage::create("pause_login.png", "pause_login.png",
		CC_CALLBACK_0(GameDefeat::menuReturnClick, this));
	menuitemReturn->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 80));



	auto menu = Menu::create( menuitemRestart, menuitemReturn, NULL);

	menu->setPosition(Vec2::ZERO);


	auto menuPause = Layer::create();
	menuPause->setPosition(Vec2::ZERO);

	auto menuBGSpr = Sprite::create("menuDefeat.png");
	menuBGSpr->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	menuPause->addChild(menuBGSpr);
	menuPause->addChild(menu, 2);


	this->addChild(menuPause);


	return true;
}


void GameDefeat::initData()
{
	winSize = Director::getInstance()->getVisibleSize();
}



void GameDefeat::menuRestartClick()
{
	Director::getInstance()->popScene();

	Director::getInstance()->replaceScene(GameScene::createScene());

}

void GameDefeat::menuReturnClick()
{
	Director::getInstance()->popScene();

	Director::getInstance()->replaceScene(GameMenuScene::createScene());
}