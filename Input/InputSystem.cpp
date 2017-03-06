//==========================================================
//InputSystem.cpp
//==========================================================

#include "Engine/Input/InputSystem.hpp"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <Xinput.h> // include the Xinput API
#pragma comment( lib, "xinput" ) // Link in the xinput.lib static library


InputSystem* s_theInputSystem = NULL;





LRESULT _stdcall windowMessageProcessingFunction(HWND windowHandle, UINT MessageId, WPARAM wParam, LPARAM lParam)
{
	if(s_theInputSystem)
	{
		switch (MessageId)
		{
	
		case WM_KEYDOWN:
			s_theInputSystem->SetKeyState((int)wParam, true);
			return 0;
		case WM_KEYUP:
			s_theInputSystem->SetKeyState((int)wParam, false);
			return 0;
		case WM_CLOSE:
			s_theInputSystem->SetSystemQuit();
			return 0;
		case WM_LBUTTONDOWN:
			s_theInputSystem->SetMouseState((int)wParam, true);
			return 0;
		case WM_LBUTTONUP:
			s_theInputSystem->SetMouseState((int)wParam +1, false);
			return 0;
		case WM_RBUTTONDOWN:
			s_theInputSystem->SetMouseState((int)wParam, true);
			return 0;
		case WM_RBUTTONUP:
			s_theInputSystem->SetMouseState((int)wParam +2, false);
			return 0;
		default:
			break;

		}
		return DefWindowProc(windowHandle, MessageId, wParam, lParam);	
	}
	return DefWindowProc(windowHandle, MessageId, wParam, lParam);	
}

void InputSystem::ProcessKeyboardInput()
{
	HWND myWindowHandle = (HWND)(m_platformHandle); 

	MSG queueMessage ;

	for(;;)
	{
	

		BOOL messageWasFound = PeekMessage( &queueMessage, myWindowHandle,0,0,PM_REMOVE);
		if(!messageWasFound)
			break;
		
			TranslateMessage( &queueMessage );
			DispatchMessage( &queueMessage );
		
		
	}


}

InputSystem::InputSystem()
	:m_platformHandle(NULL)
	,m_prevAddress(0L)
	
{
	if(!s_theInputSystem)
		s_theInputSystem = this;
	m_isReadyToQuit = false;
}
///------------------------------------------------------
///
///------------------------------------------------------
InputSystem::~InputSystem()
{

}
///------------------------------------------------------
///
///------------------------------------------------------
void InputSystem::Startup(void* platformHandle)
{
	m_platformHandle = platformHandle;
	m_prevAddress = SetWindowLong( (HWND)platformHandle, GWL_WNDPROC, (long)& windowMessageProcessingFunction );
	for (int keyIndex = 0; keyIndex < NUMBER_OF_VIRTUAL_KEYS; keyIndex++)
	{
		m_keyStates[keyIndex].m_isDown			= false;
		m_keyStates[keyIndex].m_wasJustReleased = false;
		m_keyStates[keyIndex].m_wasJustDown     = false;
	}
	for (unsigned int mouseIndex = 0; mouseIndex < NUMBER_OF_MOUSE_KEYS; mouseIndex++)
	{
		m_mouseStates[mouseIndex].m_isDown = false;
		m_mouseStates[mouseIndex].m_wasJustReleased = false;
		m_mouseStates[mouseIndex].m_wasJustDown = false;
	}

	for(unsigned int controllerIndex =0; controllerIndex < NUMBER_OF_XBOX_CONTROLLER; ++controllerIndex)
	{
		XBoxControllerState& controllerState = m_xboxControllerStates[controllerIndex];
		controllerState.m_isPluggedIn = false;
		controllerState.m_controllerID = controllerIndex;

		for(unsigned int buttonIndex = 0; buttonIndex < XBOX_NUMBER_OF_BUTTONS ; ++buttonIndex)
		{
			controllerState.m_buttonDownStates[buttonIndex] = false;;
		}
		for(unsigned int stickIndex = 0; stickIndex < XBOX_NUMBER_OF_STICKS; stickIndex++)
		{
			controllerState.m_stickPosition[stickIndex] =Vector2(0.0f,0.0f);
		}
	}
}
///------------------------------------------------------
///
///------------------------------------------------------
void InputSystem::Update()
{
	for(unsigned int i =0; i<NUMBER_OF_VIRTUAL_KEYS ; i++)
	{
		m_keyStates[i].m_wasJustReleased = false;
		m_keyStates[i].m_wasJustDown = false;
	}
	for (unsigned int i = 0; i < NUMBER_OF_MOUSE_KEYS; i++)
	{
		m_mouseStates[i].m_wasJustReleased = false;
		m_mouseStates[i].m_wasJustDown = false;
	}
	ProcessKeyboardInput();
	for(unsigned int i =0;i<3;i++)
	{
		ProcessControllerInput(m_xboxControllerStates[i]);
	}
	
}
///------------------------------------------------------
///
///------------------------------------------------------
void InputSystem::Shutdown()
{
	m_prevAddress = SetWindowLong( (HWND)m_platformHandle, GWL_WNDPROC, m_prevAddress );
	delete this;
}
///------------------------------------------------------
///
///------------------------------------------------------
bool InputSystem::IsKeyDown(int key)
{	
	if(key>= 0 && key<NUMBER_OF_VIRTUAL_KEYS)
		return m_keyStates[key].m_isDown;
	return false;
}
///------------------------------------------------------
///
///------------------------------------------------------
bool InputSystem::IsXboxControllerKeyDown(XBoxButtonID buttonID, unsigned int controllerID)
{
	if(controllerID <4)
	{
		const XBoxControllerState& controllerState = m_xboxControllerStates[controllerID];
		if(buttonID < XBOX_NUMBER_OF_BUTTONS)
			return controllerState.m_buttonDownStates[buttonID];
	}
	return false;
}
///------------------------------------------------------
///
///------------------------------------------------------
void InputSystem::SetKeyState(int key, bool isPressedDown)
{
	//if(key == VK_ESCAPE)
	//	ConsolePrintf("");
	if(key>= 0 && key < NUMBER_OF_VIRTUAL_KEYS)
	{
		if (m_keyStates [key].m_isDown==true && isPressedDown==false)
		{
			m_keyStates [key].m_wasJustReleased = true;
		}
		else if (m_keyStates [key].m_isDown==false && isPressedDown==true)
		{
			m_keyStates [key].m_wasJustDown = true;
		}
		m_keyStates [key].m_isDown = isPressedDown; 
	}
}

void InputSystem::ProcessControllerInput(XBoxControllerState& controllerState)
{
	const unsigned short BIT_A_BUTTON = 0x1000;
	const unsigned short BIT_B_BUTTON = 0x2000;
	const unsigned short BIT_X_BUTTON = 0x4000;
	const unsigned short BIT_Y_BUTTON = 0x8000;

	//const int CONTROLLER_NUMBER = 0; // can be 0,1,2,3 to support up to 4 Xbox controllers at once
	XINPUT_STATE xboxInputState;
	memset( &xboxInputState, 0, sizeof( xboxInputState) );
	DWORD errorStatus = XInputGetState( controllerState.m_controllerID, &xboxInputState );
	if( errorStatus == ERROR_SUCCESS )
	{

		controllerState.m_isPluggedIn = true;
		controllerState.m_buttonDownStates[XBOX_BUTTON_X] = (BIT_X_BUTTON & xboxInputState.Gamepad.wButtons)? true:false;
		controllerState.m_buttonDownStates[XBOX_BUTTON_Y] = (BIT_Y_BUTTON & xboxInputState.Gamepad.wButtons)? true:false;
		controllerState.m_buttonDownStates[XBOX_BUTTON_A] = (BIT_A_BUTTON & xboxInputState.Gamepad.wButtons)? true:false;
		controllerState.m_buttonDownStates[XBOX_BUTTON_B] = (BIT_B_BUTTON & xboxInputState.Gamepad.wButtons)? true:false;
		controllerState.m_buttonDownStates[XBOX_BUTTON_LEFT_TRIGGER] = (xboxInputState.Gamepad.bLeftTrigger > 127) ? true:false;
		controllerState.m_buttonDownStates[XBOX_BUTTON_RIGHT_TRIGGER] = (xboxInputState.Gamepad.bRightTrigger > 127) ? true:false;
		
		float lStickX = NormalizeXBoxControllerStickValue(xboxInputState.Gamepad.sThumbLX);
		float lStickY = NormalizeXBoxControllerStickValue(xboxInputState.Gamepad.sThumbLY);
		float rStickX = NormalizeXBoxControllerStickValue(xboxInputState.Gamepad.sThumbRX);
		float rStickY = NormalizeXBoxControllerStickValue(xboxInputState.Gamepad.sThumbRY);

		controllerState.m_stickPosition[XBOX_STICK_LEFT] = Vector2(lStickX,lStickY);
		controllerState.m_stickPosition[XBOX_STICK_RIGHT] = Vector2(rStickX,rStickY);

	}
	else
		controllerState.m_isPluggedIn = false;
	


}
///------------------------------------------------------
///
///------------------------------------------------------
float InputSystem::NormalizeXBoxControllerStickValue(short incomingValue)
{
	static const int XBOX_CONTROLLER_STICK_AXIS_OFFSET = 32768;
	static const float XBOX_CONTROLLER_STICK_RANGE = 65535.0f;
	static const float ONE_OVER_XBOX_CONTROLLER_STICK_RANGE = (1.0f/XBOX_CONTROLLER_STICK_RANGE);

	int rawStickAbsolutePosition = incomingValue + XBOX_CONTROLLER_STICK_AXIS_OFFSET;
	float normalizedStickAxisPosition = (float) rawStickAbsolutePosition * ONE_OVER_XBOX_CONTROLLER_STICK_RANGE;
	normalizedStickAxisPosition *=2.0f;
	normalizedStickAxisPosition -=1.0f;
	return normalizedStickAxisPosition;



}

///------------------------------------------------------
///
///------------------------------------------------------
const Vector2 InputSystem::GetXBoxStickPosition(XBoxStickID stickID, unsigned int controllerID) const
{
	if(controllerID <4)
	{
		const XBoxControllerState& controllerState = m_xboxControllerStates[controllerID];
		if(stickID < XBOX_NUMBER_OF_STICKS)
			return controllerState.m_stickPosition[stickID];
	}
	
	return Vector2(0.0f,0.0f);
}

bool InputSystem::WasKeyJustReleased(int key)
{
	if(key>= 0 && key<NUMBER_OF_VIRTUAL_KEYS)
		return m_keyStates[key].m_wasJustReleased;
	return false;
}

bool InputSystem::WasKeyJustDown(int key)
{
	if(key>= 0 && key<NUMBER_OF_VIRTUAL_KEYS)
		return m_keyStates[key].m_wasJustDown;
	return false;
}

bool InputSystem::WasMouseButtonJustDown(int mouseButton)
{
	if (mouseButton >= 0 && mouseButton < NUMBER_OF_VIRTUAL_KEYS)
		return m_mouseStates[mouseButton].m_wasJustDown;
	return false;
}

///------------------------------------------------------
///
///------------------------------------------------------
void InputSystem:: SetSystemQuit()
{
	m_isReadyToQuit = true;
}

bool InputSystem::IsReadyToQuit()
{
	return m_isReadyToQuit;
}
///------------------------------------------------------
///
///------------------------------------------------------
const Vector2& InputSystem::GetMousePosition()
{
	return m_mousePosition;
}
///------------------------------------------------------
///
///------------------------------------------------------
void InputSystem::SetMousePosition(const Vector2& pos)
{
	m_mousePosition = pos;
}
///------------------------------------------------------
///
///------------------------------------------------------

void InputSystem::ShowMouseCursor(bool isVisiable)
{
	if (isVisiable)
	{
		ShowCursor(TRUE);
	}
	else
	{
		ShowCursor(FALSE);
	}

}
///----------------------------------------------------------
///
///----------------------------------------------------------

bool InputSystem::IsAnyKeyDown()
{
	for (int keyIndex = 0; keyIndex < NUMBER_OF_VIRTUAL_KEYS; keyIndex++)
	{
		if (m_keyStates[keyIndex].m_isDown || m_keyStates[keyIndex].m_wasJustDown)
			return true;
	}
	return false;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void InputSystem::SetMouseState(int key, bool isPressedDown)
{
	if (key >= 0 && key < NUMBER_OF_MOUSE_KEYS)
	{
		if (m_mouseStates[key].m_isDown == true && isPressedDown == false)
		{
			m_mouseStates[key].m_wasJustReleased = true;
		}
		else if (m_mouseStates[key].m_isDown == false && isPressedDown == true)
		{
			m_mouseStates[key].m_wasJustDown = true;
		}
		m_mouseStates[key].m_isDown = isPressedDown;
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

bool InputSystem::IsMouseButtonDown(int mouseButton)
{
	if (mouseButton >= 0 && mouseButton < NUMBER_OF_VIRTUAL_KEYS)
		return m_mouseStates[mouseButton].m_isDown;
	return false;
}

bool InputSystem::WasMouseButtonJustReleased(int mouseButton)
{
	if (mouseButton >= 0 && mouseButton < NUMBER_OF_VIRTUAL_KEYS)
		return m_mouseStates[mouseButton].m_wasJustReleased;
	return false;
}
