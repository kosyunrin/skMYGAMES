

//*****************************************************************************
// 定数バッファ
//*****************************************************************************

// マトリクスバッファ
cbuffer WorldBuffer : register(b0)
{
    matrix World;
}
cbuffer ViewBuffer : register(b1)
{
    matrix View;
}
cbuffer ProjectionBuffer : register(b2)
{
    matrix Projection;
}

// マテリアルバッファ
struct MATERIAL
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float4 Emission;
    float Shininess;
    float3 Dummy; //16bit境界用
};

cbuffer MaterialBuffer : register(b3)
{
    MATERIAL Material;
}


// ライトバッファ
struct LIGHT
{
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
    float4 Specular;
    float4x4 View;
    float4x4 Pro;
    float4 CameraPos;
};

cbuffer LightBuffer : register(b4)
{
    LIGHT Light;
}




//=============================================================================
// 頂点シェーダ
//=============================================================================

struct VertexIn
{
    float4 inPosition : POSITION0;
    float4 inNormal : NORMAL0;
    float4 inDiffuse : COLOR0;
    float2 inTexCoord : TEXCOORD0;
};

struct VertexOut
{
    float4 outPosition : SV_POSITION;
    float4 outWorldPos : POSITION1;
    float4 outNormal : NORMAL0;
    float2 outTexCoord : TEXCOORD0;
    float4 outDiffuse : COLOR0;
};

VertexOut VS(VertexIn In)
{
    VertexOut outdate=(VertexOut)0;
    
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);

    outdate.outPosition = mul(In.inPosition, wvp);
    outdate.outWorldPos = mul(In.inPosition, World);
    In.inNormal.w = 0.0;
    outdate.outNormal = normalize(mul(In.inNormal, World));
    outdate.outTexCoord = In.inTexCoord;
	
    outdate.outDiffuse = In.inDiffuse;
    
    //matrix lightwvp;
    //lightwvp = mul(World, Light.View);
    //lightwvp = mul(World, Light.Pro);
    //float4 shadowTexCoord = mul(In.inPosition, lightwvp);
    //outdate.outShadowCooord = shadowTexCoord;
    
    return outdate;
}
