#include "GkInfoDetailLayer.h"

using namespace cocos2d;

GkInfoDetailLayer::GkInfoDetailLayer(void)
{
}


GkInfoDetailLayer::~GkInfoDetailLayer(void)
{
}

bool GkInfoDetailLayer::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    return true;
}

//通过图片名创建关卡对象
GkInfoDetailLayer* GkInfoDetailLayer::infoWithGk(GUAN_KA * gk, int gkIndex, bool isLast)
{
	GkInfoDetailLayer* pLayer = new GkInfoDetailLayer();
	pLayer->autorelease();
    
    
	CCSize infoSize;
    if (ISANDROID || CommonFunction::isIpad()) {
        if(isLast){
            infoSize = CCSize(328.0f, 100.0f);
        }else{
            if(gk[gkIndex].isFastMode){
                infoSize = CCSize(328.0f, 200.0f);
            }else{
                infoSize = CCSize(328.0f, 160.0f);	    
            }
        }
    }
    else{
        if(isLast){
            infoSize = CCSize(328.0f, 50.0f);
        }else{
            if(gk[gkIndex].isFastMode){
                infoSize = CCSize(328.0f, 100.0f);
            }else{
                infoSize = CCSize(328.0f, 80.0f);	    
            }
        }
    }
    
    
	pLayer->setContentSize(infoSize);
    
	// 加入一个 label-关卡名字
	CCLabelTTF* pLabeName = CCLabelTTF::create(gk[gkIndex].nName, "Verdana-Bold", CommonFunction::GetValueByDev(12));
	pLabeName->setColor(CCPauseTitle);
    
	// 加入一个 label-快牌模式	
	CCLabelTTF* pLabeFast = CCLabelTTF::create(CONS_STRING_15s, "Verdana", CommonFunction::GetValueByDev(10));
    pLabeFast->setAnchorPoint(ccp(0,0.5));
	pLabeFast->setColor(CCPauseContent);
    
    
	// 加入一个 label-第一颗星
	CCLabelTTF* pLabeText1 = CCLabelTTF::create(gk[gkIndex].conOneText,"Verdana", CommonFunction::GetValueByDev(10));
	pLabeText1->setAnchorPoint(ccp(0,0.5));
    pLabeText1->setColor(CCPauseContent);
    
	// 加入一个 label-第二颗星
	CCLabelTTF* pLabeText2 = CCLabelTTF::create(gk[gkIndex].conTwoText,"Verdana", CommonFunction::GetValueByDev(10));
	pLabeText2->setAnchorPoint(ccp(0,0.5));
    pLabeText2->setColor(CCPauseContent);
    
    
    // 加入一个 label-第三颗星
	CCLabelTTF* pLabeText3 = CCLabelTTF::create(gk[gkIndex].conThreeText,"Verdana", CommonFunction::GetValueByDev(10));
	pLabeText3->setAnchorPoint(ccp(0,0.5));
    pLabeText3->setColor(CCPauseContent);
    
    if (ISANDROID || CommonFunction::isIpad()) {
        if(isLast){
            pLabeName->setPosition( ccp(infoSize.width*0.3, infoSize.height*0.75) );
            pLayer->addChild(pLabeName, 2);
            
            pLabeText1->setPosition( ccp(infoSize.width*-0.4, infoSize.height*0.25) );
            pLayer->addChild(pLabeText1, 2);
        }else{
            if(gk[gkIndex].isFastMode){
                
                pLabeName->setPosition( ccp(infoSize.width*0.3, infoSize.height*9/10) );
                pLayer->addChild(pLabeName, 2);
                
                pLabeFast->setPosition( ccp(infoSize.width*-0.4, infoSize.height*7/10) );
                pLayer->addChild(pLabeFast, 2);
                
                pLabeText1->setPosition( ccp(infoSize.width*-0.4, infoSize.height*5/10) );
                pLayer->addChild(pLabeText1, 2);
                
                pLabeText2->setPosition( ccp(infoSize.width*-0.4, infoSize.height*3/10) );
                pLayer->addChild(pLabeText2, 2);
                
                pLabeText3->setPosition( ccp(infoSize.width*-0.4, infoSize.height/10) );
                pLayer->addChild(pLabeText3, 2);
                
            }else{
                
                pLabeName->setPosition( ccp(infoSize.width*0.3, infoSize.height*7/8) );
                pLayer->addChild(pLabeName, 2);
                
                pLabeText1->setPosition( ccp(infoSize.width*-0.4, infoSize.height*5/8) );
                pLayer->addChild(pLabeText1, 2);
                
                pLabeText2->setPosition( ccp(infoSize.width*-0.4, infoSize.height*3/8) );
                pLayer->addChild(pLabeText2, 2);
                
                pLabeText3->setPosition( ccp(infoSize.width*-0.4, infoSize.height/8) );
                pLayer->addChild(pLabeText3, 2);	
            }
        }

    }
    else{
        if(isLast){
            pLabeName->setPosition( ccp(infoSize.width*0.18, infoSize.height*0.75) );
            pLayer->addChild(pLabeName, 2);
            
            pLabeText1->setPosition( ccp(infoSize.width*-0.25, infoSize.height*0.25) );
            pLayer->addChild(pLabeText1, 2);
        }else{
            if(gk[gkIndex].isFastMode){
                
                pLabeName->setPosition( ccp(infoSize.width*0.18, infoSize.height*9/10) );
                pLayer->addChild(pLabeName, 2);
                
                pLabeFast->setPosition( ccp(infoSize.width*-0.25, infoSize.height*7/10) );
                pLayer->addChild(pLabeFast, 2);
                
                pLabeText1->setPosition( ccp(infoSize.width*-0.25, infoSize.height*5/10) );
                pLayer->addChild(pLabeText1, 2);
                
                pLabeText2->setPosition( ccp(infoSize.width*-0.25, infoSize.height*3/10) );
                pLayer->addChild(pLabeText2, 2);
                
                pLabeText3->setPosition( ccp(infoSize.width*-0.25, infoSize.height/10) );
                pLayer->addChild(pLabeText3, 2);
                
            }else{
                
                pLabeName->setPosition( ccp(infoSize.width*0.18, infoSize.height*7/8) );
                pLayer->addChild(pLabeName, 2);
                
                pLabeText1->setPosition( ccp(infoSize.width*-0.25, infoSize.height*5/8) );
                pLayer->addChild(pLabeText1, 2);
                
                pLabeText2->setPosition( ccp(infoSize.width*-0.25, infoSize.height*3/8) );
                pLayer->addChild(pLabeText2, 2);
                
                pLabeText3->setPosition( ccp(infoSize.width*-0.25, infoSize.height/8) );
                pLayer->addChild(pLabeText3, 2);	
            }
        }

    }
    
    pLayer->setVisible(true);
    
	return pLayer;
}