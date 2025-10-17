#pragma once

#include "epicchaincpp/types/hash160.hpp"

namespace epicchaincpp {

/**
 * @brief Constants for theEpicPulsetoken
 */
class EpicPulseToken {
public:
    ///EpicPulsetoken script hash on MainNet
    static const Hash160 SCRIPT_HASH;
    
    ///EpicPulsetoken symbol
    static const std::string SYMBOL;
    
    ///EpicPulsetoken decimals
    static const int DECIMALS;
    
    ///EpicPulsetoken total supply
    static const int64_t TOTAL_SUPPLY;
};

} // namespace epicchaincpp