#include "stdafx.h"
#include "resource.h"
#include "IgnoreBeforeDlg.h"
#include "IgnoreBefore.h"


// CLockThreadDlg �Ի���

IMPLEMENT_DYNAMIC(CIgnoreBeforeDlg, CModelessDlg)

CIgnoreBeforeDlg::CIgnoreBeforeDlg(CIgnoreBeforeDlg*& pThis, CWnd* pParent /*=NULL*/) : CModelessDlg(CIgnoreBeforeDlg::IDD, (CModelessDlg**)&pThis, pParent)
{

}

#pragma region MFC
CIgnoreBeforeDlg::~CIgnoreBeforeDlg()
{
}

void CIgnoreBeforeDlg::DoDataExchange(CDataExchange* pDX)
{
	CModelessDlg::DoDataExchange(pDX); 
	DDX_Control(pDX, IDC_EDIT1, m_tidEdit);
	DDX_Control(pDX, IDC_EDIT2, m_pageEdit);
	DDX_Control(pDX, IDC_EDIT7, m_floorEdit);
	DDX_Control(pDX, IDC_BUTTON1, m_startButton);
	DDX_Control(pDX, IDC_BUTTON2, m_stopButton);
}


BEGIN_MESSAGE_MAP(CIgnoreBeforeDlg, CModelessDlg)
	ON_BN_CLICKED(IDC_BUTTON1, &CIgnoreBeforeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CIgnoreBeforeDlg::OnBnClickedButton2)
END_MESSAGE_MAP()
#pragma endregion

// CLockThreadDlg ��Ϣ�������

// ��ʼ��
BOOL CIgnoreBeforeDlg::OnInitDialog()
{
	CModelessDlg::OnInitDialog();

	if (!g_ignoreBefore.m_stopFlag)
	{
		m_tidEdit.EnableWindow(FALSE);
		m_pageEdit.EnableWindow(FALSE);
		m_floorEdit.EnableWindow(FALSE);
		m_startButton.EnableWindow(FALSE);
		m_stopButton.EnableWindow(TRUE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

// ��ʼ
void CIgnoreBeforeDlg::OnBnClickedButton1()
{
	m_tidEdit.EnableWindow(FALSE);
	m_pageEdit.EnableWindow(FALSE);
	m_floorEdit.EnableWindow(FALSE);
	m_startButton.EnableWindow(FALSE);
	m_stopButton.EnableWindow(TRUE);

	g_ignoreBefore.StartIgnoreBefore();
}

// ֹͣ
void CIgnoreBeforeDlg::OnBnClickedButton2()
{
	g_ignoreBefore.StopIgnoreBefore();
}
