Shader "Custom/VertexManipulation"
{
	Properties
    {
    	_Color ("Color", Color) = (1, 1, 1, 1)
    	
    	[Header(Height)]
        _HeightOffset ("HeightOffset", Float) = 1
    	_HeightMap ("Height Map", 2D) = "black" {}
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

			sampler2D _HeightMap;
			float _HeightOffset;
			fixed4 _Color;
			
			v2f vert (appdata_base v)
			{
				v2f o;
				
				float3 worldNormal = UnityObjectToWorldNormal(v.normal);
				float vertHeight = tex2Dlod(_HeightMap, v.texcoord) * _HeightOffset;
				
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