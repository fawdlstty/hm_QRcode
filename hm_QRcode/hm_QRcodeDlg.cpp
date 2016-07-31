
// hm_QRcodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "hm_QRcode.h"
#include "hm_QRcodeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Chm_QRcodeDlg 对话框



Chm_QRcodeDlg::Chm_QRcodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Chm_QRcodeDlg::IDD, pParent)
	, m_path_src (_T ("")), m_path_bg (_T ("")), m_path_dest (_T ("")), m_pixel_width (_T ("")), m_animate_speed (_T ("")), m_tailor (FALSE), m_status (_T ("")) {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Chm_QRcodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange (pDX);
	DDX_Text (pDX, IDC_EDIT1, m_path_src);
	DDX_Text (pDX, IDC_EDIT2, m_path_bg);
	DDX_Text (pDX, IDC_EDIT3, m_path_dest);
	DDX_Text (pDX, IDC_EDIT4, m_pixel_width);
	DDX_Text (pDX, IDC_EDIT5, m_animate_speed);
	DDX_Check (pDX, IDC_CHECK1, m_tailor);
	DDX_Text (pDX, IDC_STATUS, m_status);
}

BEGIN_MESSAGE_MAP(Chm_QRcodeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED (IDC_BUTTON1, &Chm_QRcodeDlg::OnBnClickedButton1)
	ON_BN_CLICKED (IDC_BUTTON2, &Chm_QRcodeDlg::OnBnClickedButton2)
	ON_BN_CLICKED (IDC_BUTTON3, &Chm_QRcodeDlg::OnBnClickedButton3)
	ON_BN_CLICKED (IDC_BUTTON4, &Chm_QRcodeDlg::OnBnClickedButton4)
END_MESSAGE_MAP ()


// Chm_QRcodeDlg 消息处理程序

BOOL Chm_QRcodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_pixel_width = _T ("5");
	m_animate_speed = _T ("0");
	m_tailor = TRUE;
	m_status = _T ("就绪。");
	UpdateData (FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Chm_QRcodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Chm_QRcodeDlg::OnPaint()
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
HCURSOR Chm_QRcodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



CString fdsel = _T ("图片文件 (*.gif;*.png;*.jpg;*.bmp)|*.gif;*.png;*.jpg;*.bmp\0所有文件 (*.*)|*.*\0\0");

void Chm_QRcodeDlg::OnBnClickedButton1 () {
	CFileDialog fd (TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, fdsel, this);
	if (IDOK == fd.DoModal ()) {
		UpdateData (TRUE);
		m_path_src = fd.GetPathName ();
		UpdateData (FALSE);
	}
}


void Chm_QRcodeDlg::OnBnClickedButton2 () {
	CFileDialog fd (TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, fdsel, this);
	if (IDOK == fd.DoModal ()) {
		UpdateData (TRUE);
		m_path_bg = fd.GetPathName ();
		UpdateData (FALSE);
	}
}


void Chm_QRcodeDlg::OnBnClickedButton3 () {
	CFileDialog fd (FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, fdsel, this);
	if (IDOK == fd.DoModal ()) {
		UpdateData (TRUE);
		m_path_dest = fd.GetPathName ();
		UpdateData (FALSE);
	}
}


INT GetEncoderClsid (CString format, CLSID *pClsid) {
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo *pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize (&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*) (malloc (size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders (num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j) {
		if (wcscmp (pImageCodecInfo [j].MimeType, format) == 0) {
			*pClsid = pImageCodecInfo [j].Clsid;
			free (pImageCodecInfo);
			return j;  // Success
		}
	}

	free (pImageCodecInfo);
	return -1;  // Failure
}


void Chm_QRcodeDlg::OnBnClickedButton4 () {
	//检查文件是否存在
	auto check_file_exist = [] (CString path) {
		HANDLE hFile = ::CreateFile (path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == hFile) return FALSE;
		CloseHandle (hFile);
		return TRUE;
	};
	//更新状态信息
	auto update_status = [this] (CString s) { this->m_status = s; UpdateData (FALSE); };
	UpdateData (TRUE);

	//
	// 检查数据有效性
	//
	if (!check_file_exist (m_path_src)) { update_status (_T ("生成失败：二维码图片不存在。")); return; }
	if (!check_file_exist (m_path_bg)) { update_status (_T ("生成失败：背景图片不存在。")); return; }
	//if (check_file_exist (m_path_dest)) {
	//	if (IDYES != AfxMessageBox (_T ("目标文件已存在，是否覆盖？"), MB_ICONQUESTION | MB_YESNO)) {
	//		update_status (_T ("生成失败：目标文件存在，用户已取消。")); return;
	//	}
	//}
	int pixel_width = _wtoi (m_pixel_width);
	if (!(pixel_width % 2)) { update_status (_T ("生成失败：二维码宽度必须为奇数。")); return; }
	if (pixel_width < 3 || pixel_width > 15) { update_status (_T ("生成失败：二维码宽度范围错误。")); return; }
	if (pixel_width > 9) {
		if (IDYES != AfxMessageBox (_T ("二维码像素太宽，可能导致二维码无法识别，是否继续？"), MB_ICONQUESTION | MB_YESNO)) {
			update_status (_T ("生成失败：二维码像素太宽，用户已取消。")); return;
		}
	}
	int animate_speed = _wtoi (m_animate_speed);
	if (animate_speed < 0) { update_status (_T ("生成失败：动图帧间隔必须为正整数。")); return; }

	Bitmap img_src (m_path_src), img_bg (m_path_bg);
	int src_width = img_src.GetWidth (), src_height = img_src.GetHeight ();
	if (src_width < 1 || src_height < 1) { update_status (_T ("生成失败：二维码图片格式错误。")); return; }
	int bg_width = img_bg.GetWidth (), bg_height = img_bg.GetHeight ();
	if (bg_width < 1 || bg_height < 1) { update_status (_T ("生成失败：背景图片格式错误。")); return; }

	//
	// 获取源二维码大小
	//
	int i, j, k, l, m;
	Gdiplus::Color c;
#define GET_PIXEL(x,y) img_src.GetPixel(x,y,&c)
#define IF_BLACK if(c.GetR()<128)
#define IF_WRITE if(c.GetR()>127)
	for (i = j = k = l = 0; i < src_width; ++i) {
		//i代表循环变量
		//j代表当前寻找到的第几个步骤，以及实现累加
		//k代表当前循环到第几个大小
		//l代表每个像素块大概的大小
		//m代表数二维码宽度时，y的值（两次数宽度均为y）
		switch ((BYTE) (j)) {
		case 0://在左上边距中，查找到左上角定位块
			GET_PIXEL (i, i);
			IF_BLACK ++j;
			break;
		case 1://在左上(0, 0)黑中，计算每个块的大概大小
			GET_PIXEL (i, i);
			IF_WRITE ++j; else ++k;
			break;
		case 2://在左上(1, 1)白中，准备开始垂直循环，这个case只执行一次
			l = k;
			m = i + l / 2;
			++j;
			break;
		case 3://在左上(1, 1)~(5, 1)白中，查找水平方向第一个黑色块，也就是左上角定位块的最下方的黑色块
			GET_PIXEL (i, m);
			IF_BLACK ++j;
			break;
		case 4://这时候不用再扫描一遍了，直接将坐标从(6, 1)定位到(6, 6), 这个case只执行一次
			m = i;
			k = 0;
			j += 3;
			break;
		default://开始顺序遍历，如果遇到不同色泽的那么j+1
			//j为奇数代表当前色块为黑色，如果为偶数代表当前色块为白色
			GET_PIXEL (i, m);
			if (c.GetR () < 128/*black*/ == j % 2) {//当前颜色相同
				if (++k > l * 2) k = -1;//连续颜色超过一个像素块，所以跳出循环体
			} else {//当前颜色不同
				k = 0;
				++j;
			}
			break;
		}
		if (k == -1) break;//正确跳出循环
	}
#undef IF_WRITE
#undef IF_BLACK
#undef GET_PIXEL
	//未正确跳出
	if (k != -1) { update_status (_T ("二维码未正确解析。")); return; }

	int code_size = j + 6, src_pixel_size = code_size * pixel_width;
	auto get_pixel = [&img_src, src_width, code_size] (int x, int y, Gdiplus::Color *c) { img_src.GetPixel ((src_width * x / (code_size + 2)) + 10, (src_width * y / (code_size + 2)) + 10, c); };

	//
	// 计算各种绘图大小
	//
	Rect r_dest (0, 0, src_pixel_size, src_pixel_size);
	Rect r_bg (0, 0, bg_width, bg_height);
	Rect r_code (0, 0, src_pixel_size, src_pixel_size);
	if (!m_tailor) {
		//r_dest
		if (bg_width >= bg_height) r_dest.Width = src_pixel_size * bg_width / bg_height;
		else r_dest.Height = src_pixel_size * bg_height / bg_width;
	} else {
		//r_bg
		if (bg_width >= bg_height) {
			r_bg.X = (bg_width - bg_height) / 2;
			r_bg.Width = bg_height;
		} else {
			r_bg.Y = (bg_height - bg_width) / 2;
			r_bg.Height = bg_width;
		}
	}

	//
	// 生成二维码图片
	//
	Bitmap img_code (src_pixel_size, src_pixel_size, PixelFormat32bppARGB);
	//设置一个像素块中单个二维码像素
	auto set_single = [&img_code, src_pixel_size] (int x, int y, Gdiplus::Color *c) {
		img_code.SetPixel (x * src_pixel_size + src_pixel_size / 2, y * src_pixel_size + src_pixel_size / 2, *c);
	};
	//设置一个像素块中所有二维码像素
	auto set_multi = [&img_code, src_pixel_size] (int x, int y, Gdiplus::Color *c) {
		for (int i = 0; i < src_pixel_size; ++i) {
			for (int j = 0; j < src_pixel_size; ++j) {
				img_code.SetPixel (x * src_pixel_size + i, y * src_pixel_size + j, *c);
			}
		}
	};

	//迭代设置二维码像素
	for (i = 0; i < code_size; ++i) {
		for (j = 0; j < code_size; ++j) {
			get_pixel (j, i, &c);
			if (c.GetR () < 128 || c.GetG () < 128 || c.GetB () < 128) {
				c.SetValue (Gdiplus::Color::MakeARGB (255, 0, 0, 0));
			} else {
				c.SetValue (Gdiplus::Color::MakeARGB (255, 255, 255, 255));
			}
			k = code_size - i - 1;
			l = code_size - j - 1;
			if (i == 6 || j == 6                             //第六行或第六列
				|| (i < 8 && j < 8)                          //左上角定位块
				|| (k < 8 && j < 8)                          //右上角定位块
				|| (i < 8 && l < 8)                          //左下角定位块
				|| (k >= 4 && k <= 8 && l >= 4 && l <= 8)) { //右下角定位块
				set_multi (j, i, &c);
			} else {
				set_single (j, i, &c);
			}
		}
	}

	//
	// 生成目标图片
	//
	Bitmap img_dest (r_dest.Width, r_dest.Height, PixelFormat32bppARGB);
	Graphics g (&img_dest);

	//获取帧数
	int count = img_bg.GetFrameDimensionsCount ();
	GUID *pDimensionIDs = new GUID [count];
	img_bg.GetFrameDimensionsList (pDimensionIDs, count);
	wchar_t strGuid [40];
	StringFromGUID2 (pDimensionIDs [0], strGuid, 40);
	count = img_bg.GetFrameCount (&pDimensionIDs [0]);
	delete []pDimensionIDs;

	CString file_ext = m_path_dest.Right (m_path_dest.GetLength () - m_path_dest.ReverseFind (_T ('.')) - 1).MakeLower (), tmp;
	if (count > 1) {
		//多帧图片
		if (file_ext.Compare (_T ("gif"))) {
			tmp = m_path_dest.Left (m_path_dest.ReverseFind (_T ('.')));
			m_path_dest.Format (_T ("%s.gif"), tmp);
		}

		CGifEncoder ge;
		ge.SetFrameSize (src_pixel_size, src_pixel_size);
		//ge.SetDelayTime (animate_speed ? animate_speed : img_bg.getfra);
		ge.StartEncoder (m_path_dest);

		PropertyItem* pItem;
		if (animate_speed) {
			ge.SetDelayTime (animate_speed);
			pItem = NULL;
		} else {
			UINT TotalBuffer = img_bg.GetPropertyItemSize (PropertyTagFrameDelay);
			pItem = (PropertyItem*) malloc (TotalBuffer);
			img_bg.GetPropertyItem (PropertyTagFrameDelay, TotalBuffer, pItem);
		}

		GUID guid = Gdiplus::FrameDimensionTime;
		for (i = 0; i < count; ++i) {
			img_bg.SelectActiveFrame (&guid, i);
			g.DrawImage (&img_bg, r_dest, r_bg.X, r_bg.Y, r_bg.Width, r_bg.Height, Unit::UnitPixel);
			g.DrawImage (&img_code, r_dest, r_code.X, r_code.Y, r_code.Width, r_code.Height, Unit::UnitPixel);
			ge.AddFrame (&img_dest);
		}
		ge.FinishEncoder (pItem);

		if (pItem) delete pItem;
	} else {
		//单帧图片
		g.DrawImage (&img_bg, r_dest, r_bg.X, r_bg.Y, r_bg.Width, r_bg.Height, Unit::UnitPixel);
		g.DrawImage (&img_code, r_dest, r_code.X, r_code.Y, r_code.Width, r_code.Height, Unit::UnitPixel);

		if (!file_ext.Compare (_T ("jpg"))) file_ext = _T ("jpeg");
		tmp.Format (_T ("image/%s"), file_ext);

		CLSID clsid;
		GetEncoderClsid (tmp, &clsid);
		img_code.Save (m_path_dest, &clsid);
	}

	update_status (_T ("完成。"));
}
