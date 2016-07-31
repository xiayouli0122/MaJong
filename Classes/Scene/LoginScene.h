//
//  LoginScene.h
//
//  登录界面
//  
//

#pragma once

#ifndef yuri_LoginScene_h
#define yuri_LoginScene_h

#include "cocos2d.h"
//CCEditBox,添加完头文件还要添加对应的命名空间，c++真麻烦
//同时还需要继承CCEditBoxDelegate
#include "cocos-ext.h"

#include "../Layer/RegisterLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LoginScene : public CCLayer, public CCEditBoxDelegate
{
	RegisterLayer * registerLayer;

private:
	//添加两个输入框，一个账号一个密码输入
	CCEditBox * ebUserName;
	CCEditBox * ebPassword;
	//添加输入框    
	void addEditBox(CCEditBox * editBox,CCPoint editPoint, char * defaultValue,bool isPassword);

public:
	LoginScene(void);
	virtual ~LoginScene(void);

	virtual bool init();
	virtual void onExit();

	static CCScene* scene();

	virtual void onMenuLoginCallback(CCObject* pSender);
	virtual void onMenuRegisterCallback(CCObject* pSender);
	virtual void onMenuQuickGameCallback(CCObject* pSender);

	//定义了EditBox，就要申明这几个方法
	virtual void editBoxEditingDidBegin(extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(extension::CCEditBox* editBox);
     virtual void editBoxTextChanged(extension::CCEditBox* editBox, const std::string& text);
     virtual void editBoxReturn(extension::CCEditBox* editBox);

	 //响应返回键  
	 virtual void keyBackClicked();  

	CREATE_FUNC(LoginScene);
};

#endif