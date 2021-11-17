#include "InputSystem.h"

namespace PhoenixEngine
{
	void InputSystem::Startup()
	{
		const Uint8* keyboardStateSDL = SDL_GetKeyboardState(&numKeys);
		keyboardState.resize(numKeys);
		std::copy(keyboardStateSDL + 0, keyboardStateSDL + numKeys, keyboardState.begin());
		prevKeyboardState = keyboardState;
	}

	void InputSystem::Shutdown()
	{
	}

	void InputSystem::Update(float dt)
	{
		prevKeyboardState = keyboardState;
		const Uint8* keyboardStateSDL = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardStateSDL + 0, keyboardStateSDL + numKeys, keyboardState.begin());

		prevMouseButtonState = mouseButtonState;
		int x, y;
		Uint32 buttons = SDL_GetMouseState(&x, &y);
		mousePosition = glm::vec2{ x, y };
		mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttonsn[0000] & [0RML]
		mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttonsn[0000] & [0RML]
		mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // buttonsn[0000] & [0RML]
	}

	InputSystem::eKeyState InputSystem::GetKeyState(int id)
	{
		eKeyState state = eKeyState::Idle;

		bool keyDown = IsKeyDown(id);
		bool prevKeyDown = IsPreviousKeyDown(id);

		if (keyDown)
		{
			state = (prevKeyDown) ? eKeyState::Held : eKeyState::Pressed;
		}
		else
		{
			state = (prevKeyDown) ? eKeyState::Released : eKeyState::Idle;
		}

		return state;

	}

	bool InputSystem::IsKeyDown(int id) const
	{
		return keyboardState.at(id);
	}

	bool InputSystem::IsPreviousKeyDown(int id) const
	{
		return prevKeyboardState.at(id);
	}
	
	InputSystem::eKeyState InputSystem::GetButtonState(int id)
	{
		eKeyState state = eKeyState::Idle;

		bool keyDown = IsButtonDown(id);
		bool prevKeyDown = IsPreviousButtonDown(id);

		if (keyDown)
		{
			state = (prevKeyDown) ? eKeyState::Held : eKeyState::Pressed;
		}
		else
		{
			state = (prevKeyDown) ? eKeyState::Released : eKeyState::Idle;
		}

		return state;
	}
}