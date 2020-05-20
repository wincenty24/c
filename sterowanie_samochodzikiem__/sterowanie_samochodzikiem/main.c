#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <wingdi.h>
#include <commctrl.h>
#include <tchar.h>

LPSTR NazwaKlasy = "Klasa Okienka";
MSG Komunikat;// do pętli poleceń
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
HWND hwnd;
int a;
HWND g_hPrzycisk;
char text_z_text_boxa[20];
char nazwa_portu_com[20]="\\\\.\\";
HWND hTrack;
HWND hlbl;
HWND tekst_port;
char jasnosc[1];
HWND hWndExample;
HWND tekst;
HWND czytaj_znaki_uart;
HMENU hMenu ;
HWND textbox;
HWND PRZ_MAP;
HBITMAP PRZ_MAP_IMAGE_PUS;
HBITMAP PRZ_MAP_IMAGE_ZIEL;
HWND PRAWO_MAP;
HBITMAP PRAWO_MAP_IMAGE_PUS;
HBITMAP PRAWO_MAP_IMAGE_ZIEL;
HWND LEWO_MAP;
HBITMAP LEWO_MAP_IMAGE_PUS;
HBITMAP LEWO_MAP_IMAGE_ZIEL;
HWND TYL_MAP;
HBITMAP TYL_MAP_IMAGE_PUS;
HBITMAP TYL_MAP_IMAGE_ZIEL;

HWND hWndStatusBar;
char TempChar; //Temporary character used for reading
char SerialBufferread[256];//Buffer for storing Rxed Data
bool zmiennaklawiszydown=true;
bool zmiennaklawiszgdown=true;
bool zmiennaklawiszhdown=true;
bool zmiennaklawiszjdown=true;
void AddMenus(HWND);

#define IDM_CLOSE_SERIAL 1
#define IDM_OPEN_SERIAL 2
#define IDM_FILE_QUIT 3
//HMENU hMenubar;

// HMENU hMenu_Serial;
//HMENU hMenu_TOFF;
void AddMenus(HWND hwnd)
{

    HMENU hMenubar;
    HMENU hMenuSERIAL;
    HMENU hMenuAPP;

    hMenubar = CreateMenu();
    hMenuSERIAL = CreateMenu();
    hMenuAPP = CreateMenu();



    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenuSERIAL, L"&SERIAL");
    AppendMenuW(hMenuSERIAL, MF_STRING, IDM_CLOSE_SERIAL, L"&Close Serial");
    AppendMenuW(hMenuSERIAL, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenuSERIAL, MF_STRING, IDM_OPEN_SERIAL, L"&Open Serial");


    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenuAPP, L"&APPLICATION");

    AppendMenuW(hMenuAPP, MF_STRING, IDM_FILE_QUIT, L"&Quit");


    SetMenu(hwnd, hMenubar);
}


BOOL zmienna;
HANDLE hComm;  // Handle to the Serial port
BOOL   Status; // Status
DCB dcbSerialParams = { 0 };  // Initializing DCB structure
COMMTIMEOUTS timeouts = { 0 };  //Initializing timeouts structure
char SerialBuffer[64] = "000"; //Buffer to send and receive data
char do_przodu_komenda[3]="bbb";
char znaki[]="00";
DWORD BytesWritten = 0;          // No of bytes written to the port




WNDCLASSEX wc;
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    // MessageBox( NULL, "To jest wiadomoœæ.", "Wiadomoœæ", MB_ICONINFORMATION | MB_OKCANCEL );
    //return 0;


    wc.cbSize = sizeof( WNDCLASSEX );//Rozmiar struktury w bajtach. Należy tu wpisać sizeof (WINDOWCLASSEX).
    wc.style = 0;// styl
    wc.lpfnWndProc = WndProc;//Wskaźnik do procedury obsługującej okno
    wc.cbClsExtra = 0;//Dodatkowe bajty pamięci dla klasy (można ustawić na 0)
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;//Identyfikator aplikacji, która ma być właścicielem okna (zazwyczaj pierwszy parametr naszej funkcji WinMain)
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );//Ikonka okna. Dokładniej: duża ikonka, widać ją kiedy naciśniesz Alt-Tab. Ładujemy ją poleceniem LoadIcon(NULL, IDI_APPLICATION), które wybierze nam domyślną ikonkę aplikacji.
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );//Kursor myszki. Analogicznie, jak dla ikonki, korzystamy z LoadCursor(NULL, IDC_ARROW), co zaowocuje pojawieniem się naszym okienku
    wc.hbrBackground =( HBRUSH )(COLOR_WINDOW +1 );//Tło naszego okienka, czyli jego kolor i wzór
    //wc.lpszMenuName = NULL;
    wc.lpszClassName = NazwaKlasy;//Nazwa klasy, którą tworzymy. Możesz wpisać, co chcesz
    wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );//Mała ikonka naszej aplikacji. Widać ją w rogu naszego okienka oraz na pasku zadań. Dajemy tutaj to samo, co w przypadku dużej ikony.
    if( !RegisterClassEx( & wc ) )//Jeżeli jednak komisja w postaci funkcji RegisterClassEx wyraziła zgodę, zwracając wartość niezerową, to możemy śmiało przystąpić do kroku następnego, a mianowicie budowy naszego okienka
    {
        MessageBox( NULL, "Wysoka Komisja odmawia rejestracji tego okna!", "Niestety...",MB_ICONEXCLAMATION | MB_OK );
        return 1;
    }


    hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, NazwaKlasy, "Oto okienko", WS_OVERLAPPEDWINDOW,//Rozszerzone parametry stylu okna  //style okienka
                           CW_USEDEFAULT, CW_USEDEFAULT, 700, 500, NULL, NULL, hInstance, NULL );// =>CW_USEDEFAULT, CW_USEDEFAULT pozycja okna. Można ustawić na CW_USEDEFAULT, czyli na domyślną pozycję
    hWndExample = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | ES_LEFT, 10,10,100,100, hwnd, NULL, hInstance, NULL);//textbox
    tekst_port= CreateWindow("EDIT", " Wpisz nazwe portu : ", WS_VISIBLE | WS_CHILD | ES_LEFT, 500,30,200,30, hwnd, NULL, hInstance, NULL);//textbox
    textbox = CreateWindow( "EDIT", "", WS_BORDER| WS_CHILD | WS_VISIBLE, 600, 70, 60, 25, hwnd, NULL, NULL, NULL );
    g_hPrzycisk = CreateWindow( "BUTTON", "Zatwierdz", WS_CHILD | WS_VISIBLE | WS_BORDER,500, 100, 150, 30, hwnd, (HMENU) 1, NULL, NULL );
    //tekst = CreateWindow("EDIT", "WEWEWE", WS_VISIBLE | WS_CHILD | ES_LEFT, 10,300,100,100, hwnd, NULL, hInstance, NULL);


    //SendMessage (tekst_strzalka_lewo, WM_SETFONT, WPARAM (hFont), TRUE);




    if( hwnd == NULL )
    {
        MessageBox( NULL, "Okno odmówi³o przyjœcia na œwiat!", "Ale kicha...", MB_ICONEXCLAMATION );
        return 1;
    }




    PRZ_MAP = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | SS_BITMAP | WS_VISIBLE,200, 50, 300, 300, hwnd, NULL, hInstance, NULL);
    PRZ_MAP_IMAGE_PUS = (HBITMAP)LoadImageW(NULL,L"strz_przód_pueste.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    PRZ_MAP_IMAGE_ZIEL = (HBITMAP)LoadImageW(NULL,L"strz_przód_zielona.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    PRAWO_MAP = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | SS_BITMAP | WS_VISIBLE,280, 150, 300, 300, hwnd, NULL, hInstance, NULL);
    PRAWO_MAP_IMAGE_PUS = (HBITMAP)LoadImageW(NULL,L"strz_prawo_pusta.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    PRAWO_MAP_IMAGE_ZIEL = (HBITMAP)LoadImageW(NULL,L"strz_prawo_zielona.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    LEWO_MAP = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | SS_BITMAP | WS_VISIBLE,90, 150, 300, 300, hwnd, NULL, hInstance, NULL);
    LEWO_MAP_IMAGE_PUS = (HBITMAP)LoadImageW(NULL,L"strz_lewo_pusta.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    LEWO_MAP_IMAGE_ZIEL = (HBITMAP)LoadImageW(NULL,L"strz_lewo_zielona.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    TYL_MAP = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | SS_BITMAP | WS_VISIBLE,200, 210, 300, 300, hwnd, NULL, hInstance, NULL);
    TYL_MAP_IMAGE_PUS = (HBITMAP)LoadImageW(NULL,L"strz_dół_pusta.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    TYL_MAP_IMAGE_ZIEL = (HBITMAP)LoadImageW(NULL,L"strz_dół_zielona.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    SendMessageW(PRZ_MAP,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)PRZ_MAP_IMAGE_PUS);
    SendMessageW(LEWO_MAP,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)LEWO_MAP_IMAGE_PUS);
    SendMessageW(TYL_MAP,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)TYL_MAP_IMAGE_PUS);
    SendMessageW(PRAWO_MAP,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)PRAWO_MAP_IMAGE_PUS);

    /*
                    hComm = CreateFile("\\\\.\\COM3", //friendly name 3
                                   GENERIC_WRITE,      // Read/Write Access
                                   0,                                 // No Sharing, ports cant be shared
                                   NULL,                              // No Security
                                   OPEN_EXISTING,                     // Open existing port only
                                   0,                                 // Non Overlapped I/O
                                   NULL);                             // Null for Comm Devices

                dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
                dcbSerialParams.BaudRate = CBR_9600;      //BaudRate = 9600
                dcbSerialParams.ByteSize = 4;             //ByteSize = 8
                dcbSerialParams.StopBits = ONESTOPBIT;    //StopBits = 1
                dcbSerialParams.Parity = NOPARITY;      //Parity = None

                SetCommState(hComm, &dcbSerialParams);

    */
    ShowWindow( hwnd, nCmdShow ); // Poka¿ okienko...
    UpdateWindow( hwnd );
//hWndStatusBar = CreateWindowEx(0,STATUSCLASSNAME,NULL,WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,0,0,0,0,hwnd,(HMENU)IDC_STATUSBAR,(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),NULL);
    SendMessage( hWndStatusBar, PBM_SETRANGE, 100,( LPARAM ) MAKELONG( 0, 123 ) );
//SendMessageW(GAME_MAP,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)GAME_MAP_IMAGE);
    while( GetMessage( & Komunikat, NULL, 0, 0 ) )//pobiera kolejne wiadomości od systemu, a dokładniej z tzw. kolejki wiadomości
    {
        TranslateMessage( & Komunikat );//wykonuje kilka drobnych operacji z wykorzystaniem naszego komunikatu - szczegóły nie są nam do niczego potrzebne
        DispatchMessage( & Komunikat );//DispatchMessage wysyła komunikat do właściwego miejsca przeznaczenia - tutaj jest nim nasze okno. Przy tak prostym programie nie musisz podawać, do którego okna ma trafić komunikat - system "sam się domyśli"
    }
//g_hPrzycisk = CreateWindowEx( 0, "BUTTON", "Nasz przycisk", WS_CHILD | WS_VISIBLE,100, 100, 150, 30, hwnd, NULL, hInstance, NULL );


    return Komunikat.wParam;


}


LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{

    // HDC hdc;
    //PAINTSTRUCT ps;
    switch( msg )
    {
    case WM_HSCROLL:
        UpdateLabel();
        break;
    case WM_CREATE:


        CreateControls(hwnd);
        AddMenus(hwnd);


        //}
//hFont=CreateFontIndirect (20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
//SetFocus(hwnd);
        break;
    case WM_COMMAND:
        if(( HWND ) lParam == g_hPrzycisk )
        {

            int a = GetWindowText(textbox, &text_z_text_boxa[0],20);//Pobiera tekst z określonego okna.|| Uchwyt do okna zawierającego tekst.||	Bufor przyjmujący tekst. Jeśli łańcuch znaków jest zbyt długi, zostanie skrócony i zakończony znakiem zerowym.||Maksymalna liczba znaków do skopiowania do bufora (włączając znak zerowy).
            //jeżeli a ==0 error
            memset(nazwa_portu_com, 0, sizeof (nazwa_portu_com));//czyszczenie chara
            strcat(nazwa_portu_com, text_z_text_boxa);
            MessageBox(hwnd,text_z_text_boxa,"asd",NULL);


        }
        switch(LOWORD(wParam))
        {

        case IDM_CLOSE_SERIAL:
            MessageBeep(MB_ICONINFORMATION);
            CloseHandle(hComm);
            break;
        case IDM_OPEN_SERIAL:

            MessageBeep(MB_ICONINFORMATION);
            hComm = CreateFile(nazwa_portu_com, //friendly name 3
                               GENERIC_WRITE,      // Read/Write Access
                               0,                                 // No Sharing, ports cant be shared
                               NULL,                              // No Security
                               OPEN_EXISTING,                     // Open existing port only
                               0,                                 // Non Overlapped I/O
                               NULL);                             // Null for Comm Devices

            dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
            dcbSerialParams.BaudRate = CBR_9600;      //BaudRate = 9600
            dcbSerialParams.ByteSize = 4;             //ByteSize = 8
            dcbSerialParams.StopBits = ONESTOPBIT;    //StopBits = 1
            dcbSerialParams.Parity = NOPARITY;      //Parity = None

            SetCommState(hComm, &dcbSerialParams);
            break;

        case IDM_FILE_QUIT:
            MessageBeep(MB_ICONINFORMATION);
            SendMessage(hwnd, WM_CLOSE, 0, 0);
            break;
        }


        break;

    /*
    switch(LOWORD(wParam))
    {

    case IDM_CLOSE:
       MessageBox( hwnd, "Nacisnąłeś przycisk!", "Ha!", MB_ICONINFORMATION );
       DestroyWindow( hwnd );
     CloseHandle(hComm);
    break;
    case IDM_OPEN:
        MessageBox( hwnd, "Nacisnąłeś przycisk!", "Ha!", MB_ICONINFORMATION );
        hComm = CreateFile("\\\\.\\COM3", //friendly name 3
                           GENERIC_WRITE,      // Read/Write Access
                           0,                                 // No Sharing, ports cant be shared
                           NULL,                              // No Security
                           OPEN_EXISTING,                     // Open existing port only
                           0,                                 // Non Overlapped I/O
                           NULL);                             // Null for Comm Devices

        dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
        dcbSerialParams.BaudRate = CBR_9600;      //BaudRate = 9600
        dcbSerialParams.ByteSize = 4;             //ByteSize = 8
        dcbSerialParams.StopBits = ONESTOPBIT;    //StopBits = 1
        dcbSerialParams.Parity = NOPARITY;      //Parity = None

        SetCommState(hComm, &dcbSerialParams);

        MessageBeep(MB_ICONINFORMATION);
        break;

    case IDM_QUIT:
    MessageBox( hwnd, "Nacisnąłeś przycisk!", "Ha!", MB_ICONINFORMATION );
        SendMessage(hwnd, WM_CLOSE, 0, 0);
        break;
    }
    //  SetFocus(hwnd);// bo nie działay klawisze po wciśnięciu przycisków
    break;
    */
    case WM_KEYUP:
        switch(( int ) wParam )
        {
        case 0x59://y
            SendMessageW(PRZ_MAP,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)PRZ_MAP_IMAGE_PUS);
            znaki[0]='0';
            znaki[1]='0';
            if(zmiennaklawiszgdown==false)
            {
                znaki[1]='2';
            }
            if(zmiennaklawiszjdown==false)
            {
                znaki[0]='2';
            }
            zmiennaklawiszydown=true;
            Status = WriteFile(hComm,// Handle to the Serialport
                               znaki,            // Data to be written to the port
                               sizeof(znaki),   // No of bytes to write into the port
                               &BytesWritten,  // No of bytes written to the port
                               NULL);


            SetWindowText(hWndExample, znaki);

            break;
        case 0x47://g
            //znaki[1]='0';
            SendMessageW(LEWO_MAP,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)LEWO_MAP_IMAGE_PUS);
            znaki[1]='0';


            if(zmiennaklawiszydown==false )
            {

                znaki[0]='2';
                znaki[1]='2';



            }
            if(zmiennaklawiszhdown==false )
            {

                znaki[0]='1';
                znaki[1]='1';



            }

            zmiennaklawiszgdown=true;
            Status = WriteFile(hComm,// Handle to the Serialport
                               znaki,            // Data to be written to the port
                               sizeof(znaki),   // No of bytes to write into the port
                               &BytesWritten,  // No of bytes written to the port
                               NULL);

            SetWindowText(hWndExample, znaki);

            break;
        case 0x48://h
            SendMessageW(TYL_MAP,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)TYL_MAP_IMAGE_PUS);
            znaki[0]='0';
            znaki[1]='0';
            if(zmiennaklawiszgdown==false)
            {
                znaki[1]='1';
            }
            if(zmiennaklawiszjdown==false)
            {
                znaki[0]='1';
            }

            zmiennaklawiszhdown=true;
            Status = WriteFile(hComm,// Handle to the Serialport
                               znaki,            // Data to be written to the port
                               sizeof(znaki),   // No of bytes to write into the port
                               &BytesWritten,  // No of bytes written to the port
                               NULL);

            SetWindowText(hWndExample, znaki);

            break;
        case 0x4A://j
            SendMessageW(PRAWO_MAP,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)PRAWO_MAP_IMAGE_PUS);
            znaki[0]='0';
            zmiennaklawiszjdown=true;
            if(zmiennaklawiszydown==false )
            {

                znaki[0]='2';
                znaki[1]='2';



            }
            if(zmiennaklawiszhdown==false )
            {

                znaki[0]='1';
                znaki[1]='1';



            }
            Status = WriteFile(hComm,// Handle to the Serialport
                               znaki,            // Data to be written to the port
                               sizeof(znaki),   // No of bytes to write into the port
                               &BytesWritten,  // No of bytes written to the port
                               NULL);

            SetWindowText(hWndExample, znaki);

            break;
        }
        break;

    case WM_KEYDOWN:
    {
        switch(( int ) wParam )
        {
        case 0x59://y





            SendMessageW(PRZ_MAP,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)PRZ_MAP_IMAGE_ZIEL);
            memset(znaki, 0, sizeof (znaki));
            znaki[0]='2';
            znaki[1]='2';
            // znaki[2]=jasnosc;
            strcat(znaki, jasnosc);

            if(zmiennaklawiszydown==true)
            {
                Status = WriteFile(hComm,// Handle to the Serialport
                                   znaki,            // Data to be written to the port
                                   sizeof(znaki),   // No of bytes to write into the port
                                   &BytesWritten,  // No of bytes written to the port
                                   NULL);

                zmiennaklawiszydown=false;
            }

            //strncpy(jasnosc,znaki, 1);
            SetWindowText(hWndExample, znaki);
            break;
        case 0x47://g

            SendMessageW(LEWO_MAP,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)LEWO_MAP_IMAGE_ZIEL);
            znaki[0]='0';
            znaki[1]='2';

            if(zmiennaklawiszhdown==false)
            {
                znaki[0]='0';
                znaki[1]='1';

            }
            if(zmiennaklawiszgdown==true)
            {

                Status = WriteFile(hComm,// Handle to the Serialport
                                   znaki,            // Data to be written to the port
                                   sizeof(znaki),   // No of bytes to write into the port
                                   &BytesWritten,  // No of bytes written to the port
                                   NULL);


                zmiennaklawiszgdown=false;

            }
            SetWindowText(hWndExample, znaki);
            break;

        case 0x48://h
            SendMessageW(TYL_MAP,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)TYL_MAP_IMAGE_ZIEL);
            znaki[1]='1';
            znaki[0]='1';
            if(zmiennaklawiszhdown==true)
            {
                Status = WriteFile(hComm,// Handle to the Serialport
                                   znaki,            // Data to be written to the port
                                   sizeof(znaki),   // No of bytes to write into the port
                                   &BytesWritten,  // No of bytes written to the port
                                   NULL);
                zmiennaklawiszhdown=false;
            }
            SetWindowText(hWndExample, znaki);
            break;

        case 0x4A ://j
            SendMessageW(PRAWO_MAP,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)PRAWO_MAP_IMAGE_ZIEL);
            znaki[0]='2';
            znaki[1]='0';
            if(zmiennaklawiszhdown==false)
            {
                znaki[0]='1';
                znaki[1]='0';

            }
            if(zmiennaklawiszjdown==true)
            {
                Status = WriteFile(hComm,// Handle to the Serialport
                                   znaki,            // Data to be written to the port
                                   sizeof(znaki),   // No of bytes to write into the port
                                   &BytesWritten,  // No of bytes written to the port
                                   NULL);
                zmiennaklawiszjdown=false;
            }
            SetWindowText(hWndExample, znaki);

            break;

        }
    }
    break;


    case WM_CLOSE:
        DestroyWindow( hwnd );
        break;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;

    default:
        return DefWindowProc( hwnd, msg, wParam, lParam );

    }
    return 0;
}

void CreateControls(HWND hwnd)
{
    hlbl = CreateWindowW(L"Static", L"9", WS_CHILD | WS_VISIBLE,
       400, 350, 30, 30, hwnd, (HMENU)3, NULL, NULL);//napis

    INITCOMMONCONTROLSEX icex;

    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC  = ICC_LISTVIEW_CLASSES;
//    InitCommonControlsEx(&icex);

    hTrack = CreateWindowW(TRACKBAR_CLASSW, L"Trackbar Control",
                           WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
                           150, 350, 170, 30, hwnd, (HMENU) 3, NULL, NULL);

    SendMessageW(hTrack, TBM_SETRANGE,  TRUE, MAKELONG(0, 9));
    SendMessageW(hTrack, TBM_SETPAGESIZE, 0,  1);
    SendMessageW(hTrack, TBM_SETTICFREQ, 1, 0);
    SendMessageW(hTrack, TBM_SETPOS, TRUE, 9);



}
char buf[1]= {9};
void UpdateLabel(void)
{

    LRESULT pos = SendMessageW(hTrack, TBM_GETPOS, 0, 0);

    wsprintfW(buf, L"%ld", pos);
    strncpy(jasnosc,buf, 1);// kopiowanie
    // SetWindowText(hWndExample, znaki[2]);
    SetWindowTextW(hlbl, buf);
    SetFocus(hwnd);
}
