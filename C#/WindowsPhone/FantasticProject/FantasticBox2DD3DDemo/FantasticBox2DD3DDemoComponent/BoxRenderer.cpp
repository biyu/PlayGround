#include "pch.h"
#include <fstream>
#include "BoxRenderer.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;

class Box2DQueryCallback : public b2QueryCallback
{
public:
	float worldX;
	float worldY;
public:
	/// Called for each fixture found in the query AABB.
	/// @return false to terminate the query.
	bool ReportFixture(b2Fixture* fixture)
	{
		b2Body* body = fixture->GetBody();
		if (body)
		{
			body->ApplyForceToCenter(b2Vec2(0.0f, 80.0f));
		}
	}
};

BoxRenderer::BoxRenderer() : loadingcomplete(false)
{
}

BoxRenderer::~BoxRenderer()
{
	if (box2dWorld != nullptr)
	{
		delete box2dWorld;
	}
}

// Direct3DBase methods.
void BoxRenderer::CreateDeviceResources()
{
#pragma region InitialPipeline

	auto loadVSTask = DX::ReadDataAsync("BoxVertexShader.cso");
	auto loadPSTask = DX::ReadDataAsync("BoxPixelShader.cso");

	auto createVSTask = loadVSTask.then([this](Platform::Array<byte>^ fileData) {
		DX::ThrowIfFailed(
			// create vertex shader
			m_d3dDevice->CreateVertexShader(
			fileData->Data,
			fileData->Length,
			nullptr,
			&vertexshader
			)
			);
#pragma region InitialInputLayout

		// initialize input layout
		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            //{"COLOR",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};

		DX::ThrowIfFailed(
			// create input layout
			m_d3dDevice->CreateInputLayout(
			ied, 
			ARRAYSIZE(ied),
			fileData->Data,
			fileData->Length,
			&inputlayout
			)
			);
#pragma endregion
	});

	auto createPSTask = loadPSTask.then([this](Platform::Array<byte>^ fileData) {
		DX::ThrowIfFailed(
			// create pixel shader
			m_d3dDevice->CreatePixelShader(
			fileData->Data,
			fileData->Length,
			nullptr,
			&pixelshader
			)
			);
	});

#pragma endregion

#pragma region InitialGraphics

	auto createCubeTask = (createPSTask && createVSTask).then([this] () { 
		InitialVertex();
		InitialConstantBuffer();
		InitialCamera();
		InitialTexture();
		InitialWorldMatrix();
		InitialBox2DWorld();
	});

	createCubeTask.then([this] () {
		loadingcomplete = true;
	});

#pragma endregion

}

void BoxRenderer::InitialVertex()
{
	// vertex buffer
	// triangle vertices positions
	VERTEX vertices[] = {
		// small boxes
		{ XMFLOAT3(-HALF_WIDTH_OF_BOX, -HALF_HEIGHT_OF_BOX, 1.0f), XMFLOAT2(0.0f, 1.0f) /*XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)*/ },
        { XMFLOAT3(-HALF_WIDTH_OF_BOX, HALF_HEIGHT_OF_BOX, 1.0f), XMFLOAT2(0.0f, 0.0f) /*XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)*/ },
		{ XMFLOAT3(HALF_WIDTH_OF_BOX, HALF_HEIGHT_OF_BOX, 1.0f), XMFLOAT2(1.0f, 0.0f) /*XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)*/ },
		{ XMFLOAT3(HALF_WIDTH_OF_BOX, -HALF_HEIGHT_OF_BOX, 1.0f), XMFLOAT2(1.0f, 1.0f) /*XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)*/ },
		// ground box
		{ XMFLOAT3(-HALF_WIDTH_OF_GROUND_BOX, -HALF_HEIGHT_OF_GROUND_BOX, 1.0f), XMFLOAT2(0.0f, 1.0f) /*XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)*/ },
        { XMFLOAT3(-HALF_WIDTH_OF_GROUND_BOX, HALF_HEIGHT_OF_GROUND_BOX, 1.0f), XMFLOAT2(0.0f, 0.0f) /*XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)*/ },
		{ XMFLOAT3(HALF_WIDTH_OF_GROUND_BOX, HALF_HEIGHT_OF_GROUND_BOX, 1.0f), XMFLOAT2(1.0f, 0.0f) /*XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)*/ },
		{ XMFLOAT3(HALF_WIDTH_OF_GROUND_BOX, -HALF_HEIGHT_OF_GROUND_BOX, 1.0f), XMFLOAT2(0.0f, 1.0f) /*XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)*/ },
	};
	// create buffer description
	D3D11_BUFFER_DESC vertexBD = {0};
	// the size of the buffer that will be created
	vertexBD.ByteWidth = sizeof(VERTEX) * ARRAYSIZE(vertices);
	// tells Direct3D what kind of buffer to make
	vertexBD.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// a description of the data we wish to store in the vertex buffer
    D3D11_SUBRESOURCE_DATA vertexSRD = {vertices, 0, 0};
	// creates the buffer
    m_d3dDevice->CreateBuffer(&vertexBD, &vertexSRD, &vertexbuffer);

	// index buffer
	// index list
	DWORD indices[] = {
		// small box
		0, 1, 2,
		0, 2, 3,
		// ground box
		4, 5, 6,
		4, 6, 7
	};
	// buffer description
	D3D11_BUFFER_DESC indexBD;
	indexBD.Usage = D3D11_USAGE_DEFAULT;
	indexBD.ByteWidth = sizeof(DWORD) * ARRAYSIZE(indices);
	indexBD.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBD.CPUAccessFlags = 0;
	indexBD.MiscFlags = 0;
	// define subresource data
	D3D11_SUBRESOURCE_DATA indexSRD;
	indexSRD.pSysMem = indices;
	m_d3dDevice->CreateBuffer(&indexBD,&indexSRD, indexbuffer.GetAddressOf());
}

void BoxRenderer::InitialConstantBuffer()
{
	// constant buffer
	// buffer description
	D3D11_BUFFER_DESC cbbd;	
	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(cbPerObject);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;
	// create constant buffer
	m_d3dDevice->CreateBuffer(&cbbd, NULL, &cbperobjectbuffer);
}

void BoxRenderer::InitialCamera()
{
	// set camero position, target and up
	camposition = XMVectorSet( 0.0f, 0.0f, CAMERA_POSITION, 0.0f );
	camtarget = XMVectorSet( 0.0f, 0.0f, 0.0f, 0.0f );
	camup = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
	// create view space for a left-handed coordinate system by using camera info 
	camview = XMMatrixLookAtLH(camposition, camtarget, camup);	
	// create projection space
	camprojection = XMMatrixPerspectiveFovLH( 0.4f*3.14f, (float)(m_windowBounds.Width / m_windowBounds.Height), 0.1f, 1000.0f);
}
void BoxRenderer::InitialTexture()
{
	// load DDS texture from file (DirectXTK); windows phone only support DDS texture
	// create box texture
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> boxTextureResource;
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(
		m_d3dDevice.Get(),
		L"wood_box_texture.dds",
		NULL,
		&boxTextureResource,
		NULL
		)
		);
	textures.push_back(boxTextureResource);

	// create ground texture
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> groundTextureResource;
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(
		m_d3dDevice.Get(),
		L"wood_ground_texture.dds",
		NULL,
		&groundTextureResource,
		NULL
		)
		);
	textures.push_back(groundTextureResource);

	// sampler description
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory( &sampDesc, sizeof(sampDesc) );
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	DX::ThrowIfFailed(
		m_d3dDevice->CreateSamplerState(
		&sampDesc, 
		texSamplerState.GetAddressOf()
		)
		);
}

void BoxRenderer::InitialWorldMatrix()
{
	// initial matrix of boxes
	int numOfLine = (int)std::ceil((float)NUM_OF_BOXES / NUM_OF_BOXES_PER_LINE);
	for (int index=0; index<NUM_OF_BOXES; index++)
	{
		int indexOfLine = index % NUM_OF_BOXES_PER_LINE;
		int line = (int) index / NUM_OF_BOXES_PER_LINE;
		//Define box's world space matrix
		float trans_x = (HALF_WIDTH_OF_BOX * 2 + GAP_SPACE_X) * indexOfLine - (HALF_WIDTH_OF_BOX * NUM_OF_BOXES_PER_LINE + GAP_SPACE_X * (NUM_OF_BOXES_PER_LINE - 1) / 2);
		float trans_y = BOXES_CONSTANT_TRANSLATION_Y + HALF_HEIGHT_OF_BOX * 2 * numOfLine + GAP_SPACE_Y * (numOfLine - 1) - (HALF_HEIGHT_OF_BOX * 2 + GAP_SPACE_Y) * line;

		CreateNewDirectXBox(trans_x + (line%2)*GAP_Delta, trans_y);
	}
	// initial matrix of ground
	groundWorldMatrix = XMMatrixTranslation(0.0f, GROUND_CONSTANT_TRANSLATION_Y, 0);
}

void BoxRenderer::InitialBox2DWorld()
{
	// create box2d world
	b2Vec2 gravity(0.0f, -10.0f);
	bool doSleep = true;
	box2dWorld = new b2World(gravity, doSleep);

	// create static ground box body in box2d world
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, GROUND_CONSTANT_TRANSLATION_Y);
	b2Body* box2dGroundBody = box2dWorld->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(HALF_WIDTH_OF_GROUND_BOX, HALF_HEIGHT_OF_GROUND_BOX);
	box2dGroundBody->CreateFixture(&groundBox, 0.0f);

	// create dynamic box bodies in box2d world
	for (int i=0; i<NUM_OF_BOXES; i++)
	{
		DirectX::XMVECTOR scaleVector;
		DirectX::XMVECTOR rotationVector;
		DirectX::XMVECTOR translationVector;
		DirectX::XMMatrixDecompose(&scaleVector, &rotationVector, &translationVector, boxWorldMatrixUpdateV.at(i));

		CreateNewBox2DBox(translationVector.m128_f32[0], translationVector.m128_f32[1]);
	}
}

void BoxRenderer::CreateWindowSizeDependentResources()
{
	Direct3DBase::CreateWindowSizeDependentResources();
}

void BoxRenderer::Render()
{
// set our new render target object as the active render target
    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), nullptr);
	// clear the back buffer to a deep blue
    float color[4] = {0.0f, 0.2f, 0.4f, 1.0f};
    m_d3dContext->ClearRenderTargetView(
		m_renderTargetView.Get(), 
		color
		);

	// Only draw the cube once it is loaded (loading is asynchronous).
	if (!loadingcomplete)
	{
		return;
	}

    // set the vertex buffer
    UINT stride = sizeof(VERTEX);
    UINT offset = 0;
    m_d3dContext->IASetVertexBuffers(0, 1, vertexbuffer.GetAddressOf(), &stride, &offset);
	// set index buffer
	m_d3dContext->IASetIndexBuffer(indexbuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	// set the primitive topology
    m_d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// set input layout
	m_d3dContext->IASetInputLayout(inputlayout.Get());
	// set vertex shader
	m_d3dContext->VSSetShader(vertexshader.Get(), nullptr, 0);
	// set pixel shader
	m_d3dContext->PSSetShader(pixelshader.Get(), nullptr, 0);
	
	m_d3dContext->PSSetShaderResources( 0, 1, textures[0].GetAddressOf());
	m_d3dContext->PSSetSamplers(0, 1, texSamplerState.GetAddressOf());

	// draw all boxes
	for (int i=0; i<(int)box2dBoxBodyV.size(); i++)
	{
		wvp = boxWorldMatrixV.at(i) * camview * camprojection;
		cbperobj.WVP = XMMatrixTranspose(wvp);	
		m_d3dContext->UpdateSubresource(cbperobjectbuffer.Get(), 0, NULL, &cbperobj, 0, 0);
		m_d3dContext->VSSetConstantBuffers( 0, 1, cbperobjectbuffer.GetAddressOf() );
		// draw box by indices
		m_d3dContext->DrawIndexed(6, 0, 0);
	}

	m_d3dContext->PSSetShaderResources( 0, 1, textures[1].GetAddressOf());
	m_d3dContext->PSSetSamplers(0, 1, texSamplerState.GetAddressOf());

	wvp = groundWorldMatrix * camview * camprojection;
	cbperobj.WVP = XMMatrixTranspose(wvp);	
	m_d3dContext->UpdateSubresource(cbperobjectbuffer.Get(), 0, NULL, &cbperobj, 0, 0);
	m_d3dContext->VSSetConstantBuffers( 0, 1, cbperobjectbuffer.GetAddressOf() );
	// draw ground box
	m_d3dContext->DrawIndexed(6, 0, 4);

    //// switch the back buffer and the front buffer
    //swapchain->Present(1, 0);
}
	
// Method for updating time-dependent objects.
void BoxRenderer::Update(float timeTotal, float timeDelta)
{
	// update object vectors before render
	UpdateWorldVector();
	UpdateBox2DVector();

	if (box2dWorld != nullptr)
	{
		float timeStep = 1.0f / 30.0f;
		int velocityIterations = 6;
		int positionIterations = 2;

		box2dWorld->Step(timeStep, velocityIterations, positionIterations);
		for (int i=0; i<(int)box2dBoxBodyV.size(); i++)
		{
			b2Vec2 box2dPosition = box2dBoxBodyV.at(i)->GetPosition();
			float box2dAngle = box2dBoxBodyV.at(i)->GetAngle();

			// get current direct3d matrix for each box
			DirectX::XMMATRIX boxMatrix = XMMatrixIdentity();
			// translate box
			Translation = XMMatrixTranslation(box2dPosition.x, box2dPosition.y, 0.0f);
			// rotate box
			XMVECTOR rotaxis = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
			Rotation = XMMatrixRotationAxis(rotaxis, box2dAngle);
			// calculate new box's world space matrix
			boxMatrix = Rotation * Translation;

			boxWorldMatrixV[i] = boxMatrix;
		}
	}
}

void BoxRenderer::UpdateBox2DVector()
{
	if (loadingcomplete)
	{
		// check update vector if any new item here
		if ((int)box2dBoxBodyUpdateV.size() != 0)
		{
			for (int i=0; i<(int)box2dBoxBodyUpdateV.size(); i++)
			{
				box2dBoxBodyV.push_back(box2dBoxBodyUpdateV.at(i));
			}
			// clean update buffer
			box2dBoxBodyUpdateV.clear();
		}
	}
}

void BoxRenderer::UpdateWorldVector()
{
	if(loadingcomplete)
	{
		if ((int)boxWorldMatrixUpdateV.size() != 0)
		{
			for (int i=0; i<(int) (int)boxWorldMatrixUpdateV.size(); i++)
			{
				boxWorldMatrixV.push_back(boxWorldMatrixUpdateV.at(i));
			}
			// clean update buffer
			boxWorldMatrixUpdateV.clear();
		}

	}
}

void BoxRenderer::CreateNewBox2DBox(float worldX, float worldY)
{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(worldX, worldY);
		b2Body* body = box2dWorld->CreateBody(&bodyDef);

		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(HALF_WIDTH_OF_BOX, HALF_HEIGHT_OF_BOX);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.restitution = BOX_RESTITUTION;
		body->CreateFixture(&fixtureDef);

		//box2dBoxBodyV.push_back(body);
		box2dBoxBodyUpdateV.push_back(body);
}

void BoxRenderer::CreateNewDirectXBox(float worldX, float worldY)
{
	DirectX::XMMATRIX boxworld = XMMatrixIdentity();
	Translation = XMMatrixTranslation( worldX, worldY, 0.0f );
	//Set box1's world space using the transformations
	boxworld = Translation;
	//boxWorldMatrixV.push_back(boxworld);
	boxWorldMatrixUpdateV.push_back(boxworld);
}

void BoxRenderer::CreateNewBox(float worldX, float worldY)
{
	CreateNewDirectXBox(worldX, worldY);
	CreateNewBox2DBox(worldX, worldY);
}

XMVECTOR BoxRenderer::ScreenCoordToWorldCoord(float screenX, float screenY)
{
	XMVECTOR p1;
	// near point in view space
	p1 = XMVector3Unproject(XMVectorSet(screenX, screenY, 0.1f, 0.0f), 0.0f, 0.0f, m_windowBounds.Width, m_windowBounds.Height, 0.0f, 1.0f, camprojection, camview, XMMatrixIdentity());
	XMVECTOR p2;
	// far point in view space
	p2 = XMVector3Unproject(XMVectorSet(screenX, screenY, 1.0f, 0.0f), 0.0f, 0.0f, m_windowBounds.Width, m_windowBounds.Height, 0.0f, 1.0f, camprojection, camview, XMMatrixIdentity());

	float wz = 0.0f;
	// equation of line in 3d world
	float wx = ((wz-p1.m128_f32[2])*(p2.m128_f32[0]-p1.m128_f32[0]))/(p2.m128_f32[2]-p1.m128_f32[2]) + p1.m128_f32[0];
	float wy = ((wz-p1.m128_f32[2])*(p2.m128_f32[1]-p1.m128_f32[1]))/(p2.m128_f32[2]-p1.m128_f32[2]) + p1.m128_f32[1];

	return XMVectorSet(wx, wy, wz, 0.0f);
}

void BoxRenderer::ForceBoxJump()
{

}

void BoxRenderer::HandleMouseRelease(float screenX, float screenY)
{
	XMVECTOR worldVec;
	worldVec = ScreenCoordToWorldCoord(screenX, screenY);
	float worldX, worldY;
	worldX = worldVec.m128_f32[0];
	worldY = worldVec.m128_f32[1];

	CreateNewBox(worldX, worldY);
}