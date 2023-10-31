#pragma once
#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include "Camera.h"

using namespace Azul;

class Camera2D final : public Camera
{
public:
	Camera2D();
	virtual ~Camera2D();
	Camera2D(const Camera2D&) = delete;
	Camera2D& operator=(const Camera2D&) = delete;

	//camera setup
	void SetOrthographic(const float _xmin, const float _xmax, const float _ymin, 
		const float _ymax, const float _zmin, const float _zmax);

	//update camera
	void UpdateCamera() override;


protected:
	void prUpdateProjMatrix() override;


private:
	float xmin;
	float ymin;
	float xmax;
	float ymax;
	float zmin;
	float zmax;

};
#endif // !CAMERA_2D_H
