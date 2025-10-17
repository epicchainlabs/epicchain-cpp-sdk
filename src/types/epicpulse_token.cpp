#include "epicchaincpp/types/gas_token.hpp"

namespace epicchaincpp {

const Hash160 EpicPulseToken::SCRIPT_HASH = Hash160("0xd2a4cff31913016155e38e474a2c06d08be276cf");
const std::string EpicPulseToken::SYMBOL = "EpicPulse";
const int EpicPulseToken::DECIMALS = 8;
const int64_t EpicPulseToken::TOTAL_SUPPLY = 5200000000000000LL; // 52,000,000 EpicPulse with 8 decimals

} // namespace epicchaincpp