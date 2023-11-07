#include "ParticleSystem.h"

void ParticleSystem::Initialize() {
	//インスタンシング用のリソースの作成
	ParticleSystem::CreateInstancingResource();
	//SRVの作成
	srvIndex_ = TextureManager::GetInstance()->CreateInstancingShaderResourceView(instancingResource_, kMaxInstance, sizeof(ParticleForGPU));
}

void ParticleSystem::Update() {
	//エミッターの削除
	particleEmitters_.remove_if([](std::unique_ptr<ParticleEmitter>& particleEmitter) {
		if (particleEmitter->GetIsDead()) {
			particleEmitter.reset();
			return true;
		}
		return false;
		}
	);

	//エミッターの更新
	for (std::unique_ptr<ParticleEmitter>& emitter : particleEmitters_) {
		emitter->Update();
	}

	//InstancingResourceの更新
	ParticleSystem::UpdateInstancingResource();
}

void ParticleSystem::CreateInstancingResource() {
	//Instancing用のWorldTransformリソースを作る
	instancingResource_ = DirectXCommon::GetInstance()->CreateBufferResource(sizeof(ParticleForGPU) * kMaxInstance);
	//書き込むためのアドレスを取得
	ParticleForGPU* instancingData = nullptr;
	instancingResource_->Map(0, nullptr, reinterpret_cast<void**>(&instancingData));
	//単位行列を書き込んでおく
	for (uint32_t index = 0; index < kMaxInstance; ++index) {
		instancingData[index].world = MakeIdentity4x4();
		instancingData[index].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	instancingResource_->Unmap(0, nullptr);
}

void ParticleSystem::UpdateInstancingResource() {
	ParticleForGPU* instancingData = nullptr;
	numInstance_ = 0;
	instancingResource_->Map(0, nullptr, reinterpret_cast<void**>(&instancingData));
	for (std::list<std::unique_ptr<ParticleEmitter>>::iterator emitterIterator = particleEmitters_.begin(); emitterIterator != particleEmitters_.end();) {
		//パーティクルのリストを取得
		std::list<std::unique_ptr<BaseParticle>>& particles = emitterIterator->get()->GetParticles();
		for (std::list<std::unique_ptr<BaseParticle>>::iterator particleIterator = particles.begin(); particleIterator != particles.end();) {
			if (particleIterator->get()->IsDead()) {
				particleIterator = particles.erase(particleIterator);
				continue;
			}
			Matrix4x4 worldMatrix = MakeAffineMatrix(particleIterator->get()->GetScale(), particleIterator->get()->GetRotation(), particleIterator->get()->GetTranslation());
			if (numInstance_ < kMaxInstance) {
				instancingData[numInstance_].world = worldMatrix;
				instancingData[numInstance_].color = particleIterator->get()->GetColor();
				numInstance_++;
			}
			++particleIterator;
		}
		++emitterIterator;
	}
	instancingResource_->Unmap(0, nullptr);
}

ParticleEmitter* ParticleSystem::GetParticleEmitter(const std::string& name) {
	//エミッターのリストから探す
	for (std::unique_ptr<ParticleEmitter>& particleEmitter : particleEmitters_) {
		if (particleEmitter->GetName() == name) {
			return particleEmitter.get();
		}
	}
	//見つからなかったらnullptrを返す
	return nullptr;
}

std::list<ParticleEmitter*> ParticleSystem::GetParticleEmitters(const std::string& name) {
	//返却するリスト
	std::list<ParticleEmitter*> particleEmitters{};
	//エミッターをリストから探す
	for (std::unique_ptr<ParticleEmitter>& particleEmitter : particleEmitters_) {
		if (particleEmitter->GetName() == name) {
			particleEmitters.push_back(particleEmitter.get());
		}
	}
	return particleEmitters;
}