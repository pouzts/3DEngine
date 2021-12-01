#pragma once
#include "Math/MathTypes.h"
#include "Framework/System.h"
#include <SDL.h>
#include <vector>
#include <array>

namespace PhoenixEngine
{
	class InputSystem : public System
	{
	public:
		enum class eKeyState
		{
			Idle,
			Pressed,
			Held,
			Released
		};

		enum class eMouseButton
		{
			Left,
			Middle,
			Right
		};

	public:
		void Startup() override;
		void Shutdown() override;
		void Update(float dt) override;

		eKeyState GetKeyState(int id);
		bool IsKeyDown(int id) const;
		bool IsPreviousKeyDown(int id) const;

		const glm::vec2& GetMousePosition() const { return mousePosition; }
		const glm::vec2& GetMouseRelative() { return mouseRelative; }
		bool IsButtonDown(int id) { return mouseButtonState[id]; }
		bool IsPreviousButtonDown(int id) { return prevMouseButtonState[id]; }
		eKeyState GetButtonState(int id);
	
	private:
		std::vector<Uint8> keyboardState;
		std::vector<Uint8> prevKeyboardState;
		int numKeys;

		glm::vec2 mousePosition;
		glm::vec2 prevMousePosition;
		glm::vec2 mouseRelative;
		std::array<Uint32, 3> mouseButtonState;
		std::array<Uint32, 3> prevMouseButtonState;
	};
}