struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	//float4 Color : COLOR;
	float2 TexCoord : TEXCOORD;
};

Texture2D ObjTexture;
SamplerState ObjSamplerState;

float4 main(PS_INPUT input) : SV_TARGET
{
	//return input.Color;
	return ObjTexture.Sample( ObjSamplerState, input.TexCoord );
}