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






int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}