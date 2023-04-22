Shader "Custom/SobelOutline"
{
    Properties
    {
        _MainTex ("Albedo (RGB)", 2D) = "white" {}
        _OutlineThickness ("Outline Thickness", Float) = 0.01
        _OutlineColor ("Outline Color", Color) = (0, 0, 0, 1)
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
            sampler2D _CameraDepthTexture;
            float _OutlineThickness;
            float4 _OutlineColor;
            
            float SobelDepth(sampler2D tex, float2 uv, float3 offset)
            {
                float pixelCenter = LinearEyeDepth(tex2D(tex, uv).r);
                float pixelLeft   = LinearEyeDepth(tex2D(tex, uv - offset.xz).r);
                float pixelRight  = LinearEyeDepth(tex2D(tex, uv + offset.xz).r);
                float pixelUp     = LinearEyeDepth(tex2D(tex, uv + offset.zy).r);
                float pixelDown   = LinearEyeDepth(tex2D(tex, uv - offset.zy).r);

                return abs(pixelLeft - pixelCenter) +
                        abs(pixelRight - pixelCenter) +
                        abs(pixelUp - pixelCenter) +
                        abs(pixelDown - pixelCenter);
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
                float3 sceneColor = tex2D(_MainTex, i.uv);
                
                float2 screenSpaceUV = i.screenSpace.xy / i.screenSpace.w;
                float thickness = (i.screenSpace.z / i.screenSpace.w) * _OutlineThickness;
                float3 offset = float3(1.0 / _ScreenParams.x, 1.0 / _ScreenParams.y, 0.0) * thickness;
                
                float sobelDepth = SobelDepth(_CameraDepthTexture, screenSpaceUV, offset);

                // Outline color is calculated based off texture color, the
                // outline color rgb and the alpha of the passed in outline color
                float3 outlineColor = lerp(sceneColor, _OutlineColor.rgb, _OutlineColor.a);

                // Calculate final color
                float3 finalColor = lerp(sceneColor, outlineColor, sobelDepth);
                
                return float4(finalColor, 1);
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