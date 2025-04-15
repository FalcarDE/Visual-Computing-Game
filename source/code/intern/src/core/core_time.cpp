
#include "core_time.h"
#include "core_uncopyable.h"

#include <assert.h>
#include <vector>
#include <windows.h>

using namespace Core;

namespace
{
    class CTicker : private CUncopyable
    {
        public:

            static CTicker& GetInstance();

        public:

            double GetTick() const;

        private:

            double m_SecondsPerTick;

        private:

            CTicker();
    };
} // namespace

namespace
{
    class CClock : private CUncopyable
    {
        public:

            static const size_t s_MaxNumberOfDurations = 8;

        public:

            static CClock& GetInstance();

        public:

            void Reset();

            void OnFrame();

            double GetTime() const;
            double GetDurationOfFrame() const;
            size_t GetNumberOfFrame() const;
            float GetFrameRate() const;

        public:

            void AddTimer(CTimer& _rTimer);
            void RemoveTimer(CTimer& _rTimer);

        private:

            static const double s_MaxPeak;

        private:

            using CTimerVector = std::vector<CTimer*>;

        private:

            double       m_LastTick;
            double       m_DefaultDurationOfFrame;
            double       m_PredictedDurationOfFrame;
            double       m_CurrentTime;
            size_t       m_NumberOfFrames;
            size_t       m_IndexOfHistory;
            double       m_History[s_MaxNumberOfDurations];
            CTimerVector m_Timers;

        private:

            CClock();

        private:

            double CalcDurationOfLastFrame();
            double CalcDurationOfNextFrame() const;
            void AddDurationToHistory(double _DurationOfFrame);

        private:

            void NotifyTimer(double _DurationOfFrame);

        private:

            CTimerVector::iterator FindTimer(CTimer& _rTimer);
    };
} // namespace

namespace
{
    CTicker& CTicker::GetInstance()
    {
        static CTicker s_Singleton;

        return s_Singleton;
    }

    // -----------------------------------------------------------------------------

    CTicker::CTicker()
        : m_SecondsPerTick(0.0)
    {
        LARGE_INTEGER Frequency;

        ::QueryPerformanceFrequency(&Frequency);

        m_SecondsPerTick = 1.0 / static_cast<double>(Frequency.QuadPart);
    }

    // -----------------------------------------------------------------------------

    double CTicker::GetTick() const
    {
        LARGE_INTEGER Current;

        ::QueryPerformanceCounter(&Current);

        return static_cast<double>(Current.QuadPart) * m_SecondsPerTick;
    }
} // namespace

namespace
{
    const double CClock::s_MaxPeak = 0.200;
} // namespace

namespace
{
    CClock& CClock::GetInstance()
    {
        static CClock s_Singleton;

        return s_Singleton;
    }

    // -----------------------------------------------------------------------------

    CClock::CClock()
        : m_LastTick                (0.0)
        , m_DefaultDurationOfFrame  (0.03)
        , m_PredictedDurationOfFrame(0.0)
        , m_CurrentTime             (0.0)
        , m_NumberOfFrames          (0)
        , m_IndexOfHistory          (0)
        , m_Timers                  ()
    {
        m_Timers.reserve(8);

        Reset();
    }

    // -----------------------------------------------------------------------------

    void CClock::OnFrame()
    {
        double DurationOfLastFrame;

        // -----------------------------------------------------------------------------
        // Add the duration of the last frame to the history.
        // -----------------------------------------------------------------------------
        DurationOfLastFrame = CalcDurationOfLastFrame();

        AddDurationToHistory(DurationOfLastFrame);

        // -----------------------------------------------------------------------------
        // Predict the expected duration of the current frame, which also depends on the
        // previously added duration of the last frame. 
        // -----------------------------------------------------------------------------
        m_PredictedDurationOfFrame = CalcDurationOfNextFrame();

        // -----------------------------------------------------------------------------
        // Forward the current time.
        // -----------------------------------------------------------------------------
        m_CurrentTime += m_PredictedDurationOfFrame;

        ++ m_NumberOfFrames;

        // -----------------------------------------------------------------------------
        // Notify all timer about the frame step.
        // -----------------------------------------------------------------------------
        NotifyTimer(m_PredictedDurationOfFrame);
    }

    // -----------------------------------------------------------------------------

    double CClock::GetTime() const
    {
        return m_CurrentTime;
    }

    // -----------------------------------------------------------------------------

    double CClock::GetDurationOfFrame() const
    {
        return m_PredictedDurationOfFrame;
    }

    // -----------------------------------------------------------------------------

    size_t CClock::GetNumberOfFrame() const
    {
        return m_NumberOfFrames;
    }

    // -----------------------------------------------------------------------------

    float CClock::GetFrameRate() const
    {
        return 1.0f / static_cast<float>(m_PredictedDurationOfFrame);
    }

    // -----------------------------------------------------------------------------

    double CClock::CalcDurationOfLastFrame()
    {
        double CurrentTick;
        double DurationOfFrame;

        CurrentTick = CTicker::GetInstance().GetTick();

        DurationOfFrame = CurrentTick - m_LastTick;

        if (DurationOfFrame > s_MaxPeak)
        {
            DurationOfFrame = m_History[(m_IndexOfHistory - 1) & (s_MaxNumberOfDurations - 1)];
        }

        m_LastTick = CurrentTick;

        return DurationOfFrame;
    }

    // -----------------------------------------------------------------------------

    double CClock::CalcDurationOfNextFrame() const
    {
        size_t IndexOfHistory;
        double DurationOfFrames;

        IndexOfHistory = (m_IndexOfHistory + 1) & (s_MaxNumberOfDurations - 1);

        DurationOfFrames = m_History[m_IndexOfHistory];

        while (IndexOfHistory != m_IndexOfHistory)
        {
            DurationOfFrames += m_History[IndexOfHistory];

            ++ IndexOfHistory; IndexOfHistory &= s_MaxNumberOfDurations - 1;
        }

        return DurationOfFrames / s_MaxNumberOfDurations;
    }

    // -----------------------------------------------------------------------------

    void CClock::AddDurationToHistory(double _DurationOfFrame)
    {
        m_History[m_IndexOfHistory ++] = _DurationOfFrame;

        m_IndexOfHistory &= s_MaxNumberOfDurations - 1;
    }

    // -----------------------------------------------------------------------------

    void CClock::Reset()
    {
        for (m_IndexOfHistory = 0; m_IndexOfHistory < s_MaxNumberOfDurations; ++ m_IndexOfHistory)
        {
            m_History[m_IndexOfHistory] = m_DefaultDurationOfFrame;
        }

        m_LastTick                 = CTicker::GetInstance().GetTick();
        m_PredictedDurationOfFrame = m_DefaultDurationOfFrame;
        m_CurrentTime              = 0.0;
        m_NumberOfFrames           = 0;
        m_IndexOfHistory           = 0;
    }

    // -----------------------------------------------------------------------------

    void CClock::AddTimer(CTimer& _rTimer)
    {
        // -----------------------------------------------------------------------------
        // Check if timer was already added to clock.
        // -----------------------------------------------------------------------------
        assert(FindTimer(_rTimer) == m_Timers.end());

        m_Timers.push_back(&_rTimer);
    }

    // -----------------------------------------------------------------------------

    void CClock::RemoveTimer(CTimer& _rTimer)
    {
        CTimerVector::iterator TimerIterator = FindTimer(_rTimer);

        assert(TimerIterator != m_Timers.end());

        m_Timers.erase(TimerIterator);
    }

    // -----------------------------------------------------------------------------

    CClock::CTimerVector::iterator CClock::FindTimer(CTimer& _rTimer)
    {
        CTimer* pTimer;

        const CTimerVector::iterator TimerEndIterator = m_Timers.end();

        for (CTimerVector::iterator TimerIterator = m_Timers.begin(); TimerIterator != TimerEndIterator; ++ TimerIterator)
        {
            pTimer = *TimerIterator;

            assert(pTimer != nullptr);

            if (pTimer == &_rTimer)
            {
                return TimerIterator;
            }
        }

        return TimerEndIterator;
    }

    // -----------------------------------------------------------------------------

    void CClock::NotifyTimer(double _DurationOfFrame)
    {
        CTimer* pTimer;

        const CTimerVector::iterator TimerEndIterator = m_Timers.end();

        for (CTimerVector::iterator TimerIterator = m_Timers.begin(); TimerIterator != TimerEndIterator; ++ TimerIterator)
        {
            pTimer = *TimerIterator;

            assert(pTimer != nullptr);

            pTimer->Notify(_DurationOfFrame);
        }
    }
} // namespace

namespace Core
{
    CTimer::CTimer()
        : m_CurrentTime             (0.0)
        , m_PredictedDurationOfFrame(0.0)
        , m_TimeScale               (1.0f)
        , m_IsPaused                (false)
    {
        CClock::GetInstance().AddTimer(*this);
    }

    // -----------------------------------------------------------------------------

    CTimer::~CTimer()
    {
        CClock::GetInstance().RemoveTimer(*this);
    }

    // -----------------------------------------------------------------------------

    double CTimer::GetTime() const
    {
        return m_CurrentTime;
    }

    // -----------------------------------------------------------------------------

    double CTimer::GetDurationOfFrame() const
    {
        return m_PredictedDurationOfFrame;
    }

    // -----------------------------------------------------------------------------

    void CTimer::SetTimeScale(float _TimeScale)
    {
        m_TimeScale = _TimeScale;
    }

    // -----------------------------------------------------------------------------

    float CTimer::GetTimeScale() const
    {
        return m_TimeScale;
    }

    // -----------------------------------------------------------------------------

    void CTimer::Pause()
    {
        m_IsPaused = false;
    }

    // -----------------------------------------------------------------------------

    void CTimer::Resume()
    {
        m_IsPaused = true;
    }

    // -----------------------------------------------------------------------------

    bool CTimer::IsPaused() const
    {
        return m_IsPaused;
    }

    // -----------------------------------------------------------------------------

    void CTimer::Notify(double _DurationOfFrame)
    {
        if (!m_IsPaused)
        {
            m_PredictedDurationOfFrame = _DurationOfFrame * m_TimeScale;

            m_CurrentTime += m_PredictedDurationOfFrame;
        }
    }
} // namespace Core

namespace Core
{
namespace Time
{
    void Reset()
    {
        CClock::GetInstance().Reset();
    }

    // -----------------------------------------------------------------------------

    void OnFrame()
    {
        CClock::GetInstance().OnFrame();
    }

    // -----------------------------------------------------------------------------

    double GetTime()
    {
        return CClock::GetInstance().GetTime();
    }

    // -----------------------------------------------------------------------------

    double GetDurationOfFrame()
    {
        return CClock::GetInstance().GetDurationOfFrame();
    }

    // -----------------------------------------------------------------------------

    size_t GetNumberOfFrame()
    {
        return CClock::GetInstance().GetNumberOfFrame();
    }

    // -----------------------------------------------------------------------------

    float GetFrameRate()
    {
        return CClock::GetInstance().GetFrameRate();
    }
} // namespace Time
} // namespace Core
