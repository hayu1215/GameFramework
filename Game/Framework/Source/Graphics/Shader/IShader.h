//#pragma once
//#include<Framework/Source/Graphics/D3d11.h>
//#include<Framework/Source/Utility/Math/Matrix4.h>
//#include<Framework/Source/Utility/Math/Vector4.h>
//#include<string>
//
//class IShader {
//public:
//	virtual ~IShader() {};
//	virtual void passConstantBuffer(ComPtr<ID3D11DeviceContext>,const Matrix4&, float,const Vector4&) = 0;
//	virtual bool load(ComPtr<ID3D11Device>, const std::string&) = 0;
//	virtual ComPtr<ID3D11VertexShader> getVertexShader() = 0;
//	virtual ComPtr<ID3D11PixelShader> getPixelShader() = 0;
//	virtual ComPtr<ID3D11SamplerState> getSamplerState() = 0;
//	virtual ComPtr<ID3D11InputLayout> getInputLayout() = 0;
//	virtual ComPtr<ID3D11Buffer>getConstantBuffer() = 0;
//};