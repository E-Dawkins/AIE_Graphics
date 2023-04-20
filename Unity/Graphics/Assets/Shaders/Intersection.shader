Shader "Custom/Intersection"
{
	Properties
	{
		_BaseColor("Base Color", Color) = (0, 0, 0, 0)
		_InterCol("Intersect Color", Color) = (1, 1, 1, 1)
		_Falloff("Falloff", Float) = 1
	}
	SubShader
	{
		Tags { "Queue"="Transparent" "RenderType"="Transparent" }
		
		Blend SrcAlpha OneMinusSrcAlpha

		Pass
		{
			CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag
			
			#include "UnityCG.cginc"

			struct v2f
			{
				float2 uv : TEXCOORD0;
				float4 vertex : SV_POSITION;
				float4 screenPos : TEXCOORD1;
			};

			sampler2D _CameraDepthTexture;
			fixed4 _BaseColor, _InterCol;
			float _Falloff;
			
			v2f vert (appdata_base v)
			{
				v2f o;
				o.vertex = UnityObjectToClipPos(v.vertex);
				o.uv = v.texcoord.xy;
				o.screenPos = ComputeScreenPos(o.vertex);
				return o;
			}
			
			fixed4 frag (v2f i) : SV_Target
			{
				float2 screenUV = i.screenPos.xy / i.screenPos.w;
				float screenDepth = Linear01Depth(tex2D(_CameraDepthTexture, screenUV));

				// The difference between the screen depth, and the vertex depth.
				// I.e. if screen depth < vertex depth, there is an overlap.
				float depthDiff = screenDepth - Linear01Depth(i.screenPos.z / i.screenPos.w);

				// The intersection value, based off falloff and the depth difference.
				float intersect = 1 - smoothstep(0, _ProjectionParams.w * _Falloff, depthDiff);

				// Return lerped color between base color, and the intersection color.
                return lerp(_BaseColor, _InterCol, intersect);
			}
			ENDCG
		}
	}
}