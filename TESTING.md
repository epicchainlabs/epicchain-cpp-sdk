# Testing Guide for EpicChain C++ SDK

## Quick Start

### Building the Tests
```bash
cd EpicChainCpp
mkdir build
cd build
cmake ..
make
```

### Running All Tests
```bash
./tests/epicchaincpp_tests
```

## Test Organization

The test suite is organized into the following categories:

### Crypto Tests
- **Base58**: Base58 and Base58Check encoding/decoding
- **Base64**: Base64 encoding/decoding with URL-safe character support
- **ECKeyPair**: Elliptic curve key pair generation and operations
- **ECPoint**: EC point validation and compression
- **ECDSASignature**: Digital signature operations
- **Hash**: SHA256, RIPEMD160, and combined hashing
- **XEP2**: XEP-2 encryption/decryption for private keys
- **ScryptParams**: Scrypt parameter validation
- **Sign**: Signing and verification operations
- **WIF**: Wallet Import Format encoding/decoding

### Serialization Tests
- **BinaryReader**: Binary deserialization
- **BinaryWriter**: Binary serialization

### Transaction Tests
- **Transaction**: Transaction creation and serialization
- **Signer**: Transaction signer operations
- **Witness**: Transaction witness handling

### Type Tests
- **Hash160**: 160-bit hash operations
- **Hash256**: 256-bit hash operations

### Utility Tests
- **Address**: EpicChain address encoding/decoding
- **Hex**: Hexadecimal encoding/decoding

### Wallet Tests
- **Account**: Account creation and management
- **Wallet**: Wallet operations

## Running Specific Tests

### Run tests by name pattern
```bash
./tests/epicchaincpp_tests "XEP2*"  # Run all XEP2 tests
./tests/epicchaincpp_tests "ECKeyPair*"  # Run all ECKeyPair tests
```

### Run with verbose output
```bash
./tests/epicchaincpp_tests --success  # Show all test results including passes
```

### Run with timing information
```bash
./tests/epicchaincpp_tests --durations yes  # Show test execution times
```

### List all available tests
```bash
./tests/epicchaincpp_tests --list-tests
```

## Test Statistics

Current test suite statistics:
- **Total Test Cases**: 30
- **Total Test Sections**: 63
- **Total Assertions**: 692
- **Pass Rate**: 100%

## Test Coverage Areas

### Cryptographic Operations ✅
- Private/public key generation
- ECDSA signing and verification
- XEP-2 encryption/decryption
- WIF encoding/decoding
- Hash functions (SHA256, RIPEMD160)

### Encoding/Decoding ✅
- Base58/Base58Check
- Base64 (including URL-safe variants)
- Hexadecimal
- EpicChain addresses

### Serialization ✅
- Binary serialization/deserialization
- Variable-length integer encoding
- Transaction serialization

### Neo Protocol ✅
- Transaction creation
- Script building
- Address generation
- Wallet management

## Continuous Integration

To run tests in CI/CD pipeline:

```bash
#!/bin/bash
set -e

# Build
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)

# Test
./tests/epicchaincpp_tests --reporter junit --out test-results.xml

# Check results
if [ $? -eq 0 ]; then
    echo "All tests passed!"
else
    echo "Tests failed!"
    exit 1
fi
```

## Adding New Tests

Tests use the Catch2 framework. To add a new test:

1. Create a test file in the appropriate directory under `tests/`
2. Include the Catch2 header:
   ```cpp
   #include <catch2/catch_test_macros.hpp>
   ```
3. Write your test cases:
   ```cpp
   TEST_CASE("Feature description", "[category]") {
       SECTION("Test scenario") {
           // Test code
           REQUIRE(actual == expected);
       }
   }
   ```
4. Add the test file to `tests/CMakeLists.txt`

## Debugging Test Failures

### Enable verbose output
```bash
./tests/epicchaincpp_tests --success --reporter console
```

### Run with debugger
```bash
gdb ./tests/epicchaincpp_tests
(gdb) run "TestName"
```

### Use sanitizers (requires rebuild)
```bash
cmake .. -DCMAKE_CXX_FLAGS="-fsanitize=address -fsanitize=undefined"
make
./tests/epicchaincpp_tests
```

## Performance Testing

To check test performance:
```bash
./tests/epicchaincpp_tests --durations yes --order rand
```

This will show execution time for each test and run them in random order to detect order-dependent issues.

## Known Issues

- OpenSSL 3.0+ shows deprecation warnings for some EC operations
- Some compiler warnings about signed/unsigned comparisons (non-critical)

## Test Data

Test vectors are embedded in the test files and include:
- Known good WIF encodings
- Valid XEP-2 encrypted keys
- Bitcoin/EpicChain address formats
- ECDSA signature test vectors

All test data has been verified against the EpicChain specification.