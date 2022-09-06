#include "Service.h"

Alys::Service::Service(String name, BootHook::vBootCallback bootCallback, BootHook::vBootCallback periodicCallback, unsigned long interval) {
    this->bootCallback = bootCallback;
    this->periodicCallback = periodicCallback;
    this->interval = interval;

    if (this->bootCallback != NULL) {
        BootHook* bootInitHook = new Alys::BootHook("Init " + name, this->bootCallback);
        Alys::Init::getInstance().addHook(bootInitHook);
    }

    if (this->periodicCallback != NULL) {
        BootHook* bootScheduleHook = new Alys::BootHook("Schedule " + name, this->bootCallback);
        Alys::Init::getInstance().addHook(bootScheduleHook);
    }
}

bool Alys::Service::start() {
    if (this->started) return false;
    this->bootCallback();
    return true;
}

void Alys::Service::schedule() {
    Alys::MiniSched::MiniSched::getInstance().schedule(this->periodicCallback, Alys::MiniTask::ScheduleMode::REPEAT, this->interval);
}