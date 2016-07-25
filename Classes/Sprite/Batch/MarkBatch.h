//
//  MarkBatch.h
//  xzdd
//
//  Created by  on 12-3-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_MarkBatch_h
#define xzdd_MarkBatch_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include "ConstantDef.h"
#include "CommonFunction.h"
#include "Card.h"
#include "OutCard.h"
#include "GameLogical.h"
#include "ScrollWordAndImage.h"
#else 
#include "../../Common/ConstantDef.h"
#include "../../Common/CommonFunction.h"
#include "../Card.h"
#include "../OutCard.h"
#include "../../GameCore/GameLogical.h"
#include "../ScrollWordAndImage.h"
#endif


using namespace cocos2d;

//菜单类型定义
typedef enum 
{
    HT_HU,
    HT_ZHIMO,
    HT_JIPIN
} HuType; 

//桌面标记缓存 （定缺，动作显示 ）
class MarkBatch : public CCNode
{
private:
    
protected:
    CCSpriteBatchNode * markBatchNode;
    CCArray *CardsArrayWall;
    
    //辅助定缺标记使用
    BYTE    markSelected[4];    //0没有选择， 1已经选择
    
	//CCSprite*
    //头像标记
    CCArray *markIco;
    //定缺标记
    CCArray *markDingQue;
    //动作标记
    CCArray *markAction;
    //胡牌标记
    CCArray *markHu;
//     //断线标记
//     CCArray *markDisConn;
    //聊天标记
    CCArray *markChatbj;

	//ScrollWordAndImage*
    CCArray *markChat;

	//CCLabelTTF*
	//积分
    CCArray *markSoure;
    //名字
    CCArray *markName;
//     //准备好标记  网络用
//     CCArray *markReady;
    //庄标记
    CCSprite * markZhuang;
    
public:
	//初始化--------------------------------------------------
	virtual bool init();
    virtual void onExit();
    void initForSet();
    void initForReady();
	CREATE_FUNC(MarkBatch);
    
    BYTE    m_Chair;    //玩家座位
    USERTYPE        userType[4];    //用户类型 男，女
    
    //公有方法------------------------------------------------
    //设置用户标记
    void SetMarkPerson(BYTE chair,string name,long soure,const char *ico,USERTYPE type);
    void SetMarkPerson(BYTE chair,string name,long soure,const char *ico,USERTYPE type, BYTE userStatus);
    //设置用户离开
    void SetMarkPersonLeft(BYTE chair);
    //设置定缺标记
    void SetMarkDingQue(BYTE playIndex,PAI_TYPE type);
    void SetMarkAllDingQue(DING_QUE * dingque);
    //设置动作
    void SetMarkAction(BYTE playIndex,BYTE cmdID);
    //设置胡牌标记
    void SetMarkHU(BYTE playIndex,HuType type);
    //设置庄标记
    void SetMarkZhuang(BYTE playIndex);
    //设置游戏状态 准备开始，游戏状态
    void SetMarkGameStatus(bool isReady);
    //显示聊天内容
    void onChat(BYTE chair, char* msg);
    void ShowChatTimeOver(CCNode* sender,void* pIndex);
    
};

#endif