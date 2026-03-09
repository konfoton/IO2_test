#include "gpu.hpp"
#include <stdexcept>
#include <chrono>


GPU::GPU(double hourlyRate) : price(0.0f), currentStatus(Status::Idle), totalRunTimeMs(0.0) {
    if(hourlyRate < 0) {
        throw std::invalid_argument("Hourly rate cannot be negative");
    }
}

void GPU::Start() {
}

void GPU::Stop() {
}

double GPU::GetRunningTimeMs() const {
}

double GPU::GetTotalRunTimeMs() const {
}