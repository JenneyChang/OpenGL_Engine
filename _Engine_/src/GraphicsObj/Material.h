#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

namespace Azul
{
	class Material
	{
	public:
		Material(const Material&) = delete;
		Material& operator=(const Material&) = delete;

	protected:
		Material() = default;
		virtual ~Material() = default;

		virtual void SetState() { }
		virtual void SetGPUData() { }
		virtual void Draw() { }
		virtual void ResetState() { }


	};
}
#endif // !MATERIAL_H
