#include "config.h"
#include <gdiplus.h>
#include <iostream>

#include "violet.h"
#if 0
#include "vcontext.h"
#include "vcontenttext.h"
#include "notenode.h"
#include "lineedge.h"
#include "noteedge.h"
#include "arrowheadedge.h"
#include "labeledlineedge.h"
#include "igraph.h"
#include "vpoint.h"
#include "pointnode.h"
#include "imagenode.h"
#include "vicon.h"
#include "bentstyle.h"
#include "arrowheadchoicelist.h"
#include "horizontallayout.h"
#include "verticallayout.h"
#include "separator.h"
#include "multilinetext.h"
#endif

#pragma comment(lib,"ole32.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM); 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow)
{
	
    static TCHAR szAppName[] = TEXT ("HelloWin") ;
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW ;
    wndclass.cbClsExtra   = 0 ;
    wndclass.cbWndExtra   = 0 ;
    wndclass.hInstance = hInstance ;
    wndclass.hIcon = LoadIcon (NULL, IDI_APPLICATION) ;
    wndclass.hCursor = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground= (HBRUSH) GetStockObject (WHITE_BRUSH) ;
    wndclass.lpszMenuName=NULL;
    wndclass.lpfnWndProc=WndProc;
    wndclass.lpszClassName= szAppName;
    if (!RegisterClass (&wndclass))
    {
        MessageBox ( NULL, TEXT ("This program requires Windows NT!"), szAppName, MB_ICONERROR) ;
        return 0 ;
    }
      hwnd = CreateWindow( szAppName,      // window class name
        TEXT ("The Hello Program"),   // window caption
        WS_OVERLAPPEDWINDOW, // window style
        CW_USEDEFAULT,// initial x position
        CW_USEDEFAULT,// initial y position
        300,// initial x size
        200,// initial y size
        NULL, // parent window handle
        NULL, // window menu handle
        hInstance, // program instance handle
        NULL) ;
    ShowWindow (hwnd,iCmdShow);
    UpdateWindow (hwnd) ;
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage (&msg);
        DispatchMessage (&msg) ;
    }
    return msg.wParam ;
}
static void ListAllFonts(Graphics& graphics) {
    SolidBrush solidbrush(Color::Black);
    FontFamily fontfamily(L"Arial");
    Font font(&fontfamily,8,FontStyleRegular,UnitPoint);
     
    int count=0;
    int found=0;
     
    WCHAR familyName[100];
    WCHAR *familyList=NULL;
    FontFamily pFontFamily[500];     

    RectF r(0,0,300,200);
     
    InstalledFontCollection installedFontCollection;
    count=installedFontCollection.GetFamilyCount();
    installedFontCollection.GetFamilies(count,pFontFamily,&found);
     
    familyList=new WCHAR[count*sizeof(familyName)];
    wcscpy(familyList,L"");
    for(int j=0;j<count;j++){
        pFontFamily[j].GetFamilyName(familyName);
        wcscat(familyList,familyName);
        wcscat(familyList,L",");//
    }
    //graphics.DrawString(familyList,-1,&font,r,NULL,&solidbrush);
    graphics.DrawString(L"hello",-1,&font,r,NULL,&solidbrush);
    delete[] familyList;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC         hdc ;
    PAINTSTRUCT ps ;
    RECT        rect ;
	static int i = 0;
	char b[64]={0};
	
    switch (message)
    {

    case WM_CREATE:
        return 0 ;

    case   WM_PAINT: {
        violet::NoteNode node;
        violet::abstract::IGraph* g;
        g = &(node.GetGraph());
	
        std::cout<<"---->"<<std::endl;
        violet::VContext context;
        hdc = BeginPaint (hwnd, &ps) ;
        Gdiplus::Graphics graphics(hdc);
        context.Attach(graphics);
        
        violet::NoteNode node1;
        violet::NoteNode node2;
        violet::LabeledLineEdge edge;

        node1.SetText(std::string("node1"));
        node2.SetText(std::string("node2"));
        g->AddNode(node1,violet::VPoint(50,50));
        g->AddNode(node2,violet::VPoint(150,150));
        violet::VPoint points[] = {
			violet::VPoint(),violet::VPoint()
        };
        edge.SetStartArrowHead(*violet::property::ArrowHeadChoiceList::DIAMOND_WHITE);
        edge.SetEndArrowHead(*violet::property::ArrowHeadChoiceList::DIAMOND_BLACK);
        edge.SetStartLabel(std::string("1..n"));
        edge.SetCenterLabel(std::string("center"));
        edge.SetEndLabel(std::string("1"));
        g->Connect(edge,node1,violet::VPoint(1,1),node2,violet::VPoint(1,1),points);

        node1.Draw(context);
        node2.Draw(context);
        edge.SetLineStyle(violet::LineStyle::DOTTED);
        edge.SetBorderColor(violet::VColor(255,0,0));
        edge.Draw(context);

		violet::VerticalLayout *layout = new violet::VerticalLayout;
		violet::HorizontalLayout layout1;
		{
			violet::VLineText* linetext1 = new violet::VLineText;
			violet::VLineText* linetext2 = new violet::VLineText;
			violet::VLineText* linetext4 = new violet::VLineText;
			violet::VLineText* linetext3 = new violet::VLineText;
			violet::VContentText* content1 = new violet::VContentText(*linetext1);
			violet::VContentText* content2 = new violet::VContentText(*linetext2);
			violet::VContentText* content4 = new violet::VContentText(*linetext4);
			violet::VContentText* content3 = new violet::VContentText(*linetext3);
			linetext1->SetText(std::string("text1"));linetext1->UpdateBounds(context);
			linetext2->SetText(std::string("text2"));linetext2->UpdateBounds(context);
			linetext4->SetText(std::string("text4"));linetext4->UpdateBounds(context);
			linetext3->SetText(std::string("text3"));linetext3->UpdateBounds(context);
			(*layout).Add(*content1);
			(*layout).Add(*content2);
			(*layout).Add(*content4);
			(*layout).SetSeparator(*violet::Separator::LINE);
			layout1.SetSeparator(*violet::Separator::LINE);
			layout1.Add(*content3);
			layout1.Add(*layout);
			context.SetLocation(violet::VPoint(200,300));
			layout1.Draw(context);
			context.SetLocation(violet::VPoint(0,0));
			
		}
        {
            violet::MultiLineText mt;
            mt.AppendLineText(std::string("hello"));
            mt.AppendLineText(std::string("world"));
            mt.Draw(context);
            mt.SetLineText(1,std::string("hello world djsfjsd jfslfj sjlfja ls dsfjsdf sdf sdj fksdj fsadk lfasj"));
            context.Translate(30,30);
            mt.Draw(context);
            context.Translate(-30,-30);
        }
        
        //node1.SetParent(node);
    #if 1
        //g->Draw(context);
    #endif
	#if 0
        violet::VLineText* linetext = new violet::VLineText;
        violet::VContentText content(*linetext);
        linetext->SetText(std::string("label"));
        content.Draw(context,violet::VPoint(200,200));
        context.Rotate(violet::VPoint(200,200),-30);// change
        content.Draw(context,violet::VPoint(200,200));
        context.Rotate(violet::VPoint(200,200),30);// revert
        content.Draw(context,violet::VPoint(10,10));
      #endif
        //Gdiplus::Pen red(Gdiplus::Color(255, 255, 0, 0), 1);
        //graphics.DrawLine(&red, 10, 10, 100, 100);
        //TextOut(hdc,0,0,"Hello",strlen("Hello"));
        EndPaint (hwnd, &ps) ;
        return 0 ;
    }
	case WM_LBUTTONDOWN: {
        #if 0
        GetClientRect(hwnd, &rect);
		violet::NoteNode* node = new violet::NoteNode;
		sprintf(b,"node %d",i); 
		i++;
		node->SetText(std::string(b));
		int xPos = LOWORD(lParam);  // horizontal position of cursor 
		int yPos = HIWORD(lParam);  // vertical position of cursor 
		g->AddNode(*node,violet::VPoint(xPos,yPos));
		InvalidateRect(hwnd, &rect, true);
        #endif
		return 0;
	}
    case   WM_DESTROY:
        PostQuitMessage (0) ;
        return 0 ;
    }

    return DefWindowProc (hwnd, message, wParam, lParam) ;
}