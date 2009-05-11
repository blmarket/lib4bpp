#include <d3d9.h>
#include <d3dx9.h>

struct Vertex
{
	union
	{
		D3DVECTOR position;
		float x,y,z;
	};
	union
	{
		D3DVECTOR normal;
		float nx,ny,nz;
	};
	DWORD color;
	FLOAT tu,tv;

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 };
};