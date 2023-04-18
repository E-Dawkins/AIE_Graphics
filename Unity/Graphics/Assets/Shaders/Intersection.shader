Shader "Custom/Intersection"
{
    Properties
    {
        _RimColor ("Rim Color", Color) = (1, 1, 1, 1)
        _RimPower ("Rim Power", Range(0.5, 8)) = 3
    }

    SubShader
    {
        Tags
        {
            "Queue"="Transparent" "RenderType"="Opaque"
        }

        CGPROGRAM
            // Physically based Standard lighting model, and enable shadows on all light types
            #pragma surface surf Standard fullforwardshadows alpha

            // Use shader model 3.0 target, to get nicer looking lighting
            #pragma target 3.0

            // #include "UnityCG.cginc"

            /*sampler2D _CameraDepthTexture;*/
            float4 _CameraDepthTexture_ST;

            float4 _RimColor;
            float _RimPower;

            struct Input
            {
                float3 worldPos;
                float2 uv;
                float3 viewDir;
                float4 screenPos;
            };

            /*struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };*/

            /*struct v2f
            {
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
            };
            */

            /*v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = TRANSFORM_TEX(v.uv, _CameraDepthTexture);
               
                return o;
            }*/

            void surf(Input IN, inout SurfaceOutputStandard o)
            {
                /*float4 depth = tex2D(_CameraDepthTexture, IN.screenPos.xy);*/
                float3 depth = -UnityObjectToViewPos(IN.worldPos);
                float screenAlpha = IN.screenPos.a;

                /*o.Alpha = 1;
                o.Albedo = 1;*/
                o.Emission = depth.z;
                
                /*half rim = 1.0 - saturate(dot(normalize(IN.viewDir), o.Normal));
                o.Emission = (_RimColor.rgb * pow(rim, _RimPower)) * tex2D(_CameraDepthTexture, IN.uv);*/
            }

            /*fixed4 frag(v2f_img i) : COLOR
            {
                return tex2D(_CameraDepthTexture, i.uv);
            }*/
            ENDCG
    }
}