#pragma once
#include <string>

namespace tootep {

// Error class for runtime exceptions.
// Use it like this:
//
// throw tootep::Error(tootep::Error::Type::InvalidInput, "invalid input");
//
// or
//
// try {
//   // do something
// } catch (const tootep::Error &e) {
//   std::cout << e.what() << std::endl;
// }
class Error : public std::runtime_error {
public:
  enum class Type {
    InvalidInput,
    InvalidAlgo,
    InvalidDigits,
    InvalidPeriod,
    MemoryAllocation,
    InvalidUserInput,
    EmptyString,
    MissingLeadingZero,
    InvalidCounter,
    WCryptVersionMismatch,
  };

  inline static std::string type_to_str(Type t) {
    switch (t) {
    case Type::InvalidInput:
      return "invalid-b32-input";
    case Type::InvalidAlgo:
      return "invalid-algo";
    case Type::InvalidDigits:
      return "invalid-digits";
    case Type::InvalidPeriod:
      return "invalid-period";
    case Type::MemoryAllocation:
      return "memory-allocation";
    case Type::InvalidUserInput:
      return "invalid-user-input";
    case Type::EmptyString:
      return "empty-string";
    case Type::MissingLeadingZero:
      return "missing-leading-zero";
    case Type::InvalidCounter:
      return "invalid-counter";
    case Type::WCryptVersionMismatch:
      return "wcrypt-version-mismatch";
    }
  }

  Error(Type t, const std::string &extra)
      : std::runtime_error(std::string(type_to_str(t)) + ": " + extra) {}
};
} // namespace tootep
