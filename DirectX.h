#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <d2d1.h>
#include <dwrite.h>
#include <chrono>


class Graphics
{
	friend class BindBase;
public:
	Graphics(HWND hwnd, int height, int width);
	~Graphics();
	void EndFrame();
	int GetHeight() { return height; }
	int GetWidth() { return width; }
	void DrawIndexed(UINT size, UINT StartLoc=0, UINT BaseLoc=0);
	void Draw(UINT VertexCount, UINT StartLoc=0);
	void BeginFrame(const float& R,const float& G,const float& B,const float& A);
	void Resize(HWND hwnd, int width, int height);
private:
	struct cBuff
	{
		float Proportion;
		float padd[3];
	};
	cBuff                                               ConstBuff;
	bool                                                resize;
	HWND                                                hwnd;
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	//Microsoft::WRL::ComPtr<ID3D11Buffer>                pCBuff;
	D3D11_VIEWPORT   vp;
	int                                                 width;
	int                                                 height;

	Microsoft::WRL::ComPtr<ID2D1RenderTarget>          d2RenderTarget;
	Microsoft::WRL::ComPtr< ID2D1SolidColorBrush>      SolidColorBrush;
	Microsoft::WRL::ComPtr< IDWriteTextFormat>         TextFormat;

};

