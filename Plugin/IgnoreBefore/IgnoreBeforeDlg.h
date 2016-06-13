#pragma once
#include <ModelessDlg.h>
#include "afxwin.h"


// CLockThreadDlg 对话框

class CIgnoreBeforeDlg : public CModelessDlg
{
	DECLARE_DYNAMIC(CIgnoreBeforeDlg)

public:
	CIgnoreBeforeDlg(CIgnoreBeforeDlg*& pThis, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIgnoreBeforeDlg();

	// 对话框数据
	enum { IDD = IDD_BEFORE_THREAD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();


public:
	CEdit m_tidEdit;
	CEdit m_pageEdit;
	CEdit m_floorEdit;
	CButton m_startButton;
	CButton m_stopButton;
};