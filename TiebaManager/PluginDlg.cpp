/*
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

// PluginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PluginDlg.h"

#include "PluginManager.h"


// CPluginDlg 对话框

IMPLEMENT_DYNAMIC(CPluginDlg, CNormalDlg)

CPluginDlg::CPluginDlg(CPluginDlg*& pThis, CPluginManager& pluginManager, CWnd* pParent /*=NULL*/) : CNormalDlg(CPluginDlg::IDD, pParent),
	m_pThis(pThis),
	m_pluginManager(pluginManager),
	m_plugins(pluginManager.GetPlugins())
{

}

#pragma region MFC
CPluginDlg::~CPluginDlg()
{
}

void CPluginDlg::DoDataExchange(CDataExchange* pDX)
{
	CNormalDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_BUTTON1, m_configButton);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(CPluginDlg, CNormalDlg)
	ON_WM_CLOSE()
	ON_LBN_SELCHANGE(IDC_LIST1, &CPluginDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CPluginDlg::OnBnClickedButton1)
END_MESSAGE_MAP()
#pragma endregion

// CPluginDlg 消息处理程序

// 初始化
BOOL CPluginDlg::OnInitDialog()
{
	CNormalDlg::OnInitDialog();

	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);			// 设置大图标
	SetIcon(hIcon, FALSE);			// 设置小图标

	m_resize.AddControl(&m_list, RT_NULL, NULL, RT_NULL, NULL, RT_NULL, NULL, RT_KEEP_DIST_TO_BOTTOM, this);
	m_resize.AddControl(&m_configButton, RT_NULL, NULL, RT_KEEP_DIST_TO_BOTTOM, &m_list);
	m_resize.AddControl(&m_edit, RT_NULL, NULL, RT_NULL, NULL, RT_KEEP_DIST_TO_RIGHT, this, RT_KEEP_DIST_TO_BOTTOM, this);

	// 显示插件
	for (const auto& i : m_plugins)
		m_list.AddString(i->m_name);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

#pragma region UI
// 窗口 /////////////////////////////////////////////////////////////////////////////////

// 取消
void CPluginDlg::OnCancel()
{
	DestroyWindow();
}

// 关闭窗口
void CPluginDlg::OnClose()
{
	DestroyWindow();
}

// 释放this
void CPluginDlg::PostNcDestroy()
{
	CNormalDlg::PostNcDestroy();

	m_pThis = NULL;
	delete this;
}
#pragma endregion

// 选中
void CPluginDlg::OnLbnSelchangeList1()
{
	int index = m_list.GetCurSel();
	if (index == LB_ERR)
		return;
	m_edit.SetWindowText(m_plugins[index]->GetDescription());
}

// 设置
void CPluginDlg::OnBnClickedButton1()
{
	int index = m_list.GetCurSel();
	if (index == LB_ERR)
		return;
	m_plugins[m_list.GetCurSel()]->OnConfig();
}
