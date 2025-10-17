#pragma once

#include "epicchaincpp/types/hash160.hpp"

namespace epicchaincpp {

/**
 * @brief Constants for the EpicChain Token
 */
class EpicChainToken {
public:
    /// EpicChain Token script hash on MainNet
    static const Hash160 SCRIPT_HASH;
    
    /// EpicChain Token symbol
    static const std::string SYMBOL;
    
    /// EpicChain Token decimals
    static const int DECIMALS;
    
    /// EpicChain Token total supply
    static const int64_t TOTAL_SUPPLY;
};

} // namespace epicchaincpp