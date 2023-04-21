Shader "Custom/SobelOutline"
{
    Properties
    {
        _MainTex ("Albedo (RGB)", 2D) = "white" {}
        _DeltaX ("Delta X", Float) = 0.01
        _DeltaY ("Delta Y", Float) = 0.01
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 200

            CGINCLUDE
            #include "UnityCG.cginc"

            struct v2f
            {
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
                float4 screenSpace : TEXCOORD1;
            };
            
            sampler2D _MainTex;
            float _DeltaX;
            float _DeltaY;
            sampler2D _CameraDepthTexture;
            
            float Sobel(sampler2D tex, float2 uv, float mult)
            {
                float2 delta = float2(_DeltaX, _DeltaY);

                float4 hr = float4 (0,0,0,0);
                float4 vt = float4 (0,0,0,0);

                hr += tex2D(tex, (uv + float2 (-1.0, -1.0) * delta)) *  1.0;
                hr += tex2D(tex, (uv + float2 ( 1.0, -1.0) * delta)) * -1.0;
                hr += tex2D(tex, (uv + float2 (-1.0,  0.0) * delta)) *  2.0;
                hr += tex2D(tex, (uv + float2 ( 1.0,  0.0) * delta)) * -2.0;
                hr += tex2D(tex, (uv + float2 (-1.0,  1.0) * delta)) *  1.0;
                hr += tex2D(tex, (uv + float2 ( 1.0,  1.0) * delta)) * -1.0;
                
                vt += tex2D(tex, (uv + float2 (-1.0, -1.0) * delta)) *  1.0;
                vt += tex2D(tex, (uv + float2 ( 0.0, -1.0) * delta)) *  2.0;
                vt += tex2D(tex, (uv + float2 ( 1.0, -1.0) * delta)) *  1.0;
                vt += tex2D(tex, (uv + float2 (-1.0,  1.0) * delta)) * -1.0;
                vt += tex2D(tex, (uv + float2 ( 0.0,  1.0) * delta)) * -2.0;
                vt += tex2D(tex, (uv + float2 ( 1.0,  1.0) * delta)) * -1.0;
                
                return saturate(mult * sqrt(hr * hr + vt * vt));
            }

            v2f vert (appdata_base v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = v.texcoord.xy;
                o.screenSpace = ComputeScreenPos(o.vertex);
                return o;
            }
            
            fixed4 frag (v2f i) : COLOR
            {
                float2 screenSpaceUV = i.screenSpace.xy / i.screenSpace.w;
                
                // Depth value
                float depth = 10 * tex2D(_CameraDepthTexture, i.uv);

                // Sobel value
                float s = 1 - depth * saturate(Sobel(_CameraDepthTexture, screenSpaceUV, 10));

                // Return texture color * sobel color (i.e. gives it an outline)
                return tex2D(_MainTex, i.uv) * float4 (s,s,s,1);
            }
        ENDCG
        
        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            ENDCG
        }
    }
    FallBack "Diffuse"
}