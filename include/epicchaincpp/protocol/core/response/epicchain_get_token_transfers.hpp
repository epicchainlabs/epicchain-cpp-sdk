#ifndef EPICCHAINCPP_PROTOCOL_CORE_RESPONSE_EPICCHAIN_GET_TOKEN_TRANSFERS_HPP
#define EPICCHAINCPP_PROTOCOL_CORE_RESPONSE_EPICCHAIN_GET_TOKEN_TRANSFERS_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <epicchaincpp/protocol/core/response.hpp>
#include <epicchaincpp/types/hash160.hpp>
#include <epicchaincpp/types/hash256.hpp>

namespace epicchaincpp {

/**
 * Base interface for token transfer information
 */
class TokenTransfer {
public:
    virtual ~TokenTransfer() = default;
    virtual int getTimestamp() const = 0;
    virtual Hash160 getAssetHash() const = 0;
    virtual std::string getTransferAddress() const = 0;
    virtual int getAmount() const = 0;
    virtual int getBlockIndex() const = 0;
    virtual int getTransferNotifyIndex() const = 0;
    virtual Hash256 getTxHash() const = 0;
};

/**
 * Base interface for token transfers collection
 */
template<typename TTransfer>
class TokenTransfers {
public:
    virtual ~TokenTransfers() = default;
    virtual std::vector<TTransfer> getSent() const = 0;
    virtual std::vector<TTransfer> getReceived() const = 0;
    virtual std::string getTransferAddress() const = 0;
};

/**
 * Generic response type for token transfer queries
 * Used as base for XEP-11 and XEP-17 transfer responses
 */
template<typename T>
class NeoGetTokenTransfers : public Response<T> {
public:
    NeoGetTokenTransfers() = default;
    
    explicit NeoGetTokenTransfers(const nlohmann::json& j) {
        this->from_json(j);
    }
};

} // namespace epicchaincpp

#endif // EPICCHAINCPP_PROTOCOL_CORE_RESPONSE_EPICCHAIN_GET_TOKEN_TRANSFERS_HPP