
// MainFrm.cpp : implementation of the CMainFrame class
//
 


#include "stdafx.h"
#include "tool3.h"
#include <Richedit.h>
#include "MainFrm.h"
#include <cstdint>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CWnd)
	ON_WM_CREATE()
	ON_BN_CLICKED(2133,tr)
	ON_BN_CLICKED(233,w)
	ON_BN_CLICKED(2233,uw)
	ON_BN_CLICKED(22,ef)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}


// CMainFrame diagnostics

#ifdef _DEBUG



#endif //_DEBUG


// CMainFrame message handlers

class r:public CFolderPickerDialog
{
public:
	CString f;
	int last;

	r() : CFolderPickerDialog()
	{

	}
	void init() { f = m_szFileName; }
};
r *t;
HWND hc,hz;
CButton *bh;
CButton *q;
CButton *finA;
CButton *cmdos;
CStatic *b7;
ITaskbarList3 *bhr; //
HANDLE cl;

DWORD CALLBACK E(DWORD_PTR dw, LPBYTE pb, LONG cb, LONG *pcb)
{
    std::wstringstream *fr = (std::wstringstream *)dw;
    fr->write((wchar_t *)pb, int(cb/2)); 
    *pcb = cb;
    return 0;
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{	
	cl=CreateEvent(NULL,1,0,NULL);
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	bh=new CButton();

	b7=new CStatic();
	q=new CButton();
	finA=new CButton();
	cmdos=new CButton();
	CBitmap wq[2];

	wq[0].LoadBitmap(IDB_BITMAP1);
	wq[1].LoadBitmap(IDB_BITMAP4);

	wchar_t w[140];
				ExpandEnvironmentStrings(L"%USERPROFILE%\\Documents\\fold.",w,140);
				FILE *xf;
				_wfopen_s(&xf,w,L"r+");		
				DWORD c = 0;
			if(xf)  
			{
					fwscanf(xf,L"%[^\n]%*c",remmi);          //stuff from msdn. works with and w/o \n 
					t=new r();
					t->f=remmi;
					if(!(feof(xf)))
					{
						ZeroMemory(remmi,318*2);
						fwscanf(xf,L"%[^\n]%*c",remmi);
					}
					else
					{							
						wcscpy_s(remmi,L"-server");
						fwprintf(xf,L"\n%s",remmi);      // r+ shifts write pos when read.
					}
					fclose(xf);
			}
			else
			{
					c=WS_DISABLED;
					wcscpy_s(remmi,L"-server");
					t=NULL;
			}
			


	bh->Create(L"start",BS_BITMAP|WS_CHILD|WS_VISIBLE|c,CRect(50,50,170,100),this,2133);
	bh->SetBitmap(wq[0]);
	q->Create(L"stop",BS_BITMAP|WS_CHILD|WS_VISIBLE|WS_DISABLED,CRect(50+170,50,170+170,100),this,233);
	q->SetBitmap(wq[1]);
	finA->Create(L"locate",BS_TEXT|WS_CHILD|WS_VISIBLE,CRect(0+280,20+292,59+280,48+292),this,2233);
	cmdos->Create(L"commandos",BS_TEXT|WS_CHILD|WS_VISIBLE,CRect(0+350,20+292,97+350,48+292),this,22);

	b7->Create(L"to go :",WS_CHILD|WS_VISIBLE|SS_WHITEFRAME|SS_SIMPLE,CRect(0,290,473,320),this);
	 hc=CreateWindowEx(WS_EX_NOPARENTNOTIFY, MSFTEDIT_CLASS,remmi, 
		ES_MULTILINE|ES_AUTOVSCROLL| WS_VISIBLE | WS_CHILD |WS_TABSTOP|WS_VSCROLL, 
        1, 350, 450, 201, this->m_hWnd, NULL, h, NULL);
	HFONT newFont = CreateFont(22, 0, 0, 0,0 , FALSE, FALSE, FALSE, DEFAULT_CHARSET,
    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY,
	DEFAULT_PITCH | FF_DECORATIVE, L"Lucida Console");
	
	::PostMessage(hc,WM_SETFONT,(WPARAM)newFont,(LPARAM)0);
	hz=this->m_hWnd;
	::PostMessage(b7->m_hWnd,WM_SETFONT,(WPARAM)newFont,(LPARAM)0);
	return 0;
}
	HANDLE stdinRd, stdinWr, stdoutRd, stdoutWr;
int bren=5;
int cr,f,b,terminator;

PROCESS_INFORMATION pi;

/*does nothing for now*/
VOID c(VOID *)
{		
			
			CWin32Heap stringHeap(HEAP_NO_SERIALIZE, 0, 0);
			CAtlStringMgr M(&stringHeap);
			CStringA X7(&M),X8(&M),Burg(&M);
			CString p(&M);
			triggerblock z2={},z={};
			
			DWORD numberofbyteswritten;
            DWORD dwRead;
			DWORD totalbytesavailable;
			char output_cmd[500001];
			int h,c,ferrum=0,tm=400;
			BYTE w=0;
			CStringA t(&M),bear(&M);
			int monte=0;
			int r;
			
			SetThreadExecutionState(ES_CONTINUOUS|ES_SYSTEM_REQUIRED|ES_AWAYMODE_REQUIRED|ES_DISPLAY_REQUIRED);
			z2.finishup=10;
			z.E=4;

            while(1)
            {
		PeekNamedPipe(stdoutRd, NULL, 0, NULL, &totalbytesavailable, 0);

		    if(totalbytesavailable)
            {   
                    ReadFile(stdoutRd, output_cmd, min(500000,totalbytesavailable), &dwRead, NULL);
                    h = min(500000,totalbytesavailable);
                    output_cmd[h]='\0';
					t=output_cmd;	
					monte=monte+h;
					bear=bear + t;
					c=t.Find("error");
					if(c != -1)  
					{
						ferrum=1;

					}					                   
			
				if(ferrum) 
				{			

					q->EnableWindow(0);
					WaitForSingleObject(pi.hProcess,INFINITE);
					b=0;
					bh->EnableWindow();
					if(terminator) PostMessage(hz,WM_CLOSE,NULL,NULL);
					else { 		}
					bren=5;
					break;				 //'Both break and continue have no effect on an if-statement. A common misconception is										 
//that break can be used to jump out of an if compound statement.' An Introduction to the C Programming Language and Software Design.   Tim Bailey 2005
				}
			}
                Sleep(tm);
        }
}


CWinThread *rew;
int trigger;
int terminator2;

void CMainFrame::tr()
{   
	std::wstringstream fr;

	EDITSTREAM es;
	if(!trigger)
	{	
		ZeroMemory(&es,sizeof(es));
		es.dwCookie = (DWORD_PTR) &fr;
		es.pfnCallback = E;
		::SendMessage(hc, EM_STREAMOUT, SF_TEXT|SF_UNICODE, (LPARAM)&es);		
	}
	

	SECURITY_ATTRIBUTES sa={sizeof(SECURITY_ATTRIBUTES), NULL, true};    
			CreatePipe(&stdinRd, &stdinWr, &sa, 10000); 
            CreatePipe(&stdoutRd,&stdoutWr, &sa,500000);
			if(pi.hProcess) CloseHandle(pi.hProcess); 
			STARTUPINFO si;
			ZeroMemory(&si,sizeof(si));
           
			si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
            si.wShowWindow = SW_HIDE;
            si.hStdOutput = stdoutWr;
            si.hStdError = stdoutWr;         
            si.hStdInput = stdinRd;
			std::wstring w;
			if(!trigger) 
			{	
				if(!iswspace((wchar_t )fr.str()[0])) { ZeroMemory(remmi,318*2);
w=L' ' + fr.str(); w.copy(remmi,247,0);}
				else
				{ZeroMemory(remmi,318*2);
					
					fr.read(remmi,247);
				}				
				trigger++;
			}
	
			

			
			int h=CreateProcess(t->f + L"\\Bitcoin-qt.exe",remmi, NULL, NULL, TRUE, CREATE_NEW_PROCESS_GROUP, NULL, t->f, &si, &pi);        
			if(!h) 
			{

				MessageBox(L"Bad start,check location");
				return;
			}
			else bren=0;
			rew=AfxBeginThread((AFX_THREADPROC)c,NULL,0,1400000);
}


/*monero stuff */
void CMainFrame::w()
{
	b=1;
	char k[100];
	strcpy(k,"exit\n");
	DWORD numberofbyteswritten;
	WriteFile(stdinWr, k, 5, &numberofbyteswritten, NULL);
}




void CMainFrame::uw()
{
	if(!t) t=new r();
	int c= t->DoModal();
	wchar_t w[140];
	ExpandEnvironmentStrings(L"%USERPROFILE%\\Documents\\fold.",w,130);
	FILE *xf;

	if(c==IDOK)
	{
		xf=_wfopen(w,L"w+");
		t->init();
		fwprintf(xf,L"%s",t->f);
		fwprintf(xf,L"\n%s",remmi);
		fclose(xf);
		bh->EnableWindow();	
	}
	else if(t->f.IsEmpty()) {delete t; t=NULL;}
}


void CMainFrame::OnDestroy()
{
	CWnd::OnDestroy();
	if(t) delete t;
	delete bh;
	delete q;
	delete finA;
	delete cmdos;
	delete b7;
//	delete rew;

	// TODO: Add your message handler code here
}




void CMainFrame::OnClose() 
{
		FILE *xf;		
		wchar_t w[140],ferrum[198];
	if(terminator2)
	{
		DWORD c=WaitForSingleObject(pi.hProcess,140);
		if(c!= WAIT_TIMEOUT) 
		{
			SetEvent(cl);
			if(t)
			{
				ExpandEnvironmentStrings(L"%USERPROFILE%\\Documents\\fold.",w,130);
				xf=_wfopen(w,L"w+");
				fwprintf(xf,L"%s",t->f);
				if(remmi[0]==L' ')fwprintf(xf,L"\n%s",&remmi[1]);
				else fwprintf(xf,L"\n%s",remmi);
				fclose(xf); 			
			}

		CWnd::OnClose();

		}
		else CWnd::OnClose(); //

	}
	else 
	terminator2++;

	if((!b)&&(bren))	
	{
		SetEvent(cl);


			if(t)
			{
				ExpandEnvironmentStrings(L"%USERPROFILE%\\Documents\\fold.",w,130);
				xf=_wfopen(w,L"w+");
				fwprintf(xf,L"%s",t->f);
				if(remmi[0]==L' ')fwprintf(xf,L"\n%s",&remmi[1]);
				else fwprintf(xf,L"\n%s",remmi);
				fclose(xf); 			
			}
		CWnd::OnClose();
	}
	else
	{
		terminator =1;
		if(!b) this->w();
	}


}

void CMainFrame::ef()
{
	SETTEXTEX fw;

	fw.flags=4;
	fw.codepage=1200;			
//	::PostMessage(hc,EM_SETTEXTEX,(WPARAM)&fw,(LPARAM)remmi);

	stonehill(NULL);
	trigger=5-bren;
}




void stonehill(void*)
{	
	SETTEXTEX fw;
	triggerblock mo;
	CSocket c;
	c.Create();
	wchar_t w[140];
	ExpandEnvironmentStrings(L"%APPDATA%\\Bitcore\\.cookie",w,140);
	FILE *xf;
	_wfopen_s(&xf,w,L"r+");		
	char h[518];
	fwscanf(xf,L"%S",h);      //%S here is microsoft stuff.Wide char function with char arg.  
	
	fclose(xf);
	int x_len = strlen(h); // One byte is represented as two hex characters, thus we divide by two to get real length.

	CString ht[3];

	char fifty[200];
	int len=Base64EncodeGetRequiredLength(x_len);
	Base64Encode((BYTE *)h,x_len,fifty,&len,ATL_BASE64_FLAG_NOCRLF);
	fifty[len]='\0';
	char t[]="{ \"method\":\"listrece\
ivedbyaccount\",\"params\": [0],\"id\":\"listreceivedbyaccount\" }\r\n";

	std::stringstream f;
	
	f<<"POST / HTTP/1.1\r\nContent-Length: "<< sizeof(t)-1 <<"\r\nAuthorization: Basic " << fifty <<"\r\n\r\n"<<t;
 
	c.Connect(L"localhost",8332);
	char b[1000];
	c.Send(f.str().c_str(),strlen(f.str().c_str()));
	
	len=c.Receive(b,1000);

	b[len]='\0';
	ht[0]=b;
 
	fw.flags=4;
	fw.codepage=1200;			
	::SendMessage(hc,EM_SETTEXTEX,(WPARAM)&fw,(LPARAM)(LPCWSTR)ht[0]);
}