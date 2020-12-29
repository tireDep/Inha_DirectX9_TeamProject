float4x4 gViewProjection : ViewProjection;
float4x4 gWorld : World;
float4x4 gInverseTranspose : WorldInverseTranspose;

float gTime;
float a;
float3 gColor;

struct VS_INPUT 
{
   float4 mPosition : POSITION;
   float2 mTexCoord : TEXCOORD0;
   float3 mNormal : NORMAL;
};

struct VS_OUTPUT 
{
   float4 mPosition : POSITION;
   float2 mTexCoord : TEXCOORD0;
   float4 mWPos : TEXCOORD1;
   float3 mNormal : TEXCOORD2;
};

VS_OUTPUT VS( VS_INPUT Input )
{
    VS_OUTPUT Output;

   Output.mPosition = mul(Input.mPosition, gViewProjection);
   Output.mWPos = mul(Input.mPosition, gWorld);
   Output.mNormal = mul(Input.mNormal, gInverseTranspose);

   Output.mTexCoord.x = Input.mTexCoord.x;
   Output.mTexCoord.y = 1 - Input.mTexCoord.y;

   return Output;  
}

texture DiffuseSampler_Tex;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseSampler_Tex);
FILTER = MIN_MAG_MIP_LINEAR;
AddressU = Wrap;
AddressV = Wrap;
};
texture DiffuseSampler2_Tex;
sampler2D DiffuseSampler2 = sampler_state
{
   Texture = (DiffuseSampler2_Tex);
FILTER = MIN_MAG_MIP_LINEAR;
AddressU = Wrap;
AddressV = Wrap;
};

float4 PS(VS_OUTPUT Input) : COLOR0
{   
   float3 diffuseM = tex2D(DiffuseSampler, Input.mTexCoord);
   float3 diffuseM2 = tex2D(DiffuseSampler2, Input.mTexCoord);

   float multi1 = ((diffuseM2.r * sin(gTime))*2.8);
   float multi2 = diffuseM2.r * sin(gTime);
   float b = saturate(pow(multi1 + multi2, 20));
   float c = pow(multi1 + multi2, 20);

   float3 ke;
   if(a >= b)
      ke = (1.0f, 1.0f, 1.0f);
   else
      ke = (0.0f, 0.0f, 0.0f);

   float3 diffuse = (ke * gColor + diffuseM);

   if(diffuseM.x < diffuse.x || diffuseM.y < diffuse.y || diffuseM.z < diffuse.z)
	diffuse = (0.5, 0.5, 0.5);

   return float4(diffuse, 1.0);
}

//--------------------------------------------------------------//
// Pass 1
//--------------------------------------------------------------//

float4 PS1(VS_OUTPUT Input) : COLOR0
{   
   float3 diffuseM = tex2D(DiffuseSampler, Input.mTexCoord);
   float3 diffuseM2 = tex2D(DiffuseSampler2, Input.mTexCoord);

   float multi1 = ((diffuseM2.r * sin(gTime))*2.8);
   float multi2 = diffuseM2.r * sin(gTime);
   float b = saturate(pow(multi1 + multi2, 20));
   float c = pow(multi1 + multi2, 100) * 10;

   float3 ke;
   if(a >= b)
       ke = (0.8f, 0.1f, 0.1f);
   else
      ke = (0.0f, 0.0f, 0.0f);

   float3 diffuse = (ke * gColor);

   return float4(diffuse, 1.0);
}

technique Default_DirectX_Effect
{
   pass Pass_0
   {
CullMode = None;
AlphaBlendEnable = true;
DestBlend = InvsrcAlpha;
SrcBlend = SrcAlpha;
      VertexShader = compile vs_2_0 VS();
      PixelShader = compile ps_2_0 PS();
   }

  pass Pass_1
  {	
CullMode = None;
AlphaBlendEnable = true;
DestBlend = One;
SrcBlend = SrcAlpha;	
	VertexShader = compile vs_2_0 VS();
	PixelShader = compile ps_2_0 PS1();
   }

}

