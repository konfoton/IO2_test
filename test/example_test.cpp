#include <gtest/gtest.h>

#include <stdexcept>
#include <thread>
#include <tuple>
#include "gpu.hpp"

class GPUTest : public ::testing::TestWithParam<std::tuple<double>> {
   protected:
  GPU gpu;
};


TEST_P(GPUTest, Working) {
  float hourlyRate = std::get<0>(GetParam());
  gpu.Start();
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  gpu.Stop();
  EXPECT_GE(gpu.GetTotalRunTimeMs(), 2000.0);
  EXPECT_LE(gpu.GetTotalRunTimeMs(), 2100.0);
}

  
INSTANTIATE_TEST_SUITE_P(
    PowerTests,
    GPUTest,
    ::testing::Values(
        std::make_tuple(2.0),
        std::make_tuple(5.0),
        std::make_tuple(3.0),
        std::make_tuple(2.0)
    )
);

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}