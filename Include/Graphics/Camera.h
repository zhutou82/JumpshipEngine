#pragma once
#include "Math/JSMath.h"
#include <directxmath.h>
using namespace DirectX;

class CameraClass
{
public:
  CameraClass() {};
  CameraClass(const CameraClass&) = delete;
  ~CameraClass() {}
  void SetPosition(float x, float y, float z);
  void SetRotation(float x, float y, float z);

  const XMFLOAT3& GetPosition() const {return XMFLOAT3(m_PositionX, m_PositionY, m_PositionZ);}
  const XMFLOAT3& GetRotation() const {return XMFLOAT3(m_RotationX, m_RotationY, m_RotationZ);}

  void Render();
  XMMATRIX GetViewMatrix() const {return m_ViewMatrix; }

private:
  float m_PositionX = 0.f, m_PositionY = 0.f, m_PositionZ = 0.f;
  float m_RotationX = 0.f, m_RotationY = 0.f, m_RotationZ = 0.f;
  XMMATRIX m_ViewMatrix;
};