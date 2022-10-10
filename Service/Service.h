#ifndef AlysService_h
#define AlysService_h

#include <Arduino.h>
#include "Boot/BootHook.h"
#include "Boot/Init.h"
#include "MiniSched/MiniSched.h"

namespace Alys {
    class Service {
        public:
            Service(String name, BootHook::vBootCallback bootCallback, BootHook::vBootCallback periodicCallback, unsigned long interval);
            Service();

            bool start();
            void enrol();

            BootHook::vBootCallback onBootCallback;
            BootHook::vBootCallback onTickCallback;

            String name;

            unsigned long interval;
            bool started = false;

            void schedule();
    };
};

#endif