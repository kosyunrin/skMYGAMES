#include "engine.h"
#include "blur.h"

Blur::Blur(UINT width, UINT height)
{
	this->width = width;
	this->height = height;

	rtt = std::make_unique<RTT>(width, height);
}

void Blur::Render(ComPtr<ID3D11ShaderResourceView> srv, UINT factor)
{
	Shader::SetVSShader(VSShaderID::VS_Basic);
	Shader::SetPSShader(PSShaderID::PS_Blur);

	rtt->Begin();

	ConstantBuffer::SetBlurSettings(BlurSettings((float)SCREEN_WIDTH / factor, (float)SCREEN_HEIGHT / factor, 0.0f));
	Sprite::Render(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, srv.Get());

	rtt->End();

	this->srv = rtt->GetTexture();
}