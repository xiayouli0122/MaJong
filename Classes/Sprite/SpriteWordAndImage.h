//
//  SpriteWordAndImage.h
//  xzdd
//
//  Created by  on 12-7-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_SpriteWordAndImage_h
#define xzdd_SpriteWordAndImage_h
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include "CommonFunction.h"
#else 
#include "../Common/CommonFunction.h"
#endif

using namespace cocos2d;

struct ChatImg      //聊天中的图片
{
    string  nImg;           //图片文件
    float   nWidth;         //放置宽度
    float   nHeight;        //放置高度
    bool    nUsed;          //是否使用
    
    void clear()
    {
        nImg    = "";
        nWidth  = 0;
        nHeight = 0;
        nUsed   = false;
    }
};


//sprite对象，桌面上的一张牌
class SpriteWordAndImage : public CCSprite
{
    char *  m_label; 
    char *  m_fontName; 
    float   m_fontSize;
    float   m_width;
    ChatImg m_Imgs[15]; //最多一次使用15个表情
    float   image_height;
    float   image_width;
    float   line_height;
    ColorType colorType;
public:
    float   countHeight;
    //初始化--------------------------------
    SpriteWordAndImage(void);
	virtual ~SpriteWordAndImage(void);
    virtual bool init();

    void setWidth(float labelWidth);
    void setString(char *label, char *fontName, float fontSize);
    void setString(char *label);
    //通过图片名创建card对象
    static SpriteWordAndImage* Create(char *label, char *fontName, float fontSize,float width, ColorType colorType);
private:
    void AddLabel();
    //绘制表情
    void AddImages();
    //用空格填充一行
    string FillLineBySpace(string lineStr);
};

#endif