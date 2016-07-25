#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "CCApplication.h"
#include "cocos2d.h"

USING_NS_CC;
/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
enum cur_layer {
	cur_scene_valid,
	shop_layer
};

class  AppDelegate : private CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();

public:
    static int cur_scene_flag;
    static CCLayer* g_pLayer;
};

#endif // _APP_DELEGATE_H_

