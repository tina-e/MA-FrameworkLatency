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

VS_Output main(VS_Input input)
{
	VS_Output output;
	output.position = float4(input.position, 0.0f, 1.0f);
	output.uv = input.uv;
	return output;
};

