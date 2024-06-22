struct VS_Input
{
	float2 position: POSITION;
	float2 uv: UV;
};

struct VS_Output
{
	float4 position: SV_POSITION;
	float2 uv: UV;
};

Texture2D my_texture;
SamplerState my_sampler;

float4 main(VS_Output input): SV_TARGET
{	
	return my_texture.Sample(my_sampler, input.uv);
};