#include "Graphics/Camera.h"

void CameraClass::Render()
{
  Vec4f upVector = m_UpVec;
  Vec4f lookAtVector = m_LookAtVec;
  XMMATRIX rotationMatrix;
  // Load it into a XMVECTOR structure.
  // Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
  float pitch = m_Rotation.GetX()* 0.0174532925f;
  float yaw   = m_Rotation.GetY()* 0.0174532925f;
  float roll  = m_Rotation.GetZ()* 0.0174532925f;
  // Create the rotation matrix from the yaw, pitch, and roll values.
  rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
  // Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
  lookAtVector.m_XYZWMM = XMVector3TransformCoord(lookAtVector.m_XYZWMM, rotationMatrix);
  upVector.m_XYZWMM = XMVector3TransformCoord(upVector.m_XYZWMM, rotationMatrix);
  // Translate the rotated camera position to the location of the viewer.
  lookAtVector += m_Position;
  // Finally create the view matrix frdom the three updated vectors.
  m_ViewMatrix = XMMatrixLookAtLH(m_Position.m_XYZWMM, 
                                  lookAtVector.m_XYZWMM, 
                                  upVector.m_XYZWMM);
}
