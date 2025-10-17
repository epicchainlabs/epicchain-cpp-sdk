#ifndef EPICCHAINCPP_PROTOCOL_CORE_RESPONSE_EPICCHAIN_GET_TOKEN_BALANCES_HPP
#define EPICCHAINCPP_PROTOCOL_CORE_RESPONSE_EPICCHAIN_GET_TOKEN_BALANCES_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <epicchaincpp/protocol/core/response.hpp>
#include <epicchaincpp/types/hash160.hpp>

namespace epicchaincpp {

/**
 * Base interface for token balance information
 */
class TokenBalance {
public:
    virtual ~TokenBalance() = default;
    virtual Hash160 getAssetHash() const = 0;
};

/**
 * Base interface for token balances collection
 */
template<typename TBalance>
class TokenBalances {
public:
    virtual ~TokenBalances() = default;
    virtual std::string getAddress() const = 0;
    virtual std::vector<TBalance> getBalances() const = 0;
};

/**
 * Generic response type for token balance queries
 * Used as base for XEP-11 and XEP-17 balance responses
 */
template<typename T>
class NeoGetTokenBalances : public Response<T> {
public:
    NeoGetTokenBalances() = default;
    
    explicit NeoGetTokenBalances(const nlohmann::json& j) {
        this->from_json(j);
    }
};

} // namespace epicchaincpp

#endif // EPICCHAINCPP_PROTOCOL_CORE_RESPONSE_EPICCHAIN_GET_TOKEN_BALANCES_HPP