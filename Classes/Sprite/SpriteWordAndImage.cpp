//
//  SpriteWordAndImage.cpp
//  xzdd
//
//  Created by  on 12-7-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "SpriteWordAndImage.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IOSCommon.h"
#endif

using namespace cocos2d;

//初始化--------------------------------
SpriteWordAndImage::SpriteWordAndImage(void)
{
}
SpriteWordAndImage::~SpriteWordAndImage(void)
{
}
bool SpriteWordAndImage::init()
{
    if(!CCSprite::init())
    {
        return false;
    }
    CCSprite * image = CCSprite::createWithSpriteFrameName("e1.png");
    image_height = image->getContentSize().height;
    image_width  = image->getContentSize().width;
    line_height = CommonFunction::GetValueByDev(12);
    image->release();
    AddLabel();
    return true;
}
void SpriteWordAndImage::AddLabel()
{
    for (int i=0; i<15; i++) {
        m_Imgs[i].clear();        
    }
    
    CCLabelTTF * tl = CCLabelTTF::create("", m_fontName, m_fontSize);
    //生成代替图片的空格
    string imgWord = " ";
    tl->setString(imgWord.c_str());
    float imgWidth = tl->getContentSize().width;
    while (imgWidth < image_width) {
        imgWord += " ";
        tl->setString(imgWord.c_str());
        imgWidth = tl->getContentSize().width;
    }
    string oriStr = m_label;
    string outStr = "";
    string lineStr = "";
    BYTE wordBegin = 0;
    BYTE imgIndex = 0;
    BYTE lineIndex = 1;
    float width = 0;
    float height = 0;
    float lineHeight = line_height;
    bool isImage = false;
    
    int count = CommonFunction::calcCharCount(oriStr.c_str());
    for (int i=0; i<count; i++) {
        string word = CommonFunction::subString(oriStr, i,1);
        
        if (word.c_str()[0] == '[' && i+2<count) {
            string nimg;
            int end = i+1;
            while (CommonFunction::subString(oriStr, end,1).c_str()[0] != ']' && end < count) {
                end++;
            }
            if (CommonFunction::subString(oriStr, end,1).c_str()[0] == ']') {
                m_Imgs[imgIndex].nUsed = true;
                m_Imgs[imgIndex].nImg = CommonFunction::subString(oriStr,i+1,end-i-1);
                word = imgWord;
                i = end;
                isImage = true;
            }
        }
        
        lineStr += word;
        tl->setString(lineStr.c_str());
        if (colorType == CT_Black) {
            tl->setColor(CC_Black);
        }
        width = tl->getContentSize().width;
        if (width > m_width) { //判断是否要换行
            
            CCLabelTTF * l = CCLabelTTF::create(outStr.c_str(), m_fontName, m_fontSize);
            l->setAnchorPoint(ccp(0,0.5));
            if (colorType == CT_Black) {
                l->setColor(CC_Black);
            }
            l->setPosition(ccp(0, height - lineHeight*0.5));
            addChild(l);
            height -= lineHeight;
            lineHeight = line_height;
            
            outStr = word;
            lineStr = word;
            lineIndex++;
        }
        else
        {
            outStr += word;
        }
        wordBegin = i;
        
        if (isImage) { //计算图片位置 图片索引累加
            lineHeight = image_height>lineHeight?image_height:lineHeight;
            m_Imgs[imgIndex].nWidth= width > m_width?imgWidth*0.5:width-imgWidth*0.5;
            m_Imgs[imgIndex].nHeight = height - lineHeight*0.5;
            imgIndex++;
        }
        isImage = false;

    }
    
    CCLabelTTF * l = CCLabelTTF::create(outStr.c_str(), m_fontName, m_fontSize);
    l->setAnchorPoint(ccp(0,0.5));
    if (colorType == CT_Black) {
        l->setColor(CC_Black);
    }
    l->setPosition(ccp(0, height- lineHeight*0.5));
    countHeight = (height-lineHeight)*-1; //算总高度
    addChild(l);
    AddImages();
    tl->release();
}
void SpriteWordAndImage::AddImages()
{
    for (int i=0; i<15; i++) {
        if (m_Imgs[i].nUsed) {
            CCSprite * image = CCSprite::createWithSpriteFrameName(CommonFunction::GetExpressionImageByByte(m_Imgs[i].nImg));
            image->setPosition(ccp(m_Imgs[i].nWidth,m_Imgs[i].nHeight));
            addChild(image);
        }    
        else{
            return;
        }
    }
}
string SpriteWordAndImage::FillLineBySpace(string lineStr)
{
    CCLabelTTF * tl = CCLabelTTF::create("", m_fontName, m_fontSize);
    float width = 0;
    while (width<m_width) {
        lineStr += " ";
        tl->setString(lineStr.c_str());
        width = tl->getContentSize().width;
    }
    lineStr = lineStr.substr(0,lineStr.length()-1);
    tl->release();
    return lineStr;
}

void SpriteWordAndImage::setString(char *label, char *fontName, float fontSize)
{
    m_fontName = fontName;
    m_fontSize = fontSize;
    setString(label);
}
void SpriteWordAndImage::setString(char *label)
{
    m_label = label;
    
    removeAllChildrenWithCleanup(true);
    AddLabel();
}
void SpriteWordAndImage::setWidth(float labelWidth)
{
    m_width = labelWidth;  
}

//通过字符串创建对象
SpriteWordAndImage* SpriteWordAndImage::Create(char *label, char *fontName, float fontSize,float width, ColorType cType)
{
	SpriteWordAndImage* pSpriteWordAndImage = new SpriteWordAndImage();
    pSpriteWordAndImage->m_label = label;
    pSpriteWordAndImage->m_fontName = fontName;
    pSpriteWordAndImage->m_fontSize = fontSize;
    pSpriteWordAndImage->m_width = width;
    pSpriteWordAndImage->colorType = cType;
    pSpriteWordAndImage->init();
	pSpriteWordAndImage->autorelease();
    
	return pSpriteWordAndImage;
}

