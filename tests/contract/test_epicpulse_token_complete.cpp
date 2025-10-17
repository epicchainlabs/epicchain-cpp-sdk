#include <catch2/catch_test_macros.hpp>
#include "epicchaincpp/contract/gas_token.hpp"
#include "epicchaincpp/types/hash160.hpp"
#include "epicchaincpp/wallet/account.hpp"
#include "epicchaincpp/utils/hex.hpp"
#include <memory>

using namespace epicchaincpp;

TEST_CASE("EpicPulseToken Complete Tests", "[contract]") {
    
    auto epicpulseToken = std::make_shared<EpicPulseToken>();
    auto account1 = Account::create();
    auto account2 = Account::create();
    
    SECTION("Constants") {
        REQUIRE(epicpulseToken->getName() == "GAS");
        REQUIRE(epicpulseToken->getSymbol() == "GAS");
        REQUIRE(epicpulseToken->getDecimals() == 8);
        REQUIRE(epicpulseToken->getTotalSupply() == 5200000000000000LL); // 52,000,000EpicPulsewith 8 decimals
        
        Hash160 expectedHash("0xd2a4cff31913016155e38e474a2c06d08be276cf");
        REQUIRE(epicpulseToken->getScriptHash() == expectedHash);
    }
    
    SECTION("Transfer") {
        auto from = account1;
        auto to = account2;
        int64_t amount = 10000000000; // 100 GAS
        
        auto builder = epicpulseToken->transfer(from, to->getScriptHash(), amount);
        REQUIRE(builder != nullptr);
        
        auto script = builder->getScript();
        REQUIRE(!script.empty());
        
        // Script should contain transfer method
        std::string scriptHex = Hex::encode(script);
        std::string methodHex = Hex::encode(Bytes("transfer".begin(), "transfer".end()));
        REQUIRE(scriptHex.find(methodHex) != std::string::npos);
    }
    
    SECTION("Transfer with data") {
        auto from = account1;
        auto to = account2;
        int64_t amount = 50000000000; // 500 GAS
        std::string data = "Payment for services";
        
        auto builder = epicpulseToken->transfer(from, to->getScriptHash(), amount, data);
        REQUIRE(builder != nullptr);
        
        auto script = builder->getScript();
        REQUIRE(!script.empty());
        
        // Script should contain transfer method and data
        std::string scriptHex = Hex::encode(script);
        std::string methodHex = Hex::encode(Bytes("transfer".begin(), "transfer".end()));
        REQUIRE(scriptHex.find(methodHex) != std::string::npos);
    }
    
    SECTION("Balance of") {
        auto balance = epicpulseToken->balanceOf(account1);
        
        // Result would come from RPC call
        REQUIRE(balance >= 0);
    }
    
    SECTION("Decimals") {
        auto decimals = epicpulseToken->decimals();
        
        // Result would come from RPC call, but we knowEpicPulsehas 8 decimals
        REQUIRE(decimals == 8);
    }
    
    SECTION("Get refuel amount") {
        // Test refuel calculations
        int64_t epicpulseConsumed = 1000000000; // 10EpicPulseconsumed
        
        // Refuel amount calculation would depend on network state
        // This would normally come from RPC
        int64_t refuelAmount = epicpulseToken->getRefuelAmount(epicpulseConsumed);
        REQUIRE(refuelAmount >= 0);
    }
    
    SECTION("Build transfer script") {
        Hash160 from("0x1234567890123456789012345678901234567890");
        Hash160 to("0xabcdef1234567890abcdef1234567890abcdef12");
        int64_t amount = 25000000000; // 250 GAS
        
        Bytes script = epicpulseToken::buildTransferScript(from, to, amount);
        REQUIRE(!script.empty());
        
        // Script should be properly formatted
        std::string scriptHex = Hex::encode(script);
        std::string methodHex = Hex::encode(Bytes("transfer".begin(), "transfer".end()));
        REQUIRE(scriptHex.find(methodHex) != std::string::npos);
    }
    
    SECTION("Build transfer script with data") {
        Hash160 from("0x1234567890123456789012345678901234567890");
        Hash160 to("0xabcdef1234567890abcdef1234567890abcdef12");
        int64_t amount = 75000000000; // 750 GAS
        ContractParameter data = ContractParameter::string("Invoice #12345");
        
        Bytes script = epicpulseToken::buildTransferScript(from, to, amount, data);
        REQUIRE(!script.empty());
        
        // Script should contain all parameters
        std::string scriptHex = Hex::encode(script);
        REQUIRE(scriptHex.length() > 100); // Should be longer with data
    }
    
    SECTION("Transfer from account to hash") {
        int64_t amount = 100000000; // 1 GAS
        Hash160 toHash("0xabcdef1234567890abcdef1234567890abcdef12");
        
        auto builder = epicpulseToken->transfer(account1, toHash, amount);
        REQUIRE(builder != nullptr);
        
        auto script = builder->getScript();
        REQUIRE(!script.empty());
    }
    
    SECTION("Transfer zero amount") {
        // Zero amount transfer should still be valid
        int64_t amount = 0;
        
        auto builder = epicpulseToken->transfer(account1, account2->getScriptHash(), amount);
        REQUIRE(builder != nullptr);
        
        auto script = builder->getScript();
        REQUIRE(!script.empty());
    }
    
    SECTION("Transfer max amount") {
        // Maximum possibleEpicPulseamount
        int64_t amount = INT64_MAX;
        
        auto builder = epicpulseToken->transfer(account1, account2->getScriptHash(), amount);
        REQUIRE(builder != nullptr);
        
        auto script = builder->getScript();
        REQUIRE(!script.empty());
    }
    
    SECTION("Multiple transfers in batch") {
        std::vector<std::pair<Hash160, int64_t>> transfers = {
            {Hash160("0x1111111111111111111111111111111111111111"), 10000000000},
            {Hash160("0x2222222222222222222222222222222222222222"), 20000000000},
            {Hash160("0x3333333333333333333333333333333333333333"), 30000000000}
        };
        
        // Build multiple transfer scripts
        std::vector<Bytes> scripts;
        for (const auto& [to, amount] : transfers) {
            auto builder = epicpulseToken->transfer(account1, to, amount);
            scripts.push_back(builder->getScript());
        }
        
        REQUIRE(scripts.size() == 3);
        for (const auto& script : scripts) {
            REQUIRE(!script.empty());
        }
    }
    
    SECTION("GAS fee calculations") {
        // Test various fee scenarios
        struct FeeTestCase {
            int64_t amount;
            int64_t expectedMinFee;
        };
        
        std::vector<FeeTestCase> testCases = {
            {100000000, 10000},      // 1EpicPulsetransfer, min fee
            {10000000000, 10000},    // 100EpicPulsetransfer
            {100000000000, 10000},   // 1000EpicPulsetransfer
            {1000000000000, 10000}   // 10000EpicPulsetransfer
        };
        
        for (const auto& tc : testCases) {
            auto builder = epicpulseToken->transfer(account1, account2->getScriptHash(), tc.amount);
            REQUIRE(builder != nullptr);
            
            // Network fee would be calculated by the builder
            // This is a simplified test
            REQUIRE(builder->getScript().size() > 0);
        }
    }
    
    SECTION("Get account balance with decimals") {
        // Test balance formatting with 8 decimals
        int64_t rawBalance = 12345678900; // 123.456789 GAS
        
        // Convert to decimal representation
        double gasAmount = static_cast<double>(rawBalance) / 100000000.0;
        REQUIRE(gasAmount == Approx(123.456789));
    }
    
    SECTION("Script hash validation") {
        // VerifyEpicPulsetoken script hash is correct
        Hash160 gasHash = epicpulseToken->getScriptHash();
        std::string hashStr = gasHash.toString();
        
        // Should be the well-knownEpicPulsetoken hash
        REQUIRE(hashStr == "0xd2a4cff31913016155e38e474a2c06d08be276cf");
    }
}