#include "AppDelegate.h"
#include "AppMacros.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Scene/LoadingScene.h"
#include "Scene/GameScene.h"
#include "Common/ConstantDef.h"
USING_NS_CC;

int  AppDelegate::cur_scene_flag = cur_scene_valid;
CCLayer* AppDelegate::g_pLayer = NULL;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	pDirector->setOpenGLView(pEGLView);

	CCSize frameSize = pEGLView->getFrameSize();
	CCLOG("ScreenSize width:%f, height:%f", frameSize.width, frameSize.height);

#if (SCREEN_ORIENTATION == SCREEN_ORIENTATION_LANDSCAPE)		// 横屏
	float frameScale = frameSize.width/frameSize.height;
#elif (SCREEN_ORIENTATION == SCREEN_ORIENTATION_PORTRAIT)		// 竖屏
	float frameScale = frameSize.height/frameSize.width;
#else
	#error unknown target ORIENTATION!
#endif

	if( frameScale < 3.0f/2.0f )			// 窄屏，屏幕宽度:高度小于3:2
	{
		// Set the design resolution
		pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
	}
	else
	{
		// Set the design resolution
		pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
	}
	

	//use fixed resource
	float fScale = MIN(designResolutionRes.size.width/designResolutionSize.width, designResolutionRes.size.height/designResolutionSize.height);
//	CCFileUtils::sharedFileUtils()->setResourceDirectory(designResolutionRes.directory);
	pDirector->setContentScaleFactor(fScale);
	CCLOG("setContentScaleFactor fscale: %f, res.size(%f, %f), deSize(%f, %f)", fScale, designResolutionRes.size.width, designResolutionRes.size.height, designResolutionSize.width, designResolutionSize.height);

	// turn on display FPS   lyp 取消帧率
	//pDirector->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this  lyp 取消帧率
	//pDirector->setAnimationInterval(1.0 / 50);

	// create a scene. it's an autorelease object
//	CCScene* pScene = CSceneInit::scene();
//	CCScene* pScene = SceneLogo::scene();
	CCScene* pScene = LoadingScene::scene(TargetSceneMainScene);

	// run
	pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	// if you use SimpleAudioEngine, it must be pause
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	CCDirector::sharedDirector()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
