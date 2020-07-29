#pragma once
#define BONESMAX 100
#define INSTANCEMAX 10

#include<memory>
//#include<SpriteBatch.h>
//#include<SpriteFont.h>



struct INSTANCEBUFFER
{
	XMFLOAT4X4  Instanceworld;
	XMFLOAT4X4 BoneMarix[BONESMAX];
	int BoneSwitch[4];
};
// 頂点構造体
struct VERTEX_3D
{
    XMFLOAT3 Position;
    XMFLOAT3 Normal;
    XMFLOAT4 Diffuse;
    XMFLOAT2 TexCoord;
	
};
struct BonesVertex
{
	XMFLOAT3 Position;
	XMFLOAT3 Normal;
	XMFLOAT2 TexCoord;

	UINT boneID[4] = { 0,0,0,0 };
	float boneweights[4] = { 0.0f,0.0f,0.0f,0.0f };
	void AddBoneDatas(UINT BoneIDs, float BoneWeights)
	{
		for (int index = 0; index < 4; index++)
		{
			if (boneweights[index] == 0.0f)
			{
				boneID[index] = BoneIDs;
				boneweights[index] = BoneWeights;
				return;
			}
		}
	}
};
struct SkinBoneDate
{
	XMFLOAT3 Position;
	XMFLOAT3 Normal;
	XMFLOAT4 Diffuse;
	XMFLOAT2 TexCoord;

	UINT BoneID[4] = {0,0,0,0};
	float BoneWeight[4] = { 0,0,0,0 };
	void AddBoneData(UINT BoneIDs, float Weights);
};

struct VERTEX_Model
{
	XMFLOAT3 Position;
	XMFLOAT3 Normal;
	XMFLOAT2 TexCoord;
	XMFLOAT4 Kd;
	XMFLOAT4 Diffuse;
};


// 色構造体
struct COLOR
{
	COLOR(){}
	COLOR( float _r, float _g, float _b, float _a )
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	float r;
	float g;
	float b;
	float a;
};

// マテリアル構造体
struct MATERIAL
{
	COLOR		Ambient;
	COLOR		Diffuse;
	COLOR		Specular;
	COLOR		Emission;
	float		Shininess;
	float		Dummy[3];//16bit境界用
};




// マテリアル構造体
struct DX11_MODEL_MATERIAL
{
	MATERIAL		Material;
	class CTexture*	Texture;
};


// 描画サブセット構造体
struct DX11_SUBSET
{
	unsigned short	StartIndex;
	unsigned short	IndexNum;
	DX11_MODEL_MATERIAL	Material;
};

struct LIGHT
{
	XMFLOAT4	Direction;
	COLOR		Diffuse;
	COLOR		Ambient;
	XMFLOAT4 Specular;
	XMFLOAT4X4 View;
	XMFLOAT4X4 Pro;
	XMFLOAT4 CameraPos;

};
struct POINTLIGHT
{
	XMFLOAT3 position;
	float constant;
	XMFLOAT3 ambient;
	float linear;
	XMFLOAT3 diffuse;
	float quadratic;
	XMFLOAT4 specular;
};
struct SpotlLight
{
	XMFLOAT3 position;
	float cutOff;

	XMFLOAT3 direction;
	float outerCutOff;


	XMFLOAT3 ambient;
	float constant;

	XMFLOAT3 diffuse;
	float Linear;

	XMFLOAT3 specular;
	float quadratic;

};
struct FINALMATRIX
{
	XMMATRIX	FMatrix[256];
};

//class CVertexBuffer;
//class CIndexBuffer;
class CTexture;


class CRenderer
{
private:

	//state baochun

	static ID3D11SamplerState* PSS;
	static ID3D11BlendState* pBs;
	static ID3D11RasterizerState* pRs;
	//end

	static D3D_FEATURE_LEVEL       m_FeatureLevel;

	static ID3D11Device*           m_D3DDevice;
	static ID3D11DeviceContext*    m_ImmediateContext;//这个ID3D11DeviceContext接口实现一个设备上下文生成渲染命令。
	static IDXGISwapChain*         m_SwapChain;
	static ID3D11RenderTargetView* m_RenderTargetView;
	static ID3D11DepthStencilView* m_DepthStencilView;



	static ID3D11VertexShader*     m_VertexShader;
	static ID3D11PixelShader*      m_PixelShader;
	static ID3D11PixelShader*     m_UIshader;
	static ID3D11InputLayout*      m_VertexLayout;

	//buffer
	static ID3D11Buffer*			m_WorldBuffer;
	static ID3D11Buffer*			m_ViewBuffer;
	static ID3D11Buffer*			m_ProjectionBuffer;
	static ID3D11Buffer*			m_MaterialBuffer;
	static ID3D11Buffer*			m_LightBuffer;
	static ID3D11Buffer*			m_SpotBuffer;
	static ID3D11Buffer*			m_pointLightBuffer;
	static ID3D11Buffer*			m_BonesBuffer;
	//gutou
	static ID3D11VertexShader*		  m_boneShader;
	static ID3D11InputLayout*		m_boneLayout;
	static ID3D11Buffer*			m_CBBoneTranform;
	//
	static ID3D11Buffer*			m_WeaponBoneBuffer;
	static ID3D11InputLayout*  m_WeaPonBoneLayout;
	static ID3D11VertexShader* m_WeaponBoneShader;
	//biliiborede
	static ID3D11VertexShader* m_InstanceVSshader;
	static ID3D11InputLayout* m_InstanceLayout;
	static ID3D11Buffer*			m_InstanceBuffer;

	//Instanceanim
	static ID3D11Buffer*			m_InstanceBuffer_anim;

/*
	static XMMATRIX				m_WorldMatrix;
	static XMMATRIX				m_ViewMatrix;
	static XMMATRIX				m_ProjectionMatrix;
*/
	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;

	//shadow
	//new
	static ID3D11DepthStencilView* m_ShadowDepth;
	static ID3D11ShaderResourceView* m_ShadowResource;
	static ID3D11VertexShader*     m_ShadowVShader;
	static ID3D11PixelShader*      m_ShadowPShader;
	static ID3D11InputLayout*      m_ShadowLayout;
	

	static void SetShadowShadow(const char* VSname, const char* PSname);


public:
	//"pixelShader.cso"
	static void Init(const char* mainVs,const char* mianPs);
	static void SetNewVSshader(const char * Vs);
	//static void SetNewPSshader(const char* Ps);
	static void Uninit();
	static void Begin();
	static void End();
	static void BeiginShadow();
	static void SetShadowTex(int num);
	

	static std::unique_ptr<SpriteBatch> spritebich;
	static std::unique_ptr<SpriteFont> spritefont;

	static void SetDepthEnable(bool Enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(XMMATRIX * WorldMatrix);
	static void SetWorldMatrixTranspose(XMMATRIX* WorldMatrix);
	static void SetViewMatrix(XMMATRIX * ViewMatrix);
	static void SetProjectionMatrix(XMMATRIX * ProjectionMatrix);
	static void SetFinalMatrix(FINALMATRIX Finalmatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light);
	static void SetSpotLight(SpotlLight Light);
	static void SetPointLight(POINTLIGHT Light);
	static void SetVertexBuffers( ID3D11Buffer* VertexBuffer );
	static void SetBoneVertexBuffers(ID3D11Buffer* VertexBuffer);
	static void SetIndexBuffer( ID3D11Buffer* IndexBuffer );
	static void SetTexture( CTexture* Texture );
	static void SetTexture2(ID3D11ShaderResourceView* srvs);
	static void SetTextureIndex(CTexture* Texture, int texture);
	static void SetTextureJPGPNG(CTexture* Texture, int texture);
	static void DrawIndexed( unsigned int IndexCount, unsigned int StartIndexLocation, int BaseVertexLocation );

	static void SetWeponBone(XMFLOAT4X4 bonematrix);
	static void SetBones(std::vector<XMFLOAT4X4>& transforms);
	static void SetInstanceWorld(XMFLOAT4X4 world[]);
	static void SetInstanceAimWorld(INSTANCEBUFFER Sinstance[]);

	static ID3D11Device* GetDevice( void ){ return m_D3DDevice; }
	static ID3D11DeviceContext* GetDeviceContext( void ){ return m_ImmediateContext; }
	static ID3D11Buffer* GetBufferOfWorld(void) { return m_WorldBuffer; }
	static ID3D11Buffer* GetBufferofInstance(void) { return m_InstanceBuffer_anim; }

	static void BoneSL();
	static void BoneBack();
	static void ShadowDraw();
	static void ShadowEnd();
	static void WeaponBoneBegin();
	static void WeaponBoneBack();
	static void UIBegin();
	static void UIBack();
	static void DrawStringBack();
	static void InstanceBegin();
	static void InstanceEnd();
	static float DeBug_show_v3[3];
	static float Debug_show_v2[2];
	static float Debug_show_int[1];
	static float Debug_move_v3[3];
	static float Debug_move_v2[2];
	static float Debug_move_Rotation3[3];
	static float Debug_move_Rotation2[2];
	static float LightMove3_0[3];
	static float LightMove3_1[3];
	static float LightMove3_2[3];
	static float LightMove3_3[3];
	static float LightMove3_4[3];
	static float LightMove1_0[1];
	static float LightMove1_1[1];
	static float LightMove1_2[1];
	static float LightMove1_3[1];
	static float LightMove1_4[1];

	static float values[12];
	static float values2[12];
	static bool RunSwtichForZombie;
	static	std::vector<STRINGDRAW> Vstring;

};
