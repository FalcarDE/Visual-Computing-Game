
#pragma once

namespace Game
{
    class CPhase
    {
        public:

            enum EType
            {
                Finalize,
                Initialize,
                Load,
                MainMenu,
                Play,
                Unload,
                NumberOfTypes,
                Undefined = -1,
            };

        public:

            virtual ~CPhase() = default;

        public:

            // Scott Meyers Effective C++
            void OnEnter();
            EType OnRun();
            void OnLeave();

        private:

            virtual void OnInternEnter();
            virtual EType OnInternRun();
            virtual void OnInternLeave();
    };
}
