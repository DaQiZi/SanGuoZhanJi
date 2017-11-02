#include "GameScene.h"
#include "GamePause.h"
#include "GameDefeat.h"
#include "GameWin.h"

 


USING_NS_CC;



Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	initData();
	initPersonAnimationArray();
	//创建的地图类，放置在零层
	myMap = MyMap::create();
	myMap->initMap("scene1.png",winSize);
	this->addChild(myMap,0);

	rocker = LRocker::createLRocker("Direction_bt.png", "Direction_bc.png", Point(110, 60));
	rocker->startRocker();
	this->addChild(rocker,2);

	hero = Hero::create();
	hero->initHeroSprite("hero.png", "xue_back.png", "xue_fore.png");
	hero->setPosition(Point(200, 200));
	//hero->setAnimation("run_animation.plist", "run_animation.png", "run_", 8, true);

	//hero->retain();
	myMap->addChild(hero, 1);

	personArray.pushBack(hero);

	this->scheduleUpdate();

	//技能键
	button = MyControlButton::create();
	button->createButton("bt1.png","11",1);
	button->setPosition(Vec2(winSize.width - 50, 50));
	this->addChild(button, 2);

	/*bloodRrogress = BloodProgress::create();
	
	bloodRrogress->setPosition(Vec2(150, 450));
	bloodRrogress->setScale(2.2f);
	bloodRrogress->setBackgroundTexture("xue_back.png");
	bloodRrogress->setForegroundTexture("xue_fore.png");
	bloodRrogress->setTotalBlood(100.0f);
	bloodRrogress->setNowBlood(100.0f);
	this->addChild(bloodRrogress, 2);*/

	bloodRrogress = hero->getBloodProgress();
	bloodRrogress->setPosition(Vec2(150, 450));
	bloodRrogress->setScale(2.2f);
	this->addChild(bloodRrogress, 2);

	//下面两个是为了让血条更好好看  
	Sprite *xuekuang = Sprite::create("kuang.png");//添加血条的框架  
	xuekuang->setPosition(Vec2(bloodRrogress->getPositionX(), bloodRrogress->getPositionY()));
	Sprite *touxiang = Sprite::create("touxiang.png");//添加英雄的左上角的小头像  
	touxiang->setPosition(Vec2(bloodRrogress->getPositionX() - 120, bloodRrogress->getPositionY()));
	this->addChild(touxiang, 2);
	this->addChild(xuekuang, 2);


	//加上分数框

	auto scoreSpr = Sprite::create("score.png");
	scoreSpr->setPosition(Vec2(winSize.width/2+60,winSize.height-35));
	this->addChild(scoreSpr,2);

	score = 0;
	scorelabel = Label::createWithTTF(StringUtils::format("%d",score),"fonts\\Marker Felt.ttf",40);
	scorelabel->setPosition(Vec2(winSize.width/2+200,winSize.height-35));
	scorelabel->setColor(Color3B::BLACK);
	this->addChild(scorelabel,2);

	/*monster1 = MonsterOne::create();
	monster1->initMonsterSprite("monster.png", "xue_back.png", "xue_fore.png");
	monster1->setPosition(Vec2(winSize.width-200,winSize.height-200));
	monster1->startListener(hero,myMap);
	myMap->addChild(monster1);*/
	for (int i = 0; i < 10;i++)
	{
		auto monster = MonsterTwo::create();
		if (i<5)
		{
			monster->personinformation = personAnimationArray.at(1);
		}
		else{
			monster->personinformation = personAnimationArray.at(0);
		}


		monster->initMonsterSprite("xue_back.png", "xue_fore.png");
		monster->setPosition(Vec2(winSize.width - 200+i*100, rand()%(int)(winSize.height - 200)));
		monster->startListener(hero, myMap);
		myMap->addChild(monster);
		monsterArray.pushBack(monster);
		
		personArray.pushBack(monster);

	}


	skillButton = SkillButton::create("skill_fore.png", "skill_back.png");
	skillButton->setPosition(Vec2(winSize.width - 150, 60));
	this->addChild(skillButton, 2);
	


	/*draw = DrawNode::create();

	this->addChild(draw,2);*/




	auto menuitemPause = MenuItemImage::create("CloseNormal.png","CloseSelected.png",
		CC_CALLBACK_0(GameScene::menuPauseClick, this));

	menuitemPause->setPosition(Vec2(winSize.width-20,winSize.height-20));

	auto menu = Menu::create(menuitemPause,NULL);
	menu->setPosition(Vec2::ZERO);

	this->addChild(menu);

	return true;
}

void GameScene::initPersonAnimationArray()                                                                                                 
{
	PersonAnimation* person1 = new PersonAnimation();

	person1->personName = "monster.png";
	person1->personDeadName = "monster_dead2.png";

	person1->movePlist = "monsterRun.plist";
	person1->moveEachName = "monster_run";           
	person1->moveNum = 6;

	person1->attackPlist = "monsterAttack.plist";
	person1->attackEachName = "monster_attack";
	person1->attackNum = 5;

	
	//monster1->hurtAnimation("MonsterHurt.plist", "monster_hurt", 2, monster1->monsterDirection);


	person1->hurtPlist = "MonsterHurt.plist";
	person1->hurtEachName = "monster_hurt";
	person1->hurtNum = 2;

	person1->deadPlist = "MonsterDead.plist";
	person1->deadEachName = "monster_dead";
	person1->deadNum = 2;



	personAnimationArray.pushBack(person1);


	PersonAnimation* person2 = new PersonAnimation();


	person2->personName = "cattle.png";
	person2->personDeadName = "cattleDead.png";

	person2->movePlist = "cattleMove.plist";
	person2->moveEachName = "cattleMove";
	person2->moveNum = 8;

	person2->attackPlist = "cattleAttack.plist";
	person2->attackEachName = "cattleAttack";
	person2->attackNum = 6;


	//monster1->hurtAnimation("MonsterHurt.plist", "monster_hurt", 2, monster1->monsterDirection);


	person2->hurtPlist = "cattleHurt.plist";
	person2->hurtEachName = "cattleHurt";
	person2->hurtNum = 2;

	person2->deadPlist = "cattleHurt.plist";
	person2->deadEachName = "cattleHurt";
	person2->deadNum = 2;

	personAnimationArray.pushBack(person2);

}

void GameScene::menuPauseClick()
{

	auto renderTexture = RenderTexture::create(winSize.width,winSize.height);
	 
	//把当前的场景渲染一次，不是渲染到屏幕上，而是渲染到RenderTexture维护的纹理上
	//OpenGL的纹理数据是从下到上保存的，但是渲染是从上到下渲染的，所以保存的图片的颠倒的，用的时候，需要翻转Y轴

	renderTexture->begin();

	this->getParent()->visit();

	renderTexture->end();

	Director::getInstance()->pushScene(GamePause::createScene(renderTexture));

}
void GameScene::initData()
{
	winSize = Director::getInstance()->getVisibleSize();
}


void GameScene::update(float delta)
{

	float rand = rocker->returnAngle();

	//英雄死了，调用失败的界面
	if (hero->isDead)
	{
		runMenuGameDefeat();
		return;
	}

	if (monsterArray.size()==0)
	{
		judgeMenuGameWin();
		return;
	}
	
	judgeMonsterPosition();

	//judgePersonDistance();
	judgePersonPosition();


	//hero->setAnimation("run_animation.plist", "run_animation.png", "run_", 8, ro);
	//设置运动的方向
	switch (rocker->rockerDirection)
	{
	case rocker_right:
		hero->setAnimation("heroMove.plist", "heroMove", 7, rocker->rocker_run);
		
		break;
	case rocker_left:
		hero->setAnimation("heroMove.plist", "heroMove", 7, rocker->rocker_run);
		
		break;
	case rocker_up:
		hero->setAnimation("heroMove.plist", "heroMove", 7, rocker->rocker_run);
		
		break;
	case rocker_down:
		hero->setAnimation("heroMove.plist", "heroMove", 7, rocker->rocker_run);
		

		break;
	default:
		//log("isstopAnimation");
		hero->stopAnimation();
		break;
	}
	/*
			人物的移动和地图的移动的适配
	
	*/

	//拖动手柄且人物挨打，人物没有攻击，才可以动
	float moveX, moveY;
	if (rocker->rockerDirection != rocker_stay&&!hero->getHurt() && !hero->isAttack)
	{
		//判断人物的方向  如果人物是往右边走的
		//log("hurt is no");

		if (!rocker->rocker_run)
		{
			//判断人物是否走到了地图的最边缘    if (hero->getPositionX() <= (winSize.width - 10))//没有
			if (hero->getPositionX() <= (myMap->getSprite()->getContentSize().width - 10))//没有
			{
				//log("<=winsize-8");
				//精灵没有到达中心，地图到达边缘则移动英雄的位置 
				if (!hero->judgeHeroPosition(winSize) || myMap->judgeMap(hero, winSize))
				{
					///log("judgemap");
					//float rand = rocker->returnAngle();


					//hero->setPosition(hero->getPositionX() + 2 * cos(rand), hero->getPositionY() + 2 * sin(rand));

					moveX = hero->getPositionX() + 2 * cos(rand);
					moveY = hero->getPositionY() + 2 * sin(rand);

				}//人物达到中心之后，地图移动，人物只可以上下移动
				else
				{
					//	log("movemap");
					myMap->moveMap(hero, winSize, 2 * cos(rand));
					//hero->setPosition(hero->getPositionX(), hero->getPositionY() + 2 * sin(rand));

					moveX = hero->getPositionX();
					moveY = hero->getPositionY() + 2 * sin(rand);

				}

			}//有 则只能边上下的值
			else{
				//人物到边缘只能上下的走
				//hero->setPosition(hero->getPositionX(), hero->getPositionY() + 2 * sin(rand));


				moveX = hero->getPositionX();
				moveY = hero->getPositionY() + 2 * sin(rand);
			}
		}//人物往左走的时候
		else
		{
			Point temp = hero->convertToWorldSpace(Point::ZERO);
			if (temp.x >= 8)
			{
				//hero->setPosition(hero->getPositionX() + 2 * cos(rand), hero->getPositionY() + 2 * sin(rand));

				moveX = hero->getPositionX() + 2 * cos(rand);
				moveY = hero->getPositionY() + 2 * sin(rand);
			}
			else
			{
				//hero->setPosition(hero->getPositionX(), hero->getPositionY() + 2 * sin(rand));

				moveX = hero->getPositionX();
				moveY = hero->getPositionY() + 2 * sin(rand);
			}
		}

		if (moveY<0)
		{
			moveY = 0;
		}
		if (moveY>250)
		{
			moveY = 250;
		}


		hero->setPosition(Vec2(moveX, moveY));

	}



	//按了攻击按钮之后    
	/*
	第一段 攻击 点击按钮就可以触发

	第二段 攻击  打中人之后，可如果再打中人，就可以触发
	*/


	if (button->isTouch)
	{
		if (hero->isAttack)
			return;
		if (hero->getAttackPerson() && hero->isAttackPersonAgain)
		{

			hero->attackPersonAnimation("heroAttackTwo.plist", "heroAttackTwo", 19, rocker->rocker_run);
			//heroAttackJudge();
		}
		else
		{
			hero->attackAnimation("heroAttack.plist", "heroAttack.png", "heroAttack", 4, rocker->rocker_run);
			heroAttackJudge();
		}
		
      }

	//if (hero->getAttackPerson() && hero->isAttackPersonAgain&&hero->isDoubleHit)
	if (hero->isDoubleHit)
	{
		
		heroAttackJudge();
	}
	if (skillButton->isSkill)
	{
		heroAttackJudge();
		
	}



	//怪物打英雄的判断
	for (int i = 0; i < monsterArray.size();i++)
	{
		auto monster1 = monsterArray.at(i);
	
	if (monster1->isAttack)
	{
		//log("monster attack");

		if (!hero->isDead)
		{

			float dis = abs(hero->getPositionY() - monster1->getPositionY());
			if (dis <= 30)
			{
				//判断两个精灵是否相交
				//log("<=30");
				//尽量把两个精灵的rect计算准确。。。目前还不准确
				Rect heroRect = Rect(hero->getPositionX() + myMap->getPositionX() - hero->getSprite()->getContentSize().width / 2
					, hero->getPositionY() - hero->getSprite()->getContentSize().height / 2 + myMap->getPositionY(),
					hero->getSprite()->getContentSize().width - 20,
					hero->getSprite()->getContentSize().height - 10);


				Rect monsterRect = Rect(monster1->getPositionX() + myMap->getPositionX() - monster1->getSprite()->getContentSize().width / 2 + 40,
					monster1->getPositionY() + myMap->getPositionY() - monster1->getSprite()->getContentSize().height / 2,
					monster1->getSprite()->getContentSize().width - 40,
					monster1->getSprite()->getContentSize().height - 20);


				if (heroRect.intersectsRect(monsterRect))
				{
					//播放被攻击的动画
					//monster1->hurtAnimation("MonsterHurt.plist", "monster_hurt", 2, monster1->monsterDirection);
					//log("hero blooding");
					if (!hero->getHurt())
					{
						hero->hurtAnimation("heroHurt.plist", "heroHurt", 2, monster1->monsterDirection);
						
					}
					
				}
			}
		}
	}

	
	

	}
}

void GameScene::runMenuGameDefeat()
{
	

	unscheduleUpdate();
	log("game defeat!!!!!!!");
	auto renderTexture = RenderTexture::create(winSize.width, winSize.height);
	//把当前的场景渲染一次，不是渲染到屏幕上，而是渲染到RenderTexture维护的纹理上
	//OpenGL的纹理数据是从下到上保存的，但是渲染是从上到下渲染的，所以保存的图片的颠倒的，用的时候，需要翻转Y轴

	renderTexture->begin();

	this->getParent()->visit();

	renderTexture->end();



	Director::getInstance()->pushScene(GameDefeat::createScene(renderTexture));
	//Director::getInstance()->replaceScene(GameDefeat::createScene(renderTexture));
}


void GameScene::judgeMenuGameWin()
{
	/*if (!monster1->isDead)
	{
		return;
	}*/
	/*if (!monsterArray.size()==0)
	{
		return;
	}*/

	unscheduleUpdate();

	scheduleOnce(schedule_selector(GameScene::runMenuGameWin),3.0f);
	

}

void GameScene::runMenuGameWin(float d)
{
	





	//log("defeat!!!!!!!");
	auto renderTexture = RenderTexture::create(winSize.width, winSize.height);

	//把当前的场景渲染一次，不是渲染到屏幕上，而是渲染到RenderTexture维护的纹理上
	//OpenGL的纹理数据是从下到上保存的，但是渲染是从上到下渲染的，所以保存的图片的颠倒的，用的时候，需要翻转Y轴

	renderTexture->begin();

	this->getParent()->visit();

	renderTexture->end();



	Director::getInstance()->pushScene(GameWin::createScene(renderTexture,score));
}


void GameScene::judgeMonsterPosition()
{
	for (int i = 0; i < monsterArray.size();i++)
	{
		auto monster = monsterArray.at(i);
		if (monster->getPositionX()<0)
		{
			monster->setPositionX(0);
		}
		if (monster->getPositionX()>myMap->getSprite()->getContentSize().width)
		{
			monster->setPositionX(myMap->getSprite()->getContentSize().width);

		}
		if (monster->getPositionY()<0)
		{
			monster->setPositionY(0);
		}
		if (monster->getPositionY()>250)
		{
			monster->setPositionY(250);
		}
	}
}
void GameScene::judgePersonPosition()
{
	if (personArray.size()<2)
	{
		return;
	}
	int min;
	
	float minY;
	for (int i = 0; i < personArray.size();i++)
	{
		auto node1 = personArray.at(i);
		min = i;
		minY = node1->getPositionY();
		for (int j = i+1; j < personArray.size();j++)
		{
			auto node2 = personArray.at(j);
			float node2Y = node2->getPositionY();

			if (minY>node2Y)
			{
				min = j;
				minY = node2Y;
			}


		}

		if (min!=i)
		{
			personArray.swap(min,i);
		}
	}
	//log("--------------------------------------");
	for (int i = 0; i < personArray.size();i++)
	{
		auto node = personArray.at(i);

		node->setLocalZOrder(personArray.size()-i);

		//log("the z = %f ",node->getPositionY());
	}


	
}


void GameScene::judgePersonDistance(){

	//判断两个人之间的位置，如果距离小于20，则不可以再靠近
	for (int i = 0; i < personArray.size();i++)
	{
		auto node1 = personArray.at(i);
		for (int j = i+1; j < personArray.size();j++)
		{
			auto node2 = personArray.at(j);

			float disX = node1->getPositionX()+2 - node2->getPositionX();
			float disY = node1->getPositionY() +2- node2->getPositionY();
			float distance = sqrt(pow(disX,2)+pow(disY,2));
			if (distance<80.0f)
			{

				//做一个简单的判断
				node1->setPosition(node1->getPosition());
				node2->setPosition(node2->getPosition());
				


			}
			log("the distance  = %f",distance);
		}
	}
}


void GameScene::changScoreLabel(bool isSkill)
{
	if (isSkill)
	{
		score += 20;
		
	}
	else
	{
		score += 10;
	}

	scorelabel->setString(StringUtils::format("%d", score));
}



void GameScene::heroAttackJudge()
{
	//攻击检测的代码块
	//英雄打怪物的
	
	if (hero->isAttack)
	{
		//log("attack");
		//如果怪物没有死
		//一个一个的判断怪物是否被打中
		//判断开始的时候，把攻击设置为false，只要打中了，就记录为true
		hero->setAttackPerson(false);
		for (int i = 0; i < monsterArray.size(); i++)
		{
			auto monster1 = monsterArray.at(i);
			//怪物没有死才可以打中
			if (!monster1->isDead)
			{

				//log("!isdead");
				//判断怪物和英雄在Y上的距离，攻击有一定的范围
				float dis = abs(hero->getPositionY() - monster1->getPositionY());
				//如果距离小于30像素
				//
				if (dis <= 30)
				{
					//判断两个精灵是否相交
					//log("<=30");
					//尽量把两个精灵的rect计算准确。。。目前还不准确
					Rect heroRect = Rect(hero->getPositionX() + myMap->getPositionX() - hero->getSprite()->getContentSize().width / 2
						, hero->getPositionY() - hero->getSprite()->getContentSize().height / 2 + myMap->getPositionY(),
						hero->getSprite()->getContentSize().width - 20,
						hero->getSprite()->getContentSize().height - 10);


					Rect monsterRect = Rect(monster1->getPositionX() + myMap->getPositionX() - monster1->getSprite()->getContentSize().width / 2 + 40,
						monster1->getPositionY() + myMap->getPositionY() - monster1->getSprite()->getContentSize().height / 2,
						monster1->getSprite()->getContentSize().width - 40,
						monster1->getSprite()->getContentSize().height - 20);

					/*draw->drawRect(Vec2(heroRect.origin.x, heroRect.origin.y),
					Vec2(heroRect.origin.x + heroRect.size.width, heroRect.origin.y + heroRect.size.height),Color4F::RED
					);


					draw->drawRect(Vec2(monsterRect.origin.x, monsterRect.origin.y),
					Vec2(monsterRect.origin.x + monsterRect.size.width, monsterRect.origin.y + monsterRect.size.height), Color4F::RED
					);*/

					//isRectCollision(heroRect,monsterRect)

					/*

					二段攻击，和技能攻击的判断
					如果是被技能打中的，就把普攻记录的数据清除一下


					多个怪物一起打中或者没有打中这里有bug
					*/
					if (heroRect.intersectsRect(monsterRect))
					{
						//播放被攻击的动画
						//如果被打中了，就不要判断了
						if (!monster1->isHurt)
						{
							//播放瘦攻击的动画，并扣一次血
							monster1->hurtAnimation( monster1->monsterDirection);
							if (skillButton->isSkill)
							{
								changScoreLabel(true);
								log("+20");
							}
							else
							{
								changScoreLabel(false);
								log("+10");
							}

							//如果是被技能打中的  不记录数据 把普攻的数据给清除了
							if (skillButton->isSkill)
							{


								hero->setAttackPerson(false);
								hero->isAttackPersonAgain = false;

								//log("--------------------------------------------------------------");
							}
							else{

								//记录被普通攻击打中
								if (!hero->isDoubleHit)
								{

									hero->setAttackPerson(true);
									log("no double hit");

								}
								else{
									log("double hit");
								}
							}

						}



						//log("hurt");
					}



				}
			}


			//如果被打死了
			if (monster1->isDead)
			{
				monsterArray.eraseObject(monster1);

				personArray.eraseObject(monster1);

				i--;
			}


		}

		/*
		在对所有的怪物判断完攻击之后，如果没有打中任何一个怪物，则清空连击设置

		如果打中了 ，记录连击 1

		如果打中了，且 连击数 =1  则连击数 = 2

		如果根本没有打中，则连击数清空
		*/
	

		
		if (hero->getAttackPerson() && hero->heroAttackNum == 0)
		{
			hero->heroAttackNum = 1;
		}
		else if (hero->getAttackPerson() && hero->heroAttackNum == 1)
		{
			hero->isAttackPersonAgain = true;
			hero->heroAttackNum = 2;
		}
		else if (hero->getAttackPerson() == false)
		{
			hero->heroAttackNum = 0;
			hero->isAttackPersonAgain = false;
		}

		log("num = %d one =  %d  again =  %d ", hero->heroAttackNum, hero->getAttackPerson(), hero->isAttackPersonAgain);
	
		
		}
}
//bool GameScene::isRectCollision(Rect rect1, Rect rect2)
//{
//	float x1 = rect1.origin.x;//矩形1中心点的横坐标  
//	float y1 = rect1.origin.y;//矩形1中心点的纵坐标  
//	float w1 = rect1.size.width;//矩形1的宽度  
//	float h1 = rect1.size.height;//矩形1的高度  
//	float x2 = rect2.origin.x;
//	float y2 = rect2.origin.y;
//	float w2 = rect2.size.width;
//	float h2 = rect2.size.height;
//
//	if (x1 + w1*0.5<x2 - w2*0.5)
//		return false;//矩形1在矩形2左方，两者无碰撞  
//	else if (x1 - w1*0.5>x2 + w2*0.5)
//		return false;//矩形1在矩形2右方，两者无碰撞  
//	else if (y1 + h1*0.5<y2 - h2*0.5)
//		return false;//矩形1在矩形2下方，两者无碰撞  
//	else if (y1 - h1*0.5>y2 + h2*0.5)
//		return false;//矩形1在矩形2上方，两者无碰撞  
//
//	return true;
//}