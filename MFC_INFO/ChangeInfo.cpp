// ChangeInfo.cpp: 实现文件
//

#include "pch.h"
#include "MFC_INFO.h"
#include "afxdialogex.h"
#include "ChangeInfo.h"
#include "MFC_INFODlg.h"

// ChangeInfo 对话框

IMPLEMENT_DYNAMIC(ChangeInfo, CDialogEx)

ChangeInfo::ChangeInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHANGE_INFO, pParent)
	, Study_Num(_T(""))
	, Name(_T(""))
	, Sex(_T(""))
	, Number(_T(""))
	, OtherInfo(_T(""))
{

}

ChangeInfo::~ChangeInfo()
{
}

void ChangeInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT1, m_StudyNum);
	DDX_Control(pDX, IDC_EDIT2, m_Name);
	DDX_Control(pDX, IDC_COMBO1, m_Sex);
	DDX_Control(pDX, IDC_EDIT3, m_Number);
	DDX_Control(pDX, IDC_EDIT4, m_OtherInfo);

	DDX_Text(pDX, IDC_EDIT1, Study_Num);
	DDX_Text(pDX, IDC_EDIT2, Name);
	DDX_CBString(pDX, IDC_COMBO1, Sex);
	DDX_Text(pDX, IDC_EDIT3, Number);
	DDX_Text(pDX, IDC_EDIT4, OtherInfo);
}


BEGIN_MESSAGE_MAP(ChangeInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ChangeInfo::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ChangeInfo::OnBnClickedButton2)
	
	
END_MESSAGE_MAP()


// ChangeInfo 消息处理程序


void ChangeInfo::OnBnClickedButton1()//取消
{
	Study_Num = L"";
	Name = L"";
	Sex = L"";
	Number = L"";
	OtherInfo = L"";

	EndDialog(IDOK);
}


void ChangeInfo::OnBnClickedButton2()//确定
{
	CMfc_Info* p = (CMfc_Info*)father;
	UpdateData(TRUE);
	if (iscreate)
		p->AddIni(Study_Num, Name, Sex, Number, OtherInfo);
	else p->SaveIni(Study_Num, Name, Sex, Number, OtherInfo,index);

	//p->SaveLstToIni();
	
	Study_Num = L"";
	Name = L"";
	Sex = L"";
	Number = L"";
	OtherInfo = L"";
	CDialog::OnCancel();



}

void ChangeInfo::Init(void* _father, bool _iscreate,int _index) //明确是增加还是修改，通过读取lstel来实现
{
	iscreate = _iscreate;
	father = _father;
	index = _index;
}

void ChangeInfo::SetData(CString& _Study_Num, CString& _Name, CString& _Sex, CString& _Number, CString& _OtherInfo)
{
	Study_Num = _Study_Num;
	Name = _Name;
	Sex = _Sex;
	Number = _Number;
	OtherInfo = _OtherInfo;
}


