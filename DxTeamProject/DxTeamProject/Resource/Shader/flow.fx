float4x4 gWorldViewProjection : WorldViewProjection;
float4x4 gWorldInverseTranspose : WorldInverseTranspose;
float4x4 gWorld : World;
float4x4 gViewInverse;

float gTime = float( 0.00 );
float gCenter = float( 0.50 );
float gTimeAngle = float( 0.00 );

struct VS_INPUT 
{
   float4 mPosition : POSITION0;
   float2 mTexCoord : TEXCOORD;
   float3 mNormal : NORMAL;
   float3 mTangent : TANGENT;
   float3 mBinormal : BINORMAL;
};

struct VS_OUTPUT 
{
   float4 mPosition : POSITION0;
   
   float2 mwTexCoord : TEXCOORD;
   float3 mwNormal : TEXCOORD1;
   float3 mwTangent : TEXCOORD2;
   float3 mwBinormal : TEXCOORD3;
   float4 mwPosition : TEXCOORD4;
   
   float2 mwUV1 : TEXCOORD5;
   float2 mwUV2 : TEXCOORD6;
   float2 mwUV3 : TEXCOORD7;
};

float2 RotateUV(float2 UV, float2 center, float theta)
{
   float2 sc;
   
   sincos((theta / 180 * 3.14159), sc.x, sc.y);
   
   float2 uv = UV - center;
   float2 rotateUV;
   
   rotateUV.x = dot(uv, float2(sc.y, -sc.x));
   rotateUV.y = dot(uv, sc.xy);
   rotateUV += center;
   
   return rotateUV;
}

VS_OUTPUT VS( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.mPosition = mul( Input.mPosition, gWorldViewProjection);
   Output.mwNormal = mul( Input.mNormal, (float3x3) gWorldInverseTranspose);
   Output.mwTangent = mul(Input.mTangent, (float3x3) gWorldInverseTranspose);
   Output.mwBinormal = mul(Input.mBinormal, (float3x3) gWorldInverseTranspose);
   Output.mwPosition = mul(Input.mPosition, gWorld);
   
   Output.mwTexCoord.x = Input.mTexCoord.x;
   Output.mwTexCoord.y = -Input.mTexCoord.y;
   
   Output.mwUV1.x = Input.mTexCoord.x - gTime / 4;
   Output.mwUV1.y = -Input.mTexCoord.y;
   
   Output.mwUV2.y = Input.mTexCoord.x - gTime / 2;
   Output.mwUV2.x = -Input.mTexCoord.y;
   
   Output.mwUV3 = RotateUV(Input.mTexCoord, gCenter, gTimeAngle * 60);
    
   return Output;
}

float gBump = float( 0.20 );

texture distortion_Tex;
sampler2D gNormalSampler = sampler_state
{
   Texture = (distortion_Tex);
};
sampler2D gDiffuseSampler1 = sampler_state
{
   Texture = (distortion_Tex);
};
sampler2D gDiffuseSampler2 = sampler_state
{
   Texture = (distortion_Tex);
};

float4 PS(VS_OUTPUT Input) : COLOR0
{   
   float3 _n = normalize(Input.mwNormal);
   float3 _t = normalize(Input.mwTangent);
   float3 _b = normalize(Input.mwBinormal);
   
   float3 bump = gBump * (tex2D(gNormalSampler, Input.mwUV1)).rgb;
   
   float3 _nN = _n + bump.x * _t + bump.y * _b;
   
   float3 diffuseM1 = tex2D(gDiffuseSampler1, (Input.mwUV3 + _nN));
   // >> rotateMap
   
   float3 diffuseM2 = tex2D(gDiffuseSampler2, (Input.mwUV2 + _nN));
   // >> upMap
   
   float opacity = diffuseM1.x * diffuseM2.x;
   float3 diffuse = diffuseM1 * diffuseM2;
   
   return float4(1.5 * (diffuse), opacity);
}

technique Default_DirectX_Effect
{
   pass Pass_0
   {
CullMode = None;
// AlphaBlendEnable = true;
// DestBlend = InvsrcAlpha;
DestBlend = One;
SrcBlend = SrcAlpha;
      VertexShader = compile vs_2_0 VS();
      PixelShader = compile ps_2_0 PS();
   }

}

