//==========================================================
//InputSystem.hpp
//==========================================================

#pragma once

#include "Engine/Math/Vector2.hpp"
#ifndef _INPUTSYSTEM_HPP_
#define _INPUTSYSTEM_HPP_

#define  NUMBER_OF_VIRTUAL_KEYS 256
#define  NUMBER_OF_XBOX_CONTROLLER 4
#define  NUMBER_OF_MOUSE_KEYS 3

enum XBoxButtonID
{
	
	XBOX_BUTTON_X,
	XBOX_BUTTON_Y,
	XBOX_BUTTON_A,
	XBOX_BUTTON_B,
	XBOX_BUTTON_LEFT_TRIGGER,
	XBOX_BUTTON_RIGHT_TRIGGER,
	XBOX_NUMBER_OF_BUTTONS,



};

enum XBoxStickID
{
	XBOX_STICK_LEFT,
	XBOX_STICK_RIGHT,
	XBOX_NUMBER_OF_STICKS,
};
enum MouseButtonID
{
	MOUSE_BUTTON_LEFT,
	MOUSE_BUTTON_RIGHT,
	MOUSE_NUM_OF_BUTTONS
};
///------------------------------------------------------
///
///------------------------------------------------------
struct XBoxControllerState
{
	bool			m_isPluggedIn;
	unsigned int	m_controllerID;
	bool			m_buttonDownStates[XBOX_NUMBER_OF_BUTTONS];
	Vector2			m_stickPosition[XBOX_NUMBER_OF_STICKS];
};

struct KeyState
{
	bool m_isDown;
	bool m_wasJustReleased;
	bool m_wasJustDown;
};

struct MouseState
{
	bool m_isDown;
	bool m_wasJustReleased;
	bool m_wasJustDown;
};

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void Startup(void* platformHandle);
	void Update();
	void Shutdown();
	bool IsKeyDown(int key);
	bool IsMouseButtonDown(int mouseButton);
	bool WasMouseButtonJustReleased(int mouseButton);
	bool WasKeyJustDown(int key);
	bool WasMouseButtonJustDown(int mouseButton);
	bool IsReadyToQuit();
	bool WasKeyJustReleased(int key);
	bool IsXboxControllerKeyDown(XBoxButtonID buttonID, unsigned int controllerID);
	bool IsAnyKeyDown();
	void SetKeyState(int key, bool isPressedDown);
	void SetMouseState(int key, bool isPressedDown);
	void ProcessKeyboardInput();
	void ProcessControllerInput(XBoxControllerState& controllerState);
	const Vector2& GetMousePosition();
	float NormalizeXBoxControllerStickValue(short incomingValue);
	const Vector2 GetXBoxStickPosition(XBoxStickID stickID, unsigned int controllerID) const;
	void SetSystemQuit();
	void SetMousePosition(const Vector2& pos);
	void ShowMouseCursor(bool isVisiable);

protected:
	void* m_platformHandle;
	long m_prevAddress;
	bool m_isReadyToQuit;
private:
	KeyState m_keyStates[NUMBER_OF_VIRTUAL_KEYS];
	XBoxControllerState m_xboxControllerStates[NUMBER_OF_XBOX_CONTROLLER];
	MouseState m_mouseStates[NUMBER_OF_MOUSE_KEYS];
	Vector2 m_mousePosition;
};

extern InputSystem* s_theInputSystem;

#endif