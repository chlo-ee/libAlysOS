#ifndef Service_h
#define Service_h

#include <Arduino.h>
#include "Boot/BootHook.h"
#include "Boot/Init.h"
#include "MiniSched/MiniSched.h"

namespace Alys {
    class Service {
        public:
            Service(String name, BootHook::vBootCallback bootCallback, BootHook::vBootCallback periodicCallback, unsigned long interval);

            bool start();

        private:
            BootHook::vBootCallback bootCallback;
            BootHook::vBootCallback periodicCallback;

            bool started = false;
            unsigned long interval;

            void schedule();
    };
};

#endif