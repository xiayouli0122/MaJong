//
//  GameDesk.cpp
//  xzdd
//
//  Created by  on 12-2-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GameDesk.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "GameLogical.h"
#include "CommonFunction.h"

#else

#include "../GameCore/GameLogical.h"
#include "../Common/CommonFunction.h"

#endif

using namespace cocos2d;

//#pragma mark ---------------初始化---------------------
bool GameDesk::init()
{
	//super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    isPause = false;
    isHu[0] = false;
    isHu[1] = false;
    isHu[2] = false;
    isHu[3] = false;
    m_bSeenOutCard= true;
    m_Chair = 0;        //玩家座位，默认是0
    isQiangGang = false;
    //设置快牌模式
    gk = CommonFunction::GetGuanKa(GetIntegerToXML(UD_CurrentGuanKa));
    isFase = gk.isFastMode;
    iNomi  = gk.nomi;
    iDeNomi = gk.denomi;
    
    //获取玩家数据
    m_player = CommonFunction::GetPlayersByGuan(GetIntegerToXML(UD_CurrentGuanKa));
    PLAYER m_cplayer = CommonFunction::GetUser();
    sprintf(m_cplayer.nName, "我");
    userType[0] = m_cplayer.nUtype;
    userType[1] = m_player[0].nUtype;
    userType[2] = m_player[1].nUtype;
    userType[3] = m_player[2].nUtype;
    
    this->setTouchEnabled(true);
    
    //加入图片缓冲
    if (CommonFunction::isIpad()) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CONS_DefaultMjFrameFile_Ipad);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CONS_DefaultChatFrameFile_Ipad);
    }else {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CONS_DefaultMjFrameFile);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CONS_DefaultChatFrameFile);
    }
    
    CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ptPos = CCDirector::sharedDirector()->getVisibleOrigin();

    //加入桌面的牌
    deskCardsBatch = DeskCardsBatch::create();
    this->addChild(deskCardsBatch,2);
    deskCardsBatch->m_Chair = m_Chair;
    
    //加入计时器
    timer = Timer::timerWithFrameName(CONS_TIMER_BJImage);
    this->addChild(timer,3);
    
    //加入自己的牌
    myCardsBatch = MyCardsBatch::create();
    this->addChild(myCardsBatch, 6);
    
    //加入Action菜单
    actionBatch = ActionBatch::create();
    this->addChild(actionBatch,4);
    
    //加入标记缓存
    markBatch = MarkBatch::create();
    this->addChild(markBatch,5);
    markBatch->m_Chair = m_Chair;
    
    //加入游戏菜单
    gameMenu = GameMenu::create();
    gameMenu->initWithGameType(GT_SingleGame);
    this->addChild(gameMenu,10);
    
    
    
    //充值
    CCSprite * buyCoin1 = CCSprite::createWithSpriteFrameName("btn_coin_1.png");
    //    CCSprite * buyCoin2 = CCSprite::create("btn_coin_2.png");
    //    CCSprite * buyCoin3 = CCSprite::create("btn_coin_3.png");
    //    CCSprite * buyCoin4 = CCSprite::create("btn_coin_4.png");
    CCSprite * buyCoin5 = CCSprite::createWithSpriteFrameName("btn_coin_5.png");
    pBuyCoinItem = CCMenuItemSprite::create(buyCoin1,buyCoin5,NULL,this,
                                                          menu_selector(GameDesk::menuBuyCoinCallback));
    pBuyCoinItem->setAnchorPoint(ccp(0, 0));
	pBuyCoinItem->setPosition( ccp(ptPos.x, size.height*0.26) );
    
    char str[64];
    _nCash = GetIntegerToXML(UD_SINGLE_COIN);
    // 加入金币 label
    sprintf(str,"剩余币:%d",_nCash);
	pLabelCoin = CCLabelTTF::create(str, "Thonburi", CommonFunction::GetValueByDev(10));
    //    pLabelCoin->setAnchorPoint(ccp(0,0));
	pLabelCoin->setPosition( ccp(ptPos.x + size.width*0.06, size.height*0.43));
    pLabelCoin->setColor(CC_Yellow);
	this->addChild(pLabelCoin, 8);
    
    //好牌
    CCSprite * buyCard1 = CCSprite::createWithSpriteFrameName(CONS_IMG_BTN_BUY_CARD_1);
    CCSprite * buyCard2 = CCSprite::createWithSpriteFrameName(CONS_IMG_BTN_BUY_CARD_2);
    pBuyCardItem = CCMenuItemSprite::create(buyCard1,buyCard2,NULL,this,
                                                          menu_selector(GameDesk::menuBuyCardCallback));
    pBuyCardItem->setAnchorPoint(ccp(0, 0));
	pBuyCardItem->setPosition( ccp(ptPos.x + size.width*0.005, size.height*0.2) );

    
	CCMenu* pMenu2 = CCMenu::create(pBuyCardItem, pBuyCoinItem, NULL);
	pMenu2->setPosition( CCPointZero );
	this->addChild(pMenu2, 5);
    
    
    CCAnimation*  animation = CCAnimation::create();
    
    char frameName[100] = {0};
    for( int i=1;i<5;i++)
    {
        sprintf(frameName, "btn_coin_%d.png", i);
        
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName);
        animation->addSpriteFrame(pFrame);
    }
    
//     CCActionInterval*  action = CCAnimate::create(0.5, animation, false);
//     CCRepeatForever *  repeat = CCRepeatForever::actionWithAction(action);
//	animation->setDelayPerUnit(0.5);
//	CCRepeatForever *  repeat = CCRepeatForever::create(animation);
//    buyCoin1->runAction(animation);
    
    
    
    //初始化标记
    markBatch->SetMarkPerson(0, m_cplayer.nName, CommonFunction::GetGuanKaStats(GetIntegerToXML(UD_CurrentGuanKa)).nScore,
                             m_cplayer.nIco,m_cplayer.nUtype);
    for (int i= 1; i<4; i++) {
        markBatch->SetMarkPerson(i, m_player[i-1].nName, m_player[i-1].nSource, m_player[i-1].nIco,m_player[i-1].nUtype);
    }
    
    if (!CommonFunction::bIsEnterGame) {
 //       CommonFunction::addMarketLog();
        CommonFunction::bIsEnterGame = true;
    }
    
	return true;
}

void GameDesk::onExit()
{
    CCLayer::onExit();
    //    SOUND->end();
    {
        //SOUND->end();
        SOUND->stopBackgroundMusic();
        SOUND->stopAllEffects();
    }
}
void GameDesk::onEnter()
{
    CCLayer::onEnter();
    game.UIDelegate = this;
    SOUND->setBackgroundMusicVolume(GetIntegerToXML(UD_Set_Music,100)*0.01);
    SOUND->setEffectsVolume(GetIntegerToXML(UD_Set_Effect,100)*0.01);
    SOUND->playBackgroundMusic(CONS_Sound_Gaming,true);
    
    //发牌
    DealAllCardAction();
}

//发牌-------------------------------------------------
void GameDesk::DealAllCardAction()
{
    gameMenu->SetPlaying(true);
   // bool is_DingQue         = GetBoolToXML(UD_Set_Xzdq,true);             //是否需要定缺 
	bool is_DingQue         = GetBoolToXML(UD_Set_Xzdq,false);             //lyp 默认不定缺 
    GuaFengXiaYu is_enGFXY  = GFXYJiaJiaYou;  //刮风下雨模式 GFXYChengbao	= 0, GFXYJiaJiaYou	= 1
    if (GetBoolToXML(UD_Set_Jjy,true)){
        is_enGFXY  = GFXYJiaJiaYou;
    }
    bool is_3Fan            = GetBoolToXML(UD_Set_Sfqh,false);            //是否三翻起胡
    bool is_ZimoFan         = GetBoolToXML(UD_Set_Zmjd,true);             //是否自摸加底
    
	game.OnInit(is_DingQue,is_3Fan,is_ZimoFan,is_enGFXY);
    
    //发牌
    game.OnTableStatusToPlaying();
    //如果是继续开始的局，可以使用大牌
    if (GetBoolToXML(UD_IsRegularSet, true))
    {
        game.OnSceneStatusToPlaying(iNomi,iDeNomi);
        //        SetBoolToXML(UD_IsRegularSet, false);
    }
    else
    {
        game.OnSceneStatusToPlaying(0,1);
    }
    
    SetBoolToXML(UD_IsRegularSet, false);
    
    //设置庄家标记
    markBatch->SetMarkZhuang(game.m_nChairBanker);
    
    //根据庄家的位置，初始化牌墙
    deskCardsBatch->InitWall(game.m_nChairBanker);
    
    logicPlayerStateCount = WAITING;
    
    //初始化AI
    for(int i=0;i<3;i++)
    {
        Robot *r = robots+i;
        r->Init(&game,i+1);
        r->SetAILevel(gk.nAILevel);
    }
    
    myCardsBatch->SetMyCard(game.GetPlayerData());      //玩家牌
    deskCardsBatch->SetCardHand(game.GetPlayerData());  //AI牌
    
    if(is_DingQue) {
        //-------处理定缺---------
        //玩家定缺
        actionBatch->showDingQue();
        
        //AI定缺
        for(int i=0;i<3;i++)
        {
            ActionDingQue(i+1, robots[i].DingQue());
        }
        
        
        SetDeskState(D_DingQue);
    }
    else {
        SetDeskState(D_None);
    }
    
    schedule( schedule_selector(GameDesk::undateState), 1);  //增加定时器调用
}



//#pragma mark -----------------------触摸相关方法----------------------
void GameDesk::registerWithTouchDispatcher()
{
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GameDesk::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    if(CCDirector::sharedDirector()->isPaused())
    {
        return false;
    }
    //    if (d_State == D_GameOver) {
    //        gameMenu->ShowResult();
    //        return false;
    //    }
    //在当前玩家摸牌后，或选择暗杠时，接受触摸
    if(game.m_chairCurrentPlayer == 0 && (d_State == D_AfterMo_ChooseOut
                                          || d_State == D_AfterAction_ChooseCard))return myCardsBatch->touchBegan(touch);
    return false;
}

void GameDesk::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    myCardsBatch->touchEnded(touch);
}

void GameDesk::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{
    myCardsBatch->touchCancelled(touch);
}

void GameDesk::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    myCardsBatch->touchMoved(touch);
}


//#pragma mark --------------------Action菜单回调-----------------------
void GameDesk::ActionX()
{
    actionBatch->setVisible(false);   //关闭命令菜单
    
    //如果是摸牌时，动作菜单取消，直接设置为等待出牌状态
    if (d_State == D_AfterMo_ChooseAction) {
        SetDeskState(D_AfterMo_ChooseOut);
    }
    else
    {
        char buf[8];
        memset(buf, 0, sizeof(buf));
        game.OnGameMessage(0, CLIENT_CANCEL, buf, 8);
    }
    
}

void GameDesk::ActionP()
{
    char buf[8];
    memset(buf, 0, sizeof(buf));
    game.OnGameMessage(0, CLIENT_PENG, buf, 8);
}

void GameDesk::ActionZG()
{
    char buf[8];
    memset(buf, 0, sizeof(buf));
    game.OnGameMessage(0, CLIENT_ZHIGANG, buf, 8);
}
//--暗杠，或弯杠，立即执行，等待选牌
void GameDesk::ActionMoG()
{
    PLAYER_DATA *playerData = game.GetPlayerData();
    bool * chooseBuf = game.GetChooseBuf(currentActivityPlayer);
    bool haveWG = chooseBuf[2];
    
    //判断，如果只有一组牌可以杠，立即杠
    BYTE * cards = CommonFunction::GetAGEnableCards(playerData[0],game.GetStandCard()[0],haveWG);
    if (cards[0]!= 255 && cards[1] == 255) {
        Action_ChooseMoGCard(0,cards[0],0);
    }
    else
    {
        myCardsBatch->ChooseCardAfterAction(cards);
        SetDeskState(D_AfterAction_ChooseCard);
    }
    delete [] cards;
}

void GameDesk::ActionH()
{
    Action_H(0);
}

//--定缺
void GameDesk::ActionDingQue(BYTE playIndex,PAI_TYPE type)
{
    char buf[8];
    memset(buf, 0, sizeof(buf));
    buf[0] = type;
    game.OnGameMessage(playIndex, CLIENT_DINGQUE, buf, 8);
    //设置玩家手牌集合 定缺类型属性 方便在定缺模式下显示需要出的牌
    if(playIndex == 0)
    {
        myCardsBatch->dingQueType = type;
    }
    
    //显示选择标记
    markBatch->SetMarkDingQue(playIndex, type);
}

//#pragma mark ---------------逻辑层回调处理-------------------
void GameDesk::OnLogicOver()
{
    //延迟处理
    SetDeskState(D_LogicOver);
}
void GameDesk::Process_LogicOver()
{
    d_State = D_Lock; //锁定状态
    
    currentActivityPlayer = game.m_chairCurrentPlayer;
    deskCardsBatch->SetCardStand(game.GetStandCard());  //设置倒牌
    DrawTableCards();   //设置桌面牌
    if(currentActivityPlayer != 0)
    {
        //刷新AI手牌
        deskCardsBatch->SetCardHand(game.GetPlayerData());  //AI手牌
    }
    else
    {
        //刷新玩家手牌
        myCardsBatch->SetMyCard(game.GetPlayerData()); //设置手牌
    }
    timer->SetChair(game.m_chairCurrentPlayer);
    DrawLastAction();
    
    if (game.m_sysPhase == PhaseThinkingOutCard) {
        //显示上一张出牌
        if(game.m_sOutedCard.nChair != 0 && game.m_sOutedCard.nCard != 255) //别人出牌
        {
            //如果自己参与了抉择，完了又轮到自己,就要不要响。 因为抉择时已经响了
            if(!(game.m_currentCmd == CLIENT_CANCEL &&  m_bSeenOutCard))//game.m_chairCurrentPlayer ==0 &&
            {
                SOUND->playEffect(CommonFunction::GetSoundByByte(userType[game.m_sOutedCard.nChair], game.m_sOutedCard.nCard));
                deskCardsBatch->OutCardAction(game.GetPlayerData(), game.m_sOutedCard);
            }
        }
        Action_Mo();
        
    }
    else if(game.m_sysPhase == PhaseChoosing){
        m_bSeenOutCard = game.GetPlayerData()[0].bSeenOutCard;
        if (!isQiangGang) {
            if(game.m_sOutedCard.nChair !=0 && m_bSeenOutCard){
                SOUND->playEffect(CommonFunction::GetSoundByByte(userType[game.m_sOutedCard.nChair], game.m_sOutedCard.nCard));
                deskCardsBatch->OutCardAction(game.GetPlayerData(), game.m_sOutedCard);
            }
        }
        isQiangGang = false;
        PLAYER_DATA *playerData = game.GetPlayerData();
        char buf[8];
        memset(buf, 0, sizeof(buf));
        
        if (playerData[0].nState == CHOOSING)
        {
            //对玩家显示操作菜单
            bool * chooseBuf = game.GetChooseBuf(0);
            actionBatch->show(chooseBuf[1],false, chooseBuf[2], chooseBuf[3],false);
            
            SetDeskState(D_AfterOut_ChooseAction);
        }
        
        //询问AI是否要进行操作
        for (int i = 1; i< 4; i++) {
            if(playerData[i].nState == CHOOSING)
            {
                bool * chooseBuf = game.GetChooseBuf(i);
                //AI 竞争选择
                BYTE aiCommand = robots[i-1].ChoosingCommon(chooseBuf[1], chooseBuf[2], chooseBuf[3]);
                if (aiCommand == CLIENT_HU) {
                    Action_H(i);
                }
                else
                {
                    game.OnGameMessage(i, aiCommand, buf, 8);
                }
            }
        }
        
        
    }
    else if(game.m_sysPhase == PhaseSetOver){
        IsOver();
    }
    
}

void GameDesk::DrawLastAction()
{
    switch (game.m_currentCmd) {
        case CLIENT_WANGANG:
        case CLIENT_ZHIGANG:
        case CLIENT_ANGANG:
            markBatch->SetMarkAction(currentActivityPlayer, game.m_currentCmd);//显示标记
            deskCardsBatch->SetAllOutCardHide(); //隐藏出牌
            
            break;
            
        case CLIENT_PENG:
            markBatch->SetMarkAction(currentActivityPlayer, game.m_currentCmd);//显示标记
            deskCardsBatch->SetAllOutCardHide(); //隐藏出牌
            ShowCardNo13();
            
            break;
            
        case CLIENT_HU:
            DrawHu();
            break;
            
        case 0:
        case CLIENT_CANCEL:
            
            break;
            
        default:
            break;
    }
}

//根据logic，绘制胡
void GameDesk::DrawHu()
{
    int nHuCount = 0;
    bool bMyHu = false;
    for (int playerIndex=0; playerIndex<4;playerIndex++) {
        HU_CURT huCurt = game.GetHuCurt()[playerIndex];
        if (huCurt.nState == NOTHING) {
            continue;
        }
        
        if (huCurt.nState == ZI_MO || huCurt.nState == CHI_PAO)
        {
            nHuCount++;
            if (isHu[playerIndex]) {
                continue;
            }
            
            HuType huType = HT_HU;
            if (huCurt.nState == CHI_PAO) {
                huType = HT_HU;
                if (huCurt.nGainChair[1] == 0) {
                    //-------显示成就 玩家放炮
                    BYTE count;
                    gameMenu->showCJ(CommonFunction::GetChengJiu_FangPao(false, count), count);
                }
            }
            else if(huCurt.nState == ZI_MO)
            {
                huType = HT_ZHIMO;
            }
            
            if (playerIndex == 0)
            {
                gameMenu->SetStatus(StatusPlayerHu);
                bMyHu = true;
            }
            
            if (game.GetNumFan()[playerIndex] >= 4)
            {
                huType = HT_JIPIN;
                
                if (playerIndex != 0)
                {
                    gameMenu->SetStatus(StatusJipinHu);
                }
            }
            
            markBatch->SetMarkHU(playerIndex,huType);//显示胡牌标记
            if(playerIndex == 0)
            {
                //胡牌不倒，游戏结束时倒
                myCardsBatch->SetHU(huCurt.nCard);
            }
            else
            {
                //胡牌后背面向上，游戏结束时正面向上
                deskCardsBatch->SetHU(playerIndex,huCurt.nCard);
            }
            
            //胡牌成就判断
            //-------显示成就
            if (playerIndex == 0) {
                BYTE count;
                gameMenu->showCJ(CommonFunction::GetChengJiu_Hu(huCurt.nState == ZI_MO,      //自摸
                                                                CommonFunction::HaveHuType(TIANHU, huCurt),     //天胡
                                                                CommonFunction::HaveHuType(DIHU, huCurt),       //地胡
                                                                CommonFunction::HaveHuType(LONG_QIDUI, huCurt),      //青龙七对
                                                                CommonFunction::HaveHuType(GANGKAI, huCurt),    //杠上花
                                                                game.m_nCountAllot >= 104,      //最后一轮胡牌
                                                                game.GetNumFan()[0] >= 4,      //极品
                                                                game.m_nCountAllot <= 63,      //三轮内胡牌
                                                                count),count);
            }
            isHu[playerIndex] = true;
            
//            if (playerIndex == 0) {
//                //加快定时器调用
//                unschedule( schedule_selector(GameDesk::undateState));
//                schedule( schedule_selector(GameDesk::undateState), 0.5);
//            }
        }
    }
    
    if (nHuCount != 3)
    {
        if (bMyHu)
        {
            gameMenu->ShowInfoMsg(INFO_BLOOD_TIPS, 0);
        }
        else if(!isHu[0])
        {
            gameMenu->ShowInfoMsg(INFO_BLOOD_TIPS, nHuCount);
        }
    }
}

void GameDesk::DrawTableCards()
{
    for(int i=0;i<4;i++)
    {
        deskCardsBatch->SetCardTable(i, game.m_nNumTableCards[i], game.GetTableCards(i));
    }
}

void GameDesk::OnGetExCard()
{
    CHENGJIU exCard;
    BYTE count;
    count = 1;
    strcpy(exCard.name, "您有幸发到好牌，努力做一把大胡吧！");
    exCard.id = 250;
    gameMenu->showCJ(&exCard,count);
}

//#pragma mark ---------------辅助函数-------------------

//设置倒计时
void GameDesk::SetTimer(unsigned short  currentTime)
{
    CurrentTime = currentTime;
    if (d_State == D_LogicOver) {
        //timer->SetTime(CurrentTime);
    }
    else{
        timer->SetTime(CurrentTime,game.m_chairCurrentPlayer);
    }
}

//设置桌面状态
void GameDesk::SetDeskState(DeskState  state)
{
    d_State = state;
    switch (state) {
        case D_None:
            SetTimer(0);
            break;
        case D_DingQue:
            SetTimer(isFase?TIME_DingQue_F:TIME_DingQue);
            break;
        case D_AfterMo_ChooseAction:
            SetTimer(isFase?TIME_AfterMo_ChooseAction_F:TIME_AfterMo_ChooseAction);
            break;
        case D_AfterMo_ChooseOut:
            SetTimer(isFase?TIME_AfterMo_ChooseOut_F:TIME_AfterMo_ChooseOut);
            break;
        case D_AfterOut_ChooseAction:
            SetTimer(isFase?TIME_AfterOut_ChooseAction_F:TIME_AfterOut_ChooseAction);
            break;
        case D_LogicOver:
            SetTimer(0);
            break;
        case D_AfterAction_ChooseCard:
            SetTimer(isFase?TIME_AfterAction_ChooseCard_F:TIME_AfterAction_ChooseCard);
            break;
        default:
            break;
    }
}

//显示第13张牌，在摸牌和碰牌后使用
void GameDesk::ShowCardNo13()
{
    PLAYER_DATA * players = game.GetPlayerData();
    currentActivityPlayer = game.m_chairCurrentPlayer;
    
    //    if (players[currentActivityPlayer].nCardTakenNow == 255) {
    //        GameOver();
    //        return;
    //    }
    
    if (currentActivityPlayer == 0) {
        //玩家摸牌
        myCardsBatch->MoCardActive(players);
    }
    else
    {
        //AI摸牌
        deskCardsBatch->MoCardActive(currentActivityPlayer,players[currentActivityPlayer].nCardTakenNow);
        CCLOG("AI摸牌%d, %d",currentActivityPlayer,players[currentActivityPlayer].nCardTakenNow);
    }
    deskCardsBatch->SetCardWall(game.m_nCountAllot);
}

//#pragma mark ---------------过程处理-------------------
//摸牌，碰牌，杠牌后，如果还有命令选择时的处理
void GameDesk::Process_AfterMoPlayerChoose(BYTE playIndex)
{
    if (playIndex == 0) {
        bool * chooseBuf = game.GetChooseBuf(currentActivityPlayer);
        
        actionBatch->show(false,chooseBuf[1], chooseBuf[2], chooseBuf[3],true);
        //状态设置
        SetDeskState(D_AfterMo_ChooseAction);
        return;
        
    }
    else
    {
        bool * chooseBuf = game.GetChooseBuf(playIndex);
        Robot r = robots[playIndex-1];
        
        BYTE aiCommand = r.ChoosingCommonAfterMo(chooseBuf[1], chooseBuf[2], chooseBuf[3]);
        switch (aiCommand) {
            case CLIENT_ANGANG:
                markBatch->SetMarkAction(currentActivityPlayer, aiCommand);//显示标记
                Action_ChooseMoGCard(currentActivityPlayer,r.selectedCard,r.selectedCardIndex);
                break;
            case CLIENT_WANGANG:
                markBatch->SetMarkAction(currentActivityPlayer, aiCommand);//显示标记
                Action_ChooseMoGCard(currentActivityPlayer,r.selectedCard,r.selectedCardIndex);
                break;
            case CLIENT_HU:
                Action_H(playIndex);
                break;
            case CLIENT_OUTCARD:
                Action_ChooseOutCard(currentActivityPlayer,r.selectedCard,r.selectedCardIndex);
                break;
                
            default:
                break;
        }
    }
}

//胡牌后处理
bool GameDesk::IsOver()
{
    if (game.m_sysPhase == PhaseSetOver) {
        GameOver();
        return true;
    }
    return false;
}

//#pragma mark ---------------主要动作-------------------

//---摸牌---
void GameDesk::Action_Mo()
{
    d_State = D_Lock; //锁定状态
    //deskCardsBatch->SetOutCardOnDesk(); //把刚出的牌放到桌面上
    //deskCardsBatch->SetAllOutCardHide();//隐藏出牌
    currentActivityPlayer = game.m_chairCurrentPlayer;
    
    ShowCardNo13();
    
    PLAYER_DATA * players = game.GetPlayerData();
    //如果有命令选择-----  处理
    if (players[currentActivityPlayer].nState == CHOOSING)
    {
        Process_AfterMoPlayerChoose(currentActivityPlayer);
    }
    else
    {
        SetDeskState(D_AfterMo_ChooseOut);
    }
}

void GameDesk::Action_H(BYTE playerIndex)
{
    char buf[8];
    memset(buf, 0, sizeof(buf));
    game.OnGameMessage(playerIndex, CLIENT_HU, buf, 8);
}

//---选择牌---
void GameDesk::Action_ChooseCard(BYTE playIndex,BYTE card,BYTE cardIndex)
{
    if (d_State == D_AfterAction_ChooseCard) {
        Action_ChooseMoGCard(playIndex,card,cardIndex);
    }
    else if (d_State == D_AfterMo_ChooseOut){
        Action_ChooseOutCard(playIndex,card,cardIndex);
    }
}

//---强制出牌---
void GameDesk::OutCardActionForce()
{
    //----出牌超时成就-----
    if(currentActivityPlayer == 0)
    {
        BYTE count;
        gameMenu->showCJ(CommonFunction::GetChengJiu_OutCard_OverTime(count), count);
    }
    if (currentActivityPlayer == 0) {
        MyCard * outCard = myCardsBatch->GetForceOutCard();
        Action_ChooseOutCard(0,outCard->cardContent,outCard->cardIndex);
    }
    else
    {
        Action_ChooseOutCard(currentActivityPlayer,0,13);
    }
}

//---选择出牌---
void GameDesk::Action_ChooseOutCard(BYTE playIndex,BYTE card,BYTE cardIndex)
{
    d_State = D_Lock; //锁定状态
    
    //发送出牌消息 出牌逻辑
    char buf[8];
    memset(buf, 0, sizeof(buf));
    buf[0] = cardIndex;
    
    CCLOG("out card : %d,%d",card,cardIndex);
    game.OnGameMessage(playIndex, CLIENT_OUTCARD, buf, 8);
    
    //如果是玩家出牌，则马上显示
    PLAYER_DATA *playerData = game.GetPlayerData();
    if (playIndex == 0) {
        OUTED_CARD oc;
        oc.clear();
        oc.nCard = card;
        oc.nChair = 0;
        SOUND->playEffect(CommonFunction::GetSoundByByte(userType[playIndex], card));
        myCardsBatch->OutCardActive(playerData);
        deskCardsBatch->OutCardAction(playerData, oc);
    }
}


//---摸杠（包括暗杠、弯杠）选择杠牌---
void GameDesk::Action_ChooseMoGCard(BYTE playIndex,BYTE card,BYTE cardIndex)
{
    d_State = D_Lock;
    PLAYER_DATA *playerData = game.GetPlayerData();
    
    //获取是否有弯杠选择
    bool * chooseBuf = game.GetChooseBuf(currentActivityPlayer);
    bool haveWG = chooseBuf[2];
    
    char buf[8];
    memset(buf, 0, sizeof(buf));
    buf[0] = card;
    
    //如果是弯杠
    if(haveWG && CommonFunction::IsWangGangCard(card, game.GetStandCard()[playIndex]))
    {
        game.OnGameMessage(playIndex, CLIENT_WANGANG, buf, 8);
        markBatch->SetMarkAction(playIndex, CLIENT_WANGANG);
    }
    else
    {
        game.OnGameMessage(playIndex, CLIENT_ANGANG, buf, 8);
        markBatch->SetMarkAction(playIndex, CLIENT_ANGANG);
    }
    
    //杠完后无牌可摸，牌局结束
    if (game.m_sysPhase == PhaseSetOver) {
        OnLogicOver();
        //IsOver();
        return;
    }
    //有人抢杠
    else if(game.m_sysPhase == PhaseChoosing){
        isQiangGang = true;
        OnLogicOver();
        return;
    }
    
    //暗杠后需要重新显示手牌和倒牌
    if (playIndex == 0) {
        myCardsBatch->SetMyCard(playerData); //设置手牌
    }
    deskCardsBatch->SetCardStand(game.GetStandCard()); //设置倒牌
    
    if (playIndex != 0) {
        deskCardsBatch->SetCardHand(playerData); //AI暗杠，设置AI手牌
    }
    
    ShowCardNo13();
    
    //    CCLOG("game state after action %d",game.m_sysPhase);
    
    if(playerData[playIndex].nState == CHOOSING)
    {
        Process_AfterMoPlayerChoose(playIndex);
    }
    else
    {
        //设置桌面为出牌状态
        SetDeskState(D_AfterMo_ChooseOut);
    }
    
    return;
}


void GameDesk::GameOver()
{
    d_State = D_GameOver;
    myCardsBatch->SetLIANG();
    deskCardsBatch->SetLIANG(game.GetPlayerData());
    
    unscheduleAllSelectors();
    SOUND->stopBackgroundMusic();
    gameMenu->ShowResult(game.GetScore(), game.GetHuCurt(), game.GetNumFan(),
                         game.GetGangScore(), game.GetHuaZhuScore(),game.GetDaJiaoScore(),
                         game.GetPlayerData(), game.GetEndReason(), game.GetSetWinScore());
    timer->setVisible(false);
    gameMenu->SetPlaying(false);
    return;
}


//#pragma mark -------------------定时器调用-----------------------
void GameDesk::undateState(float dt)
{
    if (isPause) {
        CCDirector::sharedDirector()->pause();
        return;
    }
    
    //如果桌面状态是出牌，并且出牌的是AI，则调用AI出牌
    if (d_State == D_AfterMo_ChooseOut && game.m_chairCurrentPlayer != 0) {
        Robot r = robots[game.m_chairCurrentPlayer-1];
        r.ChoosingOutCard();
        Action_ChooseOutCard(game.m_chairCurrentPlayer,r.selectedCard,r.selectedCardIndex);
    }
    
    
    //桌面状态是 定缺，逻辑已经处理完所有的 定缺， 立即处理
    if (d_State == D_DingQue && game.m_sysPhase == PhaseThinkingOutCard) {
        //显示AI定缺图标
        SetDeskState(D_None);
        return;
    }
    
    //倒计时
    if (CurrentTime >0) {
        //时间没到，则倒计时
        CurrentTime --;
        timer->SetTime(CurrentTime);
        return;
    }
    
    //倒计时完，强制处理
    switch (d_State) {
            //----------初始状态处理-----------
        case D_None:
            timer->setVisible(true);
            //开始摸牌
            currentActivityPlayer = 0;
            Action_Mo();
            break;
            
            //----------摸牌后,动作选择超时---------
        case D_AfterMo_ChooseAction:
            ActionX();
            SetDeskState(D_AfterMo_ChooseOut);
            break;
            
            //----------出牌后,动作选择超时---------
        case D_AfterOut_ChooseAction:
            //----------选择动作后，选择牌超时------
        case D_AfterAction_ChooseCard:
            ActionX();
            break;
            
            //----------摸牌后,出牌超时---------
        case D_AfterMo_ChooseOut:
            
            OutCardActionForce(); //时间到了，强制出牌
            break;
            //----------logic处理完成---------
        case D_LogicOver:
            Process_LogicOver();
            break;
        default:
            break;
    }
}

//#pragma mark -----------------------暂停和恢复----------------------
void GameDesk::onPause()
{
    SOUND->pauseBackgroundMusic();
    actionBatch->onPause();
}
void GameDesk::onResume()
{
    isPause = false;
    SOUND->resumeBackgroundMusic();
    actionBatch->onResume();
}
void GameDesk::onSystemResume()
{
    isPause = true;
    gameMenu->Pause();
}

void GameDesk::preloadAllEffects(){
	
	SOUND->preloadBackgroundMusic(CONS_Sound_Gaming);
    
	SOUND->preloadEffect(CONS_Sound_Complete);
	SOUND->preloadEffect(CONS_Sound_Failed);
	SOUND->preloadEffect(CONS_Sound_End);
	SOUND->preloadEffect(CONS_Sound_Get);
	SOUND->preloadEffect(CONS_Sound_Through);
    
	char temp[30];
    memset(temp,0,sizeof(temp));
    
	for(int i=0;i<27;i++){
		if(i == 0 || i == 10 || i == 25 || i == 26){
			for(int j=0;j<2;j++){
				sprintf(temp,"%s%d%s%d%s","sound/man/", i, "-", j, ".mp3");
				SOUND->preloadEffect(temp);
				sprintf(temp,"%s%d%s%d%s","sound/woman/", i, "-", j, ".mp3");
				SOUND->preloadEffect(temp);
			}
		}else if(i == 9 || i == 18 || i == 22){
			for(int j=0;j<3;j++){
				sprintf(temp,"%s%d%s%d%s","sound/man/", i, "-", j, ".mp3");
				SOUND->preloadEffect(temp);
				sprintf(temp,"%s%d%s%d%s","sound/woman/", i, "-", j, ".mp3");
				SOUND->preloadEffect(temp);
			}
		}else{
			sprintf(temp,"%s%d%s","sound/man/",i,".mp3");
			SOUND->preloadEffect(temp);
			sprintf(temp,"%s%d%s","sound/woman/",i,".mp3");
			SOUND->preloadEffect(temp);
		}
	}
    
	for(int j=0;j<2;j++){
		sprintf(temp,"%s%d%s","sound/man/angang-", j, ".mp3");
		SOUND->preloadEffect(temp);
		sprintf(temp,"%s%d%s","sound/woman/angang-", j, ".mp3");
		SOUND->preloadEffect(temp);
	}
    
	for(int j=0;j<3;j++){
		sprintf(temp,"%s%d%s","sound/man/gang-", j, ".mp3");
		SOUND->preloadEffect(temp);
		sprintf(temp,"%s%d%s","sound/woman/gang-", j, ".mp3");
		SOUND->preloadEffect(temp);
	}
    
	SOUND->preloadEffect("sound/man/hu.mp3");
	SOUND->preloadEffect("sound/man/hu1.mp3");
	SOUND->preloadEffect("sound/man/hu2.mp3");
    
	SOUND->preloadEffect("sound/woman/hu.mp3");
	SOUND->preloadEffect("sound/woman/hu1.mp3");
	SOUND->preloadEffect("sound/woman/hu2.mp3");
    
	for(int j=0;j<5;j++){
		sprintf(temp,"%s%d%s","sound/man/peng-", j, ".mp3");
		SOUND->preloadEffect(temp);
		sprintf(temp,"%s%d%s","sound/woman/peng-", j, ".mp3");
		SOUND->preloadEffect(temp);
	}
}

void GameDesk::menuBuyCoinCallback(CCObject* pSender)
{
    gameMenu->ShowAddCoinMessage();
}

void GameDesk::menuBuyCardCallback(CCObject* pSender)
{
    BuyCard();
}

void GameDesk::BuyCard()
{
    if (GetBoolToXML(UD_SINGLE_TACARD,false)) {
        gameMenu->ShowInfoMsg(INFO_PROP_CARD_INUSE, 0);
    }
    else
    {
        gameMenu->PayCard();
    }
}

void GameDesk::UpdateCoinLabel()
{
    char str[64];
    _nCash = GetIntegerToXML(UD_SINGLE_COIN);
    sprintf(str,"剩余币:%d",_nCash);
    pLabelCoin->setString(str);
}

