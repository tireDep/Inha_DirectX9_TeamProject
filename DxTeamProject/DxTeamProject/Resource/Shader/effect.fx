// : shader 
// : dissolve 
// https://zubi.tistory.com/18
//

float4x4 WVPM : WorldViewProjection;
float4x4 WM : World;
float4x4 WITM : WorldInverseTranspose;

struct VS_INPUT
{
	float4 position : POSITION;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL;
};

struct VS_OUTPUT
{
	float4 pposition : POSITION;
	float2 ouv : TEXCOORD0;
	float4 wposition : TEXCOORD1;
	float3 onormal : TEXCOORD2;
};

VS_OUTPUT vs_main(VS_INPUT input)
{
	VS_OUTPUT output;

	output.pposition = mul(input.position, WVPM);
	output.wposition = mul(input.position, WM);
	output.onormal = mul(input.normal, WITM);

	output.ouv.x = input.uv.x;
	output.ouv.y = input.uv.y;
	return output;
}

texture DiffuseTexture_Tex;
sampler2D DiffuseSampler = sampler_state
{
	Texture = (DiffuseTexture_Tex);
MINFILTER = LINEAR;
MAGFILTER = LINEAR;
MIPFILTER = LINEAR;
ADDRESSU = WRAP;
ADDRESSV = WRAP;
//Texture = <DiffuseTexture_Tex>;
//FILTER = MIN_MAG_MIP_LINEAR;
//AddressU = Wrap;
//AddressV = Wrap;
};

texture DiffuseTexture2_Tex;
sampler2D DiffuseSampler2 = sampler_state
{
	//Texture = (DiffuseTexture2_Tex);
	//MAGFILTER = LINEAR;
	//MINFILTER = LINEAR;
	//MIPFILTER = LINEAR;
	//ADDRESSU = WRAP;
	//ADDRESSV = WRAP;

	Texture = <DiffuseTexture2_Tex>;
FILTER = MIN_MAG_MIP_LINEAR;
AddressU = Wrap;
AddressV = Wrap;
};

float time = 0.1;
float a = 0.9;
float3 Color = { 1.0f , 0.0f, 0.0f };
float4 gGrayColor;

struct PS_INPUT
{
	float4 pposition : POSITION;
	float2 ouv : TEXCOORD0;
	float4 wposition : TEXCOORD1;
	float3 onormal : TEXCOORD2;
};

float4 ps_main(PS_INPUT input) : COLOR
{
	float3 diffuseM = tex2D(DiffuseSampler, input.ouv);
float3 diffuseM2 = tex2D(DiffuseSampler2, input.ouv);

float multi1 = ((diffuseM2.r * sin(time)) * 2.8);
float multi2 = diffuseM2.r * sin(time);
float b = saturate(pow(multi1 + multi2, 20));

float alpha = pow(multi1 + multi2, 20);

float3 Ke;
if (a >= b)
Ke = (100.0f, 1.0f, 1.0f);
else
Ke = (0, 0, 0);

float3 diffuse = (Ke*Color + diffuseM);

// : 투명하게 하지 말고 투명도 일정 부분 이하면 회색으로 처리하는 걸로 수정 
if (alpha < 0.2)
	return gGrayColor;
	// return float4(0.4, 0.4, 0.4, 1.0);

return float4(diffuse, alpha);
}


float4 ps_main_2(PS_INPUT input) : COLOR
{
	float3 diffuseM = tex2D(DiffuseSampler, input.ouv);
float3 diffuseM2 = tex2D(DiffuseSampler2, input.ouv);

float multi1 = ((diffuseM2.r * sin(time)) * 2.8);
float multi2 = diffuseM2.r * sin(time);
float b = saturate(pow(multi1 + multi2, 20));

float c = pow(multi1 + multi2, 100) * 10;

float3 Ke;
if (a >= b)
Ke = (0.8f, 0.1f, 0.1f);
else
Ke = (0, 0, 0);

float3 diffuse = (Ke*Color);

return float4(diffuse, c);
}
//--------------------------------------------------------------//
// Technique Section for ColorShader
//--------------------------------------------------------------//
technique DissolveShader
{
	pass Pass_0
	{
		CullMode = None;
	AlphaBlendEnable = true;
	DestBlend = InvsrcAlpha;
	SrcBlend = SrcAlpha;
	VertexShader = compile vs_2_0 vs_main();
	PixelShader = compile ps_2_0 ps_main();
	}

		pass Pass_1
	{
		CullMode = None;
	AlphaBlendEnable = true;
	DestBlend = One;
	SrcBlend = SrcAlpha;
	VertexShader = compile vs_2_0 vs_main();
	PixelShader = compile ps_2_0 ps_main_2();
	}
}
