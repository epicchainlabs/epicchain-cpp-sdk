#pragma once

#include <string>
#include "epicchaincpp/types/types.hpp"

namespace epicchaincpp {

/// Address utilities for EpicChain addresses
class AddressUtils {
public:
    /// Convert a script hash to an address
    /// @param scriptHash The script hash in big-endian order
    /// @return The EpicChain address
    static std::string scriptHashToAddress(const Bytes& scriptHash);
    
    /// Convert an address to a script hash
    /// @param address The EpicChain address
    /// @return The script hash in big-endian order
    static Bytes addressToScriptHash(const std::string& address);
    
    /// Validate a EpicChain address
    /// @param address The address to validate
    /// @return True if valid, false otherwise
    static bool isValidAddress(const std::string& address);
    
    /// Get the address version byte
    /// @return The version byte for EpicChain addresses
    static uint8_t getAddressVersion();
};

} // namespace epicchaincpp