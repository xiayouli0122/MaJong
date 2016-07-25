//
//  MyTinyXmlParser.cpp
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "MyTinyXmlParser.h"
//#include "CCFileUtils.h"

using namespace std;


int MyTinyXmlParser::GetGuanKaCount()
{
    int count = 0;
//     CCFileData data(CCFileUtils::fullPathFromRelativePath(GUANKA_FILE_NAME), "r");
//     unsigned char* pBuffer = data.getBuffer();

	unsigned long  size = 0;
	unsigned char* pBuffer = CCFileUtils::sharedFileUtils()->getFileData(CCFileUtils::sharedFileUtils()->fullPathForFilename( GUANKA_FILE_NAME).c_str(),"r",&size);
    
	TiXmlDocument* guankaDoc = new TiXmlDocument();
    guankaDoc->Parse((char *)pBuffer);
    
	TiXmlElement* guanKaNumElement = guankaDoc->RootElement()->FirstChildElement();//guanka num node
	count = atoi(guanKaNumElement->GetText());
    
    delete guankaDoc;
    return count;
}

GUAN_KA * MyTinyXmlParser::GetGuanKa(){
    
    static GUAN_KA pGuanKa[15];
    
    if (!pGuanKa[0].isUsed)
    {
        for (int i=0; i<15; i++) {
            pGuanKa[i].clear();
        }
        
//         CCFileData data(CCFileUtils::fullPathFromRelativePath(GUANKA_FILE_NAME), "r");
//         unsigned char* pBuffer = data.getBuffer();

		unsigned long  size = 0;
		unsigned char* pBuffer = CCFileUtils::sharedFileUtils()->getFileData(CCFileUtils::sharedFileUtils()->fullPathForFilename( GUANKA_FILE_NAME).c_str(),"r",&size);
        
        TiXmlDocument* guankaDoc = new TiXmlDocument();
        
        guankaDoc->Parse((char *)pBuffer);
        
        TiXmlElement* configElement = guankaDoc->RootElement();//config node
        
        TiXmlElement* guanKaNumElement = configElement->FirstChildElement();//guanka num node
        //guankaNum = atoi(guanKaNumElement->GetText());
        
        TiXmlElement* guanKaElement = guanKaNumElement->NextSiblingElement();//guanka node
        
        int index = 0;
        while(guanKaElement){
            pGuanKa[index].isUsed = true;
            TiXmlElement* idElement = guanKaElement->FirstChildElement();
            pGuanKa[index].nId = atoi(idElement->GetText());
            
            TiXmlElement* nameElement = idElement->NextSiblingElement();
            strcpy(pGuanKa[index].nName, nameElement->GetText());
            
            //CCLOG("guanka = %d, name = %s", index+1, pGuanKa[index].nName);
            
            TiXmlElement* aiElement = nameElement->NextSiblingElement();
            pGuanKa[index].nAILevel = atoi(aiElement->GetText());
            
            TiXmlElement* fastElement = aiElement->NextSiblingElement();
            if(atoi(fastElement->GetText()) == 0){
                pGuanKa[index].isFastMode = false;
            }else{
                pGuanKa[index].isFastMode = true;
            }
            
            TiXmlElement* nomiElement = fastElement->NextSiblingElement();
            pGuanKa[index].nomi = atoi(nomiElement->GetText());
            TiXmlElement* denomiElement = nomiElement->NextSiblingElement();
            pGuanKa[index].denomi = atoi(denomiElement->GetText());
            
			TiXmlElement* oneTextElement = denomiElement->NextSiblingElement();
			strcpy(pGuanKa[index].conOneText, oneTextElement->GetText());
            
            TiXmlElement* conOneElement = oneTextElement->NextSiblingElement();
            loadCondition(conOneElement, pGuanKa, index, 1, 1);
            
			TiXmlElement* twoTextElement = conOneElement->NextSiblingElement();
			strcpy(pGuanKa[index].conTwoText, twoTextElement->GetText());
            
            TiXmlElement* conTwoElement = twoTextElement->NextSiblingElement();
            loadCondition(conTwoElement, pGuanKa, index, 2, 1);
            
            TiXmlElement* isDoubleElement = conTwoElement->NextSiblingElement();
            if(atoi(isDoubleElement->GetText()) == 0){
                pGuanKa[index].isDoubleCondition = false;
            }else{
                pGuanKa[index].isDoubleCondition = true;
            }	
            
			TiXmlElement* threeTextElement = isDoubleElement->NextSiblingElement();
			strcpy(pGuanKa[index].conThreeText, threeTextElement->GetText());
            
            TiXmlElement* conThree1Element = threeTextElement->NextSiblingElement();
            loadCondition(conThree1Element, pGuanKa, index, 3, 1);
            
            if(pGuanKa[index].isDoubleCondition){
                TiXmlElement* conThree2Element = conThree1Element->NextSiblingElement();
                loadCondition(conThree2Element, pGuanKa, index, 3, 2);
            }
            
            guanKaElement = guanKaElement->NextSiblingElement();
            index++;
        }
    }    
    return pGuanKa;
    
}

void MyTinyXmlParser::loadCondition(TiXmlElement* conditionElement, GUAN_KA * pGuanKa, int guankaIndex, 
	                                int conditionIndex, int conDetailIndex){
	if(conditionElement){
		TiXmlElement* scoreElement = conditionElement->FirstChildElement();//score
		
		TiXmlElement* setNumElement = scoreElement->NextSiblingElement();//setNum
        
		TiXmlElement* fanNumElement = setNumElement->NextSiblingElement();//fanNum
        
		TiXmlElement* chaohuNumElement = fanNumElement->NextSiblingElement();//chaohuNum        
        
		switch(conditionIndex){
            case 1:
                pGuanKa[guankaIndex].conditionOne.nScore = atoi(scoreElement->GetText());
                pGuanKa[guankaIndex].conditionOne.nSetNum = atoi(setNumElement->GetText());
                pGuanKa[guankaIndex].conditionOne.nFanNum = atoi(fanNumElement->GetText());
                pGuanKa[guankaIndex].conditionOne.nChaoHuNum = atoi(chaohuNumElement->GetText());
                /*CCLOG("guanka = %d, condition = %d, conDetail = %d, nScore = %d", guankaIndex+1, conditionIndex, conDetailIndex, pGuanKa[guankaIndex].conditionOne.nScore);
                 CCLOG("guanka = %d, condition = %d, conDetail = %d, nSetNum = %d", guankaIndex+1, conditionIndex, conDetailIndex, pGuanKa[guankaIndex].conditionOne.nSetNum);
                 CCLOG("guanka = %d, condition = %d, conDetail = %d, nFanNum = %d", guankaIndex+1, conditionIndex, conDetailIndex, pGuanKa[guankaIndex].conditionOne.nFanNum);
                 CCLOG("guanka = %d, condition = %d, conDetail = %d, nChaoHuNum = %d", guankaIndex+1, conditionIndex, conDetailIndex, pGuanKa[guankaIndex].conditionOne.nChaoHuNum);*/
                break;
            case 2:
                pGuanKa[guankaIndex].conditionTwo.nScore = atoi(scoreElement->GetText());
                pGuanKa[guankaIndex].conditionTwo.nSetNum = atoi(setNumElement->GetText());
                pGuanKa[guankaIndex].conditionTwo.nFanNum = atoi(fanNumElement->GetText());
                pGuanKa[guankaIndex].conditionTwo.nChaoHuNum = atoi(chaohuNumElement->GetText());			
                /*CCLOG("guanka = %d, condition = %d, conDetail = %d, nScore = %d", guankaIndex+1, conditionIndex, conDetailIndex, pGuanKa[guankaIndex].conditionTwo.nScore);
                 CCLOG("guanka = %d, condition = %d, conDetail = %d, nSetNum = %d", guankaIndex+1, conditionIndex, conDetailIndex, pGuanKa[guankaIndex].conditionTwo.nSetNum);
                 CCLOG("guanka = %d, condition = %d, conDetail = %d, nFanNum = %d", guankaIndex+1, conditionIndex, conDetailIndex, pGuanKa[guankaIndex].conditionTwo.nFanNum);
                 CCLOG("guanka = %d, condition = %d, conDetail = %d, nChaoHuNum = %d", guankaIndex+1, conditionIndex, conDetailIndex, pGuanKa[guankaIndex].conditionTwo.nChaoHuNum);*/
                break;
                
            case 3:
                if(conDetailIndex == 1){
                    pGuanKa[guankaIndex].conditionThree1.nScore = atoi(scoreElement->GetText());
                    pGuanKa[guankaIndex].conditionThree1.nSetNum = atoi(setNumElement->GetText());
                    pGuanKa[guankaIndex].conditionThree1.nFanNum = atoi(fanNumElement->GetText());
                    pGuanKa[guankaIndex].conditionThree1.nChaoHuNum = atoi(chaohuNumElement->GetText());
                    /*CCLOG("guanka = %d, condition = %d, conDetail = %d, nScore = %d", guankaIndex+1, conditionIndex, conDetailIndex, pGuanKa[guankaIndex].conditionThree1.nScore);
                     CCLOG("guanka = %d, condition = %d, conDetail = %d, nSetNum = %d", guankaIndex+1, conditionIndex, conDetailIndex, pGuanKa[guankaIndex].conditionThree1.nSetNum);
                     CCLOG("guanka = %d, condition = %d, conDetail = %d, nFanNum = %d", guankaIndex+1, conditionIndex, conDetailIndex, pGuanKa[guankaIndex].conditionThree1.nFanNum);
                     CCLOG("guanka = %d, condition = %d, conDetail = %d, nChaoHuNum = %d", guankaIndex+1, conditionIndex, conDetailIndex, pGuanKa[guankaIndex].conditionThree1.nChaoHuNum);*/
                }else{//2
                    pGuanKa[guankaIndex].conditionThree2.nScore = atoi(scoreElement->GetText());
                    pGuanKa[guankaIndex].conditionThree2.nSetNum = atoi(setNumElement->GetText());
                    pGuanKa[guankaIndex].conditionThree2.nFanNum = atoi(fanNumElement->GetText());
                    pGuanKa[guankaIndex].conditionThree2.nChaoHuNum = atoi(chaohuNumElement->GetText());
                    /*CCLOG("guanka = %d, condition = %d, conDetail = %d, nScore = %d", guankaIndex+1, conditionIndex, conDetailIndex, pGuanKa[guankaIndex].conditionThree2.nScore);
                     CCLOG("guanka = %d, condition = %d, conDetail = %d, nSetNum = %d", guankaIndex+1, conditionIndex, conDetailIndex, pGuanKa[guankaIndex].conditionThree2.nSetNum);
                     CCLOG("guanka = %d, condition = %d, conDetail = %d, nFanNum = %d", guankaIndex+1, conditionIndex, conDetailIndex, pGuanKa[guankaIndex].conditionThree2.nFanNum);
                     CCLOG("guanka = %d, condition = %d, conDetail = %d, nChaoHuNum = %d", guankaIndex+1, conditionIndex, conDetailIndex, pGuanKa[guankaIndex].conditionThree2.nChaoHuNum);*/
                }
                break;
            default:
                return;
		}	
	}
}


//#pragma mark ---------------成就处理---------------------
//获取所有成就
CHENGJIU * MyTinyXmlParser::GetChengJiu()
{
    static CHENGJIU ChengJiu[70];
    
    if (!ChengJiu[0].isUsed) {
        for (int i=0; i<70; i++) {
            ChengJiu[i].clear();
        }
        
//         CCFileData data(CCFileUtils::fullPathFromRelativePath(CHENGJIU_FILE_NAME), "r");
//         unsigned char* pBuffer = data.getBuffer();

		unsigned long  size = 0;
		unsigned char* pBuffer = CCFileUtils::sharedFileUtils()->getFileData(CCFileUtils::sharedFileUtils()->fullPathForFilename( CHENGJIU_FILE_NAME).c_str(),"r",&size);
        
        TiXmlDocument* cjDoc = new TiXmlDocument();
        
        cjDoc->Parse((char *)pBuffer);
        
        TiXmlElement* configElement = cjDoc->RootElement();//cjs node
        TiXmlElement* cjElement = configElement->FirstChildElement();//cj node
        
        int index = 0;
        while(cjElement){
            TiXmlElement* idElement = cjElement->FirstChildElement();
            ChengJiu[index].id = atoi(idElement->GetText());
            
            TiXmlElement* keyElement = idElement->NextSiblingElement();
            strcpy(ChengJiu[index].key, keyElement->GetText());
            
            TiXmlElement* infoElement = keyElement->NextSiblingElement();
            strcpy(ChengJiu[index].info, infoElement->GetText());
            
            TiXmlElement* nameElement = infoElement->NextSiblingElement();
            strcpy(ChengJiu[index].name, nameElement->GetText());
            
            ChengJiu[index].isUsed = true;
            
            cjElement = cjElement->NextSiblingElement();
            index++;
        }
        
        delete cjDoc;
    }
    
    return ChengJiu;
}


//获取更多游戏
MOREGAME * MyTinyXmlParser::GetMoreGame()
{
    static MOREGAME moreGame[10];
    
    if (!moreGame[0].isUsed) {
        for (int i=0; i<10; i++) {
            moreGame[i].clear();
        }
        
//         CCFileData data(CCFileUtils::fullPathFromRelativePath(MOREGAME_FILE_NAME), "r");
//         unsigned char* pBuffer = data.getBuffer();

		unsigned long  size = 0;
		unsigned char* pBuffer = CCFileUtils::sharedFileUtils()->getFileData(CCFileUtils::sharedFileUtils()->fullPathForFilename( MOREGAME_FILE_NAME).c_str(),"r",&size);
        
        TiXmlDocument* cjDoc = new TiXmlDocument();
        
        cjDoc->Parse((char *)pBuffer);
        
        TiXmlElement* configElement = cjDoc->RootElement();//cjs node
        TiXmlElement* cjElement = configElement->FirstChildElement();//cj node
        
        int index = 0;
        while(cjElement){
            TiXmlElement* idElement = cjElement->FirstChildElement();
            moreGame[index].id = atoi(idElement->GetText());
            
            TiXmlElement* keyElement = idElement->NextSiblingElement();
            strcpy(moreGame[index].name, keyElement->GetText());
            
            TiXmlElement* infoElement = keyElement->NextSiblingElement();
            strcpy(moreGame[index].ico, infoElement->GetText());
            
            TiXmlElement* nameElement = infoElement->NextSiblingElement();
            strcpy(moreGame[index].url, nameElement->GetText());
            
            moreGame[index].isUsed = true;
            
            cjElement = cjElement->NextSiblingElement();
            index++;
        }
        
        delete cjDoc;
    }
    
    return moreGame;
}

//获取Help页面内容
string MyTinyXmlParser::GetHelp(BYTE index)
{
    TiXmlBase::SetCondenseWhiteSpace( false );
    
//     CCFileData data(CCFileUtils::fullPathFromRelativePath(HELP_FILE_NAME), "r");
//     unsigned char* pBuffer = data.getBuffer();

	unsigned long  size = 0;
	unsigned char* pBuffer = CCFileUtils::sharedFileUtils()->getFileData(CCFileUtils::sharedFileUtils()->fullPathForFilename( HELP_FILE_NAME).c_str(),"r",&size);
    
    TiXmlDocument* helpDoc = new TiXmlDocument();
    
    helpDoc->Parse((char *)pBuffer);
    
    TiXmlElement* configElement = helpDoc->RootElement();//lines node
    TiXmlElement* h1Element = configElement->FirstChildElement();//line node
    
    string str(h1Element->GetText());
    if (index == 1) {
        str = h1Element->NextSiblingElement()->GetText();
    }
    
    return str;
}







