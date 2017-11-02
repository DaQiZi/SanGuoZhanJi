#include"MyControlButton.h"

MyControlButton::MyControlButton() :isTouch(false), button(NULL)
{

}

MyControlButton::~MyControlButton()
{

}


void MyControlButton::createButton(const char* name_png, const char* button_title, unsigned int num)
{
	Scale9Sprite* spr_btn = Scale9Sprite::create(name_png);
	int png_height = static_cast<int>(spr_btn->getContentSize().height);
	int png_width = static_cast<int>(spr_btn->getContentSize().width);

	//spr_btn->release();

	Rect rect = Rect(0, 0, png_width, png_height);
	Rect rectInsets = Rect(19, 19, 1, 1);

	auto title = Label::createWithTTF("0", "fonts\\Marker Felt.ttf", 50);
	title->setOpacity(num);

	Scale9Sprite * btnNormal = Scale9Sprite::create(name_png, rect, rectInsets);
	button = ControlButton::create(title,btnNormal);
	

	//�󶨰�ť�¼�
	bindButtonEven();
	this->addChild(button);
}



void MyControlButton::bindButtonEven()
{
	if (!button)
	{
		return;
	}

	/*button->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButton::touchDownAction), CCControlEventTouchDown);
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButton::touchDragEnter), CCControlEventTouchDragEnter);
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButton::touchDragExit), CCControlEventTouchDragExit);
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButton::touchDragInside), CCControlEventTouchDragInside);
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButton::touchDragOutside), CCControlEventTouchDragOutside);
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButton::touchUpInside), CCControlEventTouchUpInside);
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButton::touchUpOutside), CCControlEventTouchUpOutside);
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButton::touchCancel), CCControlEventTouchCancel);
*/
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(MyControlButton::touchDownAction), Control::EventType::TOUCH_DOWN);
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(MyControlButton::touchDragInside), Control::EventType::DRAG_INSIDE);
	
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(MyControlButton::touchDragOutside), Control::EventType::DRAG_OUTSIDE);
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(MyControlButton::touchDragEnter), Control::EventType::DRAG_ENTER);
	
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(MyControlButton::touchDragExit), Control::EventType::DRAG_EXIT);
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(MyControlButton::touchUpInside), Control::EventType::TOUCH_UP_INSIDE);
	
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(MyControlButton::touchUpOutside), Control::EventType::TOUCH_UP_OUTSIDE);
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(MyControlButton::touchCancel), Control::EventType::TOUCH_CANCEL);
	
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(MyControlButton::valueChanged), Control::EventType::VALUE_CHANGED);




}


/* ����괦�ڰ��²��������а�ťʱ���򴥷�һ��    ����*/
void MyControlButton::touchDownAction(Ref* pSender, Control::EventType event)
{
	isTouch = true;
	//log("touchDownAction");
}
/* ����괦�ڰ��²��������а�ť��״̬�£������밴ť��Χ���򴥷�һ�� */
void MyControlButton::touchDragEnter(Ref* pSender, Control::EventType event)
{
	//log("touchDragEnter");
}
/* ����괦�ڰ��²��������а�ť��״̬�£�����뿪��ť��Χ���򴥷�һ�� */
void MyControlButton::touchDragExit(Ref* pSender, Control::EventType event)
{
	//log("touchDragExit");
}
/* ����괦�ڰ��²��������а�ť��״̬�£������밴ť��Χ���򴥷���ֻҪ�ﵽ�������Ͳ��ϴ��� */
void MyControlButton::touchDragInside(Ref* pSender, Control::EventType event)
{
	//log("touchDragInside");
}
/* ����괦�ڰ��²��������а�ť��״̬�£�����뿪��ť��Χ���򴥷���ֻҪ�ﵽ�������Ͳ��ϴ��� */
void MyControlButton::touchDragOutside(Ref* pSender, Control::EventType event)
{
	isTouch = false;
	//log("touchDragOutside");
}  
/* ����괦�ڰ��²��������а�ť��״̬�£�����ɿ����ڰ�ť��Χ�ڣ��򴥷�һ��    �ɿ� */
void MyControlButton::touchUpInside(Ref* pSender, Control::EventType event)
{
	isTouch = false;
	log("touchUpInside");
}

/* ����괦�ڰ��²��������а�ť��״̬�£�����ɿ����ڰ�ť��Χ�⣬�򴥷�һ�� */
void MyControlButton::touchUpOutside(Ref* pSender, Control::EventType event)
{
	isTouch = false;
	//log("touchUpOutside");

}
/* ��ʱû�з���������괥������¼��Ĳ���������ע�ͣ�Ӧ�����������¼��жϰ�ť�¼��������� */
void MyControlButton::touchCancel(Ref* pSender, Control::EventType event)
{
	//log("touchCancel");
}

void MyControlButton::valueChanged(Ref* pSender, Control::EventType event)
{
	//log("valueChanged");
}