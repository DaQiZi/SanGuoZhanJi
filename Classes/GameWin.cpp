#include "GameWin.h"
#include "GameScene.h"
#include "GameMenuScene.h"


GameWin::~GameWin()
{
	for (int i = 0; i < 5;i++)
	{
		delete playerArray[i];
	}
}

Scene* GameWin::createScene(RenderTexture* spr,int s)
{
	auto scene = Scene::create();
	auto layer = GameWin::create();
	
	layer->score = s;
	layer->initEditBox();
	
	
	scene->addChild(layer,1);

	Size winSize = Director::getInstance()->getVisibleSize();

	auto spr_bg = Sprite::createWithTexture(spr->getSprite()->getTexture());
	spr_bg->setPosition(winSize.width / 2, winSize.height / 2);
	spr_bg->setColor(Color3B::GRAY);
	spr_bg->setFlipY(true);
	scene->addChild(spr_bg);

	return scene;
}


bool GameWin::init()
{
	if (!Layer::init())
	{
		return false;

	}

	initData();

	

	auto menuitemRestart = MenuItemImage::create("pause_restart.png", "pause_restart.png",
		CC_CALLBACK_0(GameWin::menuRestartClick, this));
	menuitemRestart->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 20));

	auto menuitemReturn = MenuItemImage::create("pause_login.png", "pause_login.png",
		CC_CALLBACK_0(GameWin::menuReturnClick, this));
	menuitemReturn->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 80));

	
	auto menu = Menu::create(menuitemRestart, menuitemReturn, NULL);

	menu->setPosition(Vec2::ZERO);


	menuPause = Layer::create();

	menuPause->setPosition(Vec2::ZERO);

	auto menuBGSpr = Sprite::create("menuWin.png");

	menuBGSpr->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	menuPause->addChild(menuBGSpr);

	menuPause->addChild(menu, 2);


	this->addChild(menuPause,1);

	
	return true;
}

void GameWin::nameOkClick()
{
	if (name=="")
	{
		log("is NULL");
	}
	else{
		//�ѵ�ǰ�ķ�����ֱ�Ӵ浽���һλ
		//UserDefault::getInstance()->setIntegerForKey(StringUtils::format("score%d", number).c_str(), score);

		Player* playerIndex = new Player();
		playerIndex->name = name;
		playerIndex->score = score;


		
		for (int i = 0; i < number;i++)
		{
			playerArray[i]->name = UserDefault::getInstance()->getStringForKey(StringUtils::format("name%d",i).c_str(),"null");
			playerArray[i]->score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("score%d",i).c_str(),0);

		}
		
		
		int index = number;
		for (int i = 0; i < number; i ++)
		{
			if (score>playerArray[i]->score)
			{
				index = i;
				break;
			}
		}
		if (number != 5)
		{
			number++;
		}
		for (int i = number-1; i > index;i--)
		{
			playerArray[i] = playerArray[i - 1];
		}
		
		playerArray[index] = playerIndex;

		UserDefault::getInstance()->setIntegerForKey("NUMBER",number);
		for (int i = 0; i < number;i++)
		{
			UserDefault::getInstance()->setStringForKey(StringUtils::format("name%d",i).c_str(),playerArray[i]->name);

			UserDefault::getInstance()->setIntegerForKey(StringUtils::format("score%d",i).c_str(),playerArray[i]->score);
		}

		UserDefault::getInstance()->flush();

		pEditBox_name->setVisible(false);
		menuOK->setVisible(false);
		
		/*
				�������е�ȫ����ȡ����

				Ȼ��͵�ǰ�Ľ�������

				�ٴ����ļ�
		
		*/
		
		log("the score  = %d",score);

	}
}

void GameWin::initData()
{
	winSize = Director::getInstance()->getVisibleSize();

	pEditBox_name = NULL;

	name = "";
	
	score = 0;

	for (int i = 0; i < 5; i++)
	{
		playerArray[i] = new Player();
		playerArray[i]->name = "";
		playerArray[i]->score = 0;
	}
}



void GameWin::editBoxEditingDidBegin(EditBox *editBox)
{
	CCLOG("start edit");
}
void GameWin::editBoxEditingDidEnd(EditBox *editBox)
{
	CCLOG("end edit");
}
void GameWin::editBoxReturn(EditBox *editBox)
{
	CCLOG("editbox return");
}
void GameWin::editBoxTextChanged(EditBox *editBox, const std::string &text)
{
	auto editbox = (EditBox*)editBox;
	switch (editBox->getTag())
	{
	case 101:
		CCLOG("EditBox_name changed");
		name = text;
		CCLOG("%s",name.c_str());
		break;
	
	default:
		break;
	}
}




void GameWin::menuRestartClick()
{
	Director::getInstance()->popScene();

	Director::getInstance()->replaceScene(GameScene::createScene());



}

void GameWin::menuReturnClick()
{
	Director::getInstance()->popScene();

	Director::getInstance()->replaceScene(GameMenuScene::createScene());
}


void GameWin::initEditBox()
{

	/*
	ȡ���һ���˵ķ������������С�ڵĻ����Ͳ���ʾ

	������ڵĻ�������ʾ���༭��
	
	*/
	number = UserDefault::getInstance()->getIntegerForKey("NUMBER",0);
	int lastScore;


	if (number==5)
	{
		//ȡ�����һλ
		lastScore = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("score%d",number-1).c_str(),0);
		
		if (score<=lastScore)
		{

			log("score < lastScore");
			return;
		}
	}
	/*else
	{
		number++;
		UserDefault::getInstance()->setIntegerForKey("NUMBER",number);
	}*/
	//С��5�Ļ�ֱ�Ӵ�

	
	//���һλֱ�Ӵ浱ǰ�������ȵ���ȷ����ʱ����������
	//UserDefault::getInstance()->setIntegerForKey(StringUtils::format("score%d", number).c_str(),score);
	pEditBox_name = EditBox::create(CCSizeMake(150, 40), Scale9Sprite::create("bt2.png"));

	pEditBox_name->setPosition(Vec2(winSize.width / 2 - 20, winSize.height / 2 + 40));

	pEditBox_name->setFontColor(Color3B(0, 0, 0));//����������ɫ    

	pEditBox_name->setPlaceHolder("Name:");//����Ԥ���ı�    

	pEditBox_name->setMaxLength(8);//������󳤶�    

	pEditBox_name->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//���������κΣ����ǲ���������   

	pEditBox_name->setInputFlag(cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD);//���������־λ    

	pEditBox_name->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);//���÷�������   

	pEditBox_name->setDelegate(this);//��ǰ��̳�CCEditBoxDelegate��    


	pEditBox_name->setTag(101);


	menuPause->addChild(pEditBox_name, 2);


	auto menuitemOK = MenuItemImage::create("editOK.png", "editOK.png", CC_CALLBACK_0(GameWin::nameOkClick, this));
	menuitemOK->setPosition(Vec2(winSize.width / 2 + 80, winSize.height / 2 + 40));
	//menuitemOK->setTag(102);

	menuOK = Menu::create(menuitemOK, NULL);
	menuOK->setPosition(Vec2::ZERO);

	menuPause->addChild(menuOK);
}