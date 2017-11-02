#ifndef _CONTROL_BUTTON_H_
#define _CONTROL_BUTTON_H_

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MyControlButton : public Node{
public:
	MyControlButton();
	~MyControlButton();
	CREATE_FUNC(MyControlButton);

	void createButton(const char* name_png,const char* button_title,unsigned int num);
	//�Ƿ��°�ť
	bool isTouch;

	void bindButtonEven();


	/* ����괦�ڰ��²��������а�ťʱ���򴥷�һ�� */
	void touchDownAction(Ref* pSender, Control::EventType event);

	/* ����괦�ڰ��²��������а�ť��״̬�£������밴ť��Χ���򴥷�һ�� */
	void touchDragEnter(Ref* pSender, Control::EventType event);

	/* ����괦�ڰ��²��������а�ť��״̬�£�����뿪��ť��Χ���򴥷�һ�� */
	void touchDragExit(Ref* pSender, Control::EventType event);

	/* ����괦�ڰ��²��������а�ť��״̬�£������밴ť��Χ���򴥷���ֻҪ�ﵽ�������Ͳ��ϴ��� */
	void touchDragInside(Ref* pSender, Control::EventType event);

	/* ����괦�ڰ��²��������а�ť��״̬�£�����뿪��ť��Χ���򴥷���ֻҪ�ﵽ�������Ͳ��ϴ��� */
	void touchDragOutside(Ref* pSender, Control::EventType event);

	/* ����괦�ڰ��²��������а�ť��״̬�£�����ɿ����ڰ�ť��Χ�ڣ��򴥷�һ�� */
	void touchUpInside(Ref* pSender, Control::EventType event);

	/* ����괦�ڰ��²��������а�ť��״̬�£�����ɿ����ڰ�ť��Χ�⣬�򴥷�һ�� */
	void touchUpOutside(Ref* pSender, Control::EventType event);

	/* ��ʱû�з���������괥������¼��Ĳ���������ע�ͣ�Ӧ�����������¼��жϰ�ť�¼��������� */
	void touchCancel(Ref* pSender, Control::EventType event);

	void valueChanged(Ref* pSender, Control::EventType event);

private:
	ControlButton* button;



};



#endif