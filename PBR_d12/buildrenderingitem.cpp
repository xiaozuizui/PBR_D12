#include "stdafx.h"
#include "LittleEngineResource.h"
#include <unordered_map>
#include <iostream>


#define OBJECTNUM ObjectNum++

using namespace littlemm;





void littlemm::LittleEngineResource::AddOneObjects(const RenderItem & object,littlemm::RenderLayer layer)
{
	//&Objects->f
	std::unordered_map<std::string, std::unique_ptr<RenderItem>>::const_iterator it = Objects.find(object.name);


	if (it == Objects.end())
	{
		auto ptr = std::make_unique<RenderItem>(object);
		Objects[object.name] = std::move(ptr);
		mRitemLayer[(int)layer].push_back(Objects[object.name].get());
	}
		
	else
	{
		std::string tempname = object.name+"(1)";
		for (int i=2;i<100;i++)
		{
			if(Objects.find(tempname)==Objects.end())
			{
				
				auto ptr = std::make_unique<RenderItem>(object);
				ptr->name = tempname;
				Objects[tempname] = std::move(ptr);

				mRitemLayer[(int)layer].push_back(Objects[tempname].get());
				break;
			}
			std::stringstream num;
			num << i;
			tempname = object.name + "("+num.str()+")";
			
		}
		//object->name = object->name+ "(1)";
	}

}


void LittleEngineResource::BuildShadowPath()
{
	for(int i =0;i< mRitemLayer[(int)RenderLayer::Shadow].size();i++)
	{

//		ShadowPath.push_back()
	}
}


void littlemm::LittleEngineResource::BuildRenderItems()
{
	//render item 常数更新在Update中

	RenderItem boxRitem;
	//auto boxRitem = std::make_unique<RenderItem>();
	boxRitem.name = "box";
	XMStoreFloat4x4(&boxRitem.World, XMMatrixScaling(2.0f, 2.0f, 2.0f)*XMMatrixTranslation(0.0f, 4.0f, 0.0f));
	XMStoreFloat4x4(&boxRitem.TexTransform, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	boxRitem.ObjCBIndex = ObjectNum++;
	boxRitem.Mat = mMaterials["crate0"].get();
	boxRitem.Geo = mGeometries["box"].get();
	boxRitem.PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	boxRitem.IndexCount = boxRitem.Geo->IndexCount;
	boxRitem.StartIndexLocation = 0;// boxRitem->Geo->DrawArgs["box"].StartIndexLocation;
	boxRitem.BaseVertexLocation = 0;// boxRitem->Geo->DrawArgs["box"].BaseVertexLocation;
	//boxRitem.hasShadow = true;
	//mAllRitems.push_back(std::move(boxRitem));

	//AddOneObjects(boxRitem,RenderLayer::Opaque);
	AddOneObjects(boxRitem, RenderLayer::Opaque);

	//shadowObject.push_back()


	//RenderItem shadowbox;// = std::make_unique<RenderItem>();
	//shadowbox = boxRitem;
	//shadowbox.name = "boxshadow";
	//shadowbox.ObjCBIndex = ObjectNum++;
	//shadowbox.Mat = mMaterials["boxshadow"].get();
	////mShadowedSkullRitem = shadowedSkullRitem.get();
	//AddOneObjects(shadowbox, RenderLayer::Shadow);
	//mRitemLayer[(int)RenderLayer::Shadow].push_back(.get();



	//RenderItem 


	//auto gridRitem = std::make_unique<RenderItem>();
	RenderItem gridRitem;
	gridRitem.name = "grid";
	gridRitem.World = MathHelper::Identity4x4();
	XMStoreFloat4x4(&gridRitem.TexTransform, XMMatrixScaling(8.0f, 8.0f, 1.0f));
	gridRitem.ObjCBIndex = ObjectNum++;
	gridRitem.Mat = mMaterials["tile0"].get();
	gridRitem.Geo = mGeometries["grid"].get();
	gridRitem.PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	gridRitem.IndexCount = gridRitem.Geo->IndexCount;
	gridRitem.StartIndexLocation = 0;// gridRitem->Geo->DrawArgs["grid"].StartIndexLocation;
	gridRitem.BaseVertexLocation = 0;// gridRitem->Geo->DrawArgs["grid"].BaseVertexLocation;
	//mAllRitems.push_back(std::move(gridRitem));

	AddOneObjects(gridRitem,RenderLayer::Opaque);

	XMMATRIX brickTexTransform = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	//UINT objCBIndex = 3;
	for (int i = 0; i < 5; ++i)
	{
		//auto leftCylRitem = std::make_unique<RenderItem>();
		//auto rightCylRitem = std::make_unique<RenderItem>();
		//auto leftSphereRitem = std::make_unique<RenderItem>();
		//auto rightSphereRitem = std::make_unique<RenderItem>();

		RenderItem leftCylRitem;
		RenderItem rightCylRitem;
		RenderItem leftSphereRitem;
		RenderItem rightSphereRitem;



		XMMATRIX leftCylWorld = XMMatrixTranslation(-5.0f, 1.5f, -10.0f + i * 5.0f);
		XMMATRIX rightCylWorld = XMMatrixTranslation(+5.0f, 1.5f, -10.0f + i * 5.0f);

		XMMATRIX leftSphereWorld = XMMatrixTranslation(-5.0f, 3.5f, -10.0f + i * 5.0f);
		XMMATRIX rightSphereWorld = XMMatrixTranslation(+5.0f, 3.5f, -10.0f + i * 5.0f);

		XMStoreFloat4x4(&leftCylRitem.World, rightCylWorld);
		XMStoreFloat4x4(&leftCylRitem.TexTransform, brickTexTransform);
		leftCylRitem.name = "leftc";
		leftCylRitem.ObjCBIndex = ObjectNum++;
		leftCylRitem.Mat = mMaterials["bricks0"].get();
		leftCylRitem.Geo = mGeometries["cylinder"].get();
		leftCylRitem.PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		leftCylRitem.IndexCount = leftCylRitem.Geo->IndexCount;
		leftCylRitem.StartIndexLocation = 0;//leftCylRitem.Geo.DrawArgs["cylinder"].StartIndexLocation;
		leftCylRitem.BaseVertexLocation = 0;//leftCylRitem->Geo->DrawArgs["cylinder"].BaseVertexLocation;
		AddOneObjects(leftCylRitem, RenderLayer::Opaque);


		XMStoreFloat4x4(&rightCylRitem.World, leftCylWorld);
		XMStoreFloat4x4(&rightCylRitem.TexTransform, brickTexTransform);
		rightCylRitem.name = "rightc";
		rightCylRitem.ObjCBIndex = ObjectNum++;
		rightCylRitem.Mat = mMaterials["bricks0"].get();
		rightCylRitem.Geo = mGeometries["cylinder"].get();
		rightCylRitem.PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		rightCylRitem.IndexCount = rightCylRitem.Geo->IndexCount;
		rightCylRitem.StartIndexLocation = 0;
		rightCylRitem.BaseVertexLocation = 0;
		AddOneObjects(rightCylRitem, RenderLayer::Opaque);


		XMStoreFloat4x4(&leftSphereRitem.World, leftSphereWorld);
		leftSphereRitem.name = "lefts";
		leftSphereRitem.TexTransform = MathHelper::Identity4x4();
		leftSphereRitem.ObjCBIndex = ObjectNum++;
		leftSphereRitem.Mat = mMaterials["stone0"].get();
		leftSphereRitem.Geo = mGeometries["sphere"].get();
		leftSphereRitem.PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		leftSphereRitem.IndexCount = leftSphereRitem.Geo->IndexCount;
		leftSphereRitem.StartIndexLocation = 0;
		leftSphereRitem.BaseVertexLocation = 0;
		AddOneObjects(leftSphereRitem, RenderLayer::Opaque);

		XMStoreFloat4x4(&rightSphereRitem.World, rightSphereWorld);
		rightSphereRitem.name = "rights";
		rightSphereRitem.TexTransform = MathHelper::Identity4x4();
		rightSphereRitem.ObjCBIndex = ObjectNum++;
		rightSphereRitem.Mat = mMaterials["stone0"].get();
		rightSphereRitem.Geo = mGeometries["sphere"].get();
		rightSphereRitem.PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		rightSphereRitem.IndexCount = rightSphereRitem.Geo->IndexCount;
		rightSphereRitem.StartIndexLocation = 0;// rightSphereRitem.Geo->DrawArgs["sphere"].StartIndexLocation;
		rightSphereRitem.BaseVertexLocation = 0;// rightSphereRitem->Geo->DrawArgs["sphere"].BaseVertexLocation;
		AddOneObjects(rightSphereRitem, RenderLayer::Opaque);

	//	mAllRitems.push_back(std::move(leftCylRitem));
		//mAllRitems.push_back(std::move(rightCylRitem));
	//	mAllRitems.push_back(std::move(leftSphereRitem));
	//	mAllRitems.push_back(std::move(rightSphereRitem));
	}

#ifdef WAVES
	RenderItem wavesRitem;
	wavesRitem.name = "water";
	//auto wavesRitem = std::make_unique<RenderItem>();
	wavesRitem.World = MathHelper::Identity4x4();
	XMStoreFloat4x4(&wavesRitem.World, XMMatrixTranslation(0.0f, 0.1f, 0.0f));//XMMatrixScaling(0.12f, 0.1f, 0.12f)
	XMStoreFloat4x4(&wavesRitem.TexTransform, XMMatrixScaling(5.0f, 5.0f, 1.0f));
	wavesRitem.ObjCBIndex = ObjectNum++;
	wavesRitem.Mat = mMaterials["water"].get();
	wavesRitem.Geo = mGeometries["waterGeo"].get();
	wavesRitem.PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	wavesRitem.IndexCount = wavesRitem.Geo->IndexCount;
	wavesRitem.StartIndexLocation = 0;//wavesRitemGeo->DrawArgs["grid"].StartIndexLocation;
	wavesRitem.BaseVertexLocation = 0;//wavesRitem->Geo->DrawArgs["grid"].BaseVertexLocation;
	AddOneObjects(wavesRitem, RenderLayer::Transparent);


	mWaveRitem = Objects["water"].get();

#endif

	RenderItem* shadow = Objects["box"].get();

	boxshaodw = std::make_unique<RenderItem>();
	boxshaodw->name = "boxshadow";
	*boxshaodw = *shadow;
	boxshaodw->ObjCBIndex = OBJECTNUM;
	boxshaodw->Mat = mMaterials["boxshadow"].get();


	static auto worldS = XMLoadFloat4x4(&Objects["box"]->World);
	XMVECTOR shadowPlane = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f); // xz plane
	XMVECTOR toMainLight = -XMLoadFloat3(&XMFLOAT3( 0.57735f, -0.57735f, 0.57735f));
	XMMATRIX S = XMMatrixShadow(shadowPlane, toMainLight);
	XMMATRIX shadowOffsetY = XMMatrixTranslation(0.0f, 0.001f, 0.0f);
	XMStoreFloat4x4(&boxshaodw->World, worldS*S*shadowOffsetY);

	//shadowedSkullRitem->Mat = mMaterials["shadowMat"].get();
	//mShadowedSkullRitem = shadowedSkullRitem.get();
	mRitemLayer[(int)RenderLayer::Shadow].push_back(boxshaodw.get());
	mAllRitems.push_back(boxshaodw.get());


	for (auto& e : Objects)
	{
		
		mAllRitems.push_back(e.second.get());
		//mSelectRitems.push_back(e.second.get());
	}

	// All the render items are opaque.
	//for (auto& e : mAllRitems)
	//	mOpaqueRitems.push_back(e.get());
}
