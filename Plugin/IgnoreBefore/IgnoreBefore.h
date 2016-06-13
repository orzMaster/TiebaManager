#pragma once
class CEventBase;
class CIgnoreBeforeDlg;

class CIgnoreBefore
{
public:
	bool Init();
	bool Uninit();
	void OnConfig();

	void StartIgnoreBefore();
	void StopIgnoreBefore();
	void IgnoreBeforeThread();


	CIgnoreBeforeDlg* m_ignoreBeforeDlg = NULL;

	unique_ptr<thread> m_ignoreBeforeThread;
	volatile BOOL m_stopFlag = TRUE;
};
extern CIgnoreBefore g_ignoreBefore;
