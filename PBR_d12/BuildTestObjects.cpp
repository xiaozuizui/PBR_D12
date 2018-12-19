#include "stdafx.h"
#include "LittleEngineResource.h"

void littlemm::LittleEngineResource::BuildTestObjects()
{
	auto boxRitem = std::make_unique<RenderItem>();
	boxRitem->name = "box";
	XMStoreFloat4x4(&boxRitem->World, XMMatrixScaling(2.0f, 2.0f, 2.0f)*XMMatrixTranslation(0.0f, 1.0f, 0.0f));
	XMStoreFloat4x4(&boxRitem->TexTransform, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	boxRitem->ObjCBIndex = 0;
	boxRitem->Mat = mMaterials["crate0"].get();
	boxRitem->Geo = mGeometries["box"].get();
	boxRitem->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	boxRitem->IndexCount = boxRitem->Geo->IndexCount;
	boxRitem->StartIndexLocation = 0;// boxRitem->Geo->DrawArgs["box"].StartIndexLocation;
	boxRitem->BaseVertexLocation = 0;// boxRitem->Geo->DrawArgs["box"].BaseVertexLocation;
	Objects[boxRitem->name] = std::move(boxRitem);
	//mAllRitems.push_back(std::move(boxRitem));

	auto gridRitem = std::make_unique<RenderItem>();
	gridRitem->name = "grid";
	gridRitem->World = MathHelper::Identity4x4();
	XMStoreFloat4x4(&gridRitem->TexTransform, XMMatrixScaling(8.0f, 8.0f, 1.0f));
	gridRitem->ObjCBIndex = 0;
	gridRitem->Mat = mMaterials["tile0"].get();
	gridRitem->Geo = mGeometries["grid"].get();
	gridRitem->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	gridRitem->IndexCount = gridRitem->Geo->IndexCount;
	gridRitem->StartIndexLocation = 0;// gridRitem->Geo->DrawArgs["grid"].StartIndexLocation;
	gridRitem->BaseVertexLocation = 0;// gridRitem->Geo->DrawArgs["grid"].BaseVertexLocation;
	Objects[gridRitem->name] = std::move(gridRitem);
	//mAllRitems.push_back(std::move(gridRitem));

	XMMATRIX brickTexTransform = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	UINT objCBIndex = 2;
	for (int i = 0; i < 5; ++i)
	{
		auto leftCylRitem = std::make_unique<RenderItem>();
		auto rightCylRitem = std::make_unique<RenderItem>();
		auto leftSphereRitem = std::make_unique<RenderItem>();
		auto rightSphereRitem = std::make_unique<RenderItem>();

		XMMATRIX leftCylWorld = XMMatrixTranslation(-5.0f, 1.5f, -10.0f + i * 5.0f);
		XMMATRIX rightCylWorld = XMMatrixTranslation(+5.0f, 1.5f, -10.0f + i * 5.0f);

		XMMATRIX leftSphereWorld = XMMatrixTranslation(-5.0f, 3.5f, -10.0f + i * 5.0f);
		XMMATRIX rightSphereWorld = XMMatrixTranslation(+5.0f, 3.5f, -10.0f + i * 5.0f);

		XMStoreFloat4x4(&leftCylRitem->World, rightCylWorld);
		XMStoreFloat4x4(&leftCylRitem->TexTransform, brickTexTransform);
		leftCylRitem->name = "leftc";
		leftCylRitem->ObjCBIndex = 0;// objCBIndex++;
		leftCylRitem->Mat = mMaterials["bricks0"].get();
		leftCylRitem->Geo = mGeometries["cylinder"].get();
		leftCylRitem->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		leftCylRitem->IndexCount = leftCylRitem->Geo->IndexCount;
		leftCylRitem->StartIndexLocation = 0;//leftCylRitem->Geo->DrawArgs["cylinder"].StartIndexLocation;
		leftCylRitem->BaseVertexLocation = 0;//leftCylRitem->Geo->DrawArgs["cylinder"].BaseVertexLocation;

		XMStoreFloat4x4(&rightCylRitem->World, leftCylWorld);
		XMStoreFloat4x4(&rightCylRitem->TexTransform, brickTexTransform);
		rightCylRitem->name = "rightc";
		rightCylRitem->ObjCBIndex = 0;// objCBIndex++;
		rightCylRitem->Mat = mMaterials["bricks0"].get();
		rightCylRitem->Geo = mGeometries["cylinder"].get();
		rightCylRitem->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		rightCylRitem->IndexCount = rightCylRitem->Geo->IndexCount;
		rightCylRitem->StartIndexLocation = 0;
		rightCylRitem->BaseVertexLocation = 0;

		XMStoreFloat4x4(&leftSphereRitem->World, leftSphereWorld);
		leftSphereRitem->name = "lefts";
		leftSphereRitem->TexTransform = MathHelper::Identity4x4();
		leftSphereRitem->ObjCBIndex = 0;// objCBIndex++;
		leftSphereRitem->Mat = mMaterials["stone0"].get();
		leftSphereRitem->Geo = mGeometries["sphere"].get();
		leftSphereRitem->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		leftSphereRitem->IndexCount = leftSphereRitem->Geo->IndexCount;
		leftSphereRitem->StartIndexLocation = 0;
		leftSphereRitem->BaseVertexLocation = 0;

		XMStoreFloat4x4(&rightSphereRitem->World, rightSphereWorld);
		rightSphereRitem->name = "rights";
		rightSphereRitem->TexTransform = MathHelper::Identity4x4();
		rightSphereRitem->ObjCBIndex = 0;// objCBIndex++;
		rightSphereRitem->Mat = mMaterials["stone0"].get();
		rightSphereRitem->Geo = mGeometries["sphere"].get();
		rightSphereRitem->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		rightSphereRitem->IndexCount = rightSphereRitem->Geo->IndexCount;
		rightSphereRitem->StartIndexLocation = 0;// rightSphereRitem->Geo->DrawArgs["sphere"].StartIndexLocation;
		rightSphereRitem->BaseVertexLocation = 0;// rightSphereRitem->Geo->DrawArgs["sphere"].BaseVertexLocation;


		Objects[leftCylRitem->name] = std::move(leftCylRitem);
		Objects[rightCylRitem->name] = std::move(rightCylRitem);
		Objects[leftSphereRitem->name] = std::move(leftSphereRitem);
		Objects[rightSphereRitem->name] = std::move(rightSphereRitem);


//		mAllRitems.push_back(std::move(leftCylRitem));
	//	mAllRitems.push_back(std::move(rightCylRitem));
		//mAllRitems.push_back(std::move(leftSphereRitem));
		//mAllRitems.push_back(std::move(rightSphereRitem));
	}

	// All the render items are opaque.
	
	for (auto& e : Objects)
	{
		mAllRitems.push_back(e.second.get());
	}
		//mOpaqueRitems.push_back(e.get());

}
