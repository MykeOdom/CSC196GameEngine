#include "ParticleSystem.h"

void ParticleSystem::Update(float dt)
{
	for (auto& partical : m_particles)
	{
		if (partical.isActive) partical.Update(dt);
	}
}

void ParticleSystem::Draw(Renderer& renderer)
{
	for (auto& partical : m_particles)
	{
		if (partical.isActive) partical.Draw(renderer);
	}
}

void ParticleSystem::AddParticle(const Particle::Data& data)
{
	Particle* particle = GetFreeParticle();
	if (particle)
	{
		particle->Initialize(data);
	}

}

Particle* ParticleSystem::GetFreeParticle()
{
	for (auto& partical : m_particles)
	{
		if (!partical.isActive) return &partical;
	}

	return nullptr;
}
