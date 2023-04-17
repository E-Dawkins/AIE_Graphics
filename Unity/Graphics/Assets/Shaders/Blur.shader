// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Custom/Blur"
{
    Properties
    {
        _MainTex ("Texture", 2D) = "white" {}
        _radius ("Blur radius", Range (0.01,2.0)) = 0.5
    }
    SubShader
    {
        Tags {"Queue"="Transparent" "RenderType"="Opaque"}
        
        Pass
        {
            Tags { "LightMode" = "Always" }
            
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            #pragma target 5.0

            float _radius;
            sampler2D _MainTex;
            float4 _MainTex_ST;

            #include "UnityCG.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct v2f
            {
                float4 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
            };

            v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                #if UNITY_UV_STARTS_AT_TOP
                float scale = -1.0;
                #else
                float scale = 1.0;
                #endif
                o.uv.xy = (float2(o.vertex.x, o.vertex.y*scale) + o.vertex.w) * 0.5;
                o.uv.zw = o.vertex.zw;
                return o;
            }

            fixed4 frag (v2f i) : SV_Target
            {
                half4 sum = half4(0,0,0,0);
 
                #define GRABPIXEL(weight,kernelx) tex2Dproj( _MainTex, UNITY_PROJ_COORD(float4(i.uv.x + _MainTex_ST.x * kernelx*_radius, i.uv.y, i.uv.z, i.uv.w))) * weight

                sum += GRABPIXEL(0.05, -4.0);
                sum += GRABPIXEL(0.09, -3.0);
                sum += GRABPIXEL(0.12, -2.0);
                sum += GRABPIXEL(0.15, -1.0);
                sum += GRABPIXEL(0.18,  0.0);
                sum += GRABPIXEL(0.15, +1.0);
                sum += GRABPIXEL(0.12, +2.0);
                sum += GRABPIXEL(0.09, +3.0);
                sum += GRABPIXEL(0.05, +4.0);
               
                return sum;
            }
            ENDCG
        }
    }
}
