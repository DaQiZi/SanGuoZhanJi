#include"LRocker.h"
const double PI=3.1415;

LRocker::~LRocker()
{
	_eventDispatcher->removeEventListenersForTarget(this);
}
 LRocker* LRocker::createLRocker(const char *rockerImageName, const char *rockerBGImageName, Point position)
{
	 //没有init函数也可以是实例化吗？还是只要父类的Layer初始化成功就可以了?
	 LRocker* lrocker = LRocker::create();

	 if (lrocker)
	 {
		 lrocker->rockerInit(rockerImageName,rockerBGImageName,position);
		// CCLOG("success");
		 return lrocker;
	 }


	

	// CCLOG("init defaut");
	 CC_SAFE_DELETE(lrocker);
	 return NULL;
}


 

 void LRocker::rockerInit(const char *rockerImageName, const char *rockerBGImageName, Point position)
 {
	 //在摇杆背景的上面
	 auto spr_rockerIamge = Sprite::create(rockerImageName);
	 spr_rockerIamge->setPosition(position);
	 spr_rockerIamge->setVisible(false);
	 this->addChild(spr_rockerIamge,1,tag_rockerImage);

	 auto spr_rockerBG = Sprite::create(rockerBGImageName);
	 spr_rockerBG->setPosition(position);
	 spr_rockerBG->setVisible(false);
	 this->addChild(spr_rockerBG,0,tag_rockerBG);

	 rockerBGPosition = position;
	 rockerBGR = spr_rockerBG->getContentSize().width / 2;
	 rockerDirection = rocker_stay;

	 listener = EventListenerTouchOneByOne::create();
	 listener->onTouchBegan = CC_CALLBACK_2(LRocker::onTouchBegan, this);
	 listener->onTouchMoved = CC_CALLBACK_2(LRocker::onTouchMoved,this);
	 listener->onTouchEnded = CC_CALLBACK_2(LRocker::onTouchEnded,this);
	 //Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	 //default is false
	 rocker_run = false;

	 isCanMove = false;
	 
 }

 void LRocker::startRocker()
 {
	 auto spr_iamge = (Sprite*)this->getChildByTag(tag_rockerImage);
	 spr_iamge->setVisible(true);

	 auto spr_BG = (Sprite*)this->getChildByTag(tag_rockerBG);
	 spr_BG->setVisible(true);

	 //add listener tou one by one
	 _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	 rockerDirection = rocker_stay;
 }

 void LRocker::stopRocker()
 {
	 auto spr_iamge = (Sprite*)this->getChildByTag(tag_rockerImage);
	 spr_iamge->setVisible(false);

	 auto spr_BG = (Sprite*)this->getChildByTag(tag_rockerBG);
	 spr_BG->setVisible(false);

	 //把监听去除掉
	// Director::getInstance()->getEventDispatcher()->removeEventListener();
	 _eventDispatcher->removeEventListenersForTarget(this);
 }


 bool LRocker::onTouchBegan(Touch *touch, Event *unused_event)
 {

	 Point point = touch->getLocation();

	 
	 //如果点击的时候的时候，点到了中键的小点，才可以移动
	 auto spr_image = (Sprite*)this->getChildByTag(tag_rockerImage);

	 if (spr_image->getBoundingBox().containsPoint(point))
	 {
		 isCanMove = true;
		 CCLOG("is can move");
	 }
	
	 return true;
 }


 void  LRocker::onTouchMoved(Touch *touch, Event *unused_event)
 {
	 if (!isCanMove)
	 {
		 return;
	 }

	 Point point = touch->getLocation();


	 //得到摇杆的角度
	 auto spr_image = (Sprite*)this->getChildByTag(tag_rockerImage);

	 angle = getRad(rockerBGPosition,point);


	 if (sqrt(pow(rockerBGPosition.x - point.x, 2) + pow(rockerBGPosition.y - point.y, 2))>=rockerBGR)
	 {
		 //如果手指移动的范围超过了摇杆BG，则把摇杆Image放在摇杆的边境上
		 spr_image->setPosition(getAnglePosition(rockerBGR, angle) + rockerBGPosition);
	 }
	 else
	 {
		 spr_image->setPosition(point);
	 }


	 
	 //计算出运动的方向（方向现在基本没有用，因为人物移动用的是角度，但是如果到了其他的游戏里面，可能要用到方向了），和人物的朝向

	 if (angle >= -PI / 4 && angle < PI / 4)
	 {
		 rockerDirection = rocker_right;
		 rocker_run = false;
		 CCLOG("right");
	 }
	 else if (angle>=PI/4&&angle<(PI*3)/4)
	 {
		 if (angle>=PI/2)
		 {
			 rocker_run = true;
		 }
		 else
		 {
			 rocker_run = false;
		 }
		 rockerDirection = rocker_up;
		 CCLOG("up");
	 }
	 else if (angle>=(PI*3)/4||angle<-(PI*3)/4)
	 {
		 rockerDirection = rocker_left;
		 rocker_run = true;
		 CCLOG("Left");
	 }
	 else if (angle>=-(PI*3)/4&&angle<-PI/4)
	 {
		 if (angle>=-PI/2)
		 {
			 rocker_run = false;

		 }
		 else
		 {
			 rocker_run = true;
		 }
		 rockerDirection = rocker_down;
		 CCLOG("Down");
	 }


 }

 //一个回去的动作
 void LRocker::onTouchEnded(Touch *touch, Event *unused_event)
 {
	 if (!isCanMove)
	 {
		 return;
	 }
	 auto spr_image = (Sprite*)this->getChildByTag(tag_rockerImage);

	 auto spr_BG = (Sprite*)this->getChildByTag(tag_rockerBG);

	 spr_image->stopAllActions();
	 spr_image->runAction(MoveTo::create(0.08f,spr_BG->getPosition()));
	 isCanMove = false;
	 rockerDirection = rocker_stay;
	 CCLOG("end");

	 angle = 0;
 }

 void LRocker::update(float dt)
 {
	 if (isCanMove)
	 {

	 }
 }



 float LRocker::getRad(Point point1, Point point2)
 {

	 float px1 = point1.x;
	 float py1 = point1.y;

	 float px2 = point2.x;
	 float py2 = point2.y;

	 float x = abs(px1 - px2);
	 float y = abs(py1 - py2);


	
	 float tanAngle = y / x;

	 float rad =  atan(tanAngle);;

	 //根据摇杆和摇杆座两者的位置，来判断夹角的大小

	 if (px2<px1)
	 {
		 rad = PI - rad;
	 }

	 if (py2<py1)
	 {
		 rad = -rad;
	 }
	 /*

	 float xie =sqrt(pow(x,2)+pow(y,2));

	 float cosAngle = x / xie;

	 //得到的弧度，不是角度
	 float rad = acos(cosAngle);
	 if (px2>px1)
	 {

	 }


	 if (py2<py1)
	 {
		 rad = -rad;
	 }
	 CCLOG("the rad  = %f",rad);*/
	 return rad;
 }


 //得到要把摇杆放到边界上的位置
 Point LRocker::getAnglePosition(float r, float angle)
 {
	 return Point(r*cos(angle),r*sin(angle));
 }


 float LRocker::returnAngle()
 {
	 return angle;
 }
