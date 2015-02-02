#pragma once

#include <memory>
#include <map>

namespace particles
{
	class ParticleSystem;

	class IParticleRenderer
	{
	public:
		IParticleRenderer() { }
		virtual ~IParticleRenderer() { }

		virtual void generate(ParticleSystem *sys, bool useQuads) = 0;
		virtual void destroy() = 0;
		virtual void update() = 0;
		virtual void render() = 0;

		IParticleRenderer(const IParticleRenderer &) = delete;
		IParticleRenderer & operator = (const IParticleRenderer &) = delete;
	};

	class RendererFactory
	{
		using MapOfRendererGenerators = std::map < std::string, std::shared_ptr<IParticleRenderer>(*)() >;

	protected:
		static std::unique_ptr<MapOfRendererGenerators> s_generatorMap;
		static void initGeneratorMap();
	public:
		static std::shared_ptr<IParticleRenderer> create(const char *name);
		static bool isAvailable(const char *name);
	private:
		RendererFactory();
	};
}