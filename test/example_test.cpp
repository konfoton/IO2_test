#include <gtest/gtest.h>

#include <stdexcept>
#include <tuple>
#include "gpu.hpp"
// Example test case
class GPUTest : public ::testing::Test {
 protected:
  GPU gpu;  // Shared GPU object for all tests
};


class GPUTest : public ::testing::TestWithParam<std::tuple<double>> {};


TEST_P(GPUTest, Working) {
  float hourlyRate = std::get<0>(GetParam());
  GPU gpu(hourlyRate);
  gpu.Start();
  sleep(30)
  gpu.Stop();
  
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