#pragma once
namespace  littlemm
{
	struct  IAttribute
	{
		enum Type
		{
			COLOR,
			RANGE,
			TEXTURE,
		};
	};

	struct PropertyBase 
	{
		virtual void setValue();
		virtual void getValue();

	};
}