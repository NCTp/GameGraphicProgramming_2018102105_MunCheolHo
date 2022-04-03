#include "Renderer/Renderer.h"
#include <d3dcompiler.h>
namespace library {
	/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
	  Method:   Renderer::Renderer
	  Summary:  Constructor
	  Modifies: [m_driverType, m_featureLevel, m_d3dDevice, m_d3dDevice1,
				  m_immediateContext, m_immediateContext1, m_swapChain,
				  m_swapChain1, m_renderTargetView, m_vertexShader,
				  m_pixelShader, m_vertexLayout, m_vertexBuffer].
	M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
	Renderer::Renderer() :

		m_driverType(D3D_DRIVER_TYPE_HARDWARE),
		m_featureLevel(D3D_FEATURE_LEVEL_11_1),

		m_d3dDevice(nullptr),
		m_d3dDevice1(nullptr),
		m_immediateContext(nullptr),
		m_immediateContext1(nullptr),
		m_swapChain(nullptr),
		m_swapChain1(nullptr),
		m_renderTargetView(nullptr),

		m_vertexShader(nullptr),
		m_pixelShader(nullptr),
		m_vertexLayout(nullptr),
		m_vertexBuffer(nullptr)
	{}


	/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
	  Method:   Renderer::Initialize
	  Summary:  Creates Direct3D device and swap chain
	  Args:     HWND hWnd
				  Handle to the window
	  Modifies: [m_d3dDevice, m_featureLevel, m_immediateContext,
				  m_d3dDevice1, m_immediateContext1, m_swapChain1,
				  m_swapChain, m_renderTargetView, m_vertexShader,
				  m_vertexLayout, m_pixelShader, m_vertexBuffer].
	  Returns:  HRESULT
				  Status code
	M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
	HRESULT Renderer::Initialize(_In_ HWND hWnd)
	{
		HRESULT hr = S_OK;

#pragma region GetInterfaceForDeviceAndContext

		// This flag adds support for surfaces with a color-channel ordering different
		// from the API default. It is required for compatibility with Direct2D.
		UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
		const D3D_FEATURE_LEVEL featureLevels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0
		};

#if defined(DEBUG) || defined(_DEBUG)
		deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		hr = D3D11CreateDevice(
			nullptr,								// Specify nullptr to use the default adapter.
			m_driverType,							// Create a device using the hardware graphics driver.
			nullptr,								// Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
			deviceFlags,							// Set debug and Direct2D compatibility flags.
			featureLevels,							// List of feature levels this app can support.
			ARRAYSIZE(featureLevels),				// Size of the list above.
			D3D11_SDK_VERSION,						// Always set this to D3D11_SDK_VERSION for Windows Store apps.
			&m_d3dDevice,							// Returns the Direct3D device created.
			&m_featureLevel,						// Returns feature level of device created.
			&m_immediateContext						// Returns the device immediate context.
		);
		if (FAILED(hr)) return hr;

		m_d3dDevice.As(&m_d3dDevice1);
		m_immediateContext.As(&m_immediateContext1);

#pragma endregion

#pragma region CreateSwapChain

		DXGI_SWAP_CHAIN_DESC desc = {
			
			.BufferDesc{
				.Format = DXGI_FORMAT_B8G8R8A8_UNORM
				},
			.SampleDesc = {
				.Count = 1, //multisampling setting
				.Quality = 0 //vendor-specific flag
			},

			.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,

			.BufferCount = 2,

			.OutputWindow = hWnd,
			.Windowed = TRUE,
			.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
		};

		// Create the DXGI device object to use in other factories, such as Direct2D.
		ComPtr<IDXGIDevice3> pDxgiDevice;
		m_d3dDevice.As(&pDxgiDevice);

		// Create swap chain.
		ComPtr<IDXGIAdapter> pAdapter;
		ComPtr<IDXGIFactory> pFactory;

		hr = pDxgiDevice->GetAdapter(&pAdapter);
		if (FAILED(hr)) return hr;

		hr = pAdapter->GetParent(IID_PPV_ARGS(&pFactory));
		if (FAILED(hr)) return hr;

		hr = pFactory->CreateSwapChain(
			m_d3dDevice.Get(),
			&desc,
			&m_swapChain
		);
		if (FAILED(hr)) return hr;

		m_swapChain.As(&m_swapChain1);

#pragma endregion

#pragma region CreateRenderTarget

		ComPtr<ID3D11Texture2D> pBackBuffer;
		D3D11_TEXTURE2D_DESC bbDesc;

		hr = m_swapChain->GetBuffer(
			0,
			__uuidof(ID3D11Texture2D),
			&pBackBuffer);
		if (FAILED(hr)) return hr;

		hr = m_d3dDevice->CreateRenderTargetView(
			pBackBuffer.Get(),
			nullptr,
			&m_renderTargetView
		);
		if (FAILED(hr)) return hr;

		m_immediateContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), nullptr);

		pBackBuffer->GetDesc(&bbDesc);

		// Create a depth-stencil buffer
		ComPtr<ID3D11Texture2D> pDepthStencil;
		ComPtr<ID3D11DepthStencilView> pDepthStencilView;

		CD3D11_TEXTURE2D_DESC depthStencilDesc(
			DXGI_FORMAT_D24_UNORM_S8_UINT,
			bbDesc.Width,
			bbDesc.Height,
			1, // This depth stencil view has only one texture.
			1, // Use a single mipmap level.
			D3D11_BIND_DEPTH_STENCIL
		);

		hr = m_d3dDevice->CreateTexture2D(
			&depthStencilDesc,
			nullptr,
			&pDepthStencil
		);
		if (FAILED(hr)) return hr;

		CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);

		hr = m_d3dDevice->CreateDepthStencilView(
			pDepthStencil.Get(),
			&depthStencilViewDesc,
			&pDepthStencilView
		);
		if (FAILED(hr)) return hr;

		// Create a viewport
		D3D11_VIEWPORT viewport = {
			.Width = (float)bbDesc.Width,
			.Height = (float)bbDesc.Height,
			.MinDepth = 0,
			.MaxDepth = 1
		};

		m_immediateContext->RSSetViewports(
			1,
			&viewport
		);

#pragma endregion

		// Compile vertex shader shader
		ComPtr<ID3DBlob> vsBlob = nullptr;

		hr = compileShaderFromFile(L"../Library/Shaders/Lab03.fxh", "VS", "vs_5_0", &vsBlob);
		if (FAILED(hr)) return E_FAIL;

		hr = m_d3dDevice->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), NULL, &m_vertexShader);
		if (FAILED(hr)) return E_FAIL;

		// Compile pixel shader shader
		ComPtr<ID3DBlob> psBlob = nullptr;

		hr = compileShaderFromFile(L"../Library/Shaders/Lab03.fxh", "PS", "ps_5_0", &psBlob);
		if (FAILED(hr)) return E_FAIL;

		//printf("Success\n");

		// Define the input layout
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		UINT numElements = ARRAYSIZE(layout);

		// Create the input layout
		hr = m_d3dDevice->CreateInputLayout(layout, numElements, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &m_vertexLayout);
		if (FAILED(hr)) return hr; //FALSE -> hr

		// Set the input layout
		m_immediateContext->IASetInputLayout(m_vertexLayout.Get());

		ComPtr<ID3D11PixelShader> psShader = nullptr;

		hr = m_d3dDevice->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &m_pixelShader);
		if (FAILED(hr)) return hr;

		// Create vertex buffer
		SimpleVertex vertices[] = {

			XMFLOAT3(0.0f, 0.5f, 0.5f),
			XMFLOAT3(0.5f, -0.5f, 0.5f),
			XMFLOAT3(-0.5f, -0.5f, 0.5f),
		};

		D3D11_BUFFER_DESC bd = {
			.ByteWidth = sizeof(vertices),
			.Usage = D3D11_USAGE_DEFAULT,
			.BindFlags = D3D11_BIND_VERTEX_BUFFER,
			.CPUAccessFlags = 0,
			.MiscFlags = 0
		};

		D3D11_SUBRESOURCE_DATA InitData = {
			.pSysMem = vertices,
			.SysMemPitch = 0,
			.SysMemSlicePitch = 0
		};

		hr = m_d3dDevice->CreateBuffer(&bd, &InitData, &m_vertexBuffer);
		if (FAILED(hr)) return hr;

		//Set vertex buffer
		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;
		m_immediateContext->IASetVertexBuffers(
			0,
			1,
			m_vertexBuffer.GetAddressOf(),
			&stride,
			&offset
		);

		// Set primitive topology
		m_immediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		return S_OK;
	}


	/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
	  Method:   Renderer::Render
	  Summary:  Render the frame
	M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
	void Renderer::Render()
	{
		// Just clear the backbuffer
		m_immediateContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::MidnightBlue);

		// Render a triangle
		m_immediateContext->VSSetShader(m_vertexShader.Get(), nullptr, 0);
		m_immediateContext->PSSetShader(m_pixelShader.Get(), nullptr, 0);
		m_immediateContext->Draw(3, 0);

		// Present the information
		m_swapChain->Present(0, 0);

		m_immediateContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), nullptr);
	}



	/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
	  Method:   Renderer::compileShaderFromFile
	  Summary:  Helper for compiling shaders with D3DCompile
	  Args:     PCWSTR pszFileName
				  A pointer to a constant null-terminated string that
				  contains the name of the file that contains the
				  shader code
				PCSTR pszEntryPoint
				  A pointer to a constant null-terminated string that
				  contains the name of the shader entry point function
				  where shader execution begins
				PCSTR pszShaderModel
				  A pointer to a constant null-terminated string that
				  specifies the shader target or set of shader
				  features to compile against
				ID3DBlob** ppBlobOut
				  A pointer to a variable that receives a pointer to
				  the ID3DBlob interface that you can use to access
				  the compiled code
	  Returns:  HRESULT
				  Status code
	M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
	HRESULT Renderer::compileShaderFromFile(_In_ PCWSTR pszFileName, _In_ PCSTR pszEntryPoint, _In_ PCSTR szShaderModel, _Outptr_ ID3DBlob** ppBlobOut)
	{
		

		UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
		flags |= D3DCOMPILE_DEBUG;
#endif

		const D3D_SHADER_MACRO defines[] =
		{
			"EXAMPLE_DEFINE", "1",
			NULL, NULL
		};

		//ComPtr<ID3DBlob> shaderBlob = nullptr;
		ComPtr<ID3DBlob> errorBlob = nullptr;

		HRESULT hr = D3DCompileFromFile(pszFileName, defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			pszEntryPoint, szShaderModel,
			flags, 0, ppBlobOut, &errorBlob);

		if (FAILED(hr))
		{
			if (errorBlob)
			{
				OutputDebugStringA((char*)errorBlob->GetBufferPointer());
				//errorBlob->Release();
			}
			return hr;
		}

		return hr;
	}
}


