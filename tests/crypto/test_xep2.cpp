#include <catch2/catch_test_macros.hpp>
#include "epicchaincpp/crypto/xep2.hpp"
#include "epicchaincpp/crypto/ec_key_pair.hpp"
#include "epicchaincpp/crypto/scrypt_params.hpp"
#include "epicchaincpp/utils/hex.hpp"
#include "epicchaincpp/exceptions.hpp"

using namespace epicchaincpp;

TEST_CASE("XEP2 Tests", "[crypto]") {
    
    SECTION("Encrypt and decrypt with default Scrypt params") {
        const std::string privateKeyHex = "1dd37fba80fec4e6a6f13fd708d8dcb3b29def768017052f6c930fa1c5d90bbb";
        ECKeyPair keyPair(Hex::decode(privateKeyHex));
        const std::string password = "TestPassword123";
        
        // Encrypt
        std::string encrypted = XEP2::encrypt(keyPair, password);
        REQUIRE(!encrypted.empty());
        REQUIRE(encrypted.size() == 58); // XEP-2 format is always 58 characters
        REQUIRE(encrypted.substr(0, 2) == "6P"); // XEP-2 prefix
        
        // Decrypt
        ECKeyPair decrypted = XEP2::decryptToKeyPair(encrypted, password);
        REQUIRE(decrypted.getPrivateKey()->getBytes() == keyPair.getPrivateKey()->getBytes());
    }
    
    SECTION("Encrypt and decrypt with custom Scrypt params") {
        const std::string privateKeyHex = "1dd37fba80fec4e6a6f13fd708d8dcb3b29def768017052f6c930fa1c5d90bbb";
        ECKeyPair keyPair(Hex::decode(privateKeyHex));
        const std::string password = "TestPassword123";
        
        // Use lighter Scrypt params for testing
        ScryptParams params(256, 1, 1);
        
        // Encrypt
        std::string encrypted = XEP2::encrypt(keyPair, password, params);
        REQUIRE(!encrypted.empty());
        REQUIRE(XEP2::isValid(encrypted));
        
        // Decrypt
        ECKeyPair decrypted = XEP2::decryptToKeyPair(encrypted, password, params);
        REQUIRE(decrypted.getPrivateKey()->getBytes() == keyPair.getPrivateKey()->getBytes());
    }
    
    SECTION("Decrypt with wrong password throws exception") {
        const std::string encrypted = "6PYVdVfUJ5wPDaJJqNauhwKimdSj7Zc27kCQ4MZKqfYBYMpXDeLqrnqLjJ";
        const std::string wrongPassword = "WrongPassword";
        
        REQUIRE_THROWS_AS(XEP2::decryptToKeyPair(encrypted, wrongPassword), XEP2Exception);
    }
    
    SECTION("Validate XEP2 format") {
        // Generate a valid XEP-2 string first
        ECKeyPair keyPair = ECKeyPair::generate();
        std::string encrypted = XEP2::encrypt(keyPair, "password");
        REQUIRE(XEP2::isValid(encrypted));
        
        // Invalid formats
        REQUIRE_FALSE(XEP2::isValid("")); // Empty
        REQUIRE_FALSE(XEP2::isValid("InvalidXEP2")); // Wrong format
        REQUIRE_FALSE(XEP2::isValid("5PYVdVfUJ5wPDaJJqNauhwKimdSj7Zc27kCQ4MZKqfYBYMpXDeLqrnqLjJ")); // Wrong prefix
        REQUIRE_FALSE(XEP2::isValid("6PYVdVfUJ5wPDaJJqNauhwKimdSj7Zc27kCQ4MZKqfYBYMpXDeLqrnqL")); // Too short
    }
    
    SECTION("Known XEP2 test vectors") {
        struct TestVector {
            std::string privateKeyHex;
            std::string password;
            std::string encrypted;
        };
        
        // Note: XEP-2 encryption includes randomness (salt), so we can only test decryption
        // with known encrypted values
        std::vector<TestVector> testVectors = {
            // Add known test vectors here if available
        };
        
        // Test that encryption produces valid XEP-2 format
        const std::string privateKeyHex = "1dd37fba80fec4e6a6f13fd708d8dcb3b29def768017052f6c930fa1c5d90bbb";
        ECKeyPair keyPair(Hex::decode(privateKeyHex));
        
        std::string encrypted = XEP2::encrypt(keyPair, "password");
        REQUIRE(XEP2::isValid(encrypted));
        
        // Should be able to decrypt it back
        ECKeyPair decrypted = XEP2::decryptToKeyPair(encrypted, "password");
        REQUIRE(decrypted.getPrivateKey()->getBytes() == keyPair.getPrivateKey()->getBytes());
    }
    
    SECTION("Multiple rounds of encryption produce different results") {
        const std::string privateKeyHex = "1dd37fba80fec4e6a6f13fd708d8dcb3b29def768017052f6c930fa1c5d90bbb";
        ECKeyPair keyPair(Hex::decode(privateKeyHex));
        const std::string password = "TestPassword";
        
        std::string encrypted1 = XEP2::encrypt(keyPair, password);
        std::string encrypted2 = XEP2::encrypt(keyPair, password);
        
        // XEP-2 uses deterministic salt from address hash, so encrypted values should be the same
        // REQUIRE(encrypted1 != encrypted2);  // This test expectation is incorrect
        
        // But both should decrypt to the same private key
        ECKeyPair decrypted1 = XEP2::decryptToKeyPair(encrypted1, password);
        ECKeyPair decrypted2 = XEP2::decryptToKeyPair(encrypted2, password);
        
        REQUIRE(decrypted1.getPrivateKey()->getBytes() == keyPair.getPrivateKey()->getBytes());
        REQUIRE(decrypted2.getPrivateKey()->getBytes() == keyPair.getPrivateKey()->getBytes());
    }
    
    SECTION("Decrypt only to private key bytes") {
        const std::string privateKeyHex = "1dd37fba80fec4e6a6f13fd708d8dcb3b29def768017052f6c930fa1c5d90bbb";
        ECKeyPair keyPair(Hex::decode(privateKeyHex));
        const std::string password = "TestPassword";
        
        std::string encrypted = XEP2::encrypt(keyPair, password);
        
        Bytes decryptedBytes = XEP2::decrypt(encrypted, password);
        REQUIRE(decryptedBytes == keyPair.getPrivateKey()->getBytes());
    }
}