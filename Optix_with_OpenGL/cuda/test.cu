#include "optix_cuda.h"

struct RadiancePL {
	float3 color;
	int recursive_depth;
};

struct ShadowPL {
	float attenuation;
};

