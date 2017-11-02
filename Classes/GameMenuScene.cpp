#include "GameMenuScene.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "GameRank.h"

using namespace CocosDenshion;
using namespace ui;

Scene* GameMenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameMenuScene::create();

	scene->addChild(layer);


	return scene;
}


bool GameMenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	initData();
	auto gameBGspr = Sprite::create("gameBG.png");
	gameBGspr->setPosition(Vec2(winSize.width/2,winSize.height/2));
	this->addChild(gameBGspr);

	float locationX = winSize.width - 120;
	auto menuitemStart = MenuItemImage::create("playButton.png", "playButton.png",
		CC_CALLBACK_0(GameMenuScene::menuStartClick,this));
	menuitemStart->setPosition(Vec2(locationX, winSize.height - 150));
	menuitemStart->setScale(0.7f);


	auto menuitemRank = MenuItemImage::create("rankButton.png", "rankButton.png",
		CC_CALLBACK_0(GameMenuScene::menuRankClick, this));
	menuitemRank->setPosition(Vec2(locationX, winSize.height - 220));
	menuitemRank->setScale(0.7f);

	auto menuitemEdit = MenuItemImage::create("editButton.png", "editButton.png",
		CC_CALLBACK_0(GameMenuScene::menuEditClick, this));
	menuitemEdit->setPosition(Vec2(locationX, winSize.height - 290));
	menuitemEdit->setScale(0.7f);


	auto menuitemExit = MenuItemImage::create("exitButton.png", "exitButton.png",
		CC_CALLBACK_0(GameMenuScene::menuExitClick, this));
	menuitemExit->setPosition(Vec2(locationX, winSize.height - 360));
	menuitemExit->setScale(0.7f);

	menu = Menu::create(menuitemStart,menuitemEdit,menuitemRank,menuitemExit,NULL);

	menu->setPosition(Vec2::ZERO);


	this->addChild(menu);

	musicSwitch =  UserDefault::getInstance()->getBoolForKey("MUSICSWITCH", true);
	musicVolume =  UserDefault::getInstance()->getFloatForKey("MUSICVOLUME", 1.0);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music\\01.mp3",true);
	if (musicSwitch)
	{
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(musicVolume);

	initEditScene();

	return true;
}

void  GameMenuScene::initData()
{
	winSize = Director::getInstance()->getVisibleSize();


}


void GameMenuScene::menuStartClick()
{
	log("start");

	auto scene = GameScene::createScene();
	auto action = TransitionPageTurn::create(1,scene,true);
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music\\bg1.mp3", true);
	SimpleAudioEngine::getInstance()->playEffect("music\\insertCoins.mp3");
	if (!musicSwitch)
	{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		SimpleAudioEngine::getInstance()->stopAllEffects();

	}
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(musicVolume);
	SimpleAudioEngine::getInstance()->setEffectsVolume(musicVolume);
	Director::getInstance()->replaceScene(action);

}


void GameMenuScene::menuEditClick()
{
	log("menuedit");
	menu->setEnabled(false);
	auto sprSetBG = (Sprite*)this->getChildByTag(SETBG);
	sprSetBG->setVisible(true);
	//给bg设置一个动作
	auto action1mt = MoveTo::create(0.8, Vec2(winSize.width / 2, winSize.height / 2));
	sprSetBG->runAction(action1mt);

}


void GameMenuScene::initEditScene()
{
	auto setbg = Sprite::create("editBG.png");
	setbg->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 200));

	this->addChild(setbg, 1);
	setbg->setTag(SETBG);
	setbg->setVisible(false);
	//给bg设置一个动作
	//auto action1mt =MoveTo::create(0.8,Vec2(winSize.width/2,winSize.height/2));
	//setbg->runAction(action1mt);

	//添加ok按钮
	auto okItem = MenuItemImage::create("ok.png", "ok.png", CC_CALLBACK_0(GameMenuScene::okClick, this));
	okItem->setPosition(setbg->getContentSize().width / 2, 25);
	okItem->setScale(0.5f);
	//要放在当前背景的中间，所以ok设置的是bg的图片

	//创建  开关音乐按钮
	auto onMusic = MenuItemImage::create("duihao1.png", "duihao2.png");
	auto offMusic = MenuItemImage::create("duihao2.png", "duihao1.png");
	auto musicToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameMenuScene::setMusic, this), onMusic, offMusic, NULL);
	musicToggle->setPosition(Vec2(250, 250));
	musicToggle->setScale(0.7f);
	if (!musicSwitch)
	{
		musicToggle->setSelectedIndex(1);
	}

	//创建   开关的标签
	auto musicLabel = Label::createWithTTF("Music:ON", "fonts\\Marker Felt.ttf", 30);
	musicLabel->setPosition(Vec2(120, 250));
	musicLabel->setColor(Color3B::BLACK);
	musicLabel->setTag(MUSICLABEL);
	
	setbg->addChild(musicLabel);

	//添加一个滑块
	auto slider = Slider::create();
	//添加滑块
	slider->loadSlidBallTextures("sliderBall.png");
	//添加划条
	slider->loadBarTexture("SliderBar.png");

	slider->setPosition(Vec2(setbg->getContentSize().width / 2, 150));
	//设置9宫格  可以自动设置宽高
	slider->setScale9Enabled(true);
	slider->setContentSize(Size(250, 30));
	//设置初始滑块的进度
	slider->setPercent(musicVolume*100);
	slider->addEventListener(CC_CALLBACK_1(GameMenuScene::setVolume, this));
	setbg->addChild(slider);


	auto okmenu = Menu::create(okItem, musicToggle, NULL);
	okmenu->setPosition(Vec2::ZERO);
	setbg->addChild(okmenu);
}

void GameMenuScene::menuRankClick()
{
	//log("rank");
	Director::getInstance()->pushScene(GameRank::createScene());

}

void GameMenuScene :: menuExitClick()
{
	//log("exit");
	exit(EXIT_SUCCESS);


}
void GameMenuScene::okClick()
{
	
	auto spr = (Sprite*)this->getChildByTag(SETBG);

	auto action1mt = MoveTo::create(0.8, Vec2(winSize.width / 2, winSize.height / 2 - 200));
	auto action2hide = Hide::create();
	spr->runAction(Sequence::create(action1mt, action2hide, NULL));
	//spr->removeFromParent();
	menu->setEnabled(true);

	//讲音量和音乐的开关保存到文件中去，方便以后的读取
	
	UserDefault::getInstance()->setBoolForKey("MUSICSWITCH",musicSwitch);
	UserDefault::getInstance()->setFloatForKey("MUSICVOLUME",musicVolume);


	UserDefault::getInstance()->flush();

}

void GameMenuScene::setVolume(Ref* sender)
{

	auto slider = (Slider*)sender;
	float volume = (float)slider->getPercent() / 100.0;
	musicVolume = volume;
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);

}


void GameMenuScene::setMusic(Ref* sender)
{
	auto toggle = (MenuItemToggle*)sender;
	auto setBG = (Sprite*)this->getChildByTag(SETBG);
	auto label = (Label*)setBG->getChildByTag(MUSICLABEL);
	//label->retain();

	//log("gamemenuscene set music");
	if (0 == toggle->getSelectedIndex()){


		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		label->setString("Music:ON");
		musicSwitch = true;
	}
	else{

		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		label->setString("Music:OFF");
		musicSwitch = false;
	}
}