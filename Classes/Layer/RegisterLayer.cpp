#include "RegisterLayer.h"

#include "Common\CommonFunction.h"
#include "cocos2d.h"

USING_NS_CC;

RegisterLayer::RegisterLayer(void)
{
}

RegisterLayer::~RegisterLayer(void)
{
}

//实现初始化方法，在这里完成界面控件的添加
bool RegisterLayer::init()
{

	if(!CCLayer::init())
	{
		return false;
	}

	setKeypadEnabled(true);

	CCLOG("and here is RegisterLayer");
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCLOG("origin:%f %f", origin.x, origin.y);

	//背景图片
	CCSprite * bgSprite = CCSprite::create("MengBgImage.png");
	//bgSprite->setAnchorPoint(ccp(0.5, 0.5));
	bgSprite->setPosition(ccp(size.width/2.0f, size.height/2.0f));
	CCLOG("size: %f %f", size.width, size.height);
	float spx = bgSprite->getTextureRect().getMaxX();
	float spy = bgSprite->getTextureRect().getMaxY();
	CCLOG("spx,spy:%f %f", spx, spy);
	float scaleW = size.width / spx;
	float scaleH = size.height / spy;
	CCLOG("scale: %f %f", scaleW, scaleH);
	//让背景图片全屏
	bgSprite->setScaleX(scaleH); //设置精灵宽度缩放比例
	bgSprite->setScaleY(scaleH);
	/*bgSprite->setAnchorPoint(CCPointZero);*/
	this->addChild(bgSprite, 0);

	//返回按钮
	CCMenuItemImage * backBtn = CCMenuItemImage::create(
		"CloseWin1.png","CloseWin2.png",this,
		menu_selector(RegisterLayer::onMenuBackCallback)
		 );
	 CCSize backViewSize = backBtn->getContentSize();
	 CCLOG("backview.width:%f", backViewSize.width);
	 backBtn->setPosition(ccp(origin.x + backViewSize.width , size.height  - 40));
	 CCMenu * backMenu = CCMenu::create(backBtn, NULL);
	 backMenu->setPosition(CCPointZero);
	 this->addChild(backMenu);

	 //标题文字
	 CCLabelTTF* pLabel = CCLabelTTF::create("Register Account", "Thonburi", 24);
	 pLabel->setPosition(ccp(size.width/2, size.height - 40));
	 this->addChild(pLabel);

	 //立即登录按钮
	 CCMenuItemImage * loginNowBtn = CCMenuItemImage::create(
		"RegisterAndLogin.png","RegisterAndLogin.png",this,
		menu_selector(RegisterLayer::onMenuLoginNowCallback)
		 );
	 CCSize loginSize = loginNowBtn->getContentSize();
	 loginNowBtn->setPosition(ccp(size.width/2 , 100));
	 CCMenu * loginMenu = CCMenu::create(loginNowBtn, NULL);
	 loginMenu->setPosition(CCPointZero);
	 this->addChild(loginMenu);

	 //添加注册所需的输入框
	 //玩家昵称输入框背景
	 CCSprite* userNameSprite = CCSprite::create("Register1.png");
	 CCSize inputBgSize = userNameSprite->getContentSize();
	 //输入框背景的高度
	 float itemHeight = inputBgSize.height;
	 userNameSprite->setPosition(ccp(size.width/2, size.height - 140));
	 this->addChild(userNameSprite);
	 //玩家昵称输入框
	 CCSize editSize = CCSizeMake(288, 32);
	 ebUserName = CCEditBox::create(editSize, CCScale9Sprite::create());
	 CCPoint userNamePoint = CCPointMake(size.width / 2 + 80, size.height - 140);
	 addEditBox(ebUserName, userNamePoint, UTEXT("username"),false);

	 //游戏账号输入框背景
	 CCSprite* gameAccountSprite = CCSprite::create("Register2.png");
	 gameAccountSprite->setPosition(ccp(size.width/2, size.height - itemHeight - 200));
	 this->addChild(gameAccountSprite);
	 //游戏账号输入框
	 ebGameAccount = CCEditBox::create(editSize, CCScale9Sprite::create());
	 CCPoint gameAccountPoint = CCPointMake(size.width / 2 + 80, size.height -  itemHeight - 200);
	 addEditBox(ebGameAccount, gameAccountPoint, UTEXT("game account"),false);

	 //游戏密码输入框背景
	 CCSprite* passwordSprite = CCSprite::create("Register3.png");
	 passwordSprite->setPosition(ccp(size.width/2, size.height - itemHeight * 2 -240));
	 this->addChild(passwordSprite);
	 //游戏密码输入框
	 ebPassword = CCEditBox::create(editSize, CCScale9Sprite::create());
	 CCPoint passwordPoint = CCPointMake(size.width / 2 + 80, size.height - itemHeight * 2 -240);
	 addEditBox(ebPassword, passwordPoint, UTEXT("password"),true);

	 //确认密码输入框背景
	 CCSprite* confirmPasswordSprite = CCSprite::create("Register4.png");
	 confirmPasswordSprite->setPosition(ccp(size.width/2, size.height - itemHeight *3  -280));
	 this->addChild(confirmPasswordSprite);
	 //确认密码输入框
	 ebConfirmPassword = CCEditBox::create(editSize, CCScale9Sprite::create());
	 CCPoint confirmPasswordPoint = CCPointMake(size.width / 2 + 80, size.height - itemHeight * 3 -280);
	 addEditBox(ebConfirmPassword, confirmPasswordPoint, UTEXT("confirm password"),true);

	 this->setVisible(false);

	return true;
}

/*
* 功能 ： 向场景中添加输入框并设置相应属性
* editBox : 输入框  
*editPoint : 位置
* defaultValue : 缺省文本
* isPassword : true-密码，false-非密码
*/
void RegisterLayer::addEditBox(CCEditBox * editBox,CCPoint editPoint, char * defaultValue,bool isPassword)
{
	editBox->CCNode::setPosition(editPoint.x, editPoint.y);
	editBox->setFontName("GeezaPro");
	editBox->setFontSize(18);
	//输入框文字颜色
	editBox->setFontColor(ccBLACK);
	//输入框缺省文字
	editBox->setPlaceHolder(defaultValue);
	//缺省文字颜色
	ccColor3B hintColor = {118,114,114};
	editBox->setPlaceholderFontColor(hintColor); 
	//最大长度
	editBox->setMaxLength(20); 
	//默认使用键盘return类型为Done
	editBox->setReturnType(kKeyboardReturnTypeDone); 
	////输入键盘模式
	editBox->setInputMode(kEditBoxInputModeEmailAddr); 
	if (isPassword) {
		//输入密码时的替代符
        editBox->setInputFlag(kEditBoxInputFlagPassword);
     }
	editBox->setDelegate(this); //设置委托代理对象为当前类
	this->addChild(editBox);
}

void RegisterLayer::onMenuLoginNowCallback(CCObject* pSender)
{
	//立即登录按钮点击
	CCLOG("on Login now menu clicked");
	//开始注册
	//获取输入框中的内容
	const char * userName = ebUserName->getText();
	const char * gameAccount = ebGameAccount->getText();
	const char * password = ebPassword->getText();
	const char * confirmPassword = ebConfirmPassword->getText();
	CCLOG("result:[%s, %s, %s, %s]", userName, gameAccount, password, confirmPassword);
}

void RegisterLayer::onMenuBackCallback(CCObject* pSender)
{
	//返回按钮点击
	CCLOG("on back menu clicked");
	this->setVisible(false);
}

//键盘弹出后输入框获得焦点时触发
void RegisterLayer::editBoxEditingDidBegin(extension::CCEditBox* editBox)
{
	CCLOG("editBoxEditingDidBegin");
}

//键盘隐藏后输入框失去焦点时触发
void RegisterLayer::editBoxEditingDidEnd(extension::CCEditBox* editBox)
{
	CCLOG("editBoxEditingDidEnd");
}

//输入框内文本变化时触发
void RegisterLayer::editBoxTextChanged(extension::CCEditBox* editBox, const std::string& text)
{
	//CCLOG("editBoxTextChanged:%s", text);
}

//按下返回键或点击键盘外的位置时触发（点击当前输入框时不触发）
void RegisterLayer::editBoxReturn(extension::CCEditBox* editBox)
{
	CCLOG("editBoxReturn");
}

void RegisterLayer::onExit()
{
	CCLayer::onExit();
}
