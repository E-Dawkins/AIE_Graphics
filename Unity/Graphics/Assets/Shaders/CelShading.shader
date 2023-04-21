Shader "Custom/CelShading"
{
    Properties
    {
        _Color ("Color", Color) = (1,1,1,1)
        _MainTex ("Albedo (RGB)", 2D) = "white" {}
        
        [Header(CelShading)]
        _Smoothness ("Band Smoothing", Float) = 5
        _Specular ("Specular", Float) = 400
        
        [Header(Outline)]
        _OutlineWidth ("Outline Width", Float) = 0.01
        _OutlineColor ("Outline Color", Color) = (0, 0, 0, 1)
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 200

        Stencil
        {
            Ref 1
            Pass replace
            Fail keep
            ZFail keep
        }
        
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
        
        Pass
        {
            Stencil
            {
                Ref 1
                Comp notequal
            }
            
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag

            #include "UnityCG.cginc"

            float _OutlineWidth;
            float4 _OutlineColor;

            struct appdata
            {
                float4 vertex : POSITION;
                float3 normal : NORMAL;
            };

            struct v2f
            {
                float4 vertex : SV_POSITION;
            };

            v2f vert(appdata v)
            {
                v2f o;

                float3 normal = normalize(v.normal) * _OutlineWidth;
                float3 pos = v.vertex + normal;

                o.vertex = UnityObjectToClipPos(pos);

                return o;
            }

            float4 frag(v2f i) : SV_Target
            {
                return _OutlineColor;
            }
            
            ENDCG
        }
    }
    FallBack "Diffuse"
}
