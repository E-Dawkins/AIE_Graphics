Shader "Custom/Dissolve"
{
    Properties
    {
        _Color ("Color", Color) = (1,1,1,1)
        _MainTex ("Albedo (RGB)", 2D) = "white" {}
        _Glossiness ("Smoothness", Range(0,1)) = 0.5
        _Metallic ("Metallic", Range(0,1)) = 0.0
        
        [Header(Dissolve)]
        _DissolveTex ("Dissolve Texture", 2D) = "black" {}
        _DissolveAmount ("Dissolve Amount", Range(0, 1)) = 0.5
        
        [Header(Edge)]
        [HDR]_EdgeColor ("Edge Color", Color) = (1, 1, 1, 1)
        _Range ("Edge Range", Range(0, 0.5)) = 0.1
        _Falloff ("Edge Falloff", Range(0, 1)) = 0.1
    }
    SubShader
    {
        Tags { "Queue"="Transparent" "Rendertype"="Transparent" }
        LOD 200

        CGPROGRAM
        // Physically based Standard lighting model, and enable shadows on all light types
        #pragma surface surf Standard fullforwardshadows alpha

        // Use shader model 3.0 target, to get nicer looking lighting
        #pragma target 3.0

        struct Input
        {
            float2 uv_MainTex;
            float2 uv_DissolveTex;
        };
        
        sampler2D _MainTex;
        sampler2D _DissolveTex;
        half _Glossiness;
        half _Metallic;
        fixed4 _Color;
        float _DissolveAmount;
        float _Range;
        float _Falloff;
        float3 _EdgeColor;

        void surf (Input IN, inout SurfaceOutputStandard o)
        {
            float dissolve = tex2D(_DissolveTex, IN.uv_DissolveTex).r;
            dissolve *= 0.999; // ensures that no part of the texture is visible

            // If isVisible < 0, then clip will not render this pixel
            float isVisible = dissolve - _DissolveAmount;
            clip(isVisible);
            
            float edgeColored = smoothstep(_Range + _Falloff, _Range, isVisible);
            float3 edgeColor = edgeColored * _EdgeColor;
            edgeColor *= smoothstep(0, _Falloff, _DissolveAmount);
            
            fixed4 c = tex2D(_MainTex, IN.uv_MainTex) * _Color;
            o.Albedo = c.rgb;
            o.Alpha = c.a;
            o.Metallic = _Metallic;
            o.Smoothness = _Glossiness;
            o.Emission = edgeColor;
        }
        ENDCG
    }
    FallBack "Transparent"
}
