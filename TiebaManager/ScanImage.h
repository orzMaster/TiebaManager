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

#pragma once
#include <functional>
namespace cv { class Mat; }


class CScanImage
{
protected:
	set<CString> m_leagalImage; // 已检查不违规的图片
	set<CString> m_illegalImage; // 已检查违规的图片

public:
	// 检查图片违规1，检测信任用户、获取图片地址
	BOOL CheckImageIllegal(const CString& author, std::function<void(vector<CString>&)> getImages, CString& msg);
	// 检查图片违规2，下载图片、比较图片
	BOOL DoCheckImageIllegal(vector<CString>& imgs, CString& msg);
protected:
	double GetMSSIM(const cv::Mat& i1, const cv::Mat& i2);
public:
	void ClearCache();
};
