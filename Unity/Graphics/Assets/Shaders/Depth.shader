Shader "Custom/Depth"
{
    Properties
    {
        _Multiplier ("Depth Multiplier", Range(10, 300)) = 10
        _Tint ("Depth Tint", Color) = (1, 1, 1, 1)
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
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
                float4 screenSpace : TEXCOORD1;
            };
            
            sampler2D _CameraDepthTexture;
            float _Multiplier;
            float4 _Tint;

            v2f vert (appdata_base v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = v.texcoord.xy;
                o.screenSpace = ComputeScreenPos(o.vertex);
                return o;
            }

            fixed4 frag (v2f i) : SV_Target
            {
                float2 screenSpaceUV = i.screenSpace.xy / i.screenSpace.w;

                float depth = Linear01Depth(SAMPLE_DEPTH_TEXTURE(
                    _CameraDepthTexture, screenSpaceUV));
                
                return depth * _Multiplier * _Tint;
            }
            ENDCG
        }
    }
}
