//
//  RegisterLayer.h
//
//  注册界面
//  
//

#pragma once

#ifndef yuri_RegisterLayer_h
#define yuri_RegisterLayer_h

#include "cocos2d.h"
//CCEditBox,添加完头文件还要添加对应的命名空间，c++真麻烦
//同时还需要继承CCEditBoxDelegate
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class RegisterLayer : public CCLayer, public CCEditBoxDelegate
{
private:
	//玩家昵称
	CCEditBox * ebUserName;
	//游戏账号
	CCEditBox * ebGameAccount;
	//游戏密码
	CCEditBox * ebPassword;
	//确认密码
	CCEditBox * ebConfirmPassword;
	//添加输入框    
	void addEditBox(CCEditBox * editBox,CCPoint editPoint, char * defaultValue,bool isPassword);

public:
	RegisterLayer(void);
	virtual ~RegisterLayer(void);

	virtual bool init();
	virtual void onExit();

	virtual void onMenuBackCallback(CCObject* pSender);
	virtual void onMenuLoginNowCallback(CCObject* pSender);

	//定义了EditBox，就要申明这几个方法
	virtual void editBoxEditingDidBegin(extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(extension::CCEditBox* editBox);

	 CREATE_FUNC(RegisterLayer);
};

#endif