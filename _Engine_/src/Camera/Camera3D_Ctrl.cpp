#include "Camera3D_Ctrl.h"
#include "Camera3DMan.h"
#include "InputMan.h"
#include "Vec3.h"

using namespace Azul;

void CameraCtrl::SetCamObj(GameObj* camobj)
{
	assert(camobj);
	pCameraMeshObj = camobj;

	Camera3D* cam = Camera3DMan::GetCurrCam();
	cam->GetHelper(up0, tar0, pos0, upNorm0, fwdNorm0, rightNorm0);
}

void CameraCtrl::Update()
{
	pCameraMeshObj->SetDraw(true);
	Camera3D* cam;

	Keyboard* key = InputMan::GetKeyboard();

	// change camera view
	if (key->GetKeyState(Keyboard::Key::KEY_1))
	{
		Camera3DMan::SetCurrCam(Camera::Name::FRUSTRUM);

		cam = Camera3DMan::GetCurrCam();
		cam->GetHelper(up0, tar0, pos0, upNorm0, fwdNorm0, rightNorm0);
	}
	if (key->GetKeyState(Keyboard::Key::KEY_2))
	{
		Camera3DMan::SetCurrCam(Camera::Name::FRUSTRUM_SIDE);

		cam = Camera3DMan::GetCurrCam();
		cam->GetHelper(up0, tar0, pos0, upNorm0, fwdNorm0, rightNorm0);
	}
	if (key->GetKeyState(Keyboard::Key::KEY_3))
	{
		Camera3DMan::SetCurrCam(Camera::Name::FRUSTRUM_BACK);

		cam = Camera3DMan::GetCurrCam();
		cam->GetHelper(up0, tar0, pos0, upNorm0, fwdNorm0, rightNorm0);
	}
	if (key->GetKeyState(Keyboard::Key::KEY_0))
	{
		cam = Camera3DMan::GetCurrCam();

		//reset current camera
		obj.set(0.0f, 0.0f, 0.0f);
		cam->SetHelper(up0, tar0, pos0);
	}

	// Camera Zoom
	if (key->GetKeyState(Keyboard::Key::KEY_I))
	{
		cam = Camera3DMan::GetCurrCam();

		//grab curr camera values
		Vec3 pos;
		Vec3 tar;
		Vec3 up;
		Vec3 upNorm;
		Vec3 fwdNorm;
		Vec3 rightNorm;
		cam->GetHelper(up, tar, pos, upNorm, fwdNorm, rightNorm);

		// calc zoom in
		pos += 0.1f * fwdNorm;
		tar += 0.1f * fwdNorm;
		cam->SetHelper(up, tar, pos);
	}
	if (key->GetKeyState(Keyboard::KEY_O))
	{
		cam = Camera3DMan::GetCurrCam();

		//grab curr camera values
		Vec3 pos;
		Vec3 tar;
		Vec3 up;
		Vec3 upNorm;
		Vec3 fwdNorm;
		Vec3 rightNorm;
		cam->GetHelper(up, tar, pos, upNorm, fwdNorm, rightNorm);

		// calc zoom out & update camera
		tar = obj;
		pos -= 0.1f * fwdNorm;
		cam->SetHelper(up, tar, pos);
	}

	// Camera Rotation 
	if (key->GetKeyState(Keyboard::Key::KEY_ARROW_LEFT))
	{
		cam = Camera3DMan::GetCurrCam();

		//grab curr camera values
		Vec3 pos;
		Vec3 tar;
		Vec3 up;
		Vec3 upNorm;
		Vec3 fwdNorm;
		Vec3 rightNorm;
		cam->GetHelper(up, tar, pos, upNorm, fwdNorm, rightNorm);
		tar = obj;

		Mat4 trans(Mat4::Trans::XYZ, tar);
		Mat4 negTrans(Mat4::Trans::XYZ, -tar);
		Mat4 rot(Mat4::Rot::AxisAngle, upNorm, -0.03f);
		Mat4 tmp = negTrans * rot * trans;

		up = up * tmp;
		pos = pos * tmp;
		tar = tar * tmp;

		cam->SetHelper(up, tar, pos);
	}
	if (key->GetKeyState(Keyboard::Key::KEY_ARROW_RIGHT))
	{
		cam = Camera3DMan::GetCurrCam();

		//grab curr camera values
		Vec3 pos;
		Vec3 tar;
		Vec3 up;
		Vec3 upNorm;
		Vec3 fwdNorm;
		Vec3 rightNorm;
		cam->GetHelper(up, tar, pos, upNorm, fwdNorm, rightNorm);
		tar = obj;

		// calc right rotation
		Mat4 trans(Mat4::Trans::XYZ, tar);
		Mat4 negTrans(Mat4::Trans::XYZ, -tar);
		Mat4 rot(Mat4::Rot::AxisAngle, upNorm, +0.03f);
		Mat4 tmp = negTrans * rot * trans;

		up = up * tmp;
		pos = pos * tmp;
		tar = tar * tmp;

		cam->SetHelper(up, tar, pos);
	}
	if (key->GetKeyState(Keyboard::Key::KEY_ARROW_UP))
	{
		cam = Camera3DMan::GetCurrCam();

		//grab curr camera values
		Vec3 pos;
		Vec3 tar;
		Vec3 up;
		Vec3 upNorm;
		Vec3 fwdNorm;
		Vec3 rightNorm;
		cam->GetHelper(up, tar, pos, upNorm, fwdNorm, rightNorm);
		tar = obj;

		// calc pan up
		Mat4 trans(Mat4::Trans::XYZ, tar);
		Mat4 negTrans(Mat4::Trans::XYZ, -tar);
		Mat4 rot(Mat4::Rot::AxisAngle, rightNorm, -0.03f);
		Mat4 tmp = negTrans * rot * trans;

		up = up * tmp;
		pos = pos * tmp;
		tar = tar * tmp;

		cam->SetHelper(up, tar, pos);
	}
	if (key->GetKeyState(Keyboard::Key::KEY_ARROW_DOWN))
	{
		cam = Camera3DMan::GetCurrCam();

		//grab curr camera values
		Vec3 pos;
		Vec3 tar;
		Vec3 up;
		Vec3 upNorm;
		Vec3 fwdNorm;
		Vec3 rightNorm;
		cam->GetHelper(up, tar, pos, upNorm, fwdNorm, rightNorm);
		tar = obj;

		// calc pan down
		Mat4 trans(Mat4::Trans::XYZ, tar);
		Mat4 negTrans(Mat4::Trans::XYZ, -tar);
		Mat4 rot(Mat4::Rot::AxisAngle, rightNorm, 0.03f);
		Mat4 tmp = negTrans * rot * trans;

		up = up * tmp;
		pos = pos * tmp;
		tar = tar * tmp;

		cam->SetHelper(up, tar, pos);
	}
}