float4x4 matViewProjection : ViewProjection;
float4x4 matViewInverseTranspose : ViewInverseTranspose;
float4x4 matProjection : Projection;
float4 OutlineColor
<
   string UIName = "OutlineColor";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 1.00, 1.00, 1.00, 1.00 );

float OutlineWidth
<
   string UIName = "OutlineWidth";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float( 0.005 );

struct VS_INPUT
{
   float3 Normal : NORMAL;
   float4 Position : POSITION;
};

struct VS_OUTPUT
{
   float4 Position : POSITION;
   float4 Color : COLOR;
};

VS_OUTPUT VS( VS_INPUT Input )
{
   VS_OUTPUT Output;
   Output.Position = mul(Input.Position, matViewProjection); 

   float3 normal = mul(Input.Normal, matViewInverseTranspose);
   normal = mul( normal, matProjection );

   Output.Position.xy += OutlineWidth * Output.Position.z * normal.xy;  
   Output.Color = OutlineColor;
  
   return Output;
}

struct PS_INPUT
{
   float4 Color : COLOR0;
};

float4 PS(PS_INPUT Input) : COLOR0
{  
   return Input.Color;
  
}
//--------------------------------------------------------------//
// Pass 1
//--------------------------------------------------------------//

//float4x4 matViewProjection : ViewProjection;
float4x4 matWorldInverse : WorldInverse;
float4x4 matWorldViewInverse
<
   string UIName = "matWorldViewInverse";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
> = float4x4( 1.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 1.00 );

float4 lightPositionView
<
   string UIName = "lightPositionView";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 1.00, 1.00, 0.00, 1.00 );

struct VS_INPUT2
{
   float4 Position : POSITION;
   float3 Normal : NORMAL;
};

struct VS_OUTPUT2
{
   float4 Position : POSITION;
   float3 Diffuse : TEXCOORD1;
};

VS_OUTPUT2 VS2( VS_INPUT2 Input )
{
   VS_OUTPUT2 Output;

   Output.Position = mul( Input.Position, matViewProjection );
  
   float3 objectLightPosition = mul( lightPositionView, matWorldViewInverse);
   float3 lightDir = normalize( Input.Position.xyz - objectLightPosition );
  
   Output.Diffuse = dot( -lightDir, normalize(Input.Normal));
  
   return Output;
} 

float3 SurfaceColor
<
   string UIName = "SurfaceColor";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float3( 1.00, 1.00, 0.00 );

struct PS_INPUT2
{
       float3 Diffuse : TEXCOORD1;
};

float4 PS2(PS_INPUT2 Input) : COLOR
{  
   float3 diffuse = saturate(Input.Diffuse);
   diffuse = ceil(diffuse * 5) / 5.0f;
   return float4(SurfaceColor*diffuse.xyz, 1);
}
//--------------------------------------------------------------//
// Technique Section for Default_DirectX_Effect
//--------------------------------------------------------------//
technique Default_DirectX_Effect
{
   pass Pass_0
   {
	   VertexShader = compile vs_2_0 VS();
	   PixelShader = compile ps_2_0 PS();
   }

   pass Pass_1
   {
      VertexShader = compile vs_2_0 VS2();
      PixelShader = compile ps_2_0 PS2();
   }

}

