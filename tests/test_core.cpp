#include "sodium.h"
#include "tootep/core.h"
#include "tootep/types.h"
#include <gtest/gtest.h>

TEST(CoreTest, BasicAssertion) { EXPECT_EQ(1, 1); }

TEST(CoreTest, Roundtrip) {
  if (sodium_init() != 0) {
    FAIL() << "Failed to initialize hydrogen";
  }

  bytearr secret = std::vector<uint8_t>(crypto_generichash_KEYBYTES, 0x41);
  auto period = 30;
  auto digits = tootep::DigitsLength::Eight;

  auto compute_hmac = [](const bytearr &key, const uint8_t *msg,
                         size_t msg_len) {
    auto hash = std::array<uint8_t, crypto_generichash_BYTES>();
    const uint8_t *k = key.data();
    crypto_generichash(hash.data(), hash.size(), msg, msg_len, k, key.size());
    return bytearr(hash.begin(), hash.end());
  };

  struct TestCase {
    uint64_t timestamp;
    uint64_t expected_totp;
  };
  auto test_cases = std::vector<TestCase>{
      // Taken from https://datatracker.ietf.org/doc/html/rfc6238#appendix-B
      {59, 673126},           {1111111109, 42068977}, {1111111111, 3553029},
      {1234567890, 98581033}, {2000000000, 12296278}, {20000000000, 25481910},
  };

  for (auto &test_case : test_cases) {
    auto totp =
        tootep::totp(secret, test_case.timestamp, digits, period, compute_hmac);
    EXPECT_EQ(totp, test_case.expected_totp)
        << "Failed for timestamp " << test_case.timestamp << " | got " << totp
        << " | expected " << test_case.expected_totp;
  }
}
