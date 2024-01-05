struct Input {
	float4 position : SV_POSITION;
	float3 color : COLOR;
};

float4 main(Input input) : SV_TARGET{
    return float4(1, 1, 1, 1);
}
