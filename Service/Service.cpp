#include "Service.h"

Alys::Service::Service(String name, BootHook::vBootCallback bootCallback, BootHook::vBootCallback periodicCallback, unsigned long interval) {
    this->onBootCallback = bootCallback;
    this->onTickCallback = periodicCallback;
    this->interval = interval;
    this->name = name;
}

Alys::Service::Service() {
}

void Alys::Service::enrol() {
    if (this->onBootCallback != NULL) {
        BootHook* bootInitHook = new Alys::BootHook("Init " + this->name, this->onBootCallback);
        Alys::Init::getInstance().addHook(bootInitHook);
    }

    if (this->onTickCallback != NULL) {
        BootHook* bootScheduleHook = new Alys::BootHook("Schedule " + this->name, this->onTickCallback);
        Alys::Init::getInstance().addHook(bootScheduleHook);
    }
}

bool Alys::Service::start() {
    if (this->started) return false;
    this->onBootCallback();
    return true;
}

void Alys::Service::schedule() {
    Alys::MiniSched::MiniSched::getInstance().schedule(this->onTickCallback, Alys::MiniTask::ScheduleMode::REPEAT, this->interval);
}