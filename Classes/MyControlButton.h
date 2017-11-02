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
	//是否按下按钮
	bool isTouch;

	void bindButtonEven();


	/* 当鼠标处于按下并曾经点中按钮时，则触发一次 */
	void touchDownAction(Ref* pSender, Control::EventType event);

	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标进入按钮范围，则触发一次 */
	void touchDragEnter(Ref* pSender, Control::EventType event);

	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标离开按钮范围，则触发一次 */
	void touchDragExit(Ref* pSender, Control::EventType event);

	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标进入按钮范围，则触发，只要达到条件，就不断触发 */
	void touchDragInside(Ref* pSender, Control::EventType event);

	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标离开按钮范围，则触发，只要达到条件，就不断触发 */
	void touchDragOutside(Ref* pSender, Control::EventType event);

	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标松开且在按钮范围内，则触发一次 */
	void touchUpInside(Ref* pSender, Control::EventType event);

	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标松开且在按钮范围外，则触发一次 */
	void touchUpOutside(Ref* pSender, Control::EventType event);

	/* 暂时没有发现能用鼠标触发这个事件的操作，看了注释，应该是由其它事件中断按钮事件而触发的 */
	void touchCancel(Ref* pSender, Control::EventType event);

	void valueChanged(Ref* pSender, Control::EventType event);

private:
	ControlButton* button;



};



#endif