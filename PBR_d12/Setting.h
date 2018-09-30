#pragma once

class Setting
{
	
public:

	Setting();
	~Setting();


	static int gNumFrameResource;

	static void InitSetting()
	{
		gNumFrameResource = 3;
	}
};