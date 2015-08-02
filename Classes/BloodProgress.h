#ifndef __BLOOD_H__
#define __BLOOD_H__

#include "cocos2d.h"
using namespace cocos2d;

class BloodProgress : public CCNode
{
public:
	BloodProgress();

public:
	void setBackgroundTexture(const char *pName);
	void setForegroundTexture(const char *pName);
	void setTotalProgress(float total);
	void setCurrentProgress(float progress);
	float getCurrentProgress() const;
	float getTotalProgress() const;

private:
	void setForegroundTextureRect(const CCRect &rect);

private:
	CCSprite *m_progressBackground;
	CCSprite *m_progressForeground;
	float m_totalProgress;
	float m_currentProgress;
	float m_scale;
};

#endif