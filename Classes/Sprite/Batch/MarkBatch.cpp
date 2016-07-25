//
//  MarkBatch.cpp
//  xzdd
//
//  Created by  on 12-3-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MarkBatch.h"
#include <string>
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
//#include "LayerNetGameDesk.h"
#include "IOSCommon.h"
#else 
//#include "../../Layer/Net/LayerNetGameDesk.h"
#endif


using namespace cocos2d;

//#pragma mark ----------------初始化--------------------
bool MarkBatch::init()
{
    if (CommonFunction::isIpad()) {
        markBatchNode = CCSpriteBatchNode::create(CONS_DefaultMjFrameImage_Ipad);
    }else {
        markBatchNode = CCSpriteBatchNode::create(CONS_DefaultMjFrameImage);
    }
	this->addChild(markBatchNode);

    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ptPos = CCDirector::sharedDirector()->getVisibleOrigin();

    
    //初始化所有数组
    markIco     = CCArray::create();
	markIco->retain();
//    markDisConn = CCArray::create();
    markChatbj  = CCArray::create();
	markChatbj->retain();

    markChat    = CCArray::create();
	markChat->retain();

    markAction  = CCArray::create();
	markAction->retain();

    markHu      = CCArray::create();
	markHu->retain();

//    markReady   = CCArray::create();
    markDingQue = CCArray::create();
	markDingQue->retain();

    markSoure   = CCArray::create();
	markSoure->retain();

    markName    = CCArray::create();
	markName->retain();
    
    //循环初始化标记-------------------------------------
    for(int i=0;i<4;i++)
    {
        CCSprite * dq = CCSprite::createWithSpriteFrameName(CONS_MARK_TONGImage);
        CCSprite * action = CCSprite::createWithSpriteFrameName(CONS_ActionxImage1);
        CCSprite * ico = CCSprite::createWithSpriteFrameName(CommonFunction::GetIcoImageByByte(1));
        CCSprite * disConn = CCSprite::createWithSpriteFrameName(CONS_MARK_DisConn);
        CCSprite * ready = CCSprite::createWithSpriteFrameName(CONS_MARK_ReadyImage);
        CCSprite * chatbj;
        ScrollWordAndImage * chat = ScrollWordAndImage::create();
        //CCSprite * lableFrame = CCSprite::create(CONS_MARK_LableFrameImage);

        //分数标签
        CCLabelTTF* soureLabel = CCLabelTTF::create("", "Verdana", CommonFunction::GetValueByDev(7));
        CCLabelTTF* nameLabel = CCLabelTTF::create("", "Verdana", CommonFunction::GetValueByDev(7));

        CCSprite * hu = CCSprite::createWithSpriteFrameName(CONS_MARK_HuImage);

        //设置背景位置
        switch (i) {
            case 0:
                dq->setPosition( ccp(ptPos.x + ptPos.x + winSize.width*0.98, winSize.height*0.43) );
                action->setPosition( ccp(ptPos.x + winSize.width*0.35, winSize.height*0.2) );
                //lableFrame->setPosition(ccp(ptPos.x + winSize.width*0.943, winSize.height*0.215) );
                hu->setPosition(ccp(ptPos.x + winSize.width*0.965, winSize.height*0.39) );
                chatbj = CCSprite::createWithSpriteFrameName(CONS_Image_Chat_You);
                chat->SetSize(chatbj->getContentSize().width*0.95, chatbj->getContentSize().height*0.6);
                break;
            case 1:
                dq->setPosition( ccp(ptPos.x + winSize.width*0.04, winSize.height*0.49) );
                action->setPosition( ccp(ptPos.x + winSize.width*0.18, winSize.height*0.75) );
                //lableFrame->setPosition(ccp(ptPos.x + winSize.width*0.06, winSize.height*0.555) );
                hu->setPosition(ccp(ptPos.x + winSize.width*0.08, winSize.height*0.73) );
                chatbj = CCSprite::createWithSpriteFrameName(CONS_Image_Chat_Zuo);
                chat->SetSize(chatbj->getContentSize().width*0.95, chatbj->getContentSize().height*0.6);
                break;
            case 2:
                dq->setPosition( ccp(ptPos.x + winSize.width*0.17, winSize.height*0.88) );
                action->setPosition( ccp(ptPos.x + winSize.width*0.55, winSize.height*0.82) );
                //lableFrame->setPosition(ccp(ptPos.x + winSize.width*0.19, winSize.height*0.95) );
                hu->setPosition(ccp(ptPos.x + winSize.width*0.1, winSize.height*0.87) );
                chatbj = CCSprite::createWithSpriteFrameName(CONS_Image_Chat_Shang);
                chat->SetSize(chatbj->getContentSize().width*0.81, chatbj->getContentSize().height*0.8);
                break;
            case 3:
                dq->setPosition( ccp(ptPos.x + winSize.width*0.98, winSize.height*0.60) );
                action->setPosition( ccp(ptPos.x + winSize.width*0.82, winSize.height*0.45) );
                //lableFrame->setPosition(ccp(ptPos.x + winSize.width*0.943, winSize.height*0.665) );
                hu->setPosition(ccp(ptPos.x + winSize.width*0.965, winSize.height*0.83) );
                chatbj = CCSprite::createWithSpriteFrameName(CONS_Image_Chat_You);
                chat->SetSize(chatbj->getContentSize().width*0.95, chatbj->getContentSize().height*0.6);
                break;
            default:
                break;
        }
        
        dq->setVisible(false);
        action->setVisible(false);
        ico->setVisible(false);
        disConn->setVisible(false);
        chatbj->setVisible(false);
        chat->setVisible(false);
        ready->setVisible(false);
        hu->setVisible(false);
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if(IOSCommon::IsIpad3())
        {
            dq->setScale(2.0f);
            action->setScale(2.0f);
            ico->setScale(2.0f);
            disConn->setScale(2.0f);
            chatbj->setScale(2.0f);
           // chat->setScale(2.0f);
            ready->setScale(2.0f);
            hu->setScale(2.0f);
            
            //chat->SetSize(chatbj->boundingBox().size.width*0.95, chatbj->boundingBox().size.height*0.6);
        }
#endif
        
        this->addChild(ico);
        this->addChild(disConn);
        this->addChild(dq);
        this->addChild(action);
        this->addChild(hu);
        //this->addChild(lableFrame);
        this->addChild(soureLabel);
        this->addChild(nameLabel);
        this->addChild(chatbj);
        this->addChild(chat);
        this->addChild(ready);
        
        markIco->addObject(ico);
//        markDisConn->addObject(disConn);
        markChatbj->addObject(chatbj);
        markChat->addObject(chat);
        markDingQue->addObject(dq);
        markAction->addObject(action);
        markHu->addObject(hu);
        markSoure->addObject(soureLabel);
        markName->addObject(nameLabel);
//        markReady->addObject(ready);
        markSelected[i] = 0;
    }
    
    markZhuang = CCSprite::createWithSpriteFrameName(CONS_MARK_ZhuangImage);
    this->addChild(markZhuang);
    markZhuang->setVisible(false);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        markZhuang->setScale(2.0f);
    }
#endif
    
    SetMarkGameStatus(false);

	return true;
}

void MarkBatch::onExit()
{
    markIco->release();
//    markDisConn->release();
    markChatbj->release();
    markChat->release();
    markAction->release();
    markHu->release();
//    markReady->release();
    markDingQue->release();
    markSoure->release();
    markName->release();
    CCNode::onExit();
}

//#pragma mark 一局开始时 初始化
void MarkBatch::initForSet()
{
    for (int i=0; i<4; i++) {
        ((CCSprite*)markDingQue->objectAtIndex(i))->setVisible(false);
//        markReady->objectAtIndex(i)->setVisible(false);
        ((CCSprite*)markHu->objectAtIndex(i))->setVisible(false);
    }
    markZhuang->setVisible(false);
}
void MarkBatch::initForReady()
{
    for (int i=0; i<4; i++) {
        ((CCSprite*)markDingQue->objectAtIndex(i))->setVisible(false);
        ((CCSprite*)markHu->objectAtIndex(i))->setVisible(false);
    }
    markZhuang->setVisible(false);
}

//#pragma mark ---------------设置标记----------------
//设置用户标记
void MarkBatch::SetMarkPerson(BYTE chair,string name,long soure,const char *ico,USERTYPE type)
{
    SetMarkPerson(chair,name,soure,ico,type,0);
}
void MarkBatch::SetMarkPerson(BYTE chair,string name,long soure,const char *ico,USERTYPE type,BYTE userStatus)
{
    bool isReady = userStatus == 0;
    bool isDisConn = userStatus == 0;
    chair = CommonFunction::GetChair(m_Chair, chair);
    CCSprite * sIco = (CCSprite*)markIco->objectAtIndex(chair);
    sIco->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(ico));
    sIco->setVisible(true);
    
    char str[20];
    CCLabelTTF* soureLabel = (CCLabelTTF*)markSoure->objectAtIndex(chair);
    //sprintf(str,CONS_STRING_JiFen, soure);
    soureLabel->setColor(CC_Yellow);
//    int nCoin = GetIntegerToXML(UD_SINGLE_COIN, 0);
//    if (IS_LOCAL && chair==0)
//    {
//        sprintf(str,"%ld(游戏币:%d)", soure, nCoin);
//    }
//    else
    {
        sprintf(str,"%ld", soure);
    }
    soureLabel->setString(str);
    
    CCLabelTTF* nameLabel = (CCLabelTTF*)markName->objectAtIndex(chair);
    nameLabel->setString(name.c_str());
    
    userType[chair] = type;
    
//     CCSprite * sReady = markReady->objectAtIndex(chair);
//     sReady->setVisible(isReady);
//     CCSprite * sDisConn = markDisConn->objectAtIndex(chair);
//     sDisConn->setVisible(isDisConn);
}
//设置用户离开
void MarkBatch::SetMarkPersonLeft(BYTE chair)
{
    chair = CommonFunction::GetChair(m_Chair, chair);
    CCSprite * sIco = (CCSprite*)markIco->objectAtIndex(chair);
    sIco->setVisible(false);

    CCLabelTTF* soureLabel = (CCLabelTTF*)markSoure->objectAtIndex(chair);
    soureLabel->setString("");
    
    CCLabelTTF* nameLabel = (CCLabelTTF*)markName->objectAtIndex(chair);
    nameLabel->setString("");
    
//     CCSprite * sReady = markReady->objectAtIndex(chair);
//     sReady->setVisible(false);
//     CCSprite * sDisConn = markDisConn->objectAtIndex(chair);
//     sDisConn->setVisible(false);
}
//设置定缺标记
void MarkBatch::SetMarkDingQue(BYTE playIndex,PAI_TYPE type)
{
    playIndex = CommonFunction::GetChair(m_Chair, playIndex);
    //定缺标记是所有玩家都选择完后，一起出现的
    //设置选择标记
    markSelected[playIndex] = 1;
    
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_MARK_TONGImage);
    switch (type) {
        case WAN:
            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_MARK_WANImage);
            break;
        case TIAO:
            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_MARK_TIAOImage);
            break;
        default:
            break;
    }
    CCSprite * dq = (CCSprite*)markDingQue->objectAtIndex(playIndex);
    dq->setDisplayFrame(frame);

    
    if (markSelected[0] + markSelected[1] +markSelected[2] +markSelected[3] == 4) {
        ((CCSprite*)markDingQue->objectAtIndex(0))->setVisible(true);
        ((CCSprite*)markDingQue->objectAtIndex(1))->setVisible(true);
        ((CCSprite*)markDingQue->objectAtIndex(2))->setVisible(true);
        ((CCSprite*)markDingQue->objectAtIndex(3))->setVisible(true);
    }
}
void MarkBatch::SetMarkAllDingQue(DING_QUE * dingque)
{
    for (int i=0; i<4; i++) {
        if (dingque->bRecv && dingque->nCardType != 255) {
            SetMarkDingQue(i,(PAI_TYPE)dingque->nCardType);
        }
        dingque++;
    }
}

//设置动作标记
void MarkBatch::SetMarkAction(BYTE playIndex,BYTE cmdID)
{
    if(cmdID == CLIENT_CANCEL)return;
    playIndex = CommonFunction::GetChair(m_Chair, playIndex);
    
    SOUND->playEffect(CommonFunction::GetSoundByCommand(userType[playIndex], cmdID));
    
    CCSprite * sAction = (CCSprite*)markAction->objectAtIndex(playIndex);
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_ActionxImage1);
    switch (cmdID) {
        case CLIENT_ANGANG:
            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_ActionAgImage);
            break;
        case CLIENT_WANGANG:
        case CLIENT_ZHIGANG:
            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_ActionAgImage);
            break;
        case CLIENT_PENG:
            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_ActionApImage);
            break;
        case CLIENT_HU:
            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_ActionAhImage);
            break;
        default:
            break;
    }
    sAction->setDisplayFrame(frame);
    sAction->setScale(4);
    sAction->setVisible(true);
    
    CCFadeIn* in    = CCFadeIn::create(0.3);
    CCScaleTo * sc  = CCScaleTo::create(0.3, 1);
    CCDelayTime *waiting=CCDelayTime::create(0.5f);
    CCFadeOut* out  = CCFadeOut::create(0.08);
    //CCFiniteTimeAction
    CCAction * action= CCSequence::create(CCSpawn::create(in,sc,NULL),waiting,out,NULL);
    //运行一次
    //CCActionInterval* actionShake=CCRepeat::actionWithAction((CCActionInterval*)action,1);
    sAction->stopAllActions();
    sAction->runAction(action);
}

//设置胡牌标记
void MarkBatch::SetMarkHU(BYTE playIndex,HuType type)
{
    playIndex = CommonFunction::GetChair(m_Chair, playIndex);
    
    CCSprite * sAction = (CCSprite*)markHu->objectAtIndex(playIndex);
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_MARK_HuImage);
    switch (type) {
        case HT_HU:
            break;
        case HT_ZHIMO:
            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_MARK_ZiMoImage);
            sAction->setDisplayFrame(frame);
            break;
        case HT_JIPIN:
            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_MARK_JiPinImage);
            sAction->setDisplayFrame(frame);
            break;
        default:
            break;
    }
    sAction->setVisible(true);
//     //如果不是中途加入游戏的，则不显示动画和声音
//     if (!((LayerNetGameDesk*)getParent())->isFirstLogic ){
//         sAction->setScaleX(3);
//         sAction->setScaleY(3);
//         CCFadeIn* in    = CCFadeIn::create(0.5);
//         CCActionInterval*  scaleTo = CCScaleTo::create(0.8,1);
//         CCFiniteTimeAction* action= CCSpawn::actions(in,scaleTo,NULL);
//         //运行一次
//         CCActionInterval* actionShake=CCRepeat::actionWithAction((CCActionInterval*)action,1);
//         
//         sAction->stopAllActions();
//         sAction->runAction(actionShake);
//         SOUND->playEffect(CommonFunction::GetSoundByCommand(userType[playIndex], CLIENT_HU));
//     }
}

//设置庄标记
void MarkBatch::SetMarkZhuang(BYTE playIndex)
{
    playIndex = CommonFunction::GetChair(m_Chair, playIndex);
    
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ptPos = CCDirector::sharedDirector()->getVisibleOrigin();
    switch (playIndex) {
        case 0:
            markZhuang->setPosition(ccp(ptPos.x + winSize.width*0.93, winSize.height*0.43));
            break;
        case 1:
            markZhuang->setPosition(ccp(ptPos.x + winSize.width*0.09, winSize.height*0.49));
            break;
        case 2:
            markZhuang->setPosition(ccp(ptPos.x + winSize.width*0.22, winSize.height*0.88));
            break;
        case 3:
            markZhuang->setPosition(ccp(ptPos.x + winSize.width*0.93, winSize.height*0.60));
            break;
        default:
            break;
    }
    markZhuang->setVisible(true);
}

//设置游戏状态 准备开始，游戏状态
void MarkBatch::SetMarkGameStatus(bool isReady)
{
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ptPos = CCDirector::sharedDirector()->getVisibleOrigin();
    if (isReady) {
        for(int i=0;i<4;i++)
        {
            CCSprite * ico = (CCSprite*)markIco->objectAtIndex(i);
//            CCSprite * disConn = (CCSprite*)markDisConn->objectAtIndex(i);
            CCSprite * chatbj = (CCSprite*)markChatbj->objectAtIndex(i);
//            CCSprite * ready = (CCSprite*)markReady->objectAtIndex(i);
            //分数标签
            CCLabelTTF* soureLabel = (CCLabelTTF*)markSoure->objectAtIndex(i);
            CCLabelTTF* nameLabel = (CCLabelTTF*)markName->objectAtIndex(i);
            
            //设置背景位置
            switch (i) {
                case 0:
                    ico->setPosition(ccp(ptPos.x + winSize.width*0.5, winSize.height*0.145) );
//                    disConn->setPosition(ccp(ptPos.x + winSize.width*0.47, winSize.height*0.085) );
                    chatbj->setPosition(ccp(ptPos.x + winSize.width*0.39, winSize.height*0.22));
//                    ready->setPosition(ccp(ptPos.x + winSize.width*0.6, winSize.height*0.08) );
                    soureLabel->setPosition(ccp(ptPos.x + winSize.width*0.5, winSize.height*0.03) );
                    nameLabel->setPosition(ccp(ptPos.x + winSize.width*0.5, winSize.height*0.055) );
                    break;
                case 1:
                    ico->setPosition(ccp(ptPos.x + winSize.width*0.06, winSize.height*0.546) );
//                    disConn->setPosition(ccp(ptPos.x + winSize.width*0.03, winSize.height*0.486) );
                    chatbj->setPosition(ccp(ptPos.x + winSize.width*0.17, winSize.height*0.67));
//                    ready->setPosition(ccp(ptPos.x + winSize.width*0.16, winSize.height*0.546) );
                    soureLabel->setPosition(ccp(ptPos.x + winSize.width*0.06, winSize.height*0.411) );
                    nameLabel->setPosition(ccp(ptPos.x + winSize.width*0.06, winSize.height*0.436) );
                    break;
                case 2:
                    ico->setPosition(ccp(ptPos.x + winSize.width*0.5, winSize.height*0.91) );
//                    disConn->setPosition(ccp(ptPos.x + winSize.width*0.47, winSize.height*0.85) );
                    chatbj->setPosition(ccp(ptPos.x + winSize.width*0.66, winSize.height*0.85));
//                    ready->setPosition(ccp(ptPos.x + winSize.width*0.5, winSize.height*0.75) );
                    soureLabel->setPosition(ccp(ptPos.x + winSize.width*0.5, winSize.height*0.795) );
                    nameLabel->setPosition(ccp(ptPos.x + winSize.width*0.5, winSize.height*0.82) );
                    break;
                case 3:
                    ico->setPosition(ccp(ptPos.x + winSize.width*0.94, winSize.height*0.546) );
//                    disConn->setPosition(ccp(ptPos.x + winSize.width*0.91, winSize.height*0.486) );
                    chatbj->setPosition(ccp(ptPos.x + winSize.width*0.82, winSize.height*0.64));
//                    ready->setPosition(ccp(ptPos.x + winSize.width*0.84, winSize.height*0.546) );
                    soureLabel->setPosition(ccp(ptPos.x + winSize.width*0.94, winSize.height*0.411) );
                    nameLabel->setPosition(ccp(ptPos.x + winSize.width*0.94, winSize.height*0.436) );
                    break;
                default:
                    break;
            }
        }
    }
    else{
        for(int i=0;i<4;i++)
        {
            CCSprite * ico = (CCSprite*)markIco->objectAtIndex(i);
//            CCSprite * disConn = markDisConn->objectAtIndex(i);
            CCSprite * chatbj = (CCSprite*)markChatbj->objectAtIndex(i);
//            CCSprite * ready = markReady->objectAtIndex(i);
            //分数标签
            CCLabelTTF* soureLabel = (CCLabelTTF*)markSoure->objectAtIndex(i);
            CCLabelTTF* nameLabel = (CCLabelTTF*)markName->objectAtIndex(i);
            
            //设置背景位置
            switch (i) {
                case 0:
                    ico->setPosition(ccp(ptPos.x + winSize.width*0.945, winSize.height*0.32) );
//                    disConn->setPosition(ccp(ptPos.x + winSize.width*0.915, winSize.height*0.26) );
                    chatbj->setPosition(ccp(ptPos.x + winSize.width*0.83, winSize.height*0.42));
//                    ready->setPosition(ccp(ptPos.x + winSize.width*0.985, winSize.height*0.28) );
                    soureLabel->setPosition(ccp(ptPos.x + winSize.width*0.943, winSize.height*0.203) );
                    nameLabel->setPosition(ccp(ptPos.x + winSize.width*0.943, winSize.height*0.228) );
                    break;
                case 1:
                    ico->setPosition(ccp(ptPos.x + winSize.width*0.06, winSize.height*0.66) );
//                    disConn->setPosition(ccp(ptPos.x + winSize.width*0.03, winSize.height*0.60) );
                    chatbj->setPosition(ccp(ptPos.x + winSize.width*0.20, winSize.height*0.66));
//                    ready->setPosition(ccp(ptPos.x + winSize.width*0.1, winSize.height*0.62) );
                    soureLabel->setPosition(ccp(ptPos.x + winSize.width*0.06, winSize.height*0.543) );
                    nameLabel->setPosition(ccp(ptPos.x + winSize.width*0.06, winSize.height*0.568) );
                    break;
                case 2:
                    ico->setPosition(ccp(ptPos.x + winSize.width*0.08, winSize.height*0.91) );
//                    disConn->setPosition(ccp(ptPos.x + winSize.width*0.05, winSize.height*0.85) );
                    chatbj->setPosition(ccp(ptPos.x + winSize.width*0.25, winSize.height*0.85));
//                    ready->setPosition(ccp(ptPos.x + winSize.width*0.12, winSize.height*0.87) );
                    soureLabel->setPosition(ccp(ptPos.x + winSize.width*0.19, winSize.height*0.938) );
                    nameLabel->setPosition(ccp(ptPos.x + winSize.width*0.19, winSize.height*0.963) );
                    break;
                case 3:
                    ico->setPosition(ccp(ptPos.x + winSize.width*0.945, winSize.height*0.77) );
//                    disConn->setPosition(ccp(ptPos.x + winSize.width*0.915, winSize.height*0.71) );
                    chatbj->setPosition(ccp(ptPos.x + winSize.width*0.83, winSize.height*0.83));
//                    ready->setPosition(ccp(ptPos.x + winSize.width*0.985, winSize.height*0.73) );
                    soureLabel->setPosition(ccp(ptPos.x + winSize.width*0.943, winSize.height*0.653) );
                    nameLabel->setPosition(ccp(ptPos.x + winSize.width*0.943, winSize.height*0.678) );
                    break;
                default:
                    break;
            }
        }
    }
    
    for(int i=0;i<4;i++){
        CCSprite * sChatbj = (CCSprite*)markChatbj->objectAtIndex(i);
        CCSize bjSize = sChatbj->getContentSize();
        ScrollWordAndImage *sChat = (ScrollWordAndImage*)markChat->objectAtIndex(i);
        switch (i) {
            case 0:
            case 1:
            case 3:
                sChat->setPosition(ccp(sChatbj->getPosition().x-bjSize.width*0.47,
                                       sChatbj->getPosition().y-winSize.height+bjSize.height*0.44));
                break;
            case 2:
                sChat->setPosition(ccp(sChatbj->getPosition().x-bjSize.width*0.33,
                                       sChatbj->getPosition().y-winSize.height+bjSize.height*0.422));
                break;
            default:
                break;
        }
    }
}

//#pragma mark --------显示聊天内容----------
void MarkBatch::onChat(BYTE chair, char* msg)
{
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ptPos = CCDirector::sharedDirector()->getVisibleOrigin();
    chair = CommonFunction::GetChair(m_Chair, chair);
    CCSprite * sChatbj = (CCSprite*)markChatbj->objectAtIndex(chair);
//    CCSize bjSize = sChatbj->getContentSize();
    ScrollWordAndImage *sChat = (ScrollWordAndImage*)markChat->objectAtIndex(chair);
//    switch (chair) {
//        case 0:
//        case 1:
//        case 3:
//            sChat->setPosition(ccp(sChatbj->getPosition().x-bjSize.width*0.47,
//                                   sChatbj->getPosition().y-winSize.height+bjSize.height*0.44));
//            break;
//        case 2:
//            sChat->setPosition(ccp(sChatbj->getPosition().x-bjSize.width*0.33,
//                                   sChatbj->getPosition().y-winSize.height+bjSize.height*0.422));
//            break;
//        default:
//            break;
//    }
    sChat->SetString(msg);
    sChat->setVisible(true);    
    sChatbj->setVisible(true);
    sChatbj->runAction(CCSequence::create(CCDelayTime::create(2),                                         
                                         CCCallFuncND::create(this, callfuncND_selector(MarkBatch::ShowChatTimeOver),(void*)chair),
                                         NULL)
                     );
}
//显示聊天后隐藏的回调
void MarkBatch::ShowChatTimeOver(CCNode* sender,void* pIndex)
{
	BYTE index = *(BYTE*)pIndex;
    CCSprite * sChatbj = (CCSprite*)markChatbj->objectAtIndex(index);
    ScrollWordAndImage *sChat = (ScrollWordAndImage*)markChat->objectAtIndex(index);
    sChatbj->setVisible(false);
    sChat->setVisible(false);
}








