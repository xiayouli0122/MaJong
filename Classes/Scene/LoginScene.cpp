#include "LoginScene.h"

#include "Common\CommonFunction.h"
#include "MenuScene.h"
#include "cocos2d.h"

USING_NS_CC;

LoginScene::LoginScene(void)
{
}


LoginScene::~LoginScene(void)
{
}

CCScene* LoginScene::scene()
{
	//创建一个场景
	CCScene* scene = CCScene::create();
	//创建一个登录的Layer
	LoginScene* layer = LoginScene::create();
	//将Layer添加到场景上去
	scene->addChild(layer);
	//这样登录的场景就算创建完成了
	return scene;
}

//实现初始化方法，在这里完成精灵按钮的添加
bool LoginScene::init()
{

	if(!CCLayer::init())
	{
		return false;
	}

	setKeypadEnabled(true);

	//初始化注册界面
	registerLayer = RegisterLayer::create();
	this->addChild(registerLayer, 2);

	CCLOG("and here is LoginScene");
	CCSprite * bgSprite = CCSprite::create("LoginBg_1.png");

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCLOG("origin:%f %f", origin.x, origin.y);

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

	this->addChild(bgSprite, 0);

	 CCLabelTTF* pLabel = CCLabelTTF::create("LoginScene...", "Thonburi", 24);

	 pLabel->setPosition(ccp(size.width/2, size.height/2 +290));

	 this->addChild(pLabel);

	 //登录按钮
	 CCMenuItemImage * loginBtn = CCMenuItemImage::create(
		"LoginBtn_1.png","LoginBtn_1.png",this,
		menu_selector(LoginScene::onMenuLoginCallback)
		 );
	 //算出登录按钮的大小
	 CCSize loginSize = loginBtn->getContentSize();
	 loginBtn->setPosition(ccp(size.width - loginSize.width - 100, size.height / 2 - 20));
	 CCMenu * loginMenu = CCMenu::create(loginBtn, NULL);
	 loginMenu->setPosition(CCPointZero);
	 this->addChild(loginMenu);

	 //注册按钮
	 CCMenuItemImage * registerBtn = CCMenuItemImage::create(
		"RegisterBtn.png","RegisterBtn.png",this,
		menu_selector(LoginScene::onMenuRegisterCallback)
		 );
	 //CCSize registerSize = registerBtn->getContentSize();
	 registerBtn->setPosition(ccp(size.width/2 - 80, size.height / 2 - 120));
	 CCMenu * registerMenu = CCMenu::create(registerBtn, NULL);
	 registerMenu->setPosition(CCPointZero);
	 this->addChild(registerMenu);
	 //快速游戏按钮
	 CCMenuItemImage * quickGameBtn = CCMenuItemImage::create(
		"QuickLogin.png","QuickLogin.png",this,
		menu_selector(LoginScene::onMenuQuickGameCallback)
		 );
	 //CCSize quickGameSize = quickGameBtn->getContentSize();
	 quickGameBtn->setPosition(ccp(size.width/2 + 80, size.height / 2 - 120));
	 CCMenu * quickGameMenu = CCMenu::create(quickGameBtn, NULL);
	 quickGameMenu->setPosition(CCPointZero);
	 this->addChild(quickGameMenu);

	 //添加两个输入框，一个账号一个密码输入
	 //使用两个float类型的数字创建一个size
	 CCSize editSize = CCSizeMake(300, 48);
	 ebUserName = CCEditBox::create(editSize, CCScale9Sprite::create());
	 CCPoint userNamePoint = CCPointMake(size.width / 2 + 100, size.height / 2 + 10);
	 addEditBox(ebUserName, userNamePoint, UTEXT("account"),false);

	 ebPassword = CCEditBox::create(editSize, CCScale9Sprite::create());
	 CCPoint passwordPoint = CCPointMake(size.width / 2 + 100, size.height / 2 - 40);
	 addEditBox(ebPassword, passwordPoint, UTEXT("pasword"),true);

	 //初始化读取上次用户输入的用户名直接填入
	 string username = CCUserDefault::sharedUserDefault()->getStringForKey("username");
	 //string 转char
	 const char *string=std::string(username).c_str();
	 CCLOG("username:%s", string);
	 ebUserName->setText(string);

	return true;
}

/*
* 功能 ： 向场景中添加输入框并设置相应属性
* editBox : 输入框  
*editPoint : 位置
* defaultValue : 缺省文本
* isPassword : true-密码，false-非密码
*/
void LoginScene::addEditBox(CCEditBox * editBox,CCPoint editPoint, char * defaultValue,bool isPassword)
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

void LoginScene::onMenuLoginCallback(CCObject* pSender)
{
	//登录按钮点击
	CCLOG("on Login menu clicked");

	//使用CCUserDefault类实现一键注册功能
	CCUserDefault::sharedUserDefault()->setStringForKey("username", ebUserName->getText());
	CCUserDefault::sharedUserDefault()->setStringForKey("password", ebPassword->getText());
	CCUserDefault::sharedUserDefault()->flush();

	//所以在快速登录的回调函数中只需要获取对应的"userName"和"password"即可.
	string username = CCUserDefault::sharedUserDefault()->getStringForKey("username");
	string password = CCUserDefault::sharedUserDefault()->getStringForKey("password");

	//c_str()函数返回一个指向正规C字符串的指针, 内容与本string串相同
	CCLOG("username:%s,pasword:%s", username.c_str(), password.c_str());
}

void LoginScene::onMenuRegisterCallback(CCObject* pSender)
{
	//注册按钮点击
	CCLOG("on register menu clicked");
	registerLayer->setVisible(true);
}

void LoginScene::onMenuQuickGameCallback(CCObject* pSender)
{
	//快速游戏按钮点击
	CCLOG("on quickgame menu clicked");
	//点击快速游戏按钮后，暂时这里就直接进入菜单按钮，开始游戏吧
	CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}

//键盘弹出后输入框获得焦点时触发
void LoginScene::editBoxEditingDidBegin(extension::CCEditBox* editBox)
{
	CCLOG("editBoxEditingDidBegin");
}

//键盘隐藏后输入框失去焦点时触发
void LoginScene::editBoxEditingDidEnd(extension::CCEditBox* editBox)
{
	CCLOG("editBoxEditingDidEnd");
}

//输入框内文本变化时触发
void LoginScene::editBoxTextChanged(extension::CCEditBox* editBox, const std::string& text)
{
	//CCLOG("editBoxTextChanged:%s", text);
}

//按下返回键或点击键盘外的位置时触发（点击当前输入框时不触发）
void LoginScene::editBoxReturn(extension::CCEditBox* editBox)
{
	CCLOG("editBoxReturn");
}

void LoginScene::keyBackClicked()
{
	//点击了返回按钮,执行退出程序
	CCLOG("keyBackClicked");
	onExit();
	exit(0);
}

void LoginScene::onExit()
{
	CCLayer::onExit();
}
