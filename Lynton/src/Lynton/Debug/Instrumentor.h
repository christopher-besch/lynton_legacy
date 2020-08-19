#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>

#include <string>
#include <thread>

#if LY_PROFILE
    // resolve which function signature macro will be used
    // note that this only
    // is resolved when the (pre)compiler starts, so the syntax highlighting
    // could mark the wrong one in your editor
    #if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
        #define LY_FUNC_SIG __PRETTY_FUNCTION__
    #elif defined(__DMC__) && (__DMC__ >= 0x810)
        #define LY_FUNC_SIG __PRETTY_FUNCTION__
    #elif defined(__FUNCSIG__)
        #define LY_FUNC_SIG __FUNCSIG__
    #elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
        #define LY_FUNC_SIG __FUNCTION__
    #elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
        #define LY_FUNC_SIG __FUNC__
    #elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
        #define LY_FUNC_SIG __func__
    #elif defined(__cplusplus) && (__cplusplus >= 201103)
        #define LY_FUNC_SIG __func__
    #else
        #define LY_FUNC_SIG "LY_FUNC_SIG unknown!"
    #endif

    #define LY_PROFILE_BEGIN_SESSION(name, filepath) ::Lynton::Instrumentor::get().begin_session(name, filepath)
    #define LY_PROFILE_END_SESSION() ::Lynton::Instrumentor::get().end_session()
    #define LY_PROFILE_SCOPE(name) ::Lynton::InstrumentationTimer timer##__LINE__(name);
    #define LY_PROFILE_FUNCTION() LY_PROFILE_SCOPE(LY_FUNC_SIG)
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
        std::thread::id thread_id;
    };

    struct InstrumentationSession
    {
        std::string name;
    };

    class Instrumentor
    {
    private:
        std::mutex m_mutex;
        InstrumentationSession* m_current_session;
        std::ofstream m_output_stream;
    public:
        Instrumentor()
            : m_current_session(nullptr)
        {
        }

        void begin_session(const std::string& name, const std::string& filepath = "results.json")
        {
            std::lock_guard lock(m_mutex);
            if (m_current_session) {
                // if there is already a current session, then close it before beginning new one
                // subsequent profiling output meant for the original session will end up in the
                // newly opened session instead
                // that's better than having badly formatted profiling output.
                if (Log::get_core_logger()) { // edge case: begin_session() might be before Log::init()
                    LY_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, m_current_session->name);
                }
                internal_end_session();
            }
            m_output_stream.open(filepath);
            if (m_output_stream.is_open()) {
                m_current_session = new InstrumentationSession({ name });
                write_header();
            }
            else {
                if (Log::get_core_logger()) { // edge case: begin_session() might be before Log::init()
                    LY_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
                }
            }
        }

        void end_session()
        {
            std::lock_guard lock(m_mutex);
            internal_end_session();
        }

        void write_profile(const ProfileResult& result)
        {
            std::stringstream json;

            std::string name = result.name;
            std::replace(name.begin(), name.end(), '"', '\'');

            json << ",{";
            json << "\"cat\":\"function\",";
            json << "\"dur\":" << (result.end - result.start) << ',';
            json << "\"name\":\"" << name << "\",";
            json << "\"ph\":\"X\",";
            json << "\"pid\":0,";
            json << "\"tid\":" << result.thread_id << ",";
            json << "\"ts\":" << result.start;
            json << "}";

            std::lock_guard lock(m_mutex);
            if (m_current_session) {
                m_output_stream << json.str();
                m_output_stream.flush();
            }
        }

        static Instrumentor& get()
        {
            static Instrumentor instance;
            return instance;
        }

    private:
        void write_header()
        {
            m_output_stream << "{\"otherData\": {},\"traceEvents\":[{}";
            m_output_stream.flush();
        }

        void write_footer()
        {
            m_output_stream << "]}";
            m_output_stream.flush();
        }

        // note: you must already own lock on m_mutex before
        // calling internal_end_session()
        void internal_end_session() {
            if (m_current_session) {
                write_footer();
                m_output_stream.close();
                delete m_current_session;
                m_current_session = nullptr;
            }
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

            Instrumentor::get().write_profile({ m_name, start, end, std::this_thread::get_id() });

            m_stopped = true;
        }
    };

}
