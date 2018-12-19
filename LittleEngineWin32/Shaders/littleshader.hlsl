
SamplerState gsamPointWrap        : register(s0);
SamplerState gsamPointClamp       : register(s1);
SamplerState gsamLinearWrap       : register(s2);
SamplerState gsamLinearClamp      : register(s3);
SamplerState gsamAnisotropicWrap  : register(s4);
SamplerState gsamAnisotropicClamp : register(s5);



struct MaterialData
{
	float4   DiffuseAlbedo;
	float3   FresnelR0;
	float    Roughness;
	float4x4 MatTransform;
	uint     DiffuseMapIndex;
	uint     MatPad0;
	uint     MatPad1;
	uint     MatPad2;
};


//
Texture2D gDiffuseMap[4] : register(t0);
StructuredBuffer<MaterialData> gMaterialData : register(t0, space1);



cbuffer cbPassPerFrame : register(b0)
{
	float4x4 gView;
	float4x4 gInvView;
	float4x4 gProj;
	float4x4 gInvProj;
	float4x4 gViewProj;
	float4x4 gInvViewProj;
	float3 gEyePosW;
	float cbPerObjectPad0;
	float3 gLookAt;
	float cbPerObjectPad1;
	float2 gRenderTargetSize;
	float2 gInvRenderTargetSize;
	float gNearZ;
	float gFarZ;
	float gTotalTime;
	float gDeltaTime;
	float4 gAmbientLight;

	// Indices [0, NUM_DIR_LIGHTS) are directional lights;
	// indices [NUM_DIR_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHTS) are point lights;
	// indices [NUM_DIR_LIGHTS+NUM_POINT_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHT+NUM_SPOT_LIGHTS)
	// are spot lights for a maximum of MaxLights per object.
	//Light gLights[MaxLights];
};

cbuffer cbPerObject : register(b1)
{
	float4x4 gWorld;
	float4x4 gTexTransform;
	uint gMaterialIndex;
	uint gObjPad0;
	uint gObjPad1;
	uint gObjPad2;
};

struct VertexIn
{
	float3 PosL    : POSITION;
    float3 Normal : NORMAL;
	float2 TexC    : TEXCOORD;
};

struct VertexOut
{
	float4 PosH    : SV_POSITION;
    float3 PosW    : POSITION;
    float3 NormalW : NORMAL;
	float2 TexC    : TEXCOORD;
};

VertexOut VS(VertexIn vin)
{

	MaterialData matData = gMaterialData[gMaterialIndex];

	VertexOut vout = (VertexOut)0.0f;
	float4 posw = mul(float4(vin.PosL, 1.0f), gWorld);
	vout.PosW= posw.xyz;

	vout.NormalW = mul(vin.Normal,(float3x3)gWorld);
	vout.PosH = mul(posw,gViewProj);
    vout.TexC = float2(0.0f,1.0f);

	float4 texC = mul(float4(vin.TexC, 0.0f, 1.0f), gTexTransform);
	float4 tex = mul(texC,matData.MatTransform);
	vout.TexC = texC.xy;

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{

	MaterialData matData = gMaterialData[gMaterialIndex];
	float4 diffuseAlbedo = matData.DiffuseAlbedo;
	float3 fresnelR0 = matData.FresnelR0;
	float  roughness = matData.Roughness;
	uint diffuseTexIndex = matData.DiffuseMapIndex;


	diffuseAlbedo *= gDiffuseMap[diffuseTexIndex].Sample(gsamLinearWrap, pin.TexC);
	float4 ambient = gAmbientLight*diffuseAlbedo;

	float4 color = float4(1.0f,1.0f,1.0f,1.0f);

	float4 litColor = ambient+float4(0.2f,0.2f,0.2f,0.2f);

	litColor.a = diffuseAlbedo.a;
	color = litColor;
	
	pin.NormalW = normalize(pin.NormalW);
	//float e = dot( mul(pin.NormalW, (float3x3)gViewProj),gLookAt);
	
	//if (e < 0.2f)
		//color = float4(1.0f, 1.0f, 1.0f, 1.0f);
    // Common convention to take alpha from diffuse albedo.
    
	color = float4(mul(pin.NormalW, (float3x3)gViewProj),0.0f);
    return color;
	//color = ambient;
	
    //return ambient;
}


