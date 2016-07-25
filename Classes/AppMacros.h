#ifndef __APPMACROS_H__
#define __APPMACROS_H__


#include "cocos2d.h"

// 在这里定义画布的设计尺寸和横竖屏
#define TARGET_DESIGN_RESOLUTION_SIZE	DESIGN_RESOLUTION_1138x640		// 设置设计尺寸
//#define SCREEN_ORIENTATION				SCREEN_ORIENTATION_PORTRAIT		// 设置竖屏游戏
#define SCREEN_ORIENTATION				SCREEN_ORIENTATION_LANDSCAPE	// 设置横屏游戏

// The font size 24 is designed for small resolution, so we should change it to fit for current design resolution
#define TITLE_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / designResolutionRes.size.width * 20)

// paddy
// 游戏画布的设计尺寸，是美术出图的基准尺寸
// 以横屏游戏为例，画布设计尺寸主要考虑以下5种比例的分辨率：
// 1、最宽屏比例16:9。适用于高度需要固定的游戏，以保证在缩放时，画布高度能够优先适配屏幕高度，超出的宽度部分裁剪，这里选择960*540尺寸（可无裁剪适配720P、1080P）
// 2、中间比例5:3（偏宽屏的中间比例）。适用于宽或高不需要固定的游戏，这里选择800*480尺寸（目前该分辨率设备最多）
// 3、中间比例16:10（适中的中间比例）。适用于宽或高不需要固定的游戏，这里选择960*600尺寸（16:10设备较少）
// 4、中间比例3:2（偏窄屏的中间比例）。适用于宽或高不需要固定的游戏，这里选择960*640尺寸（Android设备3:2屏幕较少，一般不采用该尺寸）
// 5、最窄屏比例4:3。适用于宽度需要固定的游戏，以保证在缩放时，画布宽度能够优先适配屏幕宽度，超出的高度部分裁剪，这里选择960*720尺寸（除了平板，手机较少4:3屏幕，一般不采用该尺寸）
// 随着今后游戏分辨率规格的升级，增加相应比例的更大尺“DESIGN_RESOLUTION_***x***”即可
#define DESIGN_RESOLUTION_960x540		0x01			// 最宽比例16:9		中等分辨率，无裁剪适配640*360,854*480,1280*720，1920*1080
#define DESIGN_RESOLUTION_800x480		0x02			// 偏宽比例5:3		中等分辨率，无裁剪适配400*240, 800*480
#define DESIGN_RESOLUTION_960x600		0x03			// 适中比例16:10	中等分辨率，无裁剪适配1680*1050，1920*1200
#define DESIGN_RESOLUTION_960x640		0x04			// 偏窄比例3:2		中等分辨率，无裁剪适配480*320, 960*640 
#define DESIGN_RESOLUTION_960x720		0x05			// 最窄比例4:3		中等分辨率，无裁剪适配320*240, 480*360，640*480，1024*768，2048*1536

#define DESIGN_RESOLUTION_1138x640		0x06

#define SCREEN_ORIENTATION_LANDSCAPE	0			// 横屏
#define SCREEN_ORIENTATION_PORTRAIT		1			// 竖屏

typedef struct tagResource
{
	cocos2d::CCSize size;
	char directory[128];
}Resource;

extern cocos2d::CCSize designResolutionSize;
extern Resource designResolutionRes;

#endif /* __APPMACROS_H__ */
