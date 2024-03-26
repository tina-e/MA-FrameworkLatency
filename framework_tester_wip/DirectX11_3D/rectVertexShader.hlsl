//struct Input {
//	float3 position : POSITION;
//	float3 color : COLOR;
//};

//struct Output {
//	float4 position : SV_POSITION;
//	float3 color : COLOR;
//};

//Output main(Input input) {
//	Output output;

//	output.position = float4(input.position.x, input.position.y, input.position.z, 1);
//	output.color = input.color;

//	return output;
//}

cbuffer ConstantBuffer : register(b0)
{
    matrix WorldViewProjection;
}

struct Input
{
    float3 position : POSITION;
    float3 color : COLOR;
};

struct Output
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

Output main(Input input)
{
    Output output;
    output.position = mul(float4(input.position, 1.0f), WorldViewProjection);
    output.color = input.color;
    return output;
}
