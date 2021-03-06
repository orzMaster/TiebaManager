﻿/*
Copyright (C) 2015  xfgryujk
http://tieba.baidu.com/f?kw=%D2%BB%B8%F6%BC%AB%C6%E4%D2%FE%C3%D8%D6%BB%D3%D0xfgryujk%D6%AA%B5%C0%B5%C4%B5%D8%B7%BD

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "stdafx.h"
#include <StringHelper.h>
#include <ConfigFile.h>
#import <msscript.ocx> no_namespace
using namespace tinyxml2;


HELPER_API DECLEAR_READ(RegexText)
{
	const XMLElement* optionNode = root.FirstChildElement(m_name);
	if (optionNode == NULL)
	{
		UseDefault();
		return;
	}

	COption<BOOL> isRegex("IsRegex");
	COption<CString> text("Text");
	isRegex.Read(*optionNode);
	text.Read(*optionNode);

	m_value.Set(isRegex, text);

	if (!IsValid(m_value))
		UseDefault();
}

HELPER_API DECLEAR_WRITE(RegexText)
{
	tinyxml2::XMLDocument* doc = root.GetDocument();
	XMLElement* optionNode = doc->NewElement(m_name);
	root.LinkEndChild(optionNode);

	COption<BOOL> isRegex("IsRegex");
	*isRegex = m_value.isRegex;
	isRegex.Write(*optionNode);
	COption<CString> text("Text");
	*text = m_value.text;
	text.Write(*optionNode);
}

HELPER_API DEFINE_READ_VECTOR(RegexText)

HELPER_API DEFINE_WRITE_VECTOR(RegexText)


// 分割字符串
HELPER_API void SplitString(CStringArray& dst, const CString& src, const CString& slipt)
{
	dst.RemoveAll();
	const int len = _tcslen(slipt);

	int start = 0, end = 0;
	while ((end = src.Find(slipt, end)) != -1)
	{
		dst.Add(src.Mid(start, end - start));
		start = end += len;
	}
	dst.Add(src.Right(src.GetLength() - start));
}


// 字符串包含
HELPER_API BOOL StringIncludes(const CString& str, const CString& content)
{
	return str.Find(content) != -1;
}

// 字符串包含
HELPER_API BOOL StringIncludes(const CString& str, const CString& content, BOOL isRegex)
{
	if (isRegex)
	{
		try
		{
			std::wregex reg(content);
			return std::regex_search((LPCWSTR)str, reg);
		}
		catch (...)
		{
			AfxMessageBox(_T("正则表达式错误！"), MB_ICONERROR);
			return FALSE;
		}
	}
	else
		return StringIncludes(str, content);
}

// 字符串包含
HELPER_API BOOL StringIncludes(const CString& str, const RegexText& content, int* _pos, int* length)
{
	BOOL result;
	if (content.isRegex)
	{
		std::wcmatch res;
		try
		{
			result = std::regex_search((LPCWSTR)str, res, content.regexp);
		}
		catch (...)
		{
			AfxMessageBox(_T("正则表达式错误！"), MB_ICONERROR);
			return FALSE;
		}

		if (result && _pos != NULL && length != NULL)
		{
			*_pos = res.position();
			*length = res.length();
		}
	}
	else
	{
		int pos = str.Find(content.text);
		result = pos != -1;
		if (result && _pos != NULL && length != NULL)
		{
			*_pos = pos;
			*length = content.text.GetLength();
		}
	}
	return result;
}

// 字符串匹配
HELPER_API BOOL StringMatchs(const CString& str, const CString& content, BOOL isRegex)
{
	if (isRegex)
	{
		try
		{
			std::wregex reg(content);
			return std::regex_match((LPCWSTR)str, reg);
		}
		catch (...)
		{
			AfxMessageBox(_T("正则表达式错误！"), MB_ICONERROR);
			return FALSE;
		}
	}
	else
		return str == content;
}

// 字符串匹配
HELPER_API BOOL StringMatchs(const CString& str, const RegexText& content)
{
	if (content.isRegex)
	{
		try
		{
			return std::regex_match((LPCWSTR)str, content.regexp);
		}
		catch (...)
		{
			AfxMessageBox(_T("正则表达式错误！"), MB_ICONERROR);
			return FALSE;
		}
	}
	else
		return str == content.text;
}


// 取字符串之间的字符串
HELPER_API CString GetStringBetween(const CString& src, const CString& left, const CString& right, int startPos)
{
	int leftPos = src.Find(left, startPos);
	if (leftPos == -1)
		return _T("");
	leftPos += left.GetLength();
	int rightPos = src.Find(right, leftPos);
	if (rightPos == -1)
		return _T("");
	return src.Mid(leftPos, rightPos - leftPos);
}

// 取字符串之间的字符串，包括左右的字符串
HELPER_API CString GetStringBetween2(const CString& src, const CString& left, const CString& right, int startPos)
{
	int leftPos = src.Find(left, startPos);
	if (leftPos == -1)
		return _T("");
	int rightPos = src.Find(right, leftPos + left.GetLength());
	if (rightPos == -1)
		return _T("");
	rightPos += right.GetLength();
	return src.Mid(leftPos, rightPos - leftPos);
}

// 取字符串之前的字符串
HELPER_API CString GetStringBefore(const CString& src, const CString& right, int startPos)
{
	int rightPos = src.Find(right, startPos);
	if (rightPos == -1)
		return _T("");
	return src.Left(rightPos);
}


// 写字符串到文件
HELPER_API BOOL WriteString(const CString& src, const CString& path)
{
	CStdioFile file;
	if (!file.Open(path, CFile::modeCreate | CFile::modeWrite))
		return FALSE;
	file.WriteString(src);
	return TRUE;
}


// Unicode转GBK
HELPER_API CStringA W2GBK(const CStringW& src)
{
	int dstLen = WideCharToMultiByte(936, 0, src, src.GetLength(), NULL, 0, NULL, NULL);
	if (dstLen == 0)
		return "";
	CStringA res;
	WideCharToMultiByte(936, 0, src, src.GetLength(), res.GetBuffer(dstLen), dstLen, NULL, NULL);
	res.ReleaseBuffer(dstLen);
	return res;
}

// GBK转Unicode
HELPER_API CStringW GBK2W(const CStringA& src)
{
	int dstLen = MultiByteToWideChar(936, 0, src, src.GetLength(), NULL, 0);
	if (dstLen == 0)
		return L"";
	CStringW res;
	MultiByteToWideChar(936, 0, src, src.GetLength(), res.GetBuffer(dstLen), dstLen);
	res.ReleaseBuffer(dstLen);
	return res;
}

// URL编码
HELPER_API CString EncodeURI(const CString& src)
{
	CComPtr<IScriptControl> script;
	if (FAILED(script.CoCreateInstance(__uuidof(ScriptControl))))
		return _T("");
	script->put_Language(_bstr_t(_T("JScript")));
	_variant_t param = src;
	SAFEARRAY* params = SafeArrayCreateVector(VT_VARIANT, 0, 1);
	LONG index = 0;
	if (FAILED(SafeArrayPutElement(params, &index, &param)))
		return _T("");
	_variant_t result;
	script->raw_Run(_bstr_t(_T("encodeURIComponent")), &params, result.GetAddress());
	SafeArrayDestroy(params);
	return (LPCTSTR)(_bstr_t)result;
}

// URL编码 GBK版
HELPER_API CString EncodeURI_GBK(const CString& _src)
{
	CString result, tmp;
	CStringA src = W2GBK(_src);
	const int len = src.GetLength();
	for (int i = 0; i < len; i++)
	{
		tmp.Format(_T("%%%02X"), src[i] & 0xFF);
		result += tmp;
	}
	return result;
}

// HTML转义
HELPER_API CString HTMLEscape(const CString& src)
{
	CString result = src;
	result.Replace(_T("&"), _T("&amp;"));
	result.Replace(_T(" "), _T("&nbsp;"));
	result.Replace(_T("<"), _T("&lt;"));
	result.Replace(_T(">"), _T("&gt;"));
	return result;
}

// HTML反转义
HELPER_API CString HTMLUnescape(const CString& src)
{
	CString result = src;
	//result.Replace(_T("<br>"), _T("\r\n")); // 不转换行符
	result.Replace(_T("&nbsp;"), _T(" "));
	result.Replace(_T("&quot;"), _T("\""));
	result.Replace(_T("&&#039;"), _T("'"));
	result.Replace(_T("&lt;"), _T("<"));
	result.Replace(_T("&gt;"), _T(">"));
	result.Replace(_T("&amp;"), _T("&"));
	return result;
}

// JS反转义，调用者应自行转义src里的双引号
HELPER_API CString JSUnescape(const CString& src)
{
	CComPtr<IScriptControl> script;
	if (FAILED(script.CoCreateInstance(__uuidof(ScriptControl))))
		return _T("");
	script->put_Language(_bstr_t(_T("JScript")));
	_variant_t result;
	if (FAILED(script->raw_Eval(_bstr_t((LPCTSTR)(_T("\"") + src + _T("\""))), result.GetAddress())))
		return _T("");
	return (LPCTSTR)(_bstr_t)result;
}
