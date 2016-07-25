#ifndef xzdd_GameMGSprite_h
#define xzdd_GameMGSprite_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"

#else 

#include "../Common/ConstantDef.h"

#endif

using namespace cocos2d;

class GameMGSprite : public CCSprite
{
    CCLabelTTF * title; //标题
    CCLabelTTF * content;//内容
	MOREGAME * moreGame;
public:
    
	GameMGSprite(void);
	~GameMGSprite(void);
    
	virtual bool init();
    
    //公有方法------------------------------
    //通过图片名创建成就对象
    static GameMGSprite* mgWithFrameName( MOREGAME * mg);
    
	void menuBackCallback(CCObject* pSender);
    
};

#endif