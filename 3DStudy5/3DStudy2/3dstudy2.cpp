#include <vector>
#include <ctime>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9shape.h>
#include "myd3d.h"
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )

LPDIRECT3D9 g_d3d9 = NULL;
LPDIRECT3DDEVICE9 g_d3ddevice = NULL;
LPDIRECT3DTEXTURE9      g_pTexture = NULL, g_pAlphaTexture = NULL; // Our texture

LPDIRECT3DVERTEXBUFFER9 g_VB = NULL;
LPDIRECT3DINDEXBUFFER9 g_IB = NULL;
LPDIRECT3DVERTEXBUFFER9 g_VBBillboard = NULL, g_VBBillboard2 = NULL, g_VB3 = NULL, g_VB4 = NULL;

LPDIRECT3DVERTEXSHADER9 g_VShader;

std::vector<std::pair<float,float> > Vpos;

float g_phi = 0;
float g_theta = 0;

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE)

struct CustomVertex
{
	FLOAT x,y,z;
	FLOAT nx,ny,nz;
	DWORD color;
};

struct CustomVertex2
{
	FLOAT x,y,z,rhw;
	DWORD color;
	FLOAT tu,tv;

	enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1};
};

struct CustomVertex3
{
	FLOAT x,y,z;
	FLOAT nx,ny,nz;
	DWORD color;
	FLOAT tu,tv;

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 };
};

struct MYINDEX
{
	WORD _0,_1,_2;
};

HRESULT InitRectangles()
{
    // Use D3DX to create a texture from a file based image
    if( FAILED( D3DXCreateTextureFromFile( g_d3ddevice, L"thingrass0000.tga", &g_pTexture ) ) )
    {
        // If texture is not in current folder, try parent folder
        if( FAILED( D3DXCreateTextureFromFile( g_d3ddevice, L"..\\thingrass0000.tga", &g_pTexture ) ) )
        {
            MessageBox( NULL, L"Could not find banana.bmp", L"3study2.exe", MB_OK );
            return E_FAIL;
        }
    }

    // Use D3DX to create a texture from a file based image
    if( FAILED( D3DXCreateTextureFromFile( g_d3ddevice, L"bos_fairway.tga", &g_pAlphaTexture ) ) )
    {
        // If texture is not in current folder, try parent folder
        if( FAILED( D3DXCreateTextureFromFile( g_d3ddevice, L"..\\bos_fairway.tga", &g_pAlphaTexture ) ) )
        {
            MessageBox( NULL, L"Could not find banana.bmp", L"3study2.exe", MB_OK );
            return E_FAIL;
        }
    }



	MYINDEX indexes[] =
	{
/*		{0,1,2},{0,2,3},
		{4,6,5},{4,7,6},
		{0,3,7},{0,7,4},
		{1,5,6},{1,6,2},
		{3,2,6},{3,6,7},
		{0,4,5},{0,5,1},*/
		{0,2,4}, {0,2,5},
		{0,3,4}, {0,3,5},
		{1,2,4}, {1,2,5},
		{1,3,4}, {1,3,5},
	};

	CustomVertex vertices[] =
	{
/*		{-1,1,1,-1,1,1,0xff00ffff },
		{1,1,1,1,1,1,0xffff00ff },
		{1,1,-1,1,1,-1,0xffffff00 },
		{-1,1,-1,-1,1,-1,0xff0000ff },
		{-1,-1,1,-1,-1,1,0xff00ff00 },
		{1,-1,1,1,-1,1,0xffff0000 },
		{1,-1,-1,1,-1,-1,0xffffffff },
		{-1,-1,-1,-1,-1,-1,0xff000000 },*/
		{ -1,0,0, -1,0,0, 0xffff0000 },
		{ 1,0,0, 1,0,0, 0xff00ffff },
		{ 0,1,0, 0,1,0, 0xff00ff00 },
		{ 0,-1,0, 0,-1,0, 0xff0000ff },
		{ 0,0,1, 0,0,1, 0xffff00ff },
		{ 0,0,-1, 0,0,-1, 0xffffffff },
	};

	int vn = sizeof(vertices) / sizeof(CustomVertex);

	if( FAILED( g_d3ddevice->CreateVertexBuffer(vn * sizeof(CustomVertex) ,0,D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_VB, NULL) ) )
		return E_FAIL;

	VOID *pData;
	
	if( FAILED( g_VB->Lock(0,sizeof(vertices),&pData, 0)))
		return E_FAIL;

	memcpy(pData, vertices, sizeof(vertices) );

	g_VB->Unlock();

	int in = sizeof(indexes) / sizeof(MYINDEX);

	if( FAILED( g_d3ddevice->CreateIndexBuffer(in * sizeof(MYINDEX),0,D3DFMT_INDEX16,D3DPOOL_DEFAULT,&g_IB,NULL)))
		return E_FAIL;

	if( FAILED( g_IB->Lock(0,sizeof(indexes),&pData, 0)))
		return E_FAIL;

	memcpy(pData, indexes, sizeof(indexes) );	

	g_IB->Unlock();

	CustomVertex Billboard[] =
	{
		{-1,-1,0,0,0,1, 0xffffffff},
		{-1,1,0,0,0,1, 0xffffffff },
		{1,1,0,0,0,1, 0xffffffff  },
		{-1,-1,0,0,0,1, 0xffffffff},
		{1,1,0,0,0,1, 0xffffffff  },
		{1,-1,0,0,0,1, 0xffffffff },
	};

	vn = sizeof(Billboard) / sizeof(CustomVertex);
	if( FAILED( g_d3ddevice->CreateVertexBuffer(vn * sizeof(CustomVertex),0, D3DFVF_CUSTOMVERTEX ,D3DPOOL_DEFAULT, &g_VBBillboard, NULL) ) )
		return E_FAIL;

	if( FAILED( g_VBBillboard->Lock(0,sizeof(Billboard),&pData,0) ) )
		return E_FAIL;

	memcpy(pData, Billboard, sizeof(Billboard) );

	g_VBBillboard->Unlock();

	CustomVertex2 Billboard2[] = {
		{110,100,0,1,0xffffffff, 1,1 },
		{400,100,0,1,0xffffffff, 1,0 },
		{400,390,0,1,0xffffffff, 0,0 },
		{110,100,0,1,0xffffffff, 1,1 },
		{400,390,0,1,0xffffffff, 0,0 },
		{110,390,0,1,0xffffffff, 0,1 },
	};

	vn = sizeof(Billboard2) / sizeof(CustomVertex2);
	if( FAILED( g_d3ddevice->CreateVertexBuffer(vn * sizeof(CustomVertex2) , 0 , CustomVertex2::FVF, D3DPOOL_DEFAULT, &g_VBBillboard2, NULL ) ) )
		return E_FAIL;

	if( FAILED( g_VBBillboard2->Lock(0, sizeof(Billboard2), &pData,0 ) ) )
		return E_FAIL;

	memcpy(pData, Billboard2, sizeof(Billboard2));

	g_VBBillboard2->Unlock();

	CustomVertex3 Billboard3[] =
	{
		{-1,-1,0,0,0,1, 0xffffffff ,0,1},
		{-1,1,0,0,0,1, 0xffffffff , 1,1},
		{1,1,0,0,0,1, 0xffffffff  , 1,0},
		{-1,-1,0,0,0,1, 0xffffffff ,0,1},
		{1,1,0,0,0,1, 0xffffffff   ,1,0},
		{1,-1,0,0,0,1, 0xffffffff  ,0,0},
		{-1,-1,0,0,0,1, 0xffffffff ,0,1},
		{-1,1,0,0,0,1, 0xffffffff , 1,1},
		{1,1,0,0,0,1, 0xffffffff  , 1,0},
		{-1,-1,0,0,0,1, 0xffffffff ,0,1},
		{1,1,0,0,0,1, 0xffffffff   ,1,0},
		{1,-1,0,0,0,1, 0xffffffff  ,0,0},
	};

	vn = sizeof(Billboard3) / sizeof(CustomVertex3);
	if( FAILED( g_d3ddevice->CreateVertexBuffer(vn * sizeof(CustomVertex3), 0, CustomVertex3::FVF, D3DPOOL_DEFAULT, &g_VB3, NULL) ) )
		return E_FAIL;

	if( FAILED( g_VB3->Lock(0, sizeof(Billboard3), &pData, 0 ) ) )
		return E_FAIL;

	memcpy(pData, Billboard3, sizeof(Billboard3) );

	g_VB3->Unlock();

	CustomVertex3 Ground[] =
	{
		{-10,0,-10, 0,1,0, 0xffffffff ,0,0},
		{-10,0,10, 0,1,0, 0xffffffff ,0,1},
		{10,0,10, 0,1,0, 0xffffffff ,1,1},
		{-10,0,-10, 0,1,0, 0xffffffff ,0,0},
		{10,0,10, 0,1,0, 0xffffffff ,1,1},
		{10,0,-10, 0,1,0, 0xffffffff ,1,0},
	};

	vn = sizeof(Ground) / sizeof(CustomVertex3);
	if( FAILED( g_d3ddevice->CreateVertexBuffer(vn * sizeof(CustomVertex3),0,CustomVertex3::FVF, D3DPOOL_DEFAULT, &g_VB4, NULL) ) )
		return E_FAIL;

	if( FAILED( g_VB4->Lock(0, sizeof(Ground), &pData, 0 ) ) )
		return E_FAIL;

	memcpy(pData, Ground, sizeof(Ground) );

	g_VB4->Unlock();

	return S_OK;
}

HRESULT AddMotion(void)
{
	CustomVertex3 Billboard3[] =
	{
		{-1,0,0,0,0,1, 0xffffffff , 0,1},
		{-1,1,0,0,0,1, 0xffffffff , 0,0},
		{ 1,1,0,0,0,1, 0xffffffff , 1,0},
		{-1,0,0,0,0,1, 0xffffffff , 0,1},
		{1 ,1,0,0,0,1, 0xffffffff  ,1,0},
		{1 ,0,0,0,0,1, 0xffffffff  ,1,1},

		
		{0,0,-1,0,0,1, 0xffffffff ,0.5,1},
		{0,1,-1,0,0,1, 0xffffffff , 1,1},
		{0,1,1,0,0,1, 0xffffffff  , 1,0},
		{0,0,-1,0,0,1, 0xffffffff ,0.5,1},
		{0,1,1,0,0,1, 0xffffffff   ,1,0},
		{0,0,1,0,0,1, 0xffffffff  ,0.5,0},
	};

	UINT iTime = timeGetTime() % 10000;
	FLOAT fAngle = iTime * ( 2.0f * D3DX_PI ) / 10000.0f;

	float xdiff,ydiff;
	xdiff = 0.2f * sinf(fAngle) + 0.2f;
	ydiff = 0.1f * cosf(fAngle);


	Billboard3[1].x += xdiff;
	Billboard3[1].y += ydiff;
	Billboard3[2].x += xdiff;
	Billboard3[2].y += ydiff;
	Billboard3[4].x += xdiff;
	Billboard3[4].y += ydiff;

/*
	Billboard3[7].x += xdiff;
	Billboard3[7].z += zdiff;
	Billboard3[8].x += xdiff;
	Billboard3[8].z += zdiff;
	Billboard3[10].x += xdiff;
	Billboard3[10].z += zdiff;
*/
	VOID *pData;

	if( FAILED( g_VB3->Lock(0, sizeof(Billboard3), &pData, 0 ) ) )
		return E_FAIL;

	memcpy(pData, Billboard3, sizeof(Billboard3) );

	g_VB3->Unlock();

	return S_OK;
}

void Cleanup(void)
{
	if(g_VB != NULL)
		g_VB->Release();

	// 텍스쳐 해제
	if(g_pTexture != NULL)
		g_pTexture->Release();

	// 디바이스 해제
	if(g_d3ddevice != NULL)
		g_d3ddevice->Release();

	// D3D9 해제
	if(g_d3d9 != NULL)
		g_d3d9->Release();
}

VOID SetupMatrices()
{
    // For our world matrix, we will just rotate the object about the y-axis.
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_d3ddevice->SetTransform( D3DTS_WORLD, &matWorld);

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the
    // origin, and define "up" to be in the y-direction.
	UINT iTime = timeGetTime() % 1000;
	FLOAT fAngle = iTime * ( 2.0f * D3DX_PI ) / 1000.0f;

    D3DXMATRIXA16 matView;
	D3DXVECTOR3 vEyePt( 10.0f * cosf(g_phi) * sinf(g_theta) , 10.0f * sinf(g_phi) , -10.0f * cosf(g_phi) * cosf(g_theta));
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    g_d3ddevice->SetTransform( D3DTS_VIEW, &matView );

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 0.1f, 100.0f );
    g_d3ddevice->SetTransform( D3DTS_PROJECTION, &matProj );

/*
	Viewport 설정은 기본값을 그대로 사용한다 치자
	D3DVIEWPORT9 vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width  = 800;
	vp.Height = 800;
	vp.MinZ   = 0.0f;
	vp.MaxZ   = 10.0f;
	g_d3ddevice->SetViewport(&vp);
*/
}

HRESULT Render(void)
{
	// 배경 및 Z-Buffer 상태 지우기
	g_d3ddevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0f, 0 );

	if( SUCCEEDED( g_d3ddevice->BeginScene() ) )
	{
		// 그리기 시작
		SetupMatrices();

		D3DXMATRIXA16 matWorld, matTemp, matView;

		// texture 설정
		g_d3ddevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1 );
		g_d3ddevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		g_d3ddevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );
		g_d3ddevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		g_d3ddevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU );
		
		g_d3ddevice->SetTexture(0, g_pAlphaTexture );
		g_d3ddevice->SetStreamSource(0, g_VB4, 0, sizeof(CustomVertex3) );
		g_d3ddevice->SetFVF(CustomVertex3::FVF);
		D3DXMatrixIdentity( &matWorld );
		g_d3ddevice->SetTransform( D3DTS_WORLD, &matWorld );
		g_d3ddevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2 );

		AddMotion();

		g_d3ddevice->SetTexture(0, g_pTexture);
		g_d3ddevice->SetStreamSource(0, g_VB3, 0, sizeof(CustomVertex3) );
		g_d3ddevice->SetFVF(CustomVertex3::FVF);

		for(size_t i=0;i<Vpos.size();i++)
		{
			D3DXMatrixIdentity( &matWorld );
			g_d3ddevice->GetTransform( D3DTS_VIEW, &matView );
			matWorld._11 = matView._11;
			matWorld._13 = matView._13;
			matWorld._31 = matView._31;
			matWorld._33 = matView._33;
			D3DXMatrixTranslation( &matTemp , (float)Vpos[i].first, 0.0f, (float)Vpos[i].second);
			D3DXMatrixMultiply( &matWorld, &matTemp, &matWorld );
			D3DXMatrixInverse( &matWorld, NULL, &matWorld );

			g_d3ddevice->SetTransform( D3DTS_WORLD, &matWorld );
			
			g_d3ddevice->DrawPrimitive(D3DPT_TRIANGLELIST,0,2);

/*				D3DXMatrixRotationY( &matWorld, D3DX_PI / 3.0f);
			D3DXMatrixMultiply( &matWorld, &matWorld, &matTemp );
			g_d3ddevice->SetTransform( D3DTS_WORLD, &matWorld );
			g_d3ddevice->DrawPrimitive(D3DPT_TRIANGLELIST,0,2);

			D3DXMatrixRotationY( &matWorld, -D3DX_PI / 3.0f);
			D3DXMatrixMultiply( &matWorld, &matWorld, &matTemp );
			g_d3ddevice->SetTransform( D3DTS_WORLD, &matWorld );
			g_d3ddevice->DrawPrimitive(D3DPT_TRIANGLELIST,0,2);*/
		}

		g_d3ddevice->EndScene();
	}
	g_d3ddevice->Present(NULL, NULL, NULL, NULL);

	return S_OK;

}

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
            return 0;

        case WM_PAINT:
            Render();
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

	srand((unsigned int)time(NULL));

	for(int i=0;i<5000;i++)
	{
		float x = (float)(rand() % 2000) / 100.0f - 10.0f;
		float y = (float)(rand() % 2000) / 100.0f - 10.0f;
		Vpos.push_back(std::make_pair(x,y));
	}	
	
	if( SUCCEEDED( InitD3D( hWnd, g_d3d9, g_d3ddevice )) && SUCCEEDED( InitRectangles() ) )
	{
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);


		MSG msg;
		ZeroMemory(&msg, sizeof(MSG) );
		while(msg.message != WM_QUIT)
		{
			if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			else
				Render();
		}
	}

	
	UnregisterClass( L"Study 3D 2", wc.hInstance );
	return 0;
}