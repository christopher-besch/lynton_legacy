#pragma once

namespace Lynton
{

	class TimeStep
	{
	private:
		float m_delta_time;
	public:
		TimeStep(float delta_time = 0.0f)
		    : m_delta_time(delta_time) {}

		inline operator float() const { return m_delta_time; }

		inline float get_seconds() const { return m_delta_time; }
		inline float get_milliseconds() const { return m_delta_time * 1000.0f; }
	};

}