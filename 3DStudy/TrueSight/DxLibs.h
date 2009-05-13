#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

class DxLibs
{
public:
	DxLibs(HWND hWnd);
	virtual ~DxLibs();

	void Render();

	LPDIRECT3D9			m_pD3d;
	LPDIRECT3DDEVICE9	m_pDevice;
};