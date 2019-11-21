// CStarRTCMenuDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "starrtcdemo.h"
#include "CStarRTCMenuDialog.h"
#include "afxdialogex.h"
#include "starrtcdemoDlg.h"
#include "CMultipleMeetingDialog.h"
#include "CSettingDialog.h"
#include "CInteracteLiveDlg.h"
#include "CIMDialog.h"
#include "CVoipDlg.h"
#include "CVoipP2PDlg.h"
#include "CAudioChatroomDlg.h"
#include <windows.h>
#include "CLogin.h"
#include "CInterfaceUrls.h"
#include "CMinClassListDlg.h"
#include "CSuperAudioChatroomDlg.h"
// CStarRTCMenuDialog 对话框

IMPLEMENT_DYNAMIC(CStarRTCMenuDialog, CDialogEx)

CStarRTCMenuDialog::CStarRTCMenuDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MENU, pParent)
{
	m_pUserManager = new CUserManager();
	m_pConfig = new CConfigManager();
	m_pLogin = NULL;
}

CStarRTCMenuDialog::~CStarRTCMenuDialog()
{
	m_bLogIn = false;

	if (m_pConfig != NULL)
	{
		delete m_pConfig;
		m_pConfig = NULL;
	}

	if (m_pUserManager != NULL)
	{
		delete m_pUserManager;
		m_pUserManager = NULL;
	}

	if (m_pLogin != NULL)
	{
		delete m_pLogin;
		m_pLogin = NULL;
	}
}

void CStarRTCMenuDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_USERID, m_UserIDEdit);
	DDX_Control(pDX, IDC_STATIC_USER_PIC, m_UserPicPicControl);
}


BEGIN_MESSAGE_MAP(CStarRTCMenuDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_IM, &CStarRTCMenuDialog::OnBnClickedButtonIm)
	ON_BN_CLICKED(IDC_BUTTON_MULTIPLE_MEETING, &CStarRTCMenuDialog::OnBnClickedButtonMultipleMeeting)
	ON_BN_CLICKED(IDC_BUTTON_INTERACTE_LIVE, &CStarRTCMenuDialog::OnBnClickedButtonInteracteLive)
	//ON_BN_CLICKED(IDC_BUTTON_PARAM_SETTING, &CStarRTCMenuDialog::OnBnClickedButtonParamSetting)
	ON_BN_CLICKED(IDC_BUTTON_LIVE_MONITOR, &CStarRTCMenuDialog::OnBnClickedButtonLiveMonitor)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CStarRTCMenuDialog::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_VOIP, &CStarRTCMenuDialog::OnBnClickedButtonVoip)
	ON_BN_CLICKED(IDC_BUTTON_VOICE_CHATROOM, &CStarRTCMenuDialog::OnBnClickedButtonVoiceChatroom)
	ON_BN_CLICKED(IDC_BUTTON_VOIP_P2P, &CStarRTCMenuDialog::OnBnClickedButtonVoipP2p)
	ON_BN_CLICKED(IDC_BUTTON_MIN_CLASS, &CStarRTCMenuDialog::OnBnClickedButtonMinClass)
	ON_BN_CLICKED(IDC_BUTTON_SUPER_CHATROOM, &CStarRTCMenuDialog::OnBnClickedButtonSuperChatroom)
END_MESSAGE_MAP()


// CStarRTCMenuDialog 消息处理程序


void CStarRTCMenuDialog::OnBnClickedButtonIm()
{
	CIMDialog dlg(m_pUserManager, m_pConfig);
	dlg.DoModal();
}


void CStarRTCMenuDialog::OnBnClickedButtonMultipleMeeting()
{
	CMultipleMeetingDialog dlg(m_pUserManager, this);
	dlg.setConfig(m_pConfig);
	dlg.DoModal();
}


void CStarRTCMenuDialog::OnBnClickedButtonInteracteLive()
{
	CInteracteLiveDlg dlg(m_pUserManager, this);
	dlg.setConfig(m_pConfig);
	dlg.DoModal();
}

/**
 * msgServer处于在线状态
 */
int CStarRTCMenuDialog::online(int maxContentLen)
{
	return 0;
}

/**
 * msgServer中断状态
 */
int CStarRTCMenuDialog::offline()
{
	return 0;
}

/*void CStarRTCMenuDialog::OnBnClickedButtonParamSetting()
{
	CSettingDialog dlg(m_pUserManager);
	dlg.DoModal();
}
*/

BOOL CStarRTCMenuDialog::OnInitDialog()
{
	m_pConfig->readConfig();
	if (m_pLogin == NULL)
	{
		m_pLogin = new CLogin(m_pUserManager, this);
	}
	//CLogin login(m_pUserManager, this);
	m_bLogIn = false;
	CInterfaceUrls::setBaseUrl(m_pUserManager->m_ServiceParam.m_strRequestListAddr);
	CDialogEx::OnInitDialog();
	
	if (m_pUserManager != NULL)
	{
		m_UserIDEdit.SetWindowText(m_pUserManager->m_ServiceParam.m_strUserId.c_str());
		bool bSuccess = m_pLogin->logIn();
		if (bSuccess)
		{
			
			m_bLogIn = true;
			m_UserIDEdit.SetWindowText(m_pUserManager->m_ServiceParam.m_strUserId.c_str());
		}
		else
		{
			m_bLogIn = false;
			AfxMessageBox("登录失败，请检查配置信息");
			OnOK();
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}




void CStarRTCMenuDialog::OnBnClickedButtonLiveMonitor()
{
	CstartrtcdemoDlg dlg(m_pUserManager);
	dlg.setConfig(m_pConfig);
	dlg.DoModal();
}


void CStarRTCMenuDialog::OnBnClickedButtonLogin()
{
	if (m_pUserManager != NULL)
	{
		m_UserIDEdit.SetWindowText(m_pUserManager->m_ServiceParam.m_strUserId.c_str());
		if (m_pLogin == NULL)
		{
			m_pLogin = new CLogin(m_pUserManager, this);
		}
		bool bSuccess = m_pLogin->logIn();
		if (bSuccess)
		{
			m_bLogIn = true;
			m_UserIDEdit.SetWindowText(m_pUserManager->m_ServiceParam.m_strUserId.c_str());
		}
		else
		{
			m_bLogIn = false;
			AfxMessageBox("user login failed");
		}
	}
}

void CStarRTCMenuDialog::OnBnClickedButtonVoip()
{
	CVoipDlg dlg(m_pUserManager);
	dlg.DoModal();
}


void CStarRTCMenuDialog::OnBnClickedButtonVoiceChatroom()
{
	CAudioChatroomDlg dlg(m_pUserManager);
	dlg.setConfig(m_pConfig);
	dlg.DoModal();
}


void CStarRTCMenuDialog::OnBnClickedButtonVoipP2p()
{
	CVoipP2PDlg dlg(m_pUserManager);
	dlg.DoModal();
}


void CStarRTCMenuDialog::OnBnClickedButtonMinClass()
{
	CMinClassListDlg dlg(m_pUserManager);
	dlg.setConfig(m_pConfig);
	dlg.DoModal();
}


void CStarRTCMenuDialog::OnBnClickedButtonSuperChatroom()
{
	CSuperAudioChatroomDlg dlg(m_pUserManager);
	dlg.setConfig(m_pConfig);
	dlg.DoModal();
}
