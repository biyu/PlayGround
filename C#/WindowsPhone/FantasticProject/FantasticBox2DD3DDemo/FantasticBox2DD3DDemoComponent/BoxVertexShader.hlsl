cbuffer cbPerObject
{
	float4x4 WVP;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	//float4 Color : COLOR;
	float2 TexCoord : TEXCOORD;
};

VS_OUTPUT main(float4 inPos : POSITION,  float2 inTexCoord : TEXCOORD /*float4 inColor : COLOR*/)
{
    VS_OUTPUT output;

    output.Pos = mul(inPos, WVP);
    //output.Color = inColor;
	 output.TexCoord = inTexCoord;

    return output;
}