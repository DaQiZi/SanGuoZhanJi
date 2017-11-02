#include "Demo.h"

Scene* Demo::createScene()
{
	auto scene = Scene::create();
	//坑点一 这里要写的是要创建的类名
	auto layer = Demo::create();

	scene->addChild(layer);

	return scene;
}


bool Demo::init()
{
	if (!Layer::init())
	{
		return false;
	}


	Size winSize = Director::getInstance()->getVisibleSize();
	auto labelItem1 = MenuItemFont::create("addItem", CC_CALLBACK_0(Demo::addSprite,this));

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan= CC_CALLBACK_2(Demo::onTouchBegan,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}


void Demo::addSprite()
{
	
}


bool onTouchBegan(Touch *touch, Event unuse_event)
{
	//Point point = touch->getLocation();

}