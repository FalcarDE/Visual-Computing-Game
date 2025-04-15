
#include "core_log.h"
#include "core_uncopyable.h"

#include <cstdarg>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

namespace
{
    class CLogger : private Core::CUncopyable
    {
        public:

            static CLogger& GetInstance()
            {
                static CLogger instance;

                return instance;
            }

        public:

            void Log(const string& _Msg);

        private:

            CLogger();

            const string CurrentDateTime();

            string	 m_FileName;
            ofstream m_Logfile;
    };
} // namespace

namespace
{
    CLogger::CLogger()
        : m_FileName("Log.txt")
        , m_Logfile ()
    {
        if (!m_Logfile.is_open()) 
        {
            m_Logfile.open(m_FileName.c_str(), ios::out);
        }

        m_Logfile.close();
    }

    // -----------------------------------------------------------------------------

    void CLogger::Log(const string& _Msg)
    {
        if (!m_Logfile.is_open()) 
        {
            m_Logfile.open(m_FileName.c_str(), ios::out | ios::app);
        }

        m_Logfile << CurrentDateTime() << ": ";
        m_Logfile << _Msg << std::endl;

        m_Logfile.close();
    }

    // -----------------------------------------------------------------------------

    const string CLogger::CurrentDateTime()
    {
        time_t     Now = time(nullptr);
        struct tm  Tstruct;
        char       Buf[80];

        localtime_s(&Tstruct, &Now);
        strftime(Buf, sizeof(Buf), "%Y-%m-%d %X", &Tstruct);

        return Buf;
    }
} // namespace

namespace Core
{
namespace Logger
{
    void Log(const string& _Msg)
    {
        CLogger::GetInstance().Log(_Msg);
    }

    // -----------------------------------------------------------------------------

    void Log(const char * _pFormat, ...)
    {
        char Msg[256];
        va_list args;

        va_start(args, _pFormat);
        vsprintf_s(Msg, _pFormat, args);
        va_end(args);

        CLogger::GetInstance().Log(Msg);
    }
} // namespace Logger
} // namespace Core