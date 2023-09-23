#pragma once
#include "afxdialogex.h"


// ChangeInfo 对话框

class ChangeInfo : public CDialogEx
{
	DECLARE_DYNAMIC(ChangeInfo)

public:
	ChangeInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ChangeInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHANGE_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CEdit m_StudyNum;
	CEdit m_Name;
	CComboBox m_Sex;
	CEdit m_Number;
	CEdit m_OtherInfo;
	//控件和变量
	CString Study_Num;
	CString Name;
	CString Sex;
	CString Number;
	CString OtherInfo;

	void* father;
	int index;
	bool iscreate;
	void Init(void* _father,bool _iscreate=0, int _index = 0);
	void SetData(CString& _Study_Num, CString& _Name, CString& _Sex, CString& _Number, CString& _OtherInfo);
	
	
};
