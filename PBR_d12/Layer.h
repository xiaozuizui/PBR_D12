#include "stdafx.h"


namespace littlemm
{
	enum class RenderLayer : int
	{
		Opaque = 0,
		Transparent,
		AlphaTested,
		Shadow,
		Count
	};
}