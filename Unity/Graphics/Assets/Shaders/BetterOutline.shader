Shader "Custom/BetterOutline"
{
    Properties
    {
        _OutlineWidth ("Outline Width", Float) = 0.01
        _OutlineColor ("Outline Color", Color) = (0 ,0, 0, 1)
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

            struct appdata
            {
                float4 vertex : POSITION;
                float3 normal : NORMAL;
            };

            struct v2f
            {
                float4 vertex : SV_POSITION;
            };
            
            float _OutlineWidth;
            float4 _OutlineColor;

            v2f vert (appdata v)
            {
                v2f o;
                
                float3 normal = normalize(v.normal) * _OutlineWidth;
                float3 pos = v.vertex + normal;
                
                o.vertex = UnityObjectToClipPos(pos);
                
                return o;
            }

            fixed4 frag (v2f i) : SV_Target
            {
                return _OutlineColor;
            }
            ENDCG
        }
    }
}
