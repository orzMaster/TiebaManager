#include "stdafx.h"
#include "IgnoreBefore.h"
#include "resource.h"
#include "IgnoreBeforeDlg.h"

#include <MiscHelper.h>

#include <TBMAPI.h>
#include <TBMCoreConfig.h>
#include <TiebaClawer.h>
#include <TiebaOperate.h>
#include <TBMOperate.h>

#include <Mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CIgnoreBefore g_ignoreBefore;

extern "C" __declspec(dllexport) bool __cdecl Init()
{
	return g_ignoreBefore.Init();
}

extern "C" __declspec(dllexport) bool __cdecl Uninit()
{
	return g_ignoreBefore.Uninit();
}

extern "C" __declspec(dllexport) LPCWSTR __cdecl GetDescription()
{
	return _T("忽略之前\r\n")
		_T("\r\n")
		_T("作者：Master");
}

extern "C" __declspec(dllexport) void __cdecl OnConfig()
{
	g_ignoreBefore.OnConfig();
}

bool CIgnoreBefore::Init()
{
	return true;
}

bool CIgnoreBefore::Uninit()
{
	return true;
}

void CIgnoreBefore::OnConfig()
{
	if (!CTBMAPI::GetTiebaOperate()->HasSetTieba())
	{
		AfxMessageBox(_T("请先确认贴吧！"), MB_ICONERROR);
		return;
	}
}