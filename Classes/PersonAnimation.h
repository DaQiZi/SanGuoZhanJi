#ifndef _PERSON_ANIMATION_H_
#define _PERSON_ANIMATION_H_
#include "iostream"
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;
class PersonAnimation : public Ref{

public:
	char* personName;
	char* personDeadName;

	char* movePlist;
	char* moveEachName;
	int moveNum;

	char* attackPlist;
	char* attackEachName;
	int attackNum;

	char* hurtPlist;
	char* hurtEachName;
	int hurtNum;

	char* deadPlist;
	char* deadEachName;
	int deadNum;
};


#endif