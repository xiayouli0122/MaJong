#include "SelectSprite.h"

using namespace cocos2d;

SelectSprite::SelectSprite(void)
{
}


SelectSprite::~SelectSprite(void)
{
}

bool SelectSprite::init()
{
    if(!CCSprite::init())
    {
        return false;
    }
    
	gou = CCSprite::createWithSpriteFrameName(CONS_Image_Set_Checkbox);
	gou->setVisible(false);
	addChild(gou, 1);
    
	setVisible(true);
    return true;
    
}

SelectSprite* SelectSprite::selectWithFrameName(const char *pFrameName)
{

	SelectSprite* pSelectSprite = new SelectSprite();
	pSelectSprite->init();
	pSelectSprite->initWithSpriteFrameName(pFrameName);
	pSelectSprite->autorelease();

	CCSize pSize = pSelectSprite->getContentSize();

	pSelectSprite->gou->setPosition(ccp(pSize.width*0.65, pSize.height*0.55));

	return pSelectSprite;

}

void SelectSprite::setSelectDisplay(SelectState s){
    
	switch(s)
	{
		case ST_Select:
			state = ST_Select;
			this->gou->setVisible(true);
			break;
		case ST_Unselect:
			state = ST_Unselect;
			this->gou->setVisible(false);
		default:
			return;
	}
    
	this->setVisible(true);
}