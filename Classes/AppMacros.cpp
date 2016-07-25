#include "AppMacros.h"
using namespace cocos2d;

/* For demonstrating using one design resolution to match different resources,
   or one resource to match different design resolutions.

   [Situation 1] Using one design resolution to match different resources.
     Please look into Appdelegate::applicationDidFinishLaunching.
     We check current device frame size to decide which resource need to be selected.
     So if you want to test this situation which said in title '[Situation 1]',
     you should change ios simulator to different device(e.g. iphone, iphone-retina3.5, iphone-retina4.0, ipad, ipad-retina),
     or change the window size in "proj.XXX/main.cpp" by "CCEGLView::setFrameSize" if you are using win32 or linux plaform
     and modify "proj.mac/AppController.mm" by changing the window rectangle.

   [Situation 2] Using one resource to match different design resolutions.
     The coordinates in your codes is based on your current design resolution rather than resource size.
     Therefore, your design resolution could be very large and your resource size could be small.
     To test this, just define the marco 'TARGET_DESIGN_RESOLUTION_SIZE' to 'DESIGN_RESOLUTION_2048X1536'
     and open iphone simulator or create a window of 480x320 size.

   [Note] Normally, developer just need to define one design resolution(e.g. 960x640) with one or more resources.
 */

// 图片资源的实际设计尺寸应该与游戏画布定义的设计尺寸一致，否则图片资源会按系数进行缩放来匹配游戏画布定义的尺寸
#if (SCREEN_ORIENTATION == SCREEN_ORIENTATION_LANDSCAPE)		// 横屏的画布设计尺寸和图片资源实际设计尺寸
	CCSize size960x540(960, 540);
	CCSize size800x480(800, 480);
	CCSize size960x600(960, 600);
	CCSize size960x640(960, 640);
	CCSize size960x720(960, 720);
	CCSize size1138x640(1138, 640);
	Resource QHDResource		=  { cocos2d::CCSizeMake(960, 540),    "QHD"};
	Resource WVGAResource		=  { cocos2d::CCSizeMake(800, 480),    "WVGA"};
	Resource WXGAResource		=  { cocos2d::CCSizeMake(960, 600),    "WXGA"};
	Resource DVGAResource		=  { cocos2d::CCSizeMake(960, 640),    "DVGA"};
	Resource XGAResource		=  { cocos2d::CCSizeMake(960, 720),    "XGA"};
	Resource XQHDResource		=  { cocos2d::CCSizeMake(1138, 640),    "XQHD"};
#elif (SCREEN_ORIENTATION == SCREEN_ORIENTATION_PORTRAIT)		// 竖屏的画布设计尺寸和图片资源实际设计尺寸
	CCSize size960x540(540, 960);
	CCSize size800x480(480, 800);
	CCSize size960x600(600, 960);
	CCSize size960x640(640, 960);
	CCSize size960x720(720, 960);
	Resource QHDResource		=  { cocos2d::CCSizeMake(540, 960),    "QHD"};
	Resource WVGAResource		=  { cocos2d::CCSizeMake(480, 800),    "WVGA"};
	Resource WXGAResource		=  { cocos2d::CCSizeMake(600, 960),    "WXGA"};
	Resource DVGAResource		=  { cocos2d::CCSizeMake(640, 960),    "DVGA"};
	Resource XGAResource		=  { cocos2d::CCSizeMake(720, 960),    "XGA"};
#else
	#error unknown target ORIENTATION!
#endif

//design resolution size , resource size , CCEGLView size, resource size can Zoom to resolution size
//CCEGLView size must display entire  resolution size

// 1、960*540，最宽屏比例16:9
#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_960x540)
	CCSize designResolutionSize = size960x540;
	Resource designResolutionRes = QHDResource;

// 2、800*480，适中比例5:3
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_800x480)
	CCSize designResolutionSize = size800x480;
	Resource designResolutionRes = WVGAResource;

// 3、960*600，适中比例16:10
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_960x600)
	CCSize designResolutionSize = size960x600;
	Resource designResolutionRes = WXGAResource;

// 4、960*640，适中比例3:2
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_960x640)
	CCSize designResolutionSize = size960x640;
	Resource designResolutionRes = DVGAResource;

// 5、960*720，最窄比例4:3
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_960x720)
	CCSize designResolutionSize = size960x720;
	Resource designResolutionRes = XGAResource;
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1138x640)
	CCSize designResolutionSize = size1138x640;
	Resource designResolutionRes = XQHDResource;
#else
	#error unknown target design resolution!
#endif