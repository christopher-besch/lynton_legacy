#pragma once

namespace Lynton
{
	typedef enum class KeyCode : uint16_t
	{
		// from glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// from glfw3.h
#define LY_KEY_SPACE           ::Lynton::Key::Space
#define LY_KEY_APOSTROPHE      ::Lynton::Key::Apostrophe    /* ' */
#define LY_KEY_COMMA           ::Lynton::Key::Comma         /* , */
#define LY_KEY_MINUS           ::Lynton::Key::Minus         /* - */
#define LY_KEY_PERIOD          ::Lynton::Key::Period        /* . */
#define LY_KEY_SLASH           ::Lynton::Key::Slash         /* / */
#define LY_KEY_0               ::Lynton::Key::D0
#define LY_KEY_1               ::Lynton::Key::D1
#define LY_KEY_2               ::Lynton::Key::D2
#define LY_KEY_3               ::Lynton::Key::D3
#define LY_KEY_4               ::Lynton::Key::D4
#define LY_KEY_5               ::Lynton::Key::D5
#define LY_KEY_6               ::Lynton::Key::D6
#define LY_KEY_7               ::Lynton::Key::D7
#define LY_KEY_8               ::Lynton::Key::D8
#define LY_KEY_9               ::Lynton::Key::D9
#define LY_KEY_SEMICOLON       ::Lynton::Key::Semicolon     /* ; */
#define LY_KEY_EQUAL           ::Lynton::Key::Equal         /* = */
#define LY_KEY_A               ::Lynton::Key::A
#define LY_KEY_B               ::Lynton::Key::B
#define LY_KEY_C               ::Lynton::Key::C
#define LY_KEY_D               ::Lynton::Key::D
#define LY_KEY_E               ::Lynton::Key::E
#define LY_KEY_F               ::Lynton::Key::F
#define LY_KEY_G               ::Lynton::Key::G
#define LY_KEY_H               ::Lynton::Key::H
#define LY_KEY_I               ::Lynton::Key::I
#define LY_KEY_J               ::Lynton::Key::J
#define LY_KEY_K               ::Lynton::Key::K
#define LY_KEY_L               ::Lynton::Key::L
#define LY_KEY_M               ::Lynton::Key::M
#define LY_KEY_N               ::Lynton::Key::N
#define LY_KEY_O               ::Lynton::Key::O
#define LY_KEY_P               ::Lynton::Key::P
#define LY_KEY_Q               ::Lynton::Key::Q
#define LY_KEY_R               ::Lynton::Key::R
#define LY_KEY_S               ::Lynton::Key::S
#define LY_KEY_T               ::Lynton::Key::T
#define LY_KEY_U               ::Lynton::Key::U
#define LY_KEY_V               ::Lynton::Key::V
#define LY_KEY_W               ::Lynton::Key::W
#define LY_KEY_X               ::Lynton::Key::X
#define LY_KEY_Y               ::Lynton::Key::Y
#define LY_KEY_Z               ::Lynton::Key::Z
#define LY_KEY_LEFT_BRACKET    ::Lynton::Key::LeftBracket   /* [ */
#define LY_KEY_BACKSLASH       ::Lynton::Key::Backslash     /* \ */
#define LY_KEY_RIGHT_BRACKET   ::Lynton::Key::RightBracket  /* ] */
#define LY_KEY_GRAVE_ACCENT    ::Lynton::Key::GraveAccent   /* ` */
#define LY_KEY_WORLD_1         ::Lynton::Key::World1        /* non-US #1 */
#define LY_KEY_WORLD_2         ::Lynton::Key::World2        /* non-US #2 */

/* function keys */
#define LY_KEY_ESCAPE          ::Lynton::Key::Escape
#define LY_KEY_ENTER           ::Lynton::Key::Enter
#define LY_KEY_TAB             ::Lynton::Key::Tab
#define LY_KEY_BACKSPACE       ::Lynton::Key::Backspace
#define LY_KEY_INSERT          ::Lynton::Key::Insert
#define LY_KEY_DELETE          ::Lynton::Key::Delete
#define LY_KEY_RIGHT           ::Lynton::Key::Right
#define LY_KEY_LEFT            ::Lynton::Key::Left
#define LY_KEY_DOWN            ::Lynton::Key::Down
#define LY_KEY_UP              ::Lynton::Key::Up
#define LY_KEY_PAGE_UP         ::Lynton::Key::PageUp
#define LY_KEY_PAGE_DOWN       ::Lynton::Key::PageDown
#define LY_KEY_HOME            ::Lynton::Key::Home
#define LY_KEY_END             ::Lynton::Key::End
#define LY_KEY_CAPS_LOCK       ::Lynton::Key::CapsLock
#define LY_KEY_SCROLL_LOCK     ::Lynton::Key::ScrollLock
#define LY_KEY_NUM_LOCK        ::Lynton::Key::NumLock
#define LY_KEY_PRINT_SCREEN    ::Lynton::Key::PrintScreen
#define LY_KEY_PAUSE           ::Lynton::Key::Pause
#define LY_KEY_F1              ::Lynton::Key::F1
#define LY_KEY_F2              ::Lynton::Key::F2
#define LY_KEY_F3              ::Lynton::Key::F3
#define LY_KEY_F4              ::Lynton::Key::F4
#define LY_KEY_F5              ::Lynton::Key::F5
#define LY_KEY_F6              ::Lynton::Key::F6
#define LY_KEY_F7              ::Lynton::Key::F7
#define LY_KEY_F8              ::Lynton::Key::F8
#define LY_KEY_F9              ::Lynton::Key::F9
#define LY_KEY_F10             ::Lynton::Key::F10
#define LY_KEY_F11             ::Lynton::Key::F11
#define LY_KEY_F12             ::Lynton::Key::F12
#define LY_KEY_F13             ::Lynton::Key::F13
#define LY_KEY_F14             ::Lynton::Key::F14
#define LY_KEY_F15             ::Lynton::Key::F15
#define LY_KEY_F16             ::Lynton::Key::F16
#define LY_KEY_F17             ::Lynton::Key::F17
#define LY_KEY_F18             ::Lynton::Key::F18
#define LY_KEY_F19             ::Lynton::Key::F19
#define LY_KEY_F20             ::Lynton::Key::F20
#define LY_KEY_F21             ::Lynton::Key::F21
#define LY_KEY_F22             ::Lynton::Key::F22
#define LY_KEY_F23             ::Lynton::Key::F23
#define LY_KEY_F24             ::Lynton::Key::F24
#define LY_KEY_F25             ::Lynton::Key::F25

/* keypad */
#define LY_KEY_KP_0            ::Lynton::Key::KP0
#define LY_KEY_KP_1            ::Lynton::Key::KP1
#define LY_KEY_KP_2            ::Lynton::Key::KP2
#define LY_KEY_KP_3            ::Lynton::Key::KP3
#define LY_KEY_KP_4            ::Lynton::Key::KP4
#define LY_KEY_KP_5            ::Lynton::Key::KP5
#define LY_KEY_KP_6            ::Lynton::Key::KP6
#define LY_KEY_KP_7            ::Lynton::Key::KP7
#define LY_KEY_KP_8            ::Lynton::Key::KP8
#define LY_KEY_KP_9            ::Lynton::Key::KP9
#define LY_KEY_KP_DECIMAL      ::Lynton::Key::KPDecimal
#define LY_KEY_KP_DIVIDE       ::Lynton::Key::KPDivide
#define LY_KEY_KP_MULTIPLY     ::Lynton::Key::KPMultiply
#define LY_KEY_KP_SUBTRACT     ::Lynton::Key::KPSubtract
#define LY_KEY_KP_ADD          ::Lynton::Key::KPAdd
#define LY_KEY_KP_ENTER        ::Lynton::Key::KPEnter
#define LY_KEY_KP_EQUAL        ::Lynton::Key::KPEqual

#define LY_KEY_LEFT_SHIFT      ::Lynton::Key::LeftShift
#define LY_KEY_LEFT_CONTROL    ::Lynton::Key::LeftControl
#define LY_KEY_LEFT_ALT        ::Lynton::Key::LeftAlt
#define LY_KEY_LEFT_SUPER      ::Lynton::Key::LeftSuper
#define LY_KEY_RIGHT_SHIFT     ::Lynton::Key::RightShift
#define LY_KEY_RIGHT_CONTROL   ::Lynton::Key::RightControl
#define LY_KEY_RIGHT_ALT       ::Lynton::Key::RightAlt
#define LY_KEY_RIGHT_SUPER     ::Lynton::Key::RightSuper
#define LY_KEY_MENU            ::Lynton::Key::Menu
