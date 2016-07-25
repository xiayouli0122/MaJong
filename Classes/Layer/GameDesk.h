//
//  GameDesk.h
//  xzdd
//
//  Created by  on 12-2-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GameDesk_h
#define xzdd_GameDesk_h

#include "cocos2d.h"
#include "GameMenu.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"
#include "TypeDef.h"
#include "MyCardsBatch.h"
#include "DeskCardsBatch.h"
#include "Timer.h"
#include "ActionBatch.h"
#include "MarkBatch.h"
#include "Robot.h"

#else 

#include "../Common/ConstantDef.h"
#include "../GameCore/TypeDef.h"
#include "../Sprite/Batch/MyCardsBatch.h"
#include "../Sprite/Batch/DeskCardsBatch.h"
#include "../Sprite/Timer.h"
#include "../Sprite/Batch/ActionBatch.h"
#include "../Sprite/Batch/MarkBatch.h"
#include "../GameCore/AI/Robot.h"

#endif


using namespace cocos2d;

//桌面状态定义
typedef enum 
{
    D_None,
    D_Lock,
    D_DingQue,
    D_AfterMo_ChooseAction,     
    D_AfterMo_ChooseOut,
    D_AfterOut_ChooseAction,
    D_AfterAction_ChooseCard,
    D_LogicOver,
    D_GameOver,
    D_ERROR
    
} DeskState; 


//游戏桌面层
class GameDesk : public cocos2d::CCLayer
{
    //私有变量------------------------------------------------
    DeskState       d_State;        //牌桌状态
    CGameLogical    game;           //主逻辑对象
    BYTE            m_Chair;        //玩家座位，默认是0
    PLAYER          * m_player;       //电脑玩家
    USERTYPE        userType[4];       //用户类型 男，女
    
    GameMenu        * gameMenu;         //游戏菜单
    MyCardsBatch    * myCardsBatch;     //自己牌缓存
    DeskCardsBatch  * deskCardsBatch;   //桌面牌缓存
    Timer           * timer;            //定时器对象
    ActionBatch     * actionBatch;      //Aciton菜单
    MarkBatch       * markBatch;        //标记缓存
    
    CCMenuItemSprite *pBuyCoinItem;     //充值
    CCMenuItemSprite *pBuyCardItem;
    int _nCash;
    CCLabelTTF *pLabelCoin;
    
    Robot  robots[3];                   //AI集合
    GUAN_KA gk;
    
    unsigned short  CurrentTime;    //当前计时器时间
    BYTE currentActivityPlayer;     //当前活动玩家
    BYTE logicPlayerStateCount;     //逻辑层玩家状态统计
    
    bool isPause;
    bool isFase;    //是否是快牌模式
    int iNomi;      //大牌几率分子
    int iDeNomi;    //大牌几率分母
    bool isPlayerHu;//玩家是否胡牌
    bool isHu[4];   //是否胡牌
    BYTE m_bSeenOutCard;
    bool isQiangGang; //是否是抢杠
public:
    //初始化--------------------------------------------------
	virtual bool init();  
    virtual void onExit();
    virtual void onEnter();
	// implement the "static node()" method manually
	CREATE_FUNC(GameDesk);
    
    virtual void menuBuyCoinCallback(CCObject* pSender);
    virtual void menuBuyCardCallback(CCObject* pSender);
    
    void BuyCard();
    
    //触摸相关方法---------------------------------------------
    virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    
    void ShowCardNo13();
    void Action_ChooseCard(BYTE playIndex,BYTE card,BYTE cardIndex);
    
    //Action菜单回调
    void ActionX();
    void ActionP();
    void ActionZG();
    void ActionMoG();
    void ActionH();
    void ActionDingQue(BYTE playIndex,PAI_TYPE type);
    
    //逻辑层回调处理 设置状态后，延时处理
    void OnLogicOver();
    void Process_LogicOver();
    void DrawLastAction();
    void DrawHu();
    void DrawTableCards();
    void OnGetExCard();//获得大牌
    
    //音效预处理
    void preloadAllEffects();
    
    void onPause();
    void onResume();
    void onSystemResume();
    
    void UpdateCoinLabel();
    
private:
    
    void DealAllCardAction();       //发牌
    void OutCardActionForce();      //强制出牌
    
    //主要动作
    void Action_Mo();
    void Action_H(BYTE playerIndex);
    void Action_ChooseOutCard(BYTE playIndex,BYTE card,BYTE cardIndex);
    void Action_ChooseMoGCard(BYTE playIndex,BYTE card,BYTE cardIndex); //摸杠（包括暗杠、弯杠）
    void GameOver();
    
    //辅助函数
    void SetTimer(unsigned short  currentTime); //设置倒计时
    void SetDeskState(DeskState  state); //设置桌面状态
    
    void Process_AfterMoPlayerChoose(BYTE playIndex); //摸牌，碰牌，杠牌后，如果还有命令选择时的处理
    bool IsOver();     //over后处理
    
    //处理状态定时器，定时调用
    void undateState(float dt);
};

#endif
