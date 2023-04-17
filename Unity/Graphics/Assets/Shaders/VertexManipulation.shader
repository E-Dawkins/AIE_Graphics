Shader "Custom/VertexManipulation"
{
	Properties
    {
        _HeightOffset ("HeightOffset", Float) = 1
    	_Color ("Color", Color) = (1, 1, 1, 1)
    }
	SubShader
	{
		Tags { "RenderType"="Opaque" }
        LOD 100
		
		Pass
		{
			CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag
			#include "UnityCG.cginc"
			
			struct v2f
			{
				float4 pos : SV_POSITION;
				float4 worldPos : TEXCOORD0;
			};

			float _HeightOffset;
			fixed4 _Color;

			// From NedMakesGames yt - https://www.youtube.com/watch?v=nohGiVNWhJE
			float Noise(float2 uv)
			{
				return frac(sin(dot(uv, float2(12.9898f, 78.233f))) * 43758.5453f);
			}
			
			v2f vert (appdata_base v)
			{
				v2f o;
				
				float3 worldNormal = UnityObjectToWorldNormal(v.normal);
				float vertHeight = Noise(v.texcoord.xy) * _HeightOffset;
				
                o.pos = UnityObjectToClipPos(v.vertex + worldNormal * vertHeight);
                o.worldPos = mul(unity_ObjectToWorld, v.vertex); // object -> world space
				
                return o;
			}
			
			fixed4 frag (v2f i) : SV_Target
			{
				return _Color;
			}
			ENDCG
		}
	}
}