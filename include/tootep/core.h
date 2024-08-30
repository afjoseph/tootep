#pragma once
#include <functional>
#include <tootep/error.h>
#include <tootep/types.h>

namespace tootep {
enum class DigitsLength { Six = 6, Eight = 8, Ten = 10 };
constexpr uint64_t MaxPeriod = 120;
constexpr uint64_t MinPeriod = 1;

uint64_t totp(const bytearr &secret, uint64_t timestamp, DigitsLength digits,
              uint64_t period,
              std::function<bytearr(const bytearr &, const uint8_t *, size_t)>
                  compute_hmac);
}; // namespace tootep
