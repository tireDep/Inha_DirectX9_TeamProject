
//--------------------------------------------------------------//
// ColorShader
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//

struct VS_INPUT
{
   float4 mPosition : POSITION;
};

struct VS_OUTPUT
{
   float4 mPosition : POSITION;
};

float4x4 gWorldMatrix;
float4x4 gViewMatrix;
float4x4 gProjectionMatrix;

float4 gColor;

VS_OUTPUT VS(VS_INPUT input)
{
   VS_OUTPUT output;
   output.mPosition = mul(input.mPosition, gWorldMatrix);
   output.mPosition = mul(output.mPosition, gViewMatrix);
   output.mPosition = mul(output.mPosition, gProjectionMatrix);
   
   return output;
 }

float4 PS() : COLOR
{
   return gColor;
}
//--------------------------------------------------------------//
// Technique Section for ColorShader
//--------------------------------------------------------------//
technique ColorShader
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 VS();
      PixelShader = compile ps_2_0 PS();
   }
}
