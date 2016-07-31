
// hm_QRcodeDlg.h : 头文件
//

#pragma once


// Chm_QRcodeDlg 对话框
class Chm_QRcodeDlg : public CDialogEx
{
// 构造
public:
	Chm_QRcodeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HM_QRCODE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_path_src;
	CString m_path_bg;
	CString m_path_dest;
	CString m_pixel_width;
	CString m_animate_speed;
	BOOL m_tailor;
	CString m_status;
	afx_msg void OnBnClickedButton1 ();
	afx_msg void OnBnClickedButton2 ();
	afx_msg void OnBnClickedButton3 ();
	afx_msg void OnBnClickedButton4 ();
};
