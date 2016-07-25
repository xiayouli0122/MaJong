//
//  MyCardsBatch.h
//  xzdd
//
//  Created by  on 12-2-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_MyCardsBatch_h
#define xzdd_MyCardsBatch_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include "ConstantDef.h"
#include "CommonFunction.h"
#include "MyCard.h"
#include "GameLogical.h"
#else 
#include "../../Common/ConstantDef.h"
#include "../../Common/CommonFunction.h"
#include "../MyCard.h"
#include "../../GameCore/GameLogical.h"
#endif

using namespace cocos2d;

//手牌缓存
class MyCardsBatch : public cocos2d::CCNode
{
//桌面状态定义
typedef enum 
{
    MC_AfterMo_ChooseOut,
    MC_AfterAction_ChooseCard,
    MC_DingQue_ChooseOut,
    MC_ERROR
} MCState;   
    
private:
    //touch事件中，循环处理被选中的手牌
    void touchSelectCard(CCPoint touchLocation);
    
    void setEnableCard();
    void setMoCard(BYTE card);
protected:
//    CCMutableArray<MyCard*> *myCardArray;           //手牌数组
//    CCMutableArray<MyCard*> *enableTouchCardArray;  //能够触摸的手牌数组
	CCArray *myCardArray;           //手牌数组
	CCArray *enableTouchCardArray;  //能够触摸的手牌数组
    MyCard * selectedCard;                          //被选择的手牌
    MyCard * shadowCard;                            //影子牌
    MyCard * moCard;                                //玩家摸到的牌
    MCState mc_state;                               //手牌状态
    
public:
	//初始化--------------------------------------------------
	virtual bool init();
    virtual void onExit();
	// implement the "static node()" method manually
	CREATE_FUNC(MyCardsBatch);
    
    PAI_TYPE dingQueType;                           //玩家定缺类型

    //公有方法------------------------------------------------
    //通过逻辑对象，设置所有手牌
    void SetMyCard(PLAYER_DATA *playerData);
    //摸牌
    void MoCardActive(PLAYER_DATA *playerData);
    //出牌后
    void OutCardActive(PLAYER_DATA *playerData);
    //在动作菜单后 选择牌
    void ChooseCardAfterAction(BYTE * cards);
    //设置胡牌 亮牌
    void SetHU(BYTE huCard);
    void SetLIANG();
    //获取需要强制出牌的索引 定缺时使用
    MyCard * GetForceOutCard();
    
    //触摸相关方法---------------------------------------------
    virtual bool touchBegan(CCTouch* touch);
	virtual void touchEnded(CCTouch* touch);
	virtual void touchCancelled(CCTouch* touch);
	virtual void touchMoved(CCTouch* touch);
};

#endif
