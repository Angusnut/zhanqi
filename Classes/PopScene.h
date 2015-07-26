#ifndef _POP_SCENE_H_
#define _POP_SCENE_H_
#include "cocos2d.h"
#include "XMLParser.h"
#include "HelloWorldScene.h"
using namespace cocos2d;

class PopScene : public CCLayer
{
public:
    static CCScene * scene();
    bool init();
    CREATE_FUNC(PopScene);
    //设置对话框的文本内容
    void setContent(int);
    //在弹出的对话框上加按钮，以下的函数是对应的按钮的处理事件
    void yesButton(int);
    void noButton(int);
    void setBg(string, int, int);
    void setContent(string, int, int);
private:
    ////设置对话框的title
    void setTitle();
    //m_size代表的是对话框背景的大小
    CCSize mSize;
    //对话框的背景精灵
    CCSprite * mBg;
    void onOK(CCObject* pSender);
    void onBack(CCObject* pSender);
    void onExit(CCObject* pSender);
};
#endif