#pragma once
class CEventBase;

class CIgnoreAfter
{
public:
	bool Init();
	bool Uninit();
	void OnConfig();
};
extern CIgnoreAfter g_ignoreAfter;
