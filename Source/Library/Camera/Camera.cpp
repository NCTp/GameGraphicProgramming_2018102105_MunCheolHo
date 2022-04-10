#include "Camera/Camera.h"

namespace library
{
    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Camera::Camera

      Summary:  Constructor

      Modifies: [m_yaw, m_pitch, m_moveLeftRight, m_moveBackForward,
                 m_moveUpDown, m_travelSpeed, m_rotationSpeed, 
                 m_padding, m_cameraForward, m_cameraRight, m_cameraUp, 
                 m_eye, m_at, m_up, m_rotation, m_view].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Camera::Camera definition (remove the comment)
    --------------------------------------------------------------------*/
    Camera::Camera(_In_ const XMVECTOR& position) :

        m_yaw(0.0f),
        m_pitch(0.0f),
        m_moveLeftRight(0.0f),
        m_moveBackForward(0.0f),
        m_moveUpDown(0.0f),
        m_travelSpeed(10.0f),
        m_rotationSpeed(10.0f),
        m_padding(),
        m_cameraForward(DEFAULT_FORWARD),
        m_cameraRight(DEFAULT_RIGHT),
        m_cameraUp(DEFAULT_UP),
        m_eye(position),
        m_at(),
        m_up(),
        m_rotation(),
        m_view()

    {}
    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Camera::GetEye

      Summary:  Returns the eye vector

      Returns:  const XMVECTOR&
                  The eye vector
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Camera::GetEye definition (remove the comment)
    --------------------------------------------------------------------*/
    const XMVECTOR& Camera::GetEye() const
    {
        return m_eye;

    }
    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Camera::GetAt

      Summary:  Returns the at vector

      Returns:  const XMVECTOR&
                  The at vector
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Camera::GetAt definition (remove the comment)
    --------------------------------------------------------------------*/
    const XMVECTOR& Camera::GetAt() const
    {
        return m_at;

    }
    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Camera::GetUp

      Summary:  Returns the up vector

      Returns:  const XMVECTOR&
                  The up vector
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Camera::GetUp definition (remove the comment)
    --------------------------------------------------------------------*/
    const XMVECTOR& Camera::GetUp() const
    {
        return m_up;

    }
    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Camera::GetView

      Summary:  Returns the view matrix

      Returns:  const XMMATRIX&
                  The view matrix
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Camera::GetView definition (remove the comment)
    --------------------------------------------------------------------*/
    const XMMATRIX& Camera::GetView() const
    {
        return m_view;
    }
    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Camera::HandleInput

      Summary:  Sets the camera state according to the given input

      Args:     const DirectionsInput& directions
                  Keyboard directional input
                const MouseRelativeMovement& mouseRelativeMovement
                  Mouse relative movement input
                FLOAT deltaTime
                  Time difference of a frame

      Modifies: [m_yaw, m_pitch, m_moveLeftRight, m_moveBackForward,
                 m_moveUpDown].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Camera::HandleInput definition (remove the comment)
    --------------------------------------------------------------------*/
    void Camera::HandleInput(_In_ const DirectionsInput& directions, _In_ const MouseRelativeMovement& mouseRelativeMovement, _In_ FLOAT deltaTime)
    {


        int xMovementInput = 0, yMovementInput = 0, zMovementInput = 0, xRotationInput = 0, yRotationInput = 0;
        //float speed = 15.0f;

        // Handle xInput
        if (directions.bRight == true)
            xMovementInput = 1;
        else if (directions.bLeft == true)
            xMovementInput = -1;

        // Handle yInput
        if (directions.bUp == true)
            yMovementInput = 1;
        else if (directions.bDown == true)
            yMovementInput = -1;

        // Handle zInput
        if (directions.bFront == true)
            zMovementInput = 1;
        else if (directions.bBack == true)
            zMovementInput = -1;


        // Handle Aim Inputs
        xRotationInput = mouseRelativeMovement.X;
        yRotationInput = mouseRelativeMovement.Y;


        // Handle Movements
        if (xMovementInput != 0 || yMovementInput != 0 || zMovementInput != 0)
        {
            XMVECTOR xmvMove = XMVectorSet((float)xMovementInput, (float)yMovementInput, (float)zMovementInput, 0.0f);
            xmvMove = XMVector3Normalize(xmvMove);
            xmvMove *= m_travelSpeed * deltaTime;

            XMFLOAT3 xmfMove;
            XMStoreFloat3(&xmfMove, xmvMove);

            m_moveLeftRight += xmfMove.x;
            m_moveUpDown += xmfMove.y;
            m_moveBackForward = xmfMove.z;
        }

        // Handle Aim
        if (xRotationInput != 0 || yRotationInput != 0)
        {
            XMVECTOR xmvRotation = XMVectorSet((float)xRotationInput, (float)yRotationInput, 0.0f, 0.0f);
            xmvRotation = XMVector3Normalize(xmvRotation);
            xmvRotation *= m_rotationSpeed * deltaTime;

            XMFLOAT3 xmfRotation;
            XMStoreFloat3(&xmfRotation, xmvRotation);

            m_yaw += xmfRotation.x;
            m_pitch += xmfRotation.y;
 
        }

    }
    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Camera::Update

      Summary:  Updates the camera based on its state

      Args:     FLOAT deltaTime
                  Time difference of a frame

      Modifies: [m_rotation, m_at, m_cameraRight, m_cameraUp, 
                 m_cameraForward, m_eye, m_moveLeftRight, 
                 m_moveBackForward, m_moveUpDown, m_up, m_view].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Camera::Update definition (remove the comment)
    --------------------------------------------------------------------*/
    void Camera::Update(_In_ FLOAT deltaTime) {
        
        XMMATRIX yawRotation;
        yawRotation = XMMatrixRotationY(m_yaw);

        m_rotation = XMMatrixRotationRollPitchYaw(m_pitch, m_yaw, 0);


        m_cameraRight = XMVector3TransformCoord(DEFAULT_RIGHT, yawRotation);
        m_cameraUp = XMVector3TransformCoord(DEFAULT_UP, yawRotation);
        m_cameraForward = XMVector3TransformCoord(DEFAULT_FORWARD, yawRotation);

        m_eye += m_moveLeftRight * m_cameraRight;
        m_eye += m_moveBackForward * m_cameraForward;
        m_eye += m_moveUpDown * m_cameraUp;

        m_moveLeftRight = 0.0f;
        m_moveBackForward = 0.0f;
        m_moveUpDown = 0.0f;

        m_at = XMVector3TransformCoord(DEFAULT_FORWARD, m_rotation) + m_eye;
        //m_at = XMVector3Normalize(m_at);
        //m_at = m_eye + m_at;

        m_up = XMVector3TransformCoord(DEFAULT_UP, m_rotation);

        m_view = XMMatrixLookAtLH(m_eye, m_at, m_up);
    };

}