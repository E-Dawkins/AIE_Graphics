Shader "Custom/Blur"
{
    Properties
    {
        _BlurStrength ("Blur Strength", Int) = 1
    }
    
    SubShader
    {
        Tags {"Queue"="Transparent"}
        
        // Unity pass to convert the screen into a texture
        GrabPass {"_ScreenTexture"}
        
        Pass
        {
            CGINCLUDE

            #pragma vertex vert
            #pragma fragment frag
            #include "UnityCG.cginc"

            struct v2f
            {
                float4 grabPos : TEXCOORD0;
                float4 pos : SV_POSITION;
            };

            v2f vert(appdata_base v)
            {
                v2f o;

                o.pos = UnityObjectToClipPos(v.vertex);
                o.grabPos = ComputeGrabScreenPos(o.pos);
                
                return o;
            }
            
            ENDCG
        }
        
        Pass
        {
            CGPROGRAM
            sampler2D _ScreenTexture;
            float4 _ScreenTexture_TexelSize;
            float4 _ScreenTexture_ST;
            int _BlurStrength;
            
            fixed4 frag(v2f i) : SV_Target
            {
                float2 res = _ScreenTexture_TexelSize.xy;
                fixed4 sum = 0;

                int samples = 2 * _BlurStrength + 1;

                // Horizontal blur
                for (float x = 0; x < samples; x++)
                {
                    float2 offset = float2(x - _BlurStrength, 0);
                    float4 grabPos = i.grabPos + float4(offset * res, 0, 0);
                    sum += tex2Dproj(_ScreenTexture, grabPos);
                }

                // Vertical blur
                for (float y = 0; y < samples; y++)
                {
                    float2 offset = float2(0, y - _BlurStrength);
                    float4 grabPos = i.grabPos + float4(offset * res, 0, 0);
                    sum += tex2Dproj(_ScreenTexture, grabPos);
                }

                // Total blur
                return sum / (samples * 2);
            }
            ENDCG
        }
    }
}
