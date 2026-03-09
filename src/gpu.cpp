#include "gpu.hpp"
#include <stdexcept>
#include <chrono>

GPU::GPU() : price(0.0f), currentStatus(Status::Idle), totalRunTimeMs(0.0), HourlyRate(0.0f) {}

GPU::GPU(double hourlyRate) : price(0.0f), currentStatus(Status::Idle), totalRunTimeMs(0.0), HourlyRate(static_cast<float>(hourlyRate)) {
    if (hourlyRate < 0) {
        throw std::invalid_argument("Hourly rate cannot be negative");
    }
}

void GPU::Start() {
    if (currentStatus == Status::Running) {
        return;
    }
    currentStatus = Status::Running;
    startTime = std::chrono::high_resolution_clock::now();
}

void GPU::Stop() {
    if (currentStatus == Status::Idle) {
        return;
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(endTime - startTime);
    totalRunTimeMs += duration.count();
    currentStatus = Status::Idle;
}

double GPU::GetTotalRunTimeMs() const {
    return totalRunTimeMs;
}

GPU::Status GPU::GetStatus() const {
    return currentStatus;
}