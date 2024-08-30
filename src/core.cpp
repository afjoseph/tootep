#include "tootep/core.h"
#include <cmath>

namespace tootep {
uint64_t totp(const bytearr &secret, uint64_t timestamp, DigitsLength digits,
              uint64_t period,
              std::function<bytearr(const bytearr &, const uint8_t *, size_t)>
                  compute_hmac) {
  if (period < MinPeriod || period > MaxPeriod) {
    throw Error(Error::Type::InvalidPeriod, "");
  }
  uint64_t counter = std::floor((double)timestamp / (double)period);
  if (counter < 0) {
    throw Error(Error::Type::InvalidCounter, "");
  }

  uint8_t *counter_bytes = reinterpret_cast<uint8_t *>(&counter);
  bytearr hmac = compute_hmac(secret, counter_bytes, 8);

  // "Dynamic truncation" in RFC 4226
  // http://tools.ietf.org/html/rfc4226#section-5.4
  auto offset = hmac[hmac.size() - 1] & 0x0f;
  auto value = (uint64_t)(((int(hmac[offset]) & 0x7f) << 24) |
                          ((int(hmac[offset + 1] & 0xff)) << 16) |
                          ((int(hmac[offset + 2] & 0xff)) << 8) |
                          (int(hmac[offset + 3]) & 0xff));
  uint64_t pow10_digits = std::pow(10, (double)digits);
  return value % pow10_digits;
}
} // namespace tootep
