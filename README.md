# Tootep

C++ library for generating TOTPs (time-based one-time passwords) according to [RFC-6238](https://tools.ietf.org/html/rfc6238)

## Running the tests
You'll need [just](https://github.com/casey/just) as a command runner
```
$ git clone https://github.com/afjoseph/tootep.git
$ cd tootep
$ just clean test
```

## Integration
Integrate to your project with CMake:

```
cd your_project/
git add submodule https://github.com/afjoseph/tootep.git ext/tootep

# Inside your CMakeLists.txt
add_subdirectory(ext/tootep)
target_link_libraries(${PROJECT_NAME} PUBLIC tootep)
target_include_directories(${PROJECT_NAME} PUBLIC ext/tootep/include)
```

## Usage
```
#include <iostream>
#include <vector>
#include "tootep/core.h"

using bytearr = std::vector<uint8_t>;

int main() {
  auto secret = bytearr(32, 0x41);
  auto period = 30;
  auto digits = tootep::DigitsLength::Eight;
  auto timestamp = now();
  auto compute_hmac = [](const bytearr &key, const uint8_t *msg,
                         size_t msg_len) {
    // Fill this with whatever HMAC algorithm you want
    return bytearr{};
  };

  auto totp = tootep::totp(secret, timestamp, digits, period, compute_hmac);
  std::cout << "My TOTP is: " << totp << std::endl;
}
```

## External Dependencies
The project itself has no extra dependencies, but the testing framework uses googletest and libsodium for testing
- [GoogleTest v1.15.2](https://github.com/google/googletest/tree/v1.15.2)
- [LibSodium v1.20.0](https://github.com/jedisct1/libsodium/tree/1.0.20-RELEASE)
