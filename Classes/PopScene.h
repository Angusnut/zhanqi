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
    ~PopScene();
    CREATE_FUNC(PopScene);
    //���öԻ�����ı�����
    void setContent(int);
    //�ڵ����ĶԻ����ϼӰ�ť�����µĺ����Ƕ�Ӧ�İ�ť�Ĵ����¼�
    void yesButton(int);
    void noButton(int);
    void setAnimation(string);
    void setBg(string, int, int);
    void setContent(string, int, int);
private:
    ////���öԻ����title
    void setTitle();
    //m_size������ǶԻ��򱳾��Ĵ�С
    CCSize mSize;
    //�Ի���ı�������
    CCSprite * mBg;
    int myflag;
    void onOK(CCObject* pSender);
    void onBack(CCObject* pSender);
    void onExit(CCObject* pSender);
    void onStart(CCObject* pSender);
	void onLoad(CCObject* pSender);
};
#endif