#pragma once
class CEventBase;

class CIgnoreBefore
{
public:
	bool Init();
	bool Uninit();
	void OnConfig();
};
extern CIgnoreBefore g_ignoreBefore;
