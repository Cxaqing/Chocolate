
// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
//#include "graphics.h"//c++ͼ�ν����
//#include "time.h"
#include "mmsystem.h"
//#include "stdio.h"
//#include "stdlib.h"
#pragma comment(lib,"winmm.lib")
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif

#include "TestDoc.h"
#include "TestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_GRAPH_ANIMATION, &CTestView::OnGraphAnimation)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_ANIMATION, &CTestView::OnUpdateGraphAnimation)
END_MESSAGE_MAP()

// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
	/*mciSendString("open lll.mp3", 0, 0, 0);
	mciSendString("play lll.mp3", 0, 0, 0);*/
	Alpha = 0.0, Beta = 0.0;
	bPlay = FALSE;

	cube = new CCube[25];
	for(int i=0; i<25; i++)
	{
		cube[i].ReadVertex();
		cube[i].ReadFacet();
		transform[i].SetMatrix(cube[i].P, 8);
	}

	int nEdge = 100;  //�Ŵ���
	for(int i=0; i<25; i++)
		transform[i].Scale(nEdge, nEdge, nEdge);  //�����任
	//transform[25].Scale(500, 500, 1);	//����

	//�ڶ�Ȧ
	transform[1].Translate(-2*nEdge, nEdge, 0);
	transform[2].Translate(0, nEdge, 0);
	transform[3].Translate(2*nEdge, nEdge, 0);
	transform[4].Translate(-2*nEdge, 0, 0);
	transform[5].Translate(2*nEdge, 0, 0);
	transform[6].Translate(-2*nEdge, -nEdge, 0);
	transform[7].Translate(0, -nEdge, 0);
	transform[8].Translate(2*nEdge, -nEdge, 0);

	//����Ȧ
	transform[9].Translate(-4*nEdge, 2*nEdge, 0);
	transform[10].Translate(-2*nEdge, 2*nEdge, 0);
	transform[11].Translate(0, 2*nEdge, 0);
	transform[12].Translate(2*nEdge, 2*nEdge, 0);
	transform[13].Translate(4*nEdge, 2*nEdge, 0);

	transform[14].Translate(-4*nEdge, nEdge, 0);
	transform[15].Translate(4*nEdge, nEdge, 0);
	transform[16].Translate(-4*nEdge, 0, 0);
	transform[17].Translate(4*nEdge, 0, 0);
	transform[18].Translate(-4*nEdge, -nEdge, 0);
	transform[19].Translate(4*nEdge, -nEdge, 0);

	transform[20].Translate(-4*nEdge, -2*nEdge, 0);
	transform[21].Translate(-2*nEdge, -2*nEdge, 0);
	transform[22].Translate(0, -2*nEdge, 0);
	transform[23].Translate(2*nEdge, -2*nEdge, 0);
	transform[24].Translate(4*nEdge, -2*nEdge, 0);

	//transform[25].Translate(0, 0, 0.5*nEdge);

	InitializeLightingScene();  //��ʼ�����ճ���
}

CTestView::~CTestView()
{
	if(cube)
	{
		delete []cube;
		cube = NULL;
	}

	if(pLight != NULL)
	{
		delete pLight;
		pLight = NULL;
	}
	if(pMaterial != NULL)
	{
		delete pMaterial;
		pMaterial = NULL;
	}
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	mciSendString(L"open ./111.mp3 alias music",NULL,0,NULL);  // (./) �򿪵�ǰ���̣� (alias) Ϊ�������� music;
	//mciSendString(L"play music",0,0,0);	//��������
	DoubleBuffer(pDC);//����ͼ��
}

void CTestView::DoubleBuffer(CDC* pDC)//˫�����ͼ
{
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(), rect.Height());
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(rect.Width()/2, rect.Height()/2);
	CDC memDC;//�����ڴ�DC
	memDC.CreateCompatibleDC(pDC);//����һ������ʾDC���ݵ��ڴ�DC
	CBitmap NewBitmap, *pOldBitmap;
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(), rect.Height());//���������ڴ�λͼ 
	pOldBitmap=memDC.SelectObject(&NewBitmap);//������λͼѡ���ڴ�DC
	memDC.FillSolidRect(rect,pDC->GetBkColor());//���ÿͻ�������ɫ
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
	memDC.SetMapMode(MM_ANISOTROPIC);//�ڴ�DC�Զ�������ϵ
	memDC.SetWindowExt(rect.Width(), rect.Height());
	memDC.SetViewportExt(rect.Width(), -rect.Height());
	memDC.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	LoadWallpaper(&memDC);//���ر���ǽ
	DrawObject(&memDC);//����ͼ��
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, -rect.Width()/2, -rect.Height()/2, SRCCOPY); //���ڴ�DC�е�λͼ��������ʾDC
	memDC.SelectObject(pOldBitmap);
	NewBitmap.DeleteObject();
	memDC.DeleteDC();
}
void CTestView::LoadWallpaper(CDC* pDC) 
{
	CRect rect;
	GetClientRect(&rect);
	CDC picDC;//�����ڴ�DC
	picDC.CreateCompatibleDC(pDC);//����һ������ʾDC���ݵ��ڴ�DC
	CBitmap NewBitmap, * pOldBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP3);//����Դ�е���λͼ
	BITMAP bmp;//����bmp�ṹ��
	NewBitmap.GetBitmap(&bmp);//��ȡλͼ��Ϣ	
	pOldBitmap = picDC.SelectObject(&NewBitmap);//��newbitmap����oldBitMap����
	pDC->StretchBlt(-rect.Width() / 2, -rect.Height() / 2, rect.Width(), rect.Height(), &picDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
	picDC.SelectObject(pOldBitmap);
	NewBitmap.DeleteObject();
	picDC.DeleteDC();
}

void CTestView::InitializeLightingScene(void)//��ʼ�����ջ���
{
	//���ù�Դ����
	nLightSourceNumber = 3;//��Դ����
 	pLight = new CLighting(nLightSourceNumber);//һά��Դ��̬����
	pLight->LightSource[0].SetPosition(0, 0, 1000);//���ù�Դλ������
	pLight->LightSource[1].SetPosition(900, 900, 1000);
	pLight->LightSource[2].SetPosition(0, 0, 1000);
 	for(int i = 0;i < nLightSourceNumber;i++)
	{
		pLight->LightSource[i].L_Diffuse = CRGB(1.0,1.0,1.0);//��Դ����������ɫ
		pLight->LightSource[i].L_Specular = CRGB(1.0,1.0,1.0);//��Դ����߹���ɫ
		pLight->LightSource[i].L_C0 = 1.0;//����˥������
		pLight->LightSource[i].L_C1 = 0.0000001;//����˥������
		pLight->LightSource[i].L_C2 = 0.00000001;//����˥������
		pLight->LightSource[i].L_OnOff = TRUE;//��Դ����
	}
	//���ò�������
	pMaterial = new CMaterial;
	pMaterial->SetAmbient(CRGB(0.107, 0.100, 0.185));//����������
	pMaterial->SetDiffuse(CRGB(0.152, 0.106, 0.126));//��������
	pMaterial->SetSpecular(CRGB(0.128, 0.156, 0.166));//���淴����
	pMaterial->SetExponent(50);//�߹�ָ��
}

void CTestView::DrawObject(CDC* pDC)//����ͼ��
{
	CZBuffer* pZBuffer = new CZBuffer;//�����ڴ�
	pZBuffer->InitialDepthBuffer(1200, 1200, 1200);
	for(int i=0; i<25; i++)
	{
		cube[i].SetScene(pLight, pMaterial);//���ó���
		cube[i].Draw(pDC,pZBuffer, bFlatShade);
	}
	delete pZBuffer;
}


void CTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Alpha = 5;
	Beta = 5;
	for(int i=0; i<25; i++)
	{
		transform[i].RotateX(Alpha);
		transform[i].RotateY(Beta);
	}
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}


void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if(!bPlay)
	{
		switch(nChar)
		{
		case VK_UP:
			Alpha = -5;
			for(int i=0; i<25; i++)
				transform[i].RotateX(Alpha);
			break;
		case VK_DOWN:
			Alpha = 5;
			for(int i=0; i<25; i++)
				transform[i].RotateX(Alpha);
			break;
		case VK_LEFT:
			Beta = -5;
			for(int i=0; i<25; i++)
				transform[i].RotateY(Beta);
			break;
		case VK_RIGHT:
			Beta = 5;
			for(int i=0; i<25; i++)
				transform[i].RotateY(Beta);
			break;
		default:
			break;
		}
		Invalidate(FALSE);
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

// CTestView printing


void CTestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView message handlers
void CTestView::OnGraphAnimation()
{
	// TODO: Add your command handler code here
	bPlay = !bPlay;
	if(bPlay)//���ö�ʱ��
		SetTimer(1,150,NULL);	
	else
		KillTimer(1);
}


void CTestView::OnUpdateGraphAnimation(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(bPlay)
 		pCmdUI->SetCheck(TRUE);
 	else
 		pCmdUI->SetCheck(FALSE);
}
