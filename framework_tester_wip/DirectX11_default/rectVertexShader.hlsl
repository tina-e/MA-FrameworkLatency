struct Input {
	float2 position : POSITION;
};

struct Output {
	float4 position : SV_POSITION;
    float3 color : COLOR;
};

Output main(Input input)
{
	Output output;
	output.position = float4(input.position.x, input.position.y, 0, 1);
	return output;
}
