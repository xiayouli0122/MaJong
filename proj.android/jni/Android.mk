LOCAL_PATH := $(call my-dir)

CLASS_PATH := ../../Classes

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared
LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES :=	hellocpp/main.cpp \
			$(CLASS_PATH)/AppMacros.cpp \
			$(CLASS_PATH)/AppDelegate.cpp \
			$(CLASS_PATH)/StoreLayer.cpp \
			$(CLASS_PATH)/CallJni.cpp \
			$(CLASS_PATH)/Common/CommonFunction.cpp \
			$(CLASS_PATH)/Common/MyTinyXmlParser.cpp \
			$(CLASS_PATH)/Common/md5.cpp \
			$(CLASS_PATH)/Entity/DeskEntity.cpp \
			$(CLASS_PATH)/Layer/GameCjLayer.cpp \
			$(CLASS_PATH)/Layer/GameDesk.cpp \
			$(CLASS_PATH)/Layer/GameMenu.cpp \
			$(CLASS_PATH)/Layer/GameMessage.cpp \
			$(CLASS_PATH)/Layer/GamePause.cpp \
			$(CLASS_PATH)/Layer/GameResult.cpp \
			$(CLASS_PATH)/Layer/GameSet.cpp \
			$(CLASS_PATH)/Layer/GameShowCj.cpp \
			$(CLASS_PATH)/Layer/GkInfoDetailLayer.cpp \
			$(CLASS_PATH)/Layer/GkInfoLayer.cpp \
			$(CLASS_PATH)/Layer/GuanKaLayer.cpp \
			$(CLASS_PATH)/Layer/SetProgress.cpp \
			$(CLASS_PATH)/Layer/PersonSet.cpp \
			$(CLASS_PATH)/Layer/GameMGLayer.cpp \
			$(CLASS_PATH)/Layer/GameHelp.cpp \
			$(CLASS_PATH)/Layer/SplashLayer.cpp \
			$(CLASS_PATH)/Sprite/Card.cpp \
			$(CLASS_PATH)/Sprite/MyCard.cpp \
			$(CLASS_PATH)/Sprite/OutCard.cpp \
			$(CLASS_PATH)/Sprite/Timer.cpp \
			$(CLASS_PATH)/Sprite/GuanKaSprite.cpp \
			$(CLASS_PATH)/Sprite/SelectSprite.cpp \
			$(CLASS_PATH)/Sprite/GameCjSprite.cpp \
			$(CLASS_PATH)/Sprite/ShowCj.cpp \
			$(CLASS_PATH)/Sprite/GameMGSprite.cpp \
			$(CLASS_PATH)/Sprite/SpriteWordAndImage.cpp \
			$(CLASS_PATH)/Sprite/ScrollWordAndImage.cpp \
			$(CLASS_PATH)/Sprite/Batch/DeskCardsBatch.cpp \
			$(CLASS_PATH)/Sprite/Batch/MyCardsBatch.cpp \
			$(CLASS_PATH)/Sprite/Batch/MarkBatch.cpp \
			$(CLASS_PATH)/Sprite/Batch/ActionBatch.cpp \
			$(CLASS_PATH)/Sprite/Batch/GuanKaBatch.cpp \
			$(CLASS_PATH)/Sprite/Batch/GameCjBatch.cpp \
			$(CLASS_PATH)/Sprite/Batch/GkInfoBatch.cpp \
			$(CLASS_PATH)/Sprite/Batch/GameMGBatch.cpp \
			$(CLASS_PATH)/Sprite/Batch/SplashBatch.cpp \
			$(CLASS_PATH)/Scene/MenuScene.cpp \
			$(CLASS_PATH)/Scene/GameScene.cpp \
			$(CLASS_PATH)/Scene/GuanKaScene.cpp \
			$(CLASS_PATH)/Scene/HelpScene.cpp \
			$(CLASS_PATH)/Scene/LoadingScene.cpp \
			$(CLASS_PATH)/Scene/SetScene.cpp \
			$(CLASS_PATH)/Scene/PersonSetScene.cpp \
			$(CLASS_PATH)/Scene/GameMoreGameScene.cpp \
			$(CLASS_PATH)/Scene/LoginScene.cpp \
			$(CLASS_PATH)/GameCore/GameLogical.cpp \
			$(CLASS_PATH)/GameCore/AI/Robot.cpp \
			$(CLASS_PATH)/tinyxml/tinystr.cpp \
			$(CLASS_PATH)/tinyxml/tinyxml.cpp \
			$(CLASS_PATH)/tinyxml/tinyxmlerror.cpp \
			$(CLASS_PATH)/tinyxml/tinyxmlparser.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

$(call import-add-path,$(COCOS2DX_ROOT))
$(call import-add-path,$(COCOS2DX_ROOT)\cocos2dx\platform\third_party\android\prebuilt)

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
