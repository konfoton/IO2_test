#include <gtest/gtest.h>

#include <stdexcept>
#include <thread>
#include <tuple>
#include "gpu.hpp"
class GPUTest : public ::testing::Test {
 protected:
  GPU gpu;
};


class GPUTest : public ::testing::TestWithParam<std::tuple<double>> {};


TEST_P(GPUTest, Working) {
  float hourlyRate = std::get<0>(GetParam());
  GPU gpu(hourlyRate);
  gpu.Start();
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  gpu.Stop();
  EXPEPECT_GE(runningTime, 2000.0);
  EXPECT_LE(runningTime, 2100.0);
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