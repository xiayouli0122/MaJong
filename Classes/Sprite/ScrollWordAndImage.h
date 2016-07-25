//
//  ScrollWordAndImage.h
//  xzdd
//
//  Created by  on 12-7-17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_ScrollWordAndImage_h
#define xzdd_ScrollWordAndImage_h
#include "cocos2d.h"
#include "SpriteWordAndImage.h"

using namespace cocos2d;

class ScrollWordAndImage : public CCLayer
{
    float width;
    float height;
    SpriteWordAndImage * image;    
public:
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	// implement the "static node()" method manually
	CREATE_FUNC(ScrollWordAndImage);
    
    void visit(void);
    void SetSize(float width, float height);
    void SetString(char *label);
};


#endif