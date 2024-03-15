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

cbuffer CBuffer
{
    matrix transform;
};

Output main(Input input)
{
    Output output;

    output.position = mul(float4(input.position.x, input.position.y, input.position.z, 1), transform);
    output.color = input.color;

    return output;
}