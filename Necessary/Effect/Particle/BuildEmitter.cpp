#include "BuildEmitter.h"

EmitterBuilder::EmitterBuilder()
{
	particleEmitter_ = new ParticleEmitter();
}

EmitterBuilder::~EmitterBuilder()
{

}

EmitterBuilder& EmitterBuilder::SetEmitterName(const std::string& name)
{
	particleEmitter_->name_ = name;
	return *this;
}

EmitterBuilder& EmitterBuilder::SetParticleType(ParticleEmitter::ParticleType particleType)
{
	particleEmitter_->particleType_ = particleType;
	return *this;
}

EmitterBuilder& EmitterBuilder::SetTranslation(const Vector3& translation)
{
	particleEmitter_->popTranslation_ = translation;
	return *this;
}

EmitterBuilder& EmitterBuilder::SetArea(const Vector3& min, const Vector3& max)
{
	particleEmitter_->popArea_ = { min,max };
	return *this;
}

EmitterBuilder& EmitterBuilder::SetRotation(const Vector3& min, const Vector3& max)
{
	particleEmitter_->popRotation_ = { min,max };
	return *this;
}

EmitterBuilder& EmitterBuilder::SetScale(const Vector3& min, const Vector3& max)
{
	particleEmitter_->popScale_ = { min,max };
	return *this;
}

EmitterBuilder& EmitterBuilder::SetAzimuth(float min, float max)
{
	particleEmitter_->popAzimuth = { min,max };
	return *this;
}

EmitterBuilder& EmitterBuilder::SetElevation(float min, float max)
{
	particleEmitter_->popElevation = { min,max };
	return *this;
}

EmitterBuilder& EmitterBuilder::SetVelocity(const Vector3& min, const Vector3& max)
{
	particleEmitter_->popVelocity_ = { min,max };
	return *this;
}

EmitterBuilder& EmitterBuilder::SetColor(const Vector4& min, const Vector4& max)
{
	particleEmitter_->popColor_ = { min,max };
	return *this;
}

EmitterBuilder& EmitterBuilder::SetLifeTime(float min, float max)
{
	particleEmitter_->popLifeTime_ = { min,max };
	return *this;
}

EmitterBuilder& EmitterBuilder::SetCount(uint32_t count)
{
	particleEmitter_->popCount_ = count;
	return *this;
}

EmitterBuilder& EmitterBuilder::SetFrequency(float frequency)
{
	particleEmitter_->popFrequency_ = frequency;
	particleEmitter_->frequencyTime_ = frequency;
	return *this;
}

EmitterBuilder& EmitterBuilder::SetDeleteTime(float deleteTime)
{
	particleEmitter_->deleteTime_ = deleteTime;
	return *this;
}

ParticleEmitter* EmitterBuilder::Build()
{
	//particleEmitter_->Initialize();
	return particleEmitter_;
}