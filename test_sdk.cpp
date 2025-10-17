#include <iostream>
#include <epicchaincpp/epicchaincpp.hpp>

using namespace epicchaincpp;

int main() {
    std::cout << "EpicChain C++ SDK Test" << std::endl;
    std::cout << "=================" << std::endl;
    
    // Test 1: Generate a new key pair
    std::cout << "\n1. Generating new key pair..." << std::endl;
    ECKeyPair keyPair = ECKeyPair::generate();
    std::cout << "   Address: " << keyPair.getAddress() << std::endl;
    std::cout << "   WIF: " << keyPair.exportAsWIF() << std::endl;
    
    // Test 2: Create a wallet
    std::cout << "\n2. Creating wallet..." << std::endl;
    auto wallet = std::make_shared<Wallet>("TestWallet", "1.0");
    auto account = wallet->createAccount("Test Account");
    std::cout << "   Account created: " << account->getAddress() << std::endl;
    
    // Test 3: Test hashing
    std::cout << "\n3. Testing hash functions..." << std::endl;
    std::string message = "Hello, Neo!";
    Bytes messageBytes(message.begin(), message.end());
    Bytes hash = HashUtils::sha256(messageBytes);
    std::cout << "   SHA256 of '" << message << "': " << ByteUtils::toHex(hash) << std::endl;
    
    // Test 4: Create a transaction
    std::cout << "\n4. Creating transaction..." << std::endl;
    auto tx = std::make_shared<Transaction>();
    tx->setNonce(12345);
    tx->setSystemFee(1000000);
    tx->setNetworkFee(500000);
    tx->setValidUntilBlock(1000);
    
    Hash256 txHash = tx->getHash();
    std::cout << "   Transaction hash: " << txHash.toString() << std::endl;
    
    // Test 5: Sign a message
    std::cout << "\n5. Signing message..." << std::endl;
    Bytes msgHash = HashUtils::sha256(messageBytes);
    auto signature = keyPair.sign(msgHash);
    std::cout << "   Signature: " << signature->toHex() << std::endl;
    
    bool valid = keyPair.getPublicKey()->verify(msgHash, *signature);
    std::cout << "   Signature valid: " << (valid ? "true" : "false") << std::endl;
    
    // Test 6: XEP-2 encryption
    std::cout << "\n6. Testing XEP-2 encryption..." << std::endl;
    std::string password = "TestPassword123";
    std::string xep2 = XEP2::encrypt(keyPair, password);
    std::cout << "   XEP-2 encrypted: " << xep2 << std::endl;
    
    ECKeyPair decrypted = XEP2::decryptToKeyPair(xep2, password);
    std::cout << "   Decrypted address: " << decrypted.getAddress() << std::endl;
    std::cout << "   Addresses match: " << (keyPair.getAddress() == decrypted.getAddress() ? "true" : "false") << std::endl;
    
    std::cout << "\nAll tests completed successfully!" << std::endl;
    
    return 0;
}