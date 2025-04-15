
#pragma once

namespace Core
{
    class CTimer
    {
        public:

            CTimer();
           ~CTimer();

        public:

            double GetTime() const;
            double GetDurationOfFrame() const;

            void SetTimeScale(float _TimeScale);
            float GetTimeScale() const;

            void Pause();
            void Resume();

            bool IsPaused() const;

        public:

            void Notify(double _DurationOfFrame);

        private:

            double m_CurrentTime;
            double m_PredictedDurationOfFrame;
            float  m_TimeScale;
            bool   m_IsPaused;
    };
} // namespace Core

namespace Core
{
namespace Time
{
    void Reset();

    void OnFrame();

    double GetTime();
    double GetDurationOfFrame();
    size_t GetNumberOfFrame();
    float GetFrameRate();
} // namespace Time
} // namespace Core
