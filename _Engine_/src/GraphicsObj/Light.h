#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include "MathEngine.h"

namespace Azul
{
	const unsigned int MAX_LIGHTS = 3;

	class Light
	{
	public:
		//Light() = delete;
		Light(const Light&) = default;
		Light& operator=(const Light&) = default;

	protected:
		Light()
		{
			this->color = Vec3(1, 1, 1);
			this->ambientIntensity = 1.0f;
			this->diffuseIntensity = 0.0f;
		}
		Light(const Vec3& _color, const float ambient, const float diffuse)
			: color(_color), ambientIntensity(ambient), diffuseIntensity(diffuse)
		{ }
		virtual ~Light() { }

		Vec3 color;
		float ambientIntensity;
		float diffuseIntensity;


	};

	class DirectionalLight : public Light
	{
	public:
		//DirectionalLight() = delete;
		DirectionalLight(const DirectionalLight&) = default;
		DirectionalLight& operator=(const DirectionalLight&) = default;

		DirectionalLight() : Light(), direction(Vec3(0, -1, 0))
		{ }
		DirectionalLight(const Vec3& color, const Vec3& dir, const float ambient, const float diffuse)
			: Light(color, ambient, diffuse), direction(dir)
		{ }
		virtual ~DirectionalLight() { }

		void Set(const Vec3& _color, const Vec3& dir, const float ambient, const float diffuse)
		{
			this->color = _color;
			this->ambientIntensity = ambient;
			this->diffuseIntensity = diffuse;
			
			this->direction = dir;
		}


	private:
		Vec3 direction;

	};

	class PointLight : public Light
	{
	public:
		//PointLight() = delete;
		PointLight(const PointLight&) = default;
		PointLight& operator=(const PointLight&) = default;

		PointLight() : Light(), position(Vec3(0, 0, 0)), constant(1.0f), linear(0.0f), exponent(0.0f)
		{ }
		PointLight(const Vec3& color, const Vec3& pos, const float ambient, const float diffuse, 
			const float _constant, const float _linear, const float exp)
			: Light(color, ambient, diffuse), position(pos), constant(_constant), linear(_linear), exponent(exp)
		{ }
		virtual ~PointLight() { }

		void Set(const Vec3& _color, const Vec3& pos, const float ambient, const float diffuse, 
			const float _constant, const float _linear, const float exp)
		{
			this->color = _color;
			this->ambientIntensity = ambient;
			this->diffuseIntensity = diffuse;

			this->position = pos;
			this->constant = _constant;
			this->linear = _linear;
			this->exponent = exp;
		}


	private:
		Vec3 position;

		float constant;
		float linear;
		float exponent;

	};

	class Spotlight : public Light
	{
	public:
		//Spotlight() = delete;
		Spotlight(const Spotlight&) = default;
		Spotlight& operator=(const Spotlight&) = default;

		Spotlight() : Light(), direction(Vec3(0, -1, 0)), position(Vec3(0, 0, 0)), constant(1.0f), 
			linear(0.0f), exponent(0.0f), edge(0.0f), procEdge(Trig::cos(edge))
		{ }
		Spotlight(const Vec3& color, const Vec3& dir, const Vec3& pos, const float ambient, const float diffuse, const float _constant, 
			const float _linear, const float exp, const float _edge)
			: Light(color, ambient, diffuse), direction(dir), position(pos), constant(_constant), linear(_linear), exponent(exp), 
			edge(_edge), procEdge(Trig::cos(_edge))
		{ }
		virtual ~Spotlight() { }


	private:
		Vec3 direction;
		Vec3 position;

		float constant;
		float linear;
		float exponent;

		float edge;
		float procEdge;


	};
}
#endif // !LIGHT_H
