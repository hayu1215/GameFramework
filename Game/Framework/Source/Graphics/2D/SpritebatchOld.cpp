//#include"SpritebatchOld.h"
//#include<algorithm>
//#include<Framework/Source/Device/D3d11.h>
//#include<Framework/Source/Application/Resource/ResourceManager.h>
//#include<Framework/Source/Utility/Judge.h>
//#include<Framework/Source/Utility/Constant.h>
//
//SpritebatchOld::SpritebatchOld()
//{
//	createVertexBuffer();
//}
//
//SpritebatchOld::SpritebatchOld(std::shared_ptr<Camera>camera) :
//	m_pCamera(camera)
//{
//	createVertexBuffer();
//}
//
//SpritebatchOld::~SpritebatchOld()
//{
//}
//
//void SpritebatchOld::begin()
//{
//	begin(SortMode::Deferred);
//}
//
//void SpritebatchOld::begin(const SortMode &sortMode)
//{
//	begin(sortMode, false);
//}
//
//void SpritebatchOld::begin(const SortMode & sortMode, bool isUI)
//{
//	m_CurrentMode = sortMode;
//	m_IsUI = isUI;
//
//	D3d11::Instance().getDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//
//	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
//	UINT stride = sizeof(TextureVertex);
//	UINT offset = 0;
//	D3d11::Instance().getDeviceContext()->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
//}
//
//void SpritebatchOld::end()
//{
//	if (m_DrawTextures.empty())return;
//
//	switch (m_CurrentMode)
//	{
//	case SortMode::Deferred:
//		deferredEnd();
//		break;
//	case SortMode::Texture:
//		textureEnd();
//		break;
//	case SortMode::BackToFront:
//		backToFrontEnd();
//		break;
//	case SortMode::FrontToBack:
//		frontToBackEnd();
//		break;
//	default:
//		break;
//	}
//	clearDrawList();
//}
//
//#pragma region draw
//
//void SpritebatchOld::draw(std::string textureName, Vector3 position)
//{
//	TextureInfo info;
//	info.textureName = textureName;
//	info.position = position;
//	m_DrawTextures.push_back(info);
//}
//
//void SpritebatchOld::draw(std::string textureName, Vector3 position, Vector4 color)
//{
//	TextureInfo info;
//	info.textureName = textureName;
//	info.position = position;
//	info.color = color;
//	m_DrawTextures.push_back(info);
//}
//
//void SpritebatchOld::draw(std::string textureName, Vector3 position, Vector4 uv, Vector4 color)
//{
//	TextureInfo info;
//	info.textureName = textureName;
//	info.position = position;
//	info.uv = uv;
//	info.color = color;
//	m_DrawTextures.push_back(info);
//}
//
//void SpritebatchOld::draw(std::string textureName, Vector3 position, Vector2 scale, Vector4 color)
//{
//	TextureInfo info;
//	info.textureName = textureName;
//	info.position = position;
//	info.scale = scale;
//	info.color = color;
//	m_DrawTextures.push_back(info);
//}
//
//void SpritebatchOld::draw(std::string textureName, Vector3 position, float angle, Vector2 orgin, Vector4 color)
//{
//	TextureInfo info;
//	info.textureName = textureName;
//	info.position = position;
//	info.angle = angle;
//	info.orgin = orgin;
//	info.color = color;
//	m_DrawTextures.push_back(info);
//}
//
//void SpritebatchOld::draw(std::string textureName, Vector3 position, Vector2 scale, float angle, Vector2 orgin, Vector4 color)
//{
//	TextureInfo info;
//	info.textureName = textureName;
//	info.position = position;
//	info.scale = scale;
//	info.angle = angle;
//	info.orgin = orgin;
//	info.color = color;
//	m_DrawTextures.push_back(info);
//}
//
//void SpritebatchOld::draw(std::string textureName, Vector3 position, Vector2 scale, float angle, Vector2 orgin, Vector4 uv, Vector4 color)
//{
//	TextureInfo info;
//	info.textureName = textureName;
//	info.position = position;
//	info.scale = scale;
//	info.angle = angle;
//	info.orgin = orgin;
//	info.uv = uv;
//	info.color = color;
//	m_DrawTextures.push_back(info);
//}
//
//#pragma endregion
//
//void SpritebatchOld::setCamera(std::shared_ptr<Camera> camera)
//{
//	m_pCamera = camera;
//}
//
//void SpritebatchOld::clearDrawList()
//{
//	//m_AlphaDrawTextures.clear();
//	m_DrawTextures.clear();
//}
//
//void SpritebatchOld::createVertexBuffer()
//{
//	float halfw = 0.5f;
//	float halfh = 0.5f;
//	TextureVertex vertices[] =
//	{
//		Vector3(-halfw,halfh,0),Vector2(0,0),//���_1,
//		Vector3(halfw,halfh,0), Vector2(1,0),//���_2
//		Vector3(-halfw,-halfh,0),Vector2(0,1), //���_3
//		Vector3(halfw,-halfh,0),Vector2(1,1), //���_4
//	};
//
//	//�o�[�e�b�N�X�o�b�t�@�[�̐錾
//	D3D11_BUFFER_DESC bd;
//
//	//�o�[�e�b�N�X�o�b�t�@�[�̒�`
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.ByteWidth = sizeof(TextureVertex) * 4;
//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bd.CPUAccessFlags = 0;
//	bd.MiscFlags = 0;
//
//	//���_�o�b�t�@�̃T�u���\�[�X�̒�`
//	D3D11_SUBRESOURCE_DATA initData;
//	initData.pSysMem = vertices;
//
//	HRESULT result = D3d11::Instance().getDevice()->CreateBuffer(&bd, &initData, m_pVertexBuffer.GetAddressOf());
//	utility::checkError(result, "�o�[�e�b�N�X�o�b�t�@�[�̍쐬���s");
//}
//
//void SpritebatchOld::deferredEnd()
//{
//	for (const auto& e : m_DrawTextures) {
//		setInfo(e.textureName, e.shaderName);
//		draw(e);
//	}
//}
//
//void SpritebatchOld::textureEnd()
//{
//	setInfo(m_DrawTextures[0].textureName, m_DrawTextures[0].shaderName);
//	//�ŏ��ɓo�^�������i�摜�A�V�F�[�_�[�j�ł��ׂĕ`�悷��
//	for (const auto& e : m_DrawTextures) {
//		draw(e);
//	}
//}
//
//void SpritebatchOld::backToFrontEnd()
//{
//	auto action = [](const TextureInfo& t1, const TextureInfo&t2)
//	{
//		return t1 > t2;
//	};
//	std::sort(m_DrawTextures.begin(), m_DrawTextures.end(), action);
//	for (const auto& e : m_DrawTextures) {
//		setInfo(e.textureName, e.shaderName);
//		draw(e);
//	}
//}
//
//void SpritebatchOld::frontToBackEnd()
//{
//	auto action = [](const TextureInfo& t1, const TextureInfo&t2)
//	{
//		return t1 < t2;
//	};
//	std::sort(m_DrawTextures.begin(), m_DrawTextures.end(), action);
//	for (const auto& e : m_DrawTextures) {
//		setInfo(e.textureName, e.shaderName);
//		draw(e);
//	}
//}
//
//void SpritebatchOld::setInfo(const std::string textureName, const std::string shaderName)
//{
//	//���_�C���v�b�g���C�A�E�g���Z�b�g
//	D3d11::Instance().getDeviceContext()->IASetInputLayout(ResourceManager::Instance().findShader(shaderName)->getInputLayout().Get());
//
//	//�g�p����V�F�[�_�[�̓o�^
//	D3d11::Instance().getDeviceContext()->VSSetShader(ResourceManager::Instance().findShader(shaderName)->getVertexShader().Get(), NULL, 0);
//	D3d11::Instance().getDeviceContext()->PSSetShader(ResourceManager::Instance().findShader(shaderName)->getPixelShader().Get(), NULL, 0);
//
//	D3d11::Instance().getDeviceContext()->VSSetConstantBuffers(0, 1, ResourceManager::Instance().findShader(shaderName)->getConstantBuffer().GetAddressOf());
//	D3d11::Instance().getDeviceContext()->PSSetConstantBuffers(0, 1, ResourceManager::Instance().findShader(shaderName)->getConstantBuffer().GetAddressOf());
//
//	//�e�N�X�`���[���V�F�[�_�[�ɓn��
//	D3d11::Instance().getDeviceContext()->PSSetSamplers(0, 1, ResourceManager::Instance().findShader(shaderName)->getSamplerState().GetAddressOf());
//
//	ID3D11ShaderResourceView* srv = ResourceManager::Instance().findTexture(textureName)->getShaderResourceView().Get();
//	D3d11::Instance().getDeviceContext()->PSSetShaderResources(0, 1, &srv);
//}
//
//void SpritebatchOld::draw(const TextureInfo &info)
//{
//	Matrix4 mView = m_pCamera.lock()->getView();
//	if (m_IsUI)mView = Matrix4::identity;
//
//	//���̒��_��Z�̒l��0������1���傫���ƁA�J������Ԃ̊O�ɂ���Ɣ��f�����
//    // �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
//	Matrix4 mProj = {
//		2.0f / (float)(WINDOW_WIDTH), 0.0f, 0.0f, 0.0f,
//		0.0f, 2.0f / (float)(WINDOW_HEIGHT), 0.0f, 0.0f,
//		0.0f, 0.0f, 1.0f, 0.0f,
//		0.0f, 0.0f, 0.0f, 1.0f
//	};
//
//	//���[���h�ϊ�
//	Matrix4 mWorld;
//
//	Matrix4 mScale;
//	mScale = Matrix4::Scale(info.scale.x*ResourceManager::Instance().findTexture(info.textureName)->getSize().x, 
//		                    info.scale.y*ResourceManager::Instance().findTexture(info.textureName)->getSize().y, 
//		                    1.0f);
//
//	Matrix4 mBeginTranslation;
//	mBeginTranslation = Matrix4::Translation(-info.orgin.x, -info.orgin.y, 0);
//
//	Matrix4 mRotate;
//	mRotate = Matrix4::RotationFromAxisZ(info.angle);
//
//	Matrix4 mEndTranslation;
//	mEndTranslation = Matrix4::Translation(info.orgin.x, info.orgin.y, 0);
//
//	Matrix4 mTranslation;
//	mTranslation = Matrix4::Translation(info.position.x, info.position.y, info.position.z);
//
//	mWorld = mScale * mBeginTranslation * mRotate * mEndTranslation * mTranslation;
//
//	Matrix4 wvp = mWorld * mView * mProj;
//	wvp = wvp.transpose();
//	ResourceManager::Instance().findShader(info.shaderName)->passConstantBuffer(D3d11::Instance().getDeviceContext(), wvp, info.color.w, info.uv);
//
//	D3d11::Instance().getDeviceContext()->Draw(4, 0);
//}
