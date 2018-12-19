#pragma once
#include "resource.h"
#include "LittleEngine.h"
#include "UploadBuffer.h"
#include "Camera.h"
#include "ConstantResource.h"
#include "Setting.h"
#include "Object.h"
#include "GeometryGenerator.h"
#include "Layer.h"
#include "wave.h"
#include "macro.h"


using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;


namespace littlemm
{




	struct RenderItem
	{
		std::string name;

		std::vector<RenderItem*> parent;
		std::vector<RenderItem*> child;


		XMFLOAT4X4 World = MathHelper::Identity4x4();

		XMFLOAT4X4 TexTransform = MathHelper::Identity4x4();


		int NumFramesDirty = Setting::gNumFrameResource;

		MeshGeometry* Geo = nullptr;
		Material* Mat = nullptr;
		ID3D12PipelineState* PiplineState = nullptr;

		D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		UINT ObjCBIndex = -1;

		// DrawIndexedInstanced parameters.
		UINT IndexCount = 0;
		UINT StartIndexLocation = 0;
		int BaseVertexLocation = 0;

	};



	class LittleEngineResource :public LittleEngine
	{
	public:

		LittleEngineResource(HWND hwnd);
		~LittleEngineResource();

		virtual bool Initialize()override;
		//LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)override;

		void GameInit();


		void OnKeyboardInput(const GameTimer & gt);
		void OnMouseDown(WPARAM btnState, int x, int y);
		void OnMouseUp(WPARAM btnState, int x, int y);
		void OnMouseMove(WPARAM btnState, int x, int y);

		virtual void OnResize()override;
		virtual void Update(const GameTimer& gt)override;
		virtual void Draw(const GameTimer& gt)override;

		void AddGeo(std::string name, GeometryGenerator::MeshData* meshdata);

	private:
		LittleEngineResource();
		void BuildFrameResource();//constant per object and frame
		void LoadTexture();
		void BuildMaterials();

		void BuildDescriptorHeaps();
		void BuildRootSignature();
		void BuildShadersAndInputLayout();
		void BuildBoxGeometry();
		void BuildPSO();
		void BuildShadowPath();

		///
	


		void BuildRenderItems();


		/*
		 * 初始化使用
		 */
		void AddOneObjects(const RenderItem & object,RenderLayer layer);




	protected:

		void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);
		void DrawselectedObje(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);

		void AnimateMaterials(const GameTimer& gt);
		void UpdateObjectCBs(const GameTimer& gt);
		void UpdateMaterialBuffer(const GameTimer& gt);
		void UpdateMainPassCB(const GameTimer& gt);

	private:

		std::vector<std::unique_ptr<ConstantResource>> mConstantResource;
		ConstantResource* mCurrConstantResource = nullptr;
		int mCurrConstantResourceIndex = 0;

		//资源类
		Microsoft::WRL::ComPtr<ID3D12RootSignature> mRootSignature = nullptr;

		UINT mCbvSrvDescriptorSize = 0;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mSrvDescriptorHeap = nullptr;



		Microsoft::WRL::ComPtr<ID3DBlob> mvsByteCode = nullptr;
		Microsoft::WRL::ComPtr<ID3DBlob> mpsByteCode = nullptr;

		std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

		//Microsoft::WRL::ComPtr<ID3D12PipelineState> mPSO = nullptr;
		//Microsoft::WRL::ComPtr<ID3D12PipelineState> SeletedPso = nullptr;

		DirectX::XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
		DirectX::XMFLOAT4X4 mView = MathHelper::Identity4x4();
		DirectX::XMFLOAT4X4 mProj = MathHelper::Identity4x4();

		/*float mTheta = 1.5f* DirectX::XM_PI;
		float mPhi = DirectX::XM_PIDIV4;
		float mRadius = 5.0f;*/

		POINT mLastMousePos;

		Camera mCamera;

		std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
		std::unordered_map<std::string, std::unique_ptr<Material>> mMaterials;
		std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;
		std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;
		std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs;

		


		//Microsoft::WRL::ComPtr<ID3DBlob> SelectVSCode = nullptr;
		//Microsoft::WRL::ComPtr<ID3DBlob> SelectPSCode = nullptr;



		//std::vector<Object>
		//
		//std::vector<RenderItem*> mOpaqueRitems;

	public:

		UINT ObjectNum=0;
		//所有物体集合
		std::unordered_map<std::string, std::unique_ptr<RenderItem>> Objects;

		std::vector<RenderItem*> mRitemLayer[(int)RenderLayer::Count];

		std::vector<RenderItem*> shadowObject;
		std::vector<std::unique_ptr<RenderItem>> ShadowPath;



		//渲染物体集合，需要时常更新
		std::vector<RenderItem*> mAllRitems;



		void BuildTestObjects();



		//shaodw test

		std::unique_ptr<RenderItem> boxshaodw;
		//


#ifdef WAVES
		std::unique_ptr<Waves> mWaves;
		RenderItem* mWaveRitem = nullptr;
	private:
		void UpdateWaves(const GameTimer& gt);
		void BuildWater();
#endif
		
	};

}