#ifndef __TERRAINGRASS_H_
#define __TERRAINGRASS_H_


#include "animations.h"
#include "THGridResource.h"
#include "DXWrap\EffectGroup.h"
#include <vector>

class CRData;


/**************************************************************/
// VBResource class - Shared vertex and index buffers
/**************************************************************/

class TerrainGrass;

class VBResource// : public CDeviceResource
{
public:
	VBResource (TerrainGrass * pGrassEffect, DWORD totalBlades, DWORD polys_per_blade);
	virtual ~VBResource();
	bool CreateGrassIndexBuffer(DWORD num_blades);//Works on the m_pGrassEffect to create the GrassIndexBuffer.
	bool CreateGrassVertexBuffers(DWORD num_blades);//Works on the m_pGrassEffect to create the GrassVertexBuffers.
	bool Matches (TerrainGrass * pGrassEffect);
	bool Succeeded () {return m_bSuccess;}

	//These are virtual functions from the CDeviceResource class.
	//They are used to handle alt-tab functionality.
	//HRESULT RestoreDeviceObjects();
 // HRESULT InvalidateDeviceObjects();

public:
	TerrainGrass * m_pGrassEffect;

	CVertexBuffer * m_pVBuffer;
	CIndexBuffer m_pIBuffer;

	bool m_bSuccess;
};



/**************************************************************/
// TerrainGrass class - draws a seemingly ubiquitous grass effect
/**************************************************************/

struct GrassPatchInfoS
{
	CVector3			m_pos;					//position of the grass patch
	bool				m_bDraw;				//do we need to draw this patch
	bool				m_bDrawPartial;			//do we need to draw this patch for clipping purposes
	DWORD				m_iPatchInd;			//starting blade index in the vertex buffer
	DWORD				m_dwColor;				//color and alpha
	WORD				m_wBladeCount;			//blade count in this patch
	float				m_fCamDist;				//the distance to the camera
	OcclusionQueryState	m_QueryState;			//State of the occlusion query
	float				m_miny, m_maxy;

	GrassPatchInfoS () {memset (this, 0, sizeof(GrassPatchInfoS));}
};

struct PatchTableEntryS
{
	short id;
	BYTE alpha;
};

#define MAX_BUFFERS			3



class _LIBFUNC TerrainGrass : public Animation, public CDeviceResource, public GridMoveHandler
{
public:
							TerrainGrass ();
							~TerrainGrass ();
	virtual const CRect&	Draw (Animator* animator);
	virtual bool			NextFrame (float dtime);

	//This function MUST be called FIRST!
	void					InitLowLODOnly (bool b) {m_bLowLODOnly = b;}
	bool					IsLowLODOnly () {return m_bLowLODOnly;}
	void					InitPatchType (int i) {m_PatchType = i;}
	int						GetPatchType () {return m_PatchType;}
	//This function MUST be called before InitBlades
	void					InitClustering (int clusterMin, int clusterMax);
	//This function MUST be called before InitBlades
	void					InitBladeShape (float midMin, float midMax, float topMin, float topMax);
	//Creates the blades in the vertex buffer
	void					InitBlades (float width, float height, int polysPerBlade);
	void					SetupGrassGrid (DWORD terrainID, DWORD gridwidth, DWORD spacing, int bladesPerPatch);
	void					SetupGrassLODs (float highlodDist, float medlodDist, float minDensity, float fallOff, float lowLODDensity);
	int						GetTerrainID() const {return m_iTerrainID;}
	void					ForceUpdate();
	void					InvalidateGrassGrid();
	//Loads the grass effect texture for this grid
	bool					LoadGrassEffectTexture(const char * fname);
	//Loads a noise texture for this grid
	bool					LoadGrassEffectNoiseTexture(BYTE * data, const char * fname);
	// called on reset/resolution change
	virtual HRESULT			RestoreDeviceObjects();
	virtual HRESULT			InvalidateDeviceObjects();

	//static void UpdateGrassBladeLimits(int poly_per_blade, int num_blades);//Sets the new maximums for the grass.  Used in the PostLoadSetup() function.
	//static void PostLoadSetup();//This is stuff to be done after all the grass data has been loaded.
	static void				RenderTest( bool set );
	static void				ForceRender( bool set );
	static void				ResetHighestGridWidth();

	//Temporarily turns the grass off
	static void				DoDrawGrass( bool b );
	//turns on and off the shadow map for shading the grass
	static void				DoShadowMap( bool b );

	friend class VBResource;
protected:
	void					UpdateGridCells( GridMoveInfo &info );
	void					UpdateGridVisibility( CVector3 &camPos, CVector3 &camDir, float dirX, float dirZ );
	void					RenderClippingTexture();
	void					DrawPatchEffect( GrassPatchInfoS & patch, int patchIndex, int lod, CVector3 & windVct, float windExp, float windYFactor );
	inline bool				IsPatchVisible( Render3D *render, GrassPatchInfoS & patch, CVector3 *bbox );

protected:
	//Grass patches
	GrassPatchInfoS						*m_pGrassGrid;	
	GrassPatchInfoS						*m_pHighDefGrassGrid;
	PatchTableEntryS					*m_LODPatchTable[MAX_BUFFERS];

	//Shared resources
	THGridResource*						m_pTHGrid;
	static std::vector<VBResource*>		s_VBResourceList;
	VBResource*							m_pVBResource;
	static DWORD						s_cReference;
	DWORD								m_cFrame;

	//grass parameters
	DWORD								m_wBladesPerPatch;
	int									m_iHighDefGridWidth;
	float								m_fHighDefGridSpacing;
	bool								m_bLowLODOnly;
	int									m_PatchType;

	//blade parameters
	float								m_fGrassHeight;
	float								m_fGrassWidth;
	int									m_iVertsPerBlade;
	int									m_iPolysPerBlade;
	float								m_fBladeDensityMult; //retrieved from settings

	//blade shape parameters
	float								m_fMidDisplacementMin;
	float								m_fMidDisplacementMax;
	float								m_fTopDisplacementMin;
	float								m_fTopDisplacementMax;

	//clustering parameters
	int									m_iClusterMin;
	int									m_iClusterMax;

	//lod control parameters
	float								m_fMinDensity;
	float								m_fFallOff;
	float								m_fLowLODDensity;
	float								m_fLODDists[MAX_BUFFERS];
	int									m_iVertsPerBladeMedLOD;

	//misc
	DWORD								m_dwGrassVersion;
	DWORD								m_dwNumBlades;
	int									m_iTerrainID;
	bool								m_bAnyPatchesToRender;
	bool								m_bForceClipRender;
	short								m_dwClipTexSize;
	CRData*								mCRDataPtr;

	DWORD								m_dwCurShader;	
	bool								m_b30Shader;

	//for detecting camera movement
	CVector3							lastCamDir;
	CVector3							lastCamPos;
	float								lastZoom;
	float								lastLetterBox;
	bool								m_bGridChanged;

	//current world bounds of the grid
	CVector3							m_GridMin;
	CVector3							m_GridMax;

	//clipping texture
	CachableTextureC					*m_pClippingTexture;
	CDirectDrawSurface8					m_pClippingSurface, m_pZSurface;

	//textures
	CachableTextureC					*m_pTexture;
	CachableTextureC					*m_pNoiseTexture;
	CSize								mDensityTexSize;

	//variables just used for the render test
	static bool							s_bRenderTest;
	static bool							s_bForceRender;
	bool								m_bOldRenderTest;
	bool								m_bOldForceRender;
	static int							s_HighestGridWidth;
	static int							s_RenderTestGridID;

	//static variable for turning off the grass temporarily
	static bool							s_bDoDrawGrass;

	//static variable for using the shadow map to shade the grass
	static bool							s_bDoShadows;


	//Grass effect shader
	static EffectGroup *					m_pEffect;
	static D3DXHANDLE						m_grass_technique30;
	static D3DXHANDLE						m_grass_technique11;
	static D3DXHANDLE						m_grass_technique11WithNoise;
	static D3DXHANDLE						m_grass_technique11Low;
	static D3DXHANDLE						m_grass_technique11WithNoiseLow;
	static D3DXHANDLE						m_clip_technique11; 
	static D3DXHANDLE						m_clip_technique14;
	static D3DXHANDLE						m_clip_techniqueFF;
	static IDirect3DVertexDeclaration9*		m_pVertDecl;
	static IDirect3DVertexDeclaration9*		m_pVertDeclLow;

	const CRect&						RenderGrassEffect (Animator* animator);
	void								RenderAllPatches(Render3D * render);
};



#endif