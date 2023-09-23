
// MFC_INFODlg.h: 头文件
//

#pragma once
#include "ChangeInfo.h"

// CMfc_Info 对话框
class CMfc_Info : public CDialogEx
{
// 构造
public:
	CMfc_Info(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_INFO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_list;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();

	ChangeInfo Cinfo;
	CString InfoIni;
	void LoadIni();
	int Lstsel;
	void SaveLstToIni();
	void SaveIni(CString& _Study_Num, CString& _Name, CString& _Sex, CString& _Number, CString& _OtherInfo,int index);
	void AddIni(CString& _Study_Num, CString& _Name, CString& _Sex, CString& _Number, CString& _OtherInfo);




};
