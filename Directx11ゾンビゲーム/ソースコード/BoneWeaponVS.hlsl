
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
cbuffer WeaponBoneBuffer : register(b10)
{
    float4x4 WeaPonMatrix;
}




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

VertexOut main(VertexIn In)
{
    VertexOut output = (VertexOut) 0;
 
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    float3 inpos = In.inPosition.xyz;
    matrix scal = (matrix) 0;
    scal._11 = 20.0f;
    scal._22 = 20.0f;
    scal._33 = 20.0f;
    inpos = mul(float4(inpos.xyz, 1.0f), scal);
    float4 pos = mul(float4(inpos.xyz, 1.0f), WeaPonMatrix);
    pos.w = 1.0;

    float4 nor = mul(float4(In.inNormal.xyz, 0.0f), WeaPonMatrix);
    nor.w = 0.0;

    output.outPosition = mul(pos, wvp);

    output.outNormal = normalize(mul(nor, World));
    output.outWorldPos = mul(pos, World);

    output.outDiffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);

    output.outTexCoord = In.inTexCoord;

    return output;
    
    
    //VertexOut outdate = (VertexOut) 0;
    
    //matrix wvp;
    //wvp = mul(World, View);
    //wvp = mul(wvp, Projection);

    //outdate.outPosition = mul(In.inPosition, wvp);
    //outdate.outWorldPos = mul(In.inPosition, World);
    //In.inNormal.w = 0.0;
    //outdate.outNormal = normalize(mul(In.inNormal, World));
    //outdate.outTexCoord = In.inTexCoord;
	
    //outdate.outDiffuse = In.inDiffuse;
    
    
    //return outdate;
}

