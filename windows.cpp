#include <windows.h>
#include <gdiplus.h>
#include "vcontext.h"
#include "notenode.h"
#include "lineedge.h"
#include "igraph.h"
#include "vpoint.h"
#pragma comment(lib,"ole32.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM); //声名消息处理函数(处理windows和接收windows消息)
//hInstance:系统为窗口分配的实例号,2和3忘了.4是显示方式
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT ("HelloWin") ; //窗体名
    HWND hwnd;//句柄
    MSG msg;//消息体
    WNDCLASS wndclass;//这义一个窗体类实例
    //设置窗体参数
    wndclass.style = CS_HREDRAW | CS_VREDRAW ; //样式
    wndclass.cbClsExtra   = 0 ;
    wndclass.cbWndExtra   = 0 ;
    wndclass.hInstance = hInstance ;//窗体实例名，由windows自动分发
    wndclass.hIcon = LoadIcon (NULL, IDI_APPLICATION) ;//显示上面的图标titlte
    wndclass.hCursor = LoadCursor (NULL, IDC_ARROW) ;//窗口光标
    wndclass.hbrBackground= (HBRUSH) GetStockObject (WHITE_BRUSH) ;//背景刷
    wndclass.lpszMenuName=NULL;
    wndclass.lpfnWndProc=WndProc;//设置窗体接收windws消息函数
    wndclass.lpszClassName= szAppName;//窗体类名
    if (!RegisterClass (&wndclass))//注册窗体类
    {
        MessageBox ( NULL, TEXT ("This program requires Windows NT!"), szAppName, MB_ICONERROR) ;
        return 0 ;
    };
    //创建一个窗体。已分配内存。返回一个窗体句柄
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
    ShowWindow (hwnd,iCmdShow);//显示窗口
    UpdateWindow (hwnd) ;//更新窗体
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage (&msg);//翻译消息并发送到windows消息队列
        DispatchMessage (&msg) ;//接收信息
    }
    return msg.wParam ;
}
static void ListAllFonts(Graphics& graphics) {
    SolidBrush solidbrush(Color::Black);
    FontFamily fontfamily(L"Arial");
    Font font(&fontfamily,8,FontStyleRegular,UnitPoint);
     
    int count=0;
    int found=0;
     
    WCHAR familyName[100];//这里为了简化程序，分配足够大的空间
    WCHAR *familyList=NULL;
    FontFamily pFontFamily[500];//同样，分配足够大的空间
     

    RectF r(0,0,300,200);
     
    InstalledFontCollection installedFontCollection;
    count=installedFontCollection.GetFamilyCount();
    installedFontCollection.GetFamilies(count,pFontFamily,&found);
     
    familyList=new WCHAR[count*sizeof(familyName)];
    wcscpy(familyList,L"");//先清空familyList，wcscpy实现对宽字节的复制操作
    for(int j=0;j<count;j++){
        pFontFamily[j].GetFamilyName(familyName);
        wcscat(familyList,familyName);//把familyName添加到familyList的最后
        wcscat(familyList,L",");//wcscat实现对宽字节字符的添加操作
    }
    //graphics.DrawString(familyList,-1,&font,r,NULL,&solidbrush);
    graphics.DrawString(L"hello",-1,&font,r,NULL,&solidbrush);
    delete[] familyList;
}
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)//消息的处理程序
{
    HDC         hdc ;
    PAINTSTRUCT ps ;
    RECT        rect ;

    switch (message)
    {

    case WM_CREATE:
        return 0 ;

    case   WM_PAINT: {
        std::cout<<"---->"<<std::endl;
        violet::NoteNode node;
        violet::NoteNode node1;
		violet::abstract::IGraph* g;
        violet::VContext context;
        hdc = BeginPaint (hwnd, &ps) ;
        Gdiplus::Graphics graphics(hdc);
        context.Attach(graphics);
        
        //node1.SetParent(node);
        node1.Translate(50,50);
        std::cout<<"node1:"<<node1.GetBounds()<<std::endl;
        node.Translate(100,100);
        node.SetText((std::string)"hello");
        std::cout<<"node:"<<node.GetBounds()<<std::endl;
        node.Draw(context);
        
        node1.SetText((std::string)"hello dfd ");
        node1.Draw(context);
        
		g = &(node.GetGraph());
		node1.SetGraph(*g);
		
		g->AddNode(node,violet::VPoint(100,100));
		g->AddNode(node1,violet::VPoint(50,50));
		
        violet::LineEdge edge;
		violet::VPoint points[1]={violet::VPoint(50,110)};
        g->Connect(edge,node,violet::VPoint(1,1),node1,violet::VPoint(1,1),points);
        #if 1
        edge.Draw(context);
        #endif
        
        //Gdiplus::Pen red(Gdiplus::Color(255, 255, 0, 0), 1);
        //graphics.DrawLine(&red, 10, 10, 100, 100);
        //TextOut(hdc,0,0,"Hello",strlen("Hello"));
        EndPaint (hwnd, &ps) ;
        return 0 ;
    }
    case   WM_DESTROY:
        PostQuitMessage (0) ;
        return 0 ;
    }

    return DefWindowProc (hwnd, message, wParam, lParam) ;
}