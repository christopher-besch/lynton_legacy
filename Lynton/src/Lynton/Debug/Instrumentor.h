#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

#if LY_PROFILE
    #define LY_PROFILE_BEGIN_SESSION(name, filepath) ::Lynton::Instrumentor::get().begin_session(name, filepath)
    #define LY_PROFILE_END_SESSION() ::Lynton::Instrumentor::get().end_session()
    #define LY_PROFILE_SCOPE(name) ::Lynton::InstrumentationTimer timer##__LINE__(name);
    #define LY_PROFILE_FUNCTION() LY_PROFILE_SCOPE(__FUNCSIG__)
#else
    #define LY_PROFILE_BEGIN_SESSION(name, filepath)
    #define LY_PROFILE_END_SESSION()
    #define LY_PROFILE_SCOPE(name)
    #define LY_PROFILE_FUNCTION()
#endif

namespace Lynton
{

    struct ProfileResult
    {
        std::string name;
        long long start, end;
        uint32_t thread_id;
    };

    struct InstrumentationSession
    {
        std::string name;
    };

    class Instrumentor
    {
    private:
        InstrumentationSession* m_current_session;
        std::ofstream m_output_stream;
        int m_profile_count;
    public:
        Instrumentor()
            : m_current_session(nullptr), m_profile_count(0)
        {
        }

        void begin_session(const std::string& name, const std::string& filepath = "results.json")
        {
            m_output_stream.open(filepath);
            write_head();
            m_current_session = new InstrumentationSession{ name };
        }

        void end_session()
        {
            write_footer();
            m_output_stream.close();
            delete m_current_session;
            m_current_session = nullptr;
            m_profile_count = 0;
        }

        void write_profile(const ProfileResult& result)
        {
            if (m_profile_count++ > 0)
                m_output_stream << ",";

            std::string name = result.name;
            std::replace(name.begin(), name.end(), '"', '\'');

            m_output_stream << "{";
            m_output_stream << "\"cat\":\"function\",";
            m_output_stream << "\"dur\":" << (result.end - result.start) << ',';
            m_output_stream << "\"name\":\"" << name << "\",";
            m_output_stream << "\"ph\":\"X\",";
            m_output_stream << "\"pid\":0,";
            m_output_stream << "\"tid\":" << result.thread_id << ",";
            m_output_stream << "\"ts\":" << result.start;
            m_output_stream << "}";

            m_output_stream.flush();
        }

        void write_head()
        {
            m_output_stream << "{\"otherData\": {},\"traceEvents\":[";
            m_output_stream.flush();
        }

        void write_footer()
        {
            m_output_stream << "]}";
            m_output_stream.flush();
        }

        static Instrumentor& get()
        {
            static Instrumentor instance;
            return instance;
        }
    };

    class InstrumentationTimer
    {
    private:
        const char* m_name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_start_timepoint;
        bool m_stopped;
    public:
        InstrumentationTimer(const char* name)
            : m_name(name), m_stopped(false)
        {
            m_start_timepoint = std::chrono::high_resolution_clock::now();
        }

        ~InstrumentationTimer()
        {
            if (!m_stopped)
                stop();
        }

        void stop()
        {
            auto end_timepoint = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_timepoint).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(end_timepoint).time_since_epoch().count();

            uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
            Instrumentor::get().write_profile({ m_name, start, end, threadID });

            m_stopped = true;
        }
    };

}
