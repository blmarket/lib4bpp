#include "DxLibs.h"
#include <stdexcept>
#include <cassert>

DxLibs::DxLibs(HWND hWnd)
{
    // Create the D3D object, which is needed to create the D3DDevice.
    if( NULL == ( m_pD3d = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		throw std::runtime_error("Init D3D Failed");

	D3DCAPS9 Caps;
	m_pD3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &Caps);

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    // depth 버퍼 설정
	d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    if( FAILED( m_pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &m_pDevice ) ) )
		throw std::runtime_error("Init D3D Device Failed");

	// device의 alpha blending 기능 설정
	m_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	m_pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	// 빛 처리는 일단 나중에
	m_pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00606060 );

	// 일단 다 그리도록
	m_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // z-buffer 사용
	m_pDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );
	m_pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
	m_pDevice->SetRenderState( D3DRS_ALPHAREF, 0x00000080 );
	m_pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );

	//m_pDevice->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1 );
}

DxLibs::~DxLibs()
{
	assert( m_pDevice != NULL && m_pD3d != NULL );
	m_pDevice->Release();
	m_pD3d->Release();
}

void DxLibs::Render(void)
{
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0f, 0 );
	if( SUCCEEDED( m_pDevice->BeginScene() ) )
	{
		m_pDevice->EndScene();
	}
	m_pDevice->Present(NULL, NULL, NULL, NULL);
}