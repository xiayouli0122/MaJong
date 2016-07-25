//
//  GameResult.cpp
//  xzdd
//
//  Created by  on 12-4-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <string>
#include "GameResult.h"
#include "SimpleAudioEngine.h"
#include "GameMenu.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
//#include "LayerNetGameDesk.h"
#include "IOSCommon.h"
#else 
//#include "Net/LayerNetGameDesk.h"
#endif

using namespace cocos2d;

bool GameResult::init()
{
	//////////////////////////////
	// 1. super init first
    ccColor4B c = {0,0,0,150};
	if (!CCLayerColor::initWithColor(c) )
	{
		return false;
	}
    
    _isPassGuan = false;
    
    //加入message层
    pGameMessage = GameMessage::create();
    this->addChild(pGameMessage,1);
    
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
//    
//    //加入背景
//    bjSprite = new CCSprite();
//    if (CommonFunction::isIpad()) {
//        bjSprite->initWithFile(CONS_Image_BG_JS_Ipad);
//    }else {
//        bjSprite->initWithFile(CONS_Image_BG_JS);
//    }
//    bjSprite->setAnchorPoint(ccp(0.5, 0.5));
//    bjSprite->setPosition(ccp(ptPos.x + winSize.width * 0.5, winSize.height * 0.5));
//    this->addChild(bjSprite,0,0);
    
    
	return true;
}

void GameResult::initWithGameType(GameType type)
{
    mType = type;
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
//    
//	// 加入菜单
//    CCSprite * ccPause = CCSprite::create(CONS_Image_Set_return);
//    CCMenuItemSprite *pItem1 = CCMenuItemSprite::create(ccPause,NULL,NULL,this, 
//                                                                      menu_selector(GameResult::menuHideCallback));
//	pItem1->setPosition( ccp(ptPos.x + winSize.width*0.95,winSize.height*0.08) ); 
//
//	CCMenu* pMenu = CCMenu::create(pItem1,NULL);
//	pMenu->setPosition( CCPointZero );
//	this->addChild(pMenu, 3);
    
    this->setVisible(false);
}

void GameResult::initForSet()
{
    removeAllChildrenWithCleanup(true);
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ptPos = CCDirector::sharedDirector()->getVisibleOrigin();
    //加入背景
    bjSprite = new CCSprite();
    if (CommonFunction::isIpad()) {
        bjSprite->initWithFile(CONS_Image_BG_JS_Ipad);
    }else {
        bjSprite->initWithFile(CONS_Image_BG_JS);
    }
    bjSprite->setAnchorPoint(ccp(0.5, 0.5));
    bjSprite->setPosition(ccp(ptPos.x + winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(bjSprite,0,0);
    
    // 加入菜单
    CCSprite * ccPause = CCSprite::createWithSpriteFrameName(CONS_Image_Set_return);
    CCSprite * ccPause2 = CCSprite::createWithSpriteFrameName(CONS_Image_Set_return_2);
    CCMenuItemSprite *pItem1 = CCMenuItemSprite::create(ccPause,ccPause2,NULL,this, 
                                                                      menu_selector(GameResult::menuHideCallback));
	pItem1->setPosition( ccp(ptPos.x + winSize.width*0.95,winSize.height*0.08) ); 
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        bjSprite->setAnchorPoint(ccp(0.5f,0.5f));
        bjSprite->setPosition(ccp(ptPos.x + winSize.width / 2.0f, winSize.height / 2.0f));
        bjSprite->setScale(2.0f);
        pItem1->setScale(2.0f);
    }
#endif
    
	CCMenu* pMenu = CCMenu::create(pItem1,NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 3);
}
//#pragma mark 显示结果网络单机通用部分
void GameResult::ShowResult(BYTE * numFan,HU_CURT * huCurt,long * gangScore,long * huazhuScore, long * dajiaoScore,PLAYER_DATA * m_sPlayer)
{
    initForSet();
    
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ptPos = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSize bjSize = bjSprite->getContentSize();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        bjSize = bjSprite->boundingBox().size;
    }
#endif
    
    for (int i=0; i<PLAYER_COUNT; i++) {
        
        char str[250];
        
        //---------合计框------------
        //姓名
        CCLabelTTF* l_name = CCLabelTTF::create(GetUserName(i), "Thonburi", CommonFunction::GetValueByDev(12));
        l_name->setPosition( ccp(ptPos.x + winSize.width*0.5-bjSize.width*0.35, 
                                 winSize.height * 0.5 + bjSize.height *(0.37-0.135*i)) );
        this->addChild(l_name,3);
        
        //姓名
        CCLabelTTF* l_name1 = CCLabelTTF::create(GetUserName(i), "Thonburi", CommonFunction::GetValueByDev(13));
        l_name1->setPosition( ccp(ptPos.x + winSize.width*0.5 - bjSize.width*(0.3 - 0.40*(i%2)) ,
                                  winSize.height * 0.5 - bjSize.height*(0.31 + 0.08*(i/2))) );
        this->addChild(l_name1,3);
        
        //合计
        CCLabelTTF* l_ji = CCLabelTTF::create(CONS_STRING_JI, "Thonburi", CommonFunction::GetValueByDev(12));
        l_ji->setColor(CC_Blue);
        l_ji->setPosition( ccp(ptPos.x + winSize.width*0.5 + bjSize.width*0.336,
                               winSize.height * 0.5 + bjSize.height *(0.34-0.135*i)) );
        this->addChild(l_ji,3);
        
        //合计番
        sprintf(str,"%d%s",numFan[i],CONS_STRING_Fan);
        CCLabelTTF* l_fan = CCLabelTTF::create(str, "Thonburi", CommonFunction::GetValueByDev(12));
        l_fan->setColor(CC_Yellow);
        l_fan->setPosition( ccp(ptPos.x + winSize.width*0.5 + bjSize.width*0.399,
                                winSize.height * 0.5 + bjSize.height *(0.31-0.135*i)) );
        this->addChild(l_fan,3);
        
        //胡图标
        CCSprite * cc_hu = CCSprite::createWithSpriteFrameName(CONS_MARK_HuImage);
        if(numFan[i] >= 4)
        {
            cc_hu->initWithSpriteFrameName(CONS_MARK_JiPinImage);
        }
        else if(huCurt[i].nState == ZI_MO)
        {
            cc_hu->initWithSpriteFrameName(CONS_MARK_ZiMoImage);
        }
        else if(huCurt[i].nState == CHI_PAO)
        {
        }
        
        else
        {
            cc_hu->setVisible(false);
        }
        cc_hu->setPosition( ccp(ptPos.x + winSize.width*0.5 - bjSize.width*0.231,
                                winSize.height * 0.5 + bjSize.height *(0.37-0.135*i)) );
        cc_hu->setScale(0.7);
        this->addChild(cc_hu,3);     
        
        //放炮
        CCLabelTTF* l_fp = CCLabelTTF::create("", "Thonburi", CommonFunction::GetValueByDev(12));
        l_fp->setColor(CC_Yellow);
        l_fp->setPosition( ccp(ptPos.x + winSize.width*0.51, 
                               winSize.height * 0.5 + bjSize.height *(0.37-0.135*i)) );
        this->addChild(l_fp,3);
        if (huCurt[i].nState == CHI_PAO) {
            CCLabelTTF* l_fpname = CCLabelTTF::create(GetUserName(huCurt[i].nGainChair[1]), "Thonburi", CommonFunction::GetValueByDev(12));
            l_fpname->setColor(CC_Red);
            l_fpname->setPosition( ccp(ptPos.x + winSize.width*0.5 - bjSize.width*0.105,
                                       winSize.height * 0.5 + bjSize.height *(0.37-0.135*i)) );
            this->addChild(l_fpname,3);
            
            l_fp->setString(CONS_STRING_GP);
        }
        else if(huCurt[i].nState == ZI_MO && numFan[i] >= 4){
            l_fp->setString(CONS_STRING_ZM);
        }

        //刮风下雨
        CCLabelTTF* l_gfxy = CCLabelTTF::create(CONS_STRING_GFXY, "Thonburi", CommonFunction::GetValueByDev(12));
        l_gfxy->setColor(CC_Red);
        l_gfxy->setPosition( ccp(ptPos.x + winSize.width*0.5 + bjSize.width*0.158, 
                                 winSize.height * 0.5 + bjSize.height *(0.37-0.135*i)) );
        this->addChild(l_gfxy,3);
        
        sprintf(str,"%ld%s",gangScore[i],CONS_STRING_Fen);
        CCLabelTTF* l_gfxyfen = CCLabelTTF::create(str, "Thonburi", CommonFunction::GetValueByDev(12));
        l_gfxyfen->setColor(CC_Yellow);
        l_gfxyfen->setPosition( ccp(ptPos.x + winSize.width*0.5 + bjSize.width*0.263, 
                                    winSize.height * 0.5 + bjSize.height *(0.37-0.135*i)) );
        this->addChild(l_gfxyfen,3);
        
        //---第二行文字---
        CCLabelTTF* l_jtfan = CCLabelTTF::create ("", "Thonburi", CommonFunction::GetValueByDev(12));
        l_jtfan->setPosition( ccp(ptPos.x + winSize.width*0.5 - bjSize.width*0.105,
                                  winSize.height * 0.5 + bjSize.height *(0.31-0.135*i)) );
        this->addChild(l_jtfan,3);
        
        //花猪
        if (m_sPlayer[i].nState == HUAZHU) {
            string strEx = "";
            for (int j=0; j<PLAYER_COUNT; j++) {
                if (m_sPlayer[j].nState != HUAZHU) {
                    strEx += GetUserName(j);
                    strEx += " ";
                }
            }
            sprintf(str,"花猪给 %s%ld%s",strEx.c_str(),huazhuScore[i],CONS_STRING_Fen);
            l_jtfan->setString(str);
        }
        //大叫
        else if(m_sPlayer[i].nState == DAJIAO && dajiaoScore[i]!= 0){
            string strEx = "";
            for (int j=0; j<PLAYER_COUNT; j++) {
                if (huCurt[j].nState == HU_DA_JIAO) {
                    strEx += GetUserName(j);
                    strEx += " ";
                }
            }
            sprintf(str,"大叫给 %s%ld%s",strEx.c_str(),dajiaoScore[i],CONS_STRING_Fen);
            l_jtfan->setString(str);
        }
        else if(m_sPlayer[i].nState == BLOOD_HU){
            //具体番
            string strEx = "";
            for(int j=0; j< huCurt[i].nCount; j++)
            {
                if(j)
                {
                    strEx += " ";
                }
                strEx += CommonFunction::HuTypeToString(huCurt[i].nMethod[j]);
            }
            l_jtfan->setString(strEx.c_str());
        }
        


    }
}
//#pragma mark 显示结果网络部分
void GameResult::ShowNetResult(HU_CURT * huCurt, PLAYER_DATA * m_sPlayer,BYTE endReason,BYTE * numFan, long *totalScore,
                   long * setScore, long *setLostScore, long * gangScore,long * huazhuScore, long * dajiaoScore)
{
    ShowResult(numFan,huCurt,gangScore,huazhuScore, dajiaoScore,m_sPlayer);
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ptPos = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSize bjSize = bjSprite->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        bjSize = bjSprite->boundingBox().size;
    }
#endif
    for (int i=0; i<PLAYER_COUNT; i++) {
        
        char str[250];
        
        //合计分
        sprintf(str,"%ld%s",totalScore[i],CONS_STRING_Fen);
        CCLabelTTF* l_fen = CCLabelTTF::create(str, "Thonburi", CommonFunction::GetValueByDev(12));
        l_fen->setColor(CC_Yellow);
        l_fen->setPosition( ccp(ptPos.x + winSize.width*0.5 + bjSize.width*0.399,
                                winSize.height * 0.5 + bjSize.height *(0.37-0.135*i)) );
        this->addChild(l_fen,3);

        //---------合计框------------
        //合计分
        sprintf(str,"%ld%s",totalScore[i],CONS_STRING_Fen);
        CCLabelTTF* l_fen1 = CCLabelTTF::create(str, "Thonburi", CommonFunction::GetValueByDev(13));
        l_fen1->setColor(CC_Yellow);
        l_fen1->setPosition( ccp(ptPos.x + winSize.width*0.5 - bjSize.width*(0.12 - 0.40*(i%2)) ,
                                 winSize.height * 0.5 - bjSize.height*(0.31 + 0.08*(i/2))));
        this->addChild(l_fen1,3);

    }

    this->setVisible(true);
}
//#pragma mark 显示结果单机部分
void GameResult::ShowLocalResult(Score_Struct * sScore, HU_CURT * huCurt, BYTE * numFan,
                            long * gangScore,long * huazhuScore, long * dajiaoScore,PLAYER_DATA * m_sPlayer,BYTE endReason, long* setFanScore)
{
    ShowResult(numFan,huCurt,gangScore,huazhuScore, dajiaoScore,m_sPlayer);
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ptPos = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSize bjSize = bjSprite->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        bjSize = bjSprite->boundingBox().size;
    }
#endif
    char str[256];
    
    for (int i=0; i<PLAYER_COUNT; i++) {
        
        //合计分
        sprintf(str,"%ld%s",setFanScore[i] + dajiaoScore[i],CONS_STRING_Fen);
        CCLabelTTF* l_fen = CCLabelTTF::create(str, "Thonburi", CommonFunction::GetValueByDev(12));
        l_fen->setColor(CC_Yellow);
        l_fen->setPosition( ccp(ptPos.x + winSize.width*0.5 + bjSize.width*0.399,
                                winSize.height * 0.5 + bjSize.height *(0.37-0.135*i)) );
        this->addChild(l_fen,3);
        
        //---------合计框------------
        //合计分
        sprintf(str,"%ld%s",sScore[i].lScore,CONS_STRING_Fen);
        CCLabelTTF* l_fen1 = CCLabelTTF::create(str, "Thonburi", CommonFunction::GetValueByDev(13));
        l_fen1->setColor(CC_Yellow);
        //show coin
        if (i==0)
        {
            l_fen1->setPosition( ccp(ptPos.x + winSize.width*0.5 - bjSize.width*0.2 ,
                                     winSize.height * 0.5 - bjSize.height*0.31));
        }
        else
        {
            l_fen1->setPosition( ccp(ptPos.x + winSize.width*0.5 - bjSize.width*(0.15 - 0.40*(i%2)) ,
                                     winSize.height * 0.5 - bjSize.height*(0.31 + 0.08*(i/2))));
        }
        
        this->addChild(l_fen1,3);
    }
    
    //-------刷新关卡统计数据
    GUANKA_STATS gkState = CommonFunction::GetGuanKaStats(GetIntegerToXML(UD_CurrentGuanKa));
    //局
    gkState.nSet++;
    //分
    gkState.nScore = gkState.nScore + sScore[0].lScore;
    
    //单机游戏金币更新
//    long lCoin = GetIntegerToXML(UD_SINGLE_COIN);
//    lCoin += sScore[0].lScore/(long)SCORE_BASE*COIN_MUL;
//    if (lCoin <0)
//    {
//        lCoin = 0;
//    }
//    SetIntegerToXML(UD_SINGLE_COIN, lCoin);
    
    long lValue = sScore[0].lScore/(long)SCORE_BASE*COIN_MUL;
    int  nCoin = 0;
    if (lValue>0)
    {
        nCoin = CommonFunction::AddCoin(lValue);
        sprintf(str,"(游戏币+%ld)",lValue);
    }
    else if(lValue<0)
    {
        nCoin = CommonFunction::SubCoin(-lValue);
        sprintf(str,"(游戏币%ld)",lValue);
    }
    else
    {
        sprintf(str,"(游戏币+0)");
    }
    
    ((GameMenu *)this->getParent())->HideInfoMsg();
    if (CommonFunction::SubmitCoin(nCoin) == 1)
    {
//        ((GameMenu *)this->getParent())->ShowRecInfoMsg(nCoin);
        ((GameMenu *)this->getParent())->ShowInfoMsg(INFO_NEW_RECORD, nCoin);
    }
    
    //show coin
    
    CCLabelTTF* l_coin = CCLabelTTF::create(str, "Thonburi", CommonFunction::GetValueByDev(12));
    l_coin->setColor(CC_Yellow);
    l_coin->setPosition( ccp(ptPos.x + winSize.width*0.5 - bjSize.width*0.06 ,
                             winSize.height * 0.5 - bjSize.height*0.31) );
    this->addChild(l_coin,3);

    
//    if (mType == GT_SingleGame)
//    {
//        long lCoin = GetIntegerToXML(UD_SINGLE_COIN);
//        lCoin += sScore[0].lScore/(long)SCORE_BASE*COIN_MUL;
//        if (lCoin <0)
//        {
//            lCoin = 0;
//        }
//        SetIntegerToXML(UD_SINGLE_COIN, lCoin);
//        if (lCoin < 20)
//        {
//            //paddy test 提示充值
//            CCLOG("***** no coin *****");
//            ((GameMenu *)this->getParent())->ShowNoCoinMessage();
//        }
//    }
    
    //番
    gkState.nFan = gkState.nFan + numFan[0];
    //极品
    if (numFan[0] >= 4) {
        gkState.nJiPin++;
    }
    CommonFunction::SetGuanKaStats(gkState);
    
    //-------更新其他玩家数据
    PLAYER * p = CommonFunction::GetPlayersByGuan(gkState.guanKa);
    p[0].nSource = p[0].nSource + sScore[1].lScore;
    p[1].nSource = p[1].nSource + sScore[2].lScore;
    p[2].nSource = p[2].nSource + sScore[3].lScore;
    CommonFunction::SetPlayers(p);
    
    //-------显示成就
    BYTE count;
    ((GameMenu *)this->getParent())->showCJ(CommonFunction::GetChengJiu_GameOver(
                                            m_sPlayer[0].nState == HUAZHU,          //是否花猪
                                            m_sPlayer[0].nState == DAJIAO,          //是否大叫
                                            endReason == REASON_NOCARD,     //是否流局
                                            numFan[0] != 0,                 //是否胡牌
                                            numFan[0],                    //番数
                                            count),
                                            count);
    
    //-------过关判断
    GUAN_KA gk = CommonFunction::GetGuanKa(GetIntegerToXML(UD_CurrentGuanKa));

    //判断是否3星过关
    if (gk.isDoubleCondition) {
        if (CommonFunction::IsReachCONDITION(gk.conditionThree1, gkState.nScore, gkState.nSet, gkState.nFan, gkState.nJiPin) &&
            CommonFunction::IsReachCONDITION(gk.conditionThree2, gkState.nScore, gkState.nSet, gkState.nFan, gkState.nJiPin)) {
            gkState.passStar = 3;
            PassGuan(gkState);
        }
    }
    else
    {
        if(CommonFunction::IsReachCONDITION(gk.conditionThree1, gkState.nScore, gkState.nSet, gkState.nFan, gkState.nJiPin))
        {
            gkState.passStar = 3;
            PassGuan(gkState);
        }
    }
//    ((GameMenu *)this->getParent())->_isPassGuan = _isPassGuan;
    //判断是否2星过关
    if (!_isPassGuan && CommonFunction::IsReachCONDITION(gk.conditionTwo, gkState.nScore, gkState.nSet, gkState.nFan, gkState.nJiPin))
    {
        gkState.passStar = 2;
        PassGuan(gkState);
    }
    //判断是否1星过关
    if (!_isPassGuan && CommonFunction::IsReachCONDITION(gk.conditionOne, gkState.nScore, gkState.nSet, gkState.nFan, gkState.nJiPin))
    {
        gkState.passStar = 1;
        PassGuan(gkState);
    }
    
    ((GameMenu *)this->getParent())->_isPassGuan = _isPassGuan;
    
    //-----根据合计 播放音效------
    if(_isPassGuan)  //过关
    {
        SOUND->playEffect(CONS_Sound_Through);
    }
    else if(sScore[0].lScore > 0) //胜利
    {
        SOUND->playEffect(CONS_Sound_Complete);
    }
    else if(sScore[0].lScore == 0) //分为0
    {
        SOUND->playEffect(CONS_Sound_End);
    }
    else //失败
    {
        SOUND->playEffect(CONS_Sound_Failed);
    }

    
    this->setVisible(true);
}

//过关的更新
void GameResult::PassGuan(GUANKA_STATS gk)
{
    _isPassGuan = true;
    
//    bool bIsGkOpened = GetBoolToXML(UD_GUANKA_OPEN, false);
    
    if (ISANDROID)
    {
        CommonFunction::sendStatistic(gk.nSet, gk.guanKa, GetIntegerToXML(UD_SINGLE_COIN));
        
    }
    
    if (gk.guanKa == 1)
    {
        SetBoolToXML(UD_PASS_GUANKA_1, true);
    }
    
    if (gk.guanKa == 3) {
        SetBoolToXML(UD_PASS_GUANKA_3, true);
    }
    
    //过关设置
    if (gk.guanKa + 1 <= 12)
    {
        GUANKA_STATS nextgk = CommonFunction::GetGuanKaStats(gk.guanKa + 1);
//        if (bIsGkOpened)
//        {
//            nextgk.isLock = false;
//        }
        
        nextgk.isLock = false;
        
        CommonFunction::SetGuanKaStats(nextgk);
    }
    
    gk.nSet = 0;
    gk.nScore = 0;
    gk.nFan = 0;
    gk.nJiPin = 0;
    
    CommonFunction::SetGuanKaStats(gk);
}

//获取用户名
char * GameResult::GetUserName(BYTE index)
{
    if(mType== GT_SingleGame)
    {
        static char temp[125];
        memset(temp,0,sizeof(temp));
        char * str = temp;        
        PLAYER * m_player = CommonFunction::GetPlayersByGuan(GetIntegerToXML(UD_CurrentGuanKa));
        PLAYER m_user = CommonFunction::GetUser();
        
        if (index==0)
        {
//            sprintf(str,"%s",m_user.nName);
            sprintf(str, "我");
        }
        else{
            sprintf(str, "%s",m_player[index-1].nName);
        }
        return str;
    }
//     else{
//         return ((LayerNetGameDesk*)getParent()->getParent())->GetUserName(index);
//     }
}

//#pragma mark -----------------------菜单动作----------------------
void GameResult::menuHideCallback(CCObject* pSender)
{
    this->setVisible(false);
    ((GameMenu *)this->getParent())->onResultHide();
}


