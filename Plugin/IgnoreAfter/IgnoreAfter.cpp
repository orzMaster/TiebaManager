#include "stdafx.h"
#include "IgnoreAfter.h"
#include "resource.h"
#include "IgnoreAfterDlg.h"

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

CIgnoreAfter g_ignoreAfter;

extern "C" __declspec(dllexport) bool __cdecl Init()
{
	return g_ignoreAfter.Init();
}

extern "C" __declspec(dllexport) bool __cdecl Uninit()
{
	return g_ignoreAfter.Uninit();
}

extern "C" __declspec(dllexport) LPCWSTR __cdecl GetDescription()
{
	return _T("忽略之后\r\n")
		_T("\r\n")
		_T("作者：Master");
}

extern "C" __declspec(dllexport) void __cdecl OnConfig()
{
	g_ignoreAfter.OnConfig();
}

bool CIgnoreAfter::Init()
{
	return true;
}

bool CIgnoreAfter::Uninit()
{
	return true;
}

void CIgnoreAfter::OnConfig()
{
	if (!CTBMAPI::GetTiebaOperate()->HasSetTieba())
	{
		AfxMessageBox(_T("请先确认贴吧！"), MB_ICONERROR);
		return;
	}
}