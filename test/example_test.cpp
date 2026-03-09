#include <gtest/gtest.h>

#include <stdexcept>
#include <thread>
#include <tuple>
#include "gpu.hpp"

class GPUTest : public ::testing::TestWithParam<std::tuple<int>> {
   protected:
  GPU gpu;
};


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