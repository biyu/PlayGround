#pragma once

#include "Direct3DBase.h"

#define NUM_OF_BOXES 1
#define NUM_OF_BOXES_PER_LINE 6
#define HALF_WIDTH_OF_BOX 2.0f
#define HALF_HEIGHT_OF_BOX 2.0f
#define HALF_WIDTH_OF_GROUND_BOX 30.0f
#define HALF_HEIGHT_OF_GROUND_BOX 1.5f
#define GAP_SPACE_X 1.0f
#define GAP_SPACE_Y 1.0f
#define GAP_Delta 0.5f
#define BOXES_CONSTANT_TRANSLATION_Y 15.0f
#define GROUND_CONSTANT_TRANSLATION_Y -15.0f

#define CAMERA_POSITION -90.0f

#define BOX_RESTITUTION 0.7f

struct VERTEX
{
	DirectX::XMFLOAT3 pos;
	//DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT2 texCoord;
};

struct cbPerObject
{
	DirectX::XMMATRIX WVP;
};

// This class renders a simple spinning cube.
ref class BoxRenderer sealed : public Direct3DBase
{
public:
	BoxRenderer();
	virtual ~BoxRenderer();
	// Direct3DBase methods.
	virtual void CreateDeviceResources() override;
	virtual void CreateWindowSizeDependentResources() override;
	virtual void Render() override;
	// Method for updating time-dependent objects.
	void Update(float timeTotal, float timeDelta);
public:
	void HandleMouseRelease(float screenX, float screenY);
private:
	void CreateNewBox(float worldX, float worldY);
	void CreateNewBox2DBox(float worldX, float worldY);
	void CreateNewDirectXBox(float worldX, float worldY);
	DirectX::XMVECTOR ScreenCoordToWorldCoord(float screenX, float screenY);
private:
	// direct3d
	void InitialVertex();
	void InitialConstantBuffer();
	void InitialCamera();
	void InitialTexture();
	void InitialWorldMatrix();
private:
	// box2d
	void InitialBox2DWorld();
	void ForceBoxJump();
private:
	void UpdateBox2DVector();
	void UpdateWorldVector();
private:
	// direct 3d
	// vertex buffer in system memory
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexbuffer;
	// index buffer
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexbuffer;
	// constant buffer for matrix
	Microsoft::WRL::ComPtr<ID3D11Buffer> cbperobjectbuffer;
	// vertext and pixel shaders
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexshader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelshader;
	// input layout
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputlayout;
	// texture
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> >textures;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> texSamplerState;

	DirectX::XMMATRIX wvp;
	//DirectX::XMMATRIX world;
	DirectX::XMMATRIX camview;
	DirectX::XMMATRIX camprojection;

	DirectX::XMVECTOR camposition;
	DirectX::XMVECTOR camtarget;
	DirectX::XMVECTOR camup;

	cbPerObject cbperobj;
	DirectX::XMMATRIX Rotation;
	DirectX::XMMATRIX Scale;
	DirectX::XMMATRIX Translation;
	// matrix collection of Direct3D boxes
	std::vector<DirectX::XMMATRIX> boxWorldMatrixV;
	std::vector<DirectX::XMMATRIX> boxWorldMatrixUpdateV;
	DirectX::XMMATRIX groundWorldMatrix;
private:
	// box2d
	b2World* box2dWorld;
	b2Body* box2dGroundBody;
	std::vector<b2Body*> box2dBoxBodyV;
	std::vector<b2Body*> box2dBoxBodyUpdateV;
private:
	bool loadingcomplete;
};
