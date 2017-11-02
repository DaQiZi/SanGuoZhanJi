#ifndef _BLOOD_PROGRESS_H_
#define _BLOOD_PROGRESS_H_
#include "cocos2d.h"
using namespace cocos2d;

class BloodProgress : public Sprite{


public:
	BloodProgress();
	void setBackgroundTexture(const char* name);
	void setForegroundTexture(const char* name);
	void setTotalBlood(float blood);
	void setNowBlood(float blood);

	float getTotalBlood();
	float getNowBlood();

	CREATE_FUNC(BloodProgress);
	
private:
	Sprite* spr_bloodProgressBackground;
	Sprite* spr_bloodProgressForeground;
	float totalBlood;
	float nowBlood;
	float scale;
	//Sprite* bloodRrogress;
};


#endif