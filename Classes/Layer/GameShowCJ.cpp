//
//  GameShowCJ.cpp
//  xzdd
//
//  Created by  on 12-4-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameShowCJ.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

//初始化--------------------------------------------------
bool GameShowCJ::init()
{
	//super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    cjIndex = 0;
    playIndex = 0;
    showing = false;
    
    cc_showCJ = ShowCJ::creatShowCJ();
    this->addChild(cc_showCJ,1);
    cc_showCJ->setVisible(false);
    return true;
}


void GameShowCJ::showCJ(CHENGJIU * cj,BYTE & count)
{
    for (int i=0; i<count; i++) {
        m_cj[cjIndex++] = *cj;
        if (cjIndex == 20) {
            cjIndex = 0;
        }
        cj++;
    }
    schedule( schedule_selector(GameShowCJ::checkCJ));  //增加定时器调用
}
//#pragma mark -------------------定时器调用-----------------------
void GameShowCJ::checkCJ(float dt)
{
    showNextCJ();
}
void GameShowCJ::showNextCJ()
{
    if (showing) {
        return;
    }
    if (cjIndex == playIndex) {
        unschedule(schedule_selector(GameShowCJ::checkCJ));
        return;
    }
    showing = true;
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSize cj_size = cc_showCJ->getContentSize();
    cc_showCJ->setVisible(true);
    cc_showCJ->setPosition(ccp(size.width*0.5,size.height+cj_size.height*0.5));
    cc_showCJ->show(&m_cj[playIndex++]);
    CCActionInterval*  actionTo = CCMoveTo::create(1.5, CCPointMake(size.width*0.5,size.height-cj_size.height*0.5));
    CCActionInterval*  actionStop = CCMoveTo::create(1.5, CCPointMake(size.width*0.5,size.height-cj_size.height*0.5));
    
    CCAction *sequneceAction = CCSequence::create(actionTo,actionStop,
                                                   CCCallFunc::create(this, callfunc_selector(GameShowCJ::showEnd)),//结束动画用的回调
                                                   NULL); 
    cc_showCJ->runAction(sequneceAction);
    SOUND->playEffect(CONS_Sound_Get);

    if (playIndex == 20) {
        playIndex = 0;
    }
}

void GameShowCJ::showEnd()
{    
    cc_showCJ->setVisible(false);
    showing = false;
}















