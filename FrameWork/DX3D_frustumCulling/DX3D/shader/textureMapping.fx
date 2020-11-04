//--------------------------------------------------------------//
// TextureMapping
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//

struct VS_INPUT
{
	float4 mPosition : POSITION;
	float2 mTexCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 mPosition : POSITION;
	float2 mTexCoord : TEXCOORD0;
};

float4x4 gWorldMatrix;
float4x4 gViewMatrix;
float4x4 gProjectionMatrix;

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
	output.mPosition = mul(input.mPosition, gWorldMatrix);
	output.mPosition = mul(output.mPosition, gViewMatrix);
	output.mPosition = mul(output.mPosition, gProjectionMatrix);

	output.mTexCoord = input.mTexCoord;

	return output;
};

texture DiffuseMap_Tex;

sampler2D DiffuseSampler = sampler_state
{
	Texture = (DiffuseMap_Tex);
};
struct PS_INPUT
{
	float2 mTexCoord : TEXCOORD;
};

float4 PS(PS_INPUT input) : COLOR
{

	float4 albedo = tex2D(DiffuseSampler, input.mTexCoord);
	if (0.24 < input.mTexCoord.y && input.mTexCoord.y < 0.25f)
	{
		albedo = 1;
	}
	else if (0.49 < input.mTexCoord.y && input.mTexCoord.y < 0.50f)
	{
		albedo = float4(1, 0, 0, 1);
	}
	else if (0.74 < input.mTexCoord.y && input.mTexCoord.y < 0.75f)
	{
		albedo = 1;
	}

	if (0.24 < input.mTexCoord.x && input.mTexCoord.x < 0.25f)
		albedo = 1;

	else if (0.49 < input.mTexCoord.x && input.mTexCoord.x < 0.50f)
	{
		albedo = 1;
	}
	else if (0.74 < input.mTexCoord.x && input.mTexCoord.x < 0.75f)
	{
		albedo = 1;
	}
	else if (0.99 < input.mTexCoord.x && input.mTexCoord.x < 1.00f)
	{
		albedo = 1;
	}
	return albedo.rgba;

};
//--------------------------------------------------------------//
// Technique Section for TextureMapping
//--------------------------------------------------------------//
technique TextureMapping
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}

}