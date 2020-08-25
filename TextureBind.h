#pragma once
#include "ImageFile.h"
#include "BindBase.h"
#include <memory>
class TextureBind : public BindBase
{
public:
	TextureBind(std::wstring path, Graphics* pGFX)
		:
		BindBase(pGFX)
	{
		
		Img = new ImageFile(path);
		PrivateImage = true;

		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = Img->GetWidth();
		textureDesc.Height = Img->GetHeight();
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = Img->GetFilePtr();

		sd.SysMemPitch = Img->GetWidth() * sizeof(unsigned int);
		GetDevice()->CreateTexture2D(&textureDesc, &sd, &pTexture);

		// create the resource view on the texture
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = textureDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = 1;
		GetDevice()->CreateShaderResourceView(pTexture.Get(), &srvDesc, &pTextureView);
	}

	TextureBind(ImageFile* img, Graphics* pGFX)
		:
		BindBase(pGFX)
	{

		Img =img;
		PrivateImage = false;

		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = Img->GetWidth();
		textureDesc.Height = Img->GetHeight();
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = Img->GetFilePtr();

		sd.SysMemPitch = Img->GetWidth() * sizeof(unsigned int);
		GetDevice()->CreateTexture2D(&textureDesc, &sd, &pTexture);

		// create the resource view on the texture
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = textureDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = 1;
		GetDevice()->CreateShaderResourceView(pTexture.Get(), &srvDesc, &pTextureView);
	}
	void Bind()
	{
		GetContext()->PSSetShaderResources(0, 1u, pTextureView.GetAddressOf());
	}
	~TextureBind()
	{
		if (PrivateImage)
		{
			delete Img;
			Img = nullptr;
		}
	}
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture;
	ImageFile* Img;
	bool PrivateImage = false;
};