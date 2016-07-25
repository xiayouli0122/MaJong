#ifndef _STORE_LAYER_H_
#define _STORE_LAYER_H_

#include "cocos2d.h"
#include "Layer/GameMessage.h"

USING_NS_CC;

class CStoreLayer : public CCLayer
{
private:
	GameMessage* m_pMessage;
public:
	CStoreLayer(void);
	~CStoreLayer(void);

	bool init();

	void CanleCallback( CCObject* pSender );

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){ return true; };
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){};
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){};

	CREATE_FUNC( CStoreLayer );

	void billCallbackFor1Goal();
	void billCallbackFor5Goal();
	void billCallbackFor10Goal();
};

#endif // !_STORE_LAYER_H_
