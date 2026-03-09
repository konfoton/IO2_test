#include <gtest/gtest.h>

#include <stdexcept>
#include <thread>
#include <tuple>
#include "gpu.hpp"

class GPUTest : public ::testing::TestWithParam<std::tuple<int>> {
   protected:
  GPU gpu;
};

class ConstructorTest : public ::testing::TestWithParam<std::tuple<double>> {};

class PriceTest : public ::testing::TestWithParam<std::tuple<double, int>> {};

TEST_P(ConstructorTest, Constructor) {
  double hourlyRate = std::get<0>(GetParam());
  if (hourlyRate < 0) {
    EXPECT_THROW(GPU(hourlyRate), std::invalid_argument);
  } else {
    EXPECT_NO_THROW(GPU(hourlyRate));
  }
}

INSTANTIATE_TEST_SUITE_P(
    ConstructorTests,
    ConstructorTest,
    ::testing::Values(
        std::make_tuple(0.0),
        std::make_tuple(10.0),
        std::make_tuple(50.0),
        std::make_tuple(100.0),
        std::make_tuple(-5.0),
        std::make_tuple(-10.0)
    )
);

TEST_P(PriceTest, CalculatesCorrectPrice) {
  double hourlyRate = std::get<0>(GetParam());
  int runTimeMs = std::get<1>(GetParam());
  
  GPU gpu(hourlyRate);
  gpu.Start();
  std::this_thread::sleep_for(std::chrono::milliseconds(runTimeMs));
  gpu.Stop();
  
  double expectedHours = static_cast<double>(runTimeMs) / (1000.0 * 60.0 * 60.0);
  double expectedPrice = expectedHours * hourlyRate;
  
  EXPECT_NEAR(gpu.GetPrice(), expectedPrice, expectedPrice * 0.1 + 0.0001);
}

INSTANTIATE_TEST_SUITE_P(
    PriceTests,
    PriceTest,
    ::testing::Values(
        std::make_tuple(100.0, 1000),
        std::make_tuple(50.0, 2000),    
        std::make_tuple(200.0, 500),   
        std::make_tuple(0.0, 1000)     
    )
);

TEST_P(GPUTest, Working) {
  int mliseconds = std::get<0>(GetParam());
  gpu.Start();
  std::this_thread::sleep_for(std::chrono::milliseconds(mliseconds));
  gpu.Stop();
  EXPECT_GE(gpu.GetTotalRunTimeMs(), static_cast<double>(mliseconds));
  EXPECT_LE(gpu.GetTotalRunTimeMs(), static_cast<double>(mliseconds) + 100.0);
}

  
INSTANTIATE_TEST_SUITE_P(
    PowerTests,
    GPUTest,
    ::testing::Values(
        std::make_tuple(1000),
        std::make_tuple(1500),
        std::make_tuple(3000),
        std::make_tuple(2000)
    )
);

// class MaxCostTest : public ::testing::TestWithParam<std::tuple<double, double>> {};

// TEST_P(MaxCostTest, StopsWhenMaxCostReached) {
//   double hourlyRate = std::get<0>(GetParam());
//   double maxCost = std::get<1>(GetParam());
  
//   GPU gpu(hourlyRate, maxCost);
//   gpu.Start();
  
//   double timeNeededMs = (maxCost / hourlyRate) * 3600.0 * 1000.0 + 500.0;
//   std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(timeNeededMs)));
  
//   EXPECT_EQ(gpu.GetStatus(), GPU::Status::Idle);
//   EXPECT_LE(gpu.GetPrice(), maxCost);
// }

// TEST_P(MaxCostTest, ConstructorRejectsNegativeMaxCost) {
//   double hourlyRate = std::get<0>(GetParam());
//   double maxCost = std::get<1>(GetParam());
  
//   if (maxCost < 0) {
//     EXPECT_THROW(GPU(hourlyRate, maxCost), std::invalid_argument);
//   }
// }

// INSTANTIATE_TEST_SUITE_P(
//     MaxCostTests,
//     MaxCostTest,
//     ::testing::Values(
//         std::make_tuple(3600000.0, 1.0),  // $3.6M/hr = $1/ms, max $1 -> stops after ~1ms
//         std::make_tuple(3600000.0, 2.0),  // $3.6M/hr, max $2 -> stops after ~2ms
//         std::make_tuple(100.0, -5.0)      // Negative max cost should throw
//     )
// );


int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}