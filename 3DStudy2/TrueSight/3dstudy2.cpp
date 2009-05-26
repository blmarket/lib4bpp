#include <vector>
#include <ctime>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9shape.h>
#include <sstream>
#include <iostream>
#include "DxLibs.h"
#include "Vertex.h"

float g_phi = 0.5f;
float g_theta = 0.0f;

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;

        case WM_PAINT:			
            ValidateRect( hWnd, NULL );
            return 0;

		case WM_KEYDOWN:
			switch(wParam)
			{
			case 'R':
				g_phi = g_theta = 0.0f;
				break;
			case VK_DOWN:
				g_phi -= 0.1f;
				if(g_phi < -D3DX_PI / 2.0f + 0.1f)
					g_phi = -D3DX_PI / 2.0f + 0.1f;
				break;
			case VK_UP:
				g_phi += 0.1f;
				if(g_phi > D3DX_PI / 2.0f - 0.1f)
					g_phi = D3DX_PI / 2.0f - 0.1f;
				break;
			case VK_LEFT:
				g_theta -= 0.1f;
				break;
			case VK_RIGHT:
				g_theta += 0.1f;
				break;
			};
			return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}

INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
		L"Study 3D 2", NULL
    };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( L"Study 3D 2", L"Study 3D 2 - Draw Rectangle",
                              WS_OVERLAPPEDWINDOW, 100, 100, 800, 800,
                              NULL, NULL, wc.hInstance, NULL );

	try
	{
		DxLibs dxlibs(hWnd);

		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);

		MSG msg;
		ZeroMemory(&msg, sizeof(MSG) );
		while(msg.message != WM_QUIT || msg.message != WM_DESTROY)
		{
			if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			else
				dxlibs.Render();
		}
	} 
	catch( std::runtime_error &err )
	{
		MessageBox(hWnd, L"Initialization of DirectX 9 has failed", L"Error", MB_OK);
		return -1;
	}

	UnregisterClass( L"Study 3D 2", wc.hInstance );
	return 0;
}