#pragma once
#include <GL\glew.h>

#include "GameObject.h"
#include "Component.h"
#include "Camera.h"
#include "Transform.h"
#include "Input.h"
#include "Time.h"

#include <SDL/SDL_keycode.h>

// Reference: https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};


// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class CameraFlyController : public Component
{ 

    friend class GameObject;

private:

	CameraFlyController ( GameObject & hostObject )
        : Component ( ComponentTypes::CAMERA_FLY_CONTROLLER, hostObject )
    {
		m_camera = nullptr;
        WorldUp = glm::vec3 ( 0.0f, 1.0f, 0.0f );
        Yaw = YAW;
        Pitch = PITCH;
        MovementSpeed = SPEED;
        MouseSensitivity = SENSITIVITY;
        updateCameraVectors ( );
	}

public:

    void Awake ( ) override
    {
        // Technically these only need to be called on the first script.
        // But there currently isn't away of doing that.
        Input::RegisterKey ( SDLK_a ); // left
        Input::RegisterKey ( SDLK_d ); // right
        Input::RegisterKey ( SDLK_w ); // forward
        Input::RegisterKey ( SDLK_s ); // back
        Input::RegisterKey ( SDLK_q ); // down
        Input::RegisterKey ( SDLK_e ); // up
    }

	void SetCamera ( Camera & camera )
	{
		m_camera = &camera;
        Zoom = camera.GetFoV ( );
	}

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard ( Camera_Movement direction, float deltaTime )
    {
        glm::vec3 Position = m_camera->GetGameObject( ).GetTransform ( ).GetPosition ( );

        float velocity = MovementSpeed * deltaTime;

        if ( direction == FORWARD )
            Position += Front * velocity;
        if ( direction == BACKWARD )
            Position -= Front * velocity;
        if ( direction == LEFT )
            Position -= Right * velocity;
        if ( direction == RIGHT )
            Position += Right * velocity;
        if ( direction == UP )
            Position += Up * velocity;
        if ( direction == DOWN )
            Position -= Up * velocity;

        m_camera->GetGameObject ( ).GetTransform ( ).SetPosition ( Position );
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement ( float xoffset, float yoffset, GLboolean constrainPitch = true )
    {
        if ( yoffset == 0.0f && xoffset == 0.0f ) return;

        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if ( constrainPitch )
        {
            if ( Pitch > 89.0f )
                Pitch = 89.0f;
            if ( Pitch < -89.0f )
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors ( );
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll ( int yoffset )
    {
        Zoom -= ( float ) yoffset;
        if ( Zoom < 1.0f )
            Zoom = 1.0f;
        if ( Zoom > 45.0f )
            Zoom = 45.0f;
    }

    void Update ( ) override
    {
        Component::Update ( );

        #pragma region Camera controls

        float _deltaTime = Time::GetDeltaTime ( );

        if (  Input::IsKeyPressed ( SDLK_a ) )
        {
            ProcessKeyboard ( Camera_Movement::LEFT, _deltaTime );
        }
        if ( Input::IsKeyPressed ( SDLK_d ) )
        {
            ProcessKeyboard ( Camera_Movement::RIGHT, _deltaTime );
        }
        if ( Input::IsKeyPressed ( SDLK_w ) )
        {
            ProcessKeyboard ( Camera_Movement::FORWARD, _deltaTime );
        }
        if ( Input::IsKeyPressed ( SDLK_s ) )
        {
            ProcessKeyboard ( Camera_Movement::BACKWARD, _deltaTime );
        }
        if ( Input::IsKeyPressed ( SDLK_e ) )
        {
            ProcessKeyboard ( Camera_Movement::UP, _deltaTime );
        }
        if ( Input::IsKeyPressed ( SDLK_q ) )
        {
            ProcessKeyboard ( Camera_Movement::DOWN, _deltaTime );
        }

        auto & mouseDelta = Input::GetMouseDelta ( );
        ProcessMouseMovement ( (float) mouseDelta.x, (float) mouseDelta.y, true );

        auto & wheelDelta = Input::GetMouseWheelDelta ( );
        ProcessMouseScroll ( wheelDelta.y );

        UpdateCamera ( );

        #pragma endregion

    }

private:

    // euler Angles
    float Yaw;
    float Pitch;

    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    Camera * m_camera;

    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors ( )
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos ( glm::radians ( Yaw ) ) * cos ( glm::radians ( Pitch ) );
        front.y = sin ( glm::radians ( Pitch ) );
        front.z = sin ( glm::radians ( Yaw ) ) * cos ( glm::radians ( Pitch ) );
        Front = glm::normalize ( front );
        // also re-calculate the Right and Up vector
        Right = glm::normalize ( glm::cross ( Front, WorldUp ) );  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize ( glm::cross ( Right, Front ) );
    }

    void UpdateCamera ( )
    {
        m_camera->SetCameraForward ( Front );
        m_camera->SetCameraUp ( Up );
        m_camera->SetFoV ( Zoom );
    }


};

