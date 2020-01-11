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
  void SetPosition(const Vec4f& pos) { m_Position = pos; }
  void SetRosition(const Vec4f& rot) { m_Rotation = rot;}
  const Vec4f& GetPosition() const { return m_Position; }
  const Vec4f& GetRotation() const { return m_Rotation; }

  void SetUpVec(const Vec4f& up) { m_UpVec = up; }
  void SetLookAt(const Vec4f& lookat) {m_LookAtVec = lookat;}
  const Vec4f& GetUpVec() const {return m_UpVec;}
  const Vec4f& GetLookAt() const {return m_LookAtVec;}

  void Render();
  const XMMATRIX& GetViewMatrix() const {return m_ViewMatrix; }
  
  void Move(const Vec4f& vec) { m_ViewMatrix  *= XMMatrixTranslation(vec.GetX(), vec.GetY(), vec.GetZ()); }
  
private:
  XMMATRIX m_ViewMatrix;
  Vec4f m_Position;
  Vec4f m_Rotation;
  Vec4f m_UpVec;
  Vec4f m_ForwardVec;
  Vec4f m_LookAtVec;
};