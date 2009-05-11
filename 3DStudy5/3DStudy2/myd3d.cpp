#include "myd3d.h"
#include <d3d9.h>

HRESULT InitD3D( HWND hWnd, LPDIRECT3D9 &d3d9, LPDIRECT3DDEVICE9 &device)
{
    // Create the D3D object, which is needed to create the D3DDevice.
    if( NULL == ( d3d9 = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

	D3DCAPS9 Caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &Caps);

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    // depth ���� ����
	d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    if( FAILED( d3d9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &device ) ) )
        return E_FAIL;

	// device�� alpha blending ��� ����
	device->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	// �� ó���� �ϴ� ���߿�
	device->SetRenderState( D3DRS_LIGHTING, FALSE );
	device->SetRenderState( D3DRS_AMBIENT, 0x00606060 );

	// �ϴ� �� �׸�����
	device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // z-buffer ���
	device->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );
	device->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
	device->SetRenderState( D3DRS_ALPHAREF, 0x00000080 );
	device->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );

	//device->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1 );

	return S_OK;
}