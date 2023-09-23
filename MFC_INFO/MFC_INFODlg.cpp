
// MFC_INFODlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC_INFO.h"
#include "MFC_INFODlg.h"
#include "afxdialogex.h"
#include "ChangeInfo.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMfc_Info 对话框



CMfc_Info::CMfc_Info(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_INFO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfc_Info::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CMfc_Info, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMfc_Info::OnBnClickedButton1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMfc_Info::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMfc_Info::OnBnClickedButton3)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CMfc_Info::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON5, &CMfc_Info::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CMfc_Info::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMfc_Info 消息处理程序

BOOL CMfc_Info::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	DWORD  style = m_list.GetExtendedStyle();
	style |= LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE;
	m_list.SetExtendedStyle(style);
	m_list.InsertColumn(0, _T("学号"), LVCFMT_CENTER, 150);
	m_list.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(2, _T("性别"), LVCFMT_CENTER, 50);
	m_list.InsertColumn(3, _T("联系方式"), LVCFMT_CENTER, 150);
	m_list.InsertColumn(4, _T("备注"), LVCFMT_CENTER, 200);
	InfoIni.Format(L"F:\\info.ini");
	LoadIni();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMfc_Info::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMfc_Info::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);

}



void CMfc_Info::OnBnClickedButton1()
{
	Cinfo.Init(this, 1, Lstsel);
	Cinfo.DoModal();
	
}


void CMfc_Info::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;


}


void CMfc_Info::OnBnClickedButton3()//删除
{

	m_list.DeleteItem(Lstsel);
	CString key;
	key.Format(L"count_%d", Lstsel);
	WritePrivateProfileStringW(key, NULL, NULL, InfoIni);
	SaveLstToIni();

}


void CMfc_Info::LoadIni()//加载文件数据
{
	int count = GetPrivateProfileIntW(L"main", L"count", 0, InfoIni);

	for (int i = 0; i < count; i++)
	{
		CString Study_Num, Name, Sex, Number, OtherInfo, _AppName;
		_AppName.Format(L"count_%d", i);
		wchar_t wRead[0xff];//重点 

		GetPrivateProfileStringW(_AppName, L"Study_Num", L"", wRead, 0xff, InfoIni);
		Study_Num.Format(L"%s", wRead);
		GetPrivateProfileStringW(_AppName, L"Name", L"", wRead, 0xff, InfoIni);
		Name.Format(L"%s", wRead);
		GetPrivateProfileStringW(_AppName, L"Sex", L"", wRead, 0xff, InfoIni);
		Sex.Format(L"%s", wRead);
		GetPrivateProfileStringW(_AppName, L"Number", L"", wRead, 0xff, InfoIni);
		Number.Format(L"%s", wRead);
		GetPrivateProfileStringW(_AppName, L"OtherInfo", L"", wRead, 0xff, InfoIni);
		OtherInfo.Format(L"%s", wRead);

		m_list.InsertItem(i, Study_Num);
		m_list.SetItemText(i, 1, Name);
		m_list.SetItemText(i, 2, Sex);
		m_list.SetItemText(i, 3, Number);
		m_list.SetItemText(i, 4, OtherInfo);
	}

}

void CMfc_Info::SaveLstToIni()
{
	int count = m_list.GetItemCount();
	for (int i = 0; i < count; i++)
	{
		CString Study_Num = m_list.GetItemText(i, 0);
		CString Name = m_list.GetItemText(i, 1);
		CString Sex = m_list.GetItemText(i, 2);
		CString Number = m_list.GetItemText(i, 3);
		CString OtherInfo = m_list.GetItemText(i, 4);

		CString key;
		key.Format(L"count_%d", i);
		WritePrivateProfileStringW(key, L"Study_Num", Study_Num, InfoIni);
		WritePrivateProfileStringW(key, L"Name", Name, InfoIni);
		WritePrivateProfileStringW(key, L"Sex", Sex, InfoIni);
		WritePrivateProfileStringW(key, L"Number", Number, InfoIni);
		WritePrivateProfileStringW(key, L"OtherInfo", OtherInfo, InfoIni);

	}
	CString wCount;
	wCount.Format(L"%d", count);
	WritePrivateProfileStringW(L"main", L"count", wCount, InfoIni);

}

void CMfc_Info::SaveIni(CString& _Study_Num, CString& _Name, CString& _Sex, CString& _Number, CString& _OtherInfo,int index)
{
	
	CString key;
	key.Format(L"count_%d", index);

	WritePrivateProfileStringW(key, L"Study_Num", _Study_Num, InfoIni);
	WritePrivateProfileStringW(key, L"Name", _Name, InfoIni);
	WritePrivateProfileStringW(key, L"Sex", _Sex, InfoIni);
	WritePrivateProfileStringW(key, L"Number", _Number, InfoIni);
	WritePrivateProfileStringW(key, L"OtherInfo", _OtherInfo, InfoIni);

	m_list.SetItemText(index, 0,_Study_Num);
	m_list.SetItemText(index, 1, _Name);
	m_list.SetItemText(index, 2, _Sex);
	m_list.SetItemText(index, 3, _Number);
	m_list.SetItemText(index, 4, _OtherInfo);
}

void CMfc_Info::AddIni(CString& _Study_Num, CString& _Name, CString& _Sex, CString& _Number, CString& _OtherInfo)
{

	int count = GetPrivateProfileIntW(L"main", L"count", 0, InfoIni);
	CString key;
	key.Format(L"count_%d", count);
	WritePrivateProfileStringW(key, L"Study_Num", _Study_Num, InfoIni);
	WritePrivateProfileStringW(key, L"Name", _Name, InfoIni);
	WritePrivateProfileStringW(key, L"Sex", _Sex, InfoIni);
	WritePrivateProfileStringW(key, L"Number", _Number, InfoIni);
	WritePrivateProfileStringW(key, L"OtherInfo", _OtherInfo, InfoIni);
	count++;
	CString wCount;
	wCount.Format(L"%d", count);
	WritePrivateProfileStringW(L"main", L"count", wCount, InfoIni);
	int icount = m_list.GetItemCount();
	m_list.InsertItem(icount, _Study_Num);
	m_list.SetItemText(icount, 1, _Name);
	m_list.SetItemText(icount, 2, _Sex);
	m_list.SetItemText(icount, 3, _Number);
	m_list.SetItemText(icount, 4, _OtherInfo);

}
 


void CMfc_Info::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)//左键单击事件获取选择的是第几行
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST1);
	int index = pNMItemActivate->iItem;
	if (index != -1)
	{
		Lstsel = pNMItemActivate->iItem;
	}

}

//退出
void CMfc_Info::OnBnClickedButton5()
{
	
	int result = AfxMessageBox(_T("确定要退出吗？"), MB_ICONQUESTION | MB_YESNO);
	if (result == IDYES)
	{
		exit(1);
	}

}

 
void CMfc_Info::OnBnClickedButton4()//修改信息
{
	CString SN = m_list.GetItemText(Lstsel, 0);
	CString NM = m_list.GetItemText(Lstsel, 1);
	CString SEX = m_list.GetItemText(Lstsel, 2);
	CString NUM = m_list.GetItemText(Lstsel, 3);
	CString OTHER = m_list.GetItemText(Lstsel, 4);
	Cinfo.Init(this,0,Lstsel);
	Cinfo.SetData(SN, NM, SEX, NUM, OTHER);
	Cinfo.DoModal();
}
