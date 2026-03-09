#pragma once
#include <chrono>

class GPU {
public:
    float price;
    
    enum class Status {
        Idle,
        Running,
    };

    GPU();
    void Start();
    void Stop();
    double GetRunningTimeMs() const;
    double GetTotalRunTimeMs() const;
    Status GetStatus() const;

private:
    Status currentStatus;
    std::chrono::high_resolution_clock::time_point startTime;
    double totalRunTimeMs;
};