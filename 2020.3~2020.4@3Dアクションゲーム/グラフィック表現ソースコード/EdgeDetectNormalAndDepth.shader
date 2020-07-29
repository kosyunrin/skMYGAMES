Shader "Edge Detection Normals And Depth" {
	Properties {
		_MainTex ("Base (RGB)", 2D) = "white" {}
		_EdgeOnly("Edge Only", Float) = 1.0
		_EdgeColor("Edge Color", Color) = (0, 0, 0, 1)
		_BackgroundColor("Background Color", Color) = (1, 1, 1, 1)
		_SampleDistance("Sample Distance", Float) = 1.0
		_Sensitivity("Sensitivity", Vector) = (1, 1, 1, 1)
	}
	SubShader {
		CGINCLUDE
		
		#include "UnityCG.cginc"
		
		sampler2D _MainTex;
		half4 _MainTex_TexelSize;
		fixed _EdgeOnly;
		fixed4 _EdgeColor;
		fixed4 _BackgroundColor;
		float _SampleDistance;
		half4 _Sensitivity;
		fixed4 _DetectiveColor;
		float _DetectiveRange;
		float _DetectiveRangeWidth;
		float _DetectiveRangeLimit;
		float4 _PlayerPosition;
		float4x4 _CurrentViewProjectionInverseMatrix;
		float4x4 _CurrentCameraToWorldMatrix;
		sampler2D _DetectiveTexture;
		float _DetectiveTextureWidth;
		float _DetectiveTextureLength;
		
		sampler2D _CameraDepthTexture;
		sampler2D _CameraDepthNormalsTexture;
		
		struct v2f {
			float4 pos : SV_POSITION;
			half2 uv[6]: TEXCOORD0;
		};

		v2f vert(appdata_img v) {
			v2f o;
			o.pos = UnityObjectToClipPos(v.vertex);
			
			half2 uv = v.texcoord;
			o.uv[0] = uv;
			
			#if UNITY_UV_STARTS_AT_TOP
			if (_MainTex_TexelSize.y < 0)
				uv.y = 1 - uv.y;
			#endif
			
			o.uv[1] = uv + _MainTex_TexelSize.xy * half2(1,1) * _SampleDistance;
			o.uv[2] = uv + _MainTex_TexelSize.xy * half2(-1,-1) * _SampleDistance;
			o.uv[3] = uv + _MainTex_TexelSize.xy * half2(-1,1) * _SampleDistance;
			o.uv[4] = uv + _MainTex_TexelSize.xy * half2(1,-1) * _SampleDistance;
			
			o.uv[5] = uv;

			return o;
		}
		
		half CheckSame(half4 center, half4 sample) {
			half2 centerNormal = center.xy;
			float centerDepth = DecodeFloatRG(center.zw);
			half2 sampleNormal = sample.xy;
			float sampleDepth = DecodeFloatRG(sample.zw);
			
			half2 diffNormal = abs(centerNormal - sampleNormal) * _Sensitivity.x;
			int isSameNormal = (diffNormal.x + diffNormal.y) < 0.1;

			float diffDepth = abs(centerDepth - sampleDepth) * _Sensitivity.y;
			int isSameDepth = diffDepth < 0.1 * centerDepth;
			
			return isSameNormal * isSameDepth ? 1.0 : 0.0;
		}

		fixed4 fragRobertsCrossDepthAndNormal(v2f i) : SV_Target {
			half4 sample1 = tex2D(_CameraDepthNormalsTexture, i.uv[1]);
			half4 sample2 = tex2D(_CameraDepthNormalsTexture, i.uv[2]);
			half4 sample3 = tex2D(_CameraDepthNormalsTexture, i.uv[3]);
			half4 sample4 = tex2D(_CameraDepthNormalsTexture, i.uv[4]);
			
			half edge = 1.0;
			
			edge *= CheckSame(sample1, sample2);
			edge *= CheckSame(sample3, sample4);
			
			fixed4 diffuseColor = tex2D(_MainTex, i.uv[0]);

			float tempDepth;
			half3 normal;
			DecodeDepthNormal(tex2D(_CameraDepthNormalsTexture, i.uv[5]), tempDepth, normal);
			normal = mul((float3x3)_CurrentCameraToWorldMatrix, normal);
			normal = normalize(max(0, (abs(normal) - 0.05)));

			float d = SAMPLE_DEPTH_TEXTURE(_CameraDepthTexture, i.uv[5]);
			#if UNITY_REVERSED_Z
			d = 1.0 - d;
			#endif
			float4 H = float4(i.uv[5].x * 2 - 1, i.uv[5].y * 2 - 1, d * 2 - 1, 1);
			float4 D = mul(_CurrentViewProjectionInverseMatrix, H);
			float4 worldPos = D / D.w;
			float4 hasObj = step(d, 0.999);
			worldPos = float4(worldPos.xyz, 1.0) * hasObj;

			float4 playerPos = _PlayerPosition;
			float pixelDistance = distance(worldPos.xyz, playerPos.xyz);
			float minDistance = max(_DetectiveRange - _DetectiveRangeWidth, _DetectiveRangeLimit);
			float distancePercent = (pixelDistance - minDistance) / (_DetectiveRange - minDistance);

			float3 meshesPos = worldPos;
			float3 Back = -UNITY_MATRIX_V[2].xyz;
			float3 Right = UNITY_MATRIX_V[0].xyz;
			meshesPos.y = 0.0;
			Back.y = 0.0;
			Right.y = 0.0;
			Back = normalize(Back);
			Right = normalize(Right);
			float2 meshesUV = float2(dot(meshesPos, Back) / _DetectiveTextureWidth + 0.5, dot(meshesPos, Right) / _DetectiveTextureLength + 0.5);
			#if UNITY_UV_STARTS_AT_TOP
			if (_MainTex_TexelSize.y < 0)
				meshesUV.y = 1 - meshesUV.y;
			#endif
			fixed4 scanMeshCol = tex2D(_DetectiveTexture, meshesUV);

			if (distancePercent < 1.0)
			{
				fixed4 withEdgeColor = lerp(_EdgeColor, diffuseColor, edge);
				fixed4 onlyEdgeColor = lerp(_EdgeColor, _BackgroundColor, edge);
				fixed4 colorEdge = lerp(withEdgeColor, onlyEdgeColor, _EdgeOnly);
				fixed4 DetectRangeColor = lerp(colorEdge, _DetectiveColor + scanMeshCol, saturate(distancePercent));
				return DetectRangeColor;
			}
			return diffuseColor;
		}
		
		ENDCG
		
		Pass {
			ZTest Always Cull Off ZWrite Off
			
			CGPROGRAM
			
			#pragma vertex vert
			#pragma fragment fragRobertsCrossDepthAndNormal
			
			ENDCG
		}
	}
	FallBack Off
}