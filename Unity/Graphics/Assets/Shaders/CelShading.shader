Shader "Custom/CelShading"
{
    Properties
    {
        _Color ("Color", Color) = (1,1,1,1)
        _MainTex ("Albedo (RGB)", 2D) = "white" {}
        _Smoothness ("Band Smoothing", Float) = 5
        _Specular ("Specular", Float) = 400
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 200

        CGPROGRAM
        // Surface shader uses out own LightingCel function to determine lighting
        #pragma surface surf Cel

        // Use shader model 3.0 target, to get nicer looking lighting
        #pragma target 3.0

        struct Input
        {
            float2 uv_MainTex;
        };

        sampler2D _MainTex;
        fixed4 _Color;
        float _Smoothness, _Specular;

        fixed4 LightingCel(SurfaceOutput s, fixed3 lightDir, fixed3 viewDir, float atten)
        {
            float3 normal = normalize(s.Normal);
            float diffuse = dot(normal, lightDir);

            // Makes the cutoff width constant across the surface
            float delta = fwidth(diffuse) * _Smoothness;

            // Smooths out the diffuse cutoff point between light / dark
            float diffuseSmooth = smoothstep(0, delta, diffuse);

            // The vector halfway between the light / view directions
            float3 halfwayVec = normalize(lightDir + viewDir);
            
            float specular = dot(normal, halfwayVec);
            specular = pow(specular * diffuseSmooth, _Specular);

            // Smooths the specular cutoff point
            float specularSmooth = smoothstep(0, 0.01 * _Smoothness, specular);
            
            float3 col = s.Albedo * ((diffuseSmooth + specularSmooth) * _LightColor0 + unity_AmbientSky);
            return float4(col, s.Alpha);
        }

        void surf (Input IN, inout SurfaceOutput o)
        {
            fixed4 c = tex2D (_MainTex, IN.uv_MainTex) * _Color;
            o.Albedo = c.rgb;
            o.Alpha = c.a;
        }
        ENDCG
    }
    FallBack "Diffuse"
}
