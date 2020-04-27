
// IPCAppDlg.h: 헤더 파일
//

#pragma once

#include "CLayerManager.h"	// Added by ClassView
#include "CChatAppLayer.h"	// Added by ClassView
#include "CEthernetLayer.h"	// Added by ClassView
#include "CFileLayer.h"	// Added by ClassView


// CIPCAppDlg 대화 상자
class CIPCAppDlg : public CDialogEx, public CBaseLayer
{
// 생성입니다.
public:
	CIPCAppDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IPCAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListChat;
	CString m_stMessage;
	UINT m_unSrcAddr;
	UINT m_unDstAddr;
	afx_msg void OnSendMessage();
	afx_msg void OnButtonAddrSet();
	afx_msg void OnCheckBroadcast();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	BOOL			Receive(unsigned char* ppayload);
	inline void		SendData();
	virtual ~CIPCAppDlg();
protected:
	afx_msg LRESULT OnRegSendMsg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRegAckMsg(WPARAM wParam, LPARAM lParam);
private:
	CLayerManager	m_LayerMgr;
	CChatAppLayer* m_ChatApp;
	int				m_nAckReady;
	BOOL			m_bSendReady;
	enum {
		IPC_INITIALIZING,
		IPC_READYTOSEND,
		IPC_WAITFORACK,
		IPC_ERROR,
		IPC_BROADCASTMODE,
		IPC_UNICASTMODE,
		IPC_ADDR_SET,
		IPC_ADDR_RESET
	};

	void			SetDlgState(int state);
	inline void		EndofProcess();
	inline void		SetRegstryMessage();
public:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};
