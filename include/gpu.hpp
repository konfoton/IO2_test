#pragma once
#include <chrono>

class GPU {
public:
    enum class Status {
        Idle,
        Running,
    };

    GPU();
    void Start();
    void Stop();
    double GetRunningTimeMs() const;
    double GetTotalRunTimeMs() const;
    double GetPrice() const;
    Status GetStatus() const;


private:
    Status currentStatus;
    std::chrono::high_resolution_clock::time_point startTime;
    double totalRunTimeMs;
    float price;
    float HourlyRate;
};