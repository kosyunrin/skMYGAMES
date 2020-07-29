float random2(in float2 vec)
{
    return frac(sin(dot(vec.xy, float2(12.9898, 78.233))) * 43758.5453123);
  // return frac(sin(dot(vec.xy, float2(12.9898, 78.233))) * 43758.5453123);

}
float2 random22(in float2 vec)
{
    vec = float2(dot(vec, float2(127.1, 311.7)), dot(vec, float2(269.5, 183.3)));
    return frac(sin(vec) * (43758.5453123));
}
float voronoi2(in float2 vec)
{
    float2 ivec = floor(vec); //qu zhen shu
    float2 fvec = frac(vec);
    float value = 1.0;
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            float2 offset = float2(x, y);
            
            float2 pos;
            pos = random22(ivec + offset);
            float dist = distance(pos + offset, fvec);
            value = min(value, dist);
        }

    }
    return value;
}
//ƒoƒŠƒ…[ƒmƒCƒY‚QD
float valueNosise2(in float2 vec)
{
    float2 ivec = floor(vec);
    float2 fvec = frac(vec);
    float a = dot(random22(ivec + float2(0.0, 0.0)) * 2.0 - 1.0, fvec - float2(0.0, 0.0));

    float b = dot(random22(ivec + float2(1.0, 0.0)) * 2.0 - 1.0, fvec - float2(1.0, 0.0));

    float c = dot(random22(ivec + float2(0.0, 1.0)) * 2.0 - 1.0, fvec - float2(0.0, 1.0));
    float d = dot(random22(ivec + float2(1.0, 1.0)) * 2.0 - 1.0, fvec - float2(1.0, 1.0));
    fvec = smoothstep(0.0, 1.0, fvec);
    return lerp(lerp(a, b, fvec.x), lerp(c, d, fvec.x), fvec.y);

}
//”ñ®”ƒuƒ‰ƒEƒ“‰^“®‚QD
float fbm2(in float2 vec, int octave)
{
    float value = 0.0;
    float amplitude = 0.5;
    float frequency = 0.0;
    
    for (int i = 0; i < octave; i++)
    {
        value += amplitude * valueNosise2(vec);
        vec *= 2.0;
        amplitude *= 0.5;
    }
    return value;
}
float fbm2offet(in float2 vec, int octave,float offset=0.0)
{
    float value = 0.0;
    float amplitude = 0.5;
    
    for (int i = 0; i < octave; i++)
    {
        value += amplitude * valueNosise2(vec + offset);
        vec *= 2.0;
        amplitude *= 0.5;
    }
    return value;
}

//3D
float random3(in float3 vec)
{
    return frac(sin(dot(vec.xyz, float3(12.9898, 78.233, 47.2311))) * 43758.5453123);
}
//3DƒoƒŠƒ…[ƒmƒCƒY
float ValieNoise3(in float3 vec)
{
    float3 ivec = floor(vec);
    float3 fvec = frac(vec);
    
    float a = random3(ivec + float3(0.0, 0.0, 0.0));
    float b = random3(ivec + float3(1.0, 0.0, 0.0));
    float c = random3(ivec + float3(0.0, 1.0, 0.0));
    float d = random3(ivec + float3(1.0, 1.0, 0.0));
    float e = random3(ivec + float3(0.0, 0.0, 1.0));
    float f = random3(ivec + float3(1.0, 0.0, 1.0));
    float g = random3(ivec + float3(0.0, 1.0, 1.0));
    float h = random3(ivec + float3(1.0, 1.0, 1.0));
    
    
    fvec = smoothstep(0.0, 1.0, fvec);
    float v1 = lerp(lerp(a, b, fvec.x), lerp(c, d, fvec.x), fvec.y);
    float v2 = lerp(lerp(e, f, fvec.x), lerp(g, h, fvec.x), fvec.y);
    float v3 = lerp(v1, v2, fvec.z);
    return v3;
}
float3 random33(in float3 vec)
{
    vec = float3(dot(vec, float3(127.1, 311.7, 245.4)),
    dot(vec, float3(269.5, 183.3, 131.2)),
    dot(vec, float3(522.3, 243.1, 532.4)));
    return frac(sin(vec) * 43758.5453123);

}
//”ñ®”ƒuƒ‰ƒEƒ“‰^“®‚QD
float fbm3(in float3 vec, int octave)
{
    float value = 0.0;
    float amplitude = 0.5;
    float frequency = 0.0;
    
    for (int i = 0; i < octave; i++)
    {
        value += amplitude * ValieNoise3(vec);
        vec *= 2.0;
        amplitude *= 0.5;
    }
    return value;
}
float tubulence2(in float2 vec, int octave)
{
    float value = 0.0;
    float amplitude = 0.5f;
    for (int i = 0; i < octave;i++)
    {
        value += amplitude * abs(valueNosise2(vec));
        vec * 2.0;
        amplitude *= 0.5f;
    }
    return value;
}