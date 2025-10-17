#pragma once

#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include "epicchaincpp/types/types.hpp"
#include "epicchaincpp/types/hash256.hpp"
#include "epicchaincpp/types/hash160.hpp"

namespace epicchaincpp {

/// Base class for RPC responses
class EpicChainResponse {
protected:
    nlohmann::json rawJson_;
    
public:
    explicit EpicChainResponse(const nlohmann::json& json) : rawJson_(json) {}
    virtual ~EpicChainResponse() = default;
    
    const nlohmann::json& getRawJson() const { return rawJson_; }
};

/// Version response
class EpicChainGetVersionResponse : public EpicChainResponse {
public:
    struct Version {
        int tcpPort;
        int wsPort;
        uint32_t nonce;
        std::string userAgent;
        uint32_t startHeight;
        uint32_t currentBlockIndex;
        uint32_t currentStateRootIndex;
    };
    
    explicit EpicChainGetVersionResponse(const nlohmann::json& json);
    
    Version getVersion() const;
};

/// Block response
class EpicChainGetBlockResponse : public EpicChainResponse {
public:
    struct Block {
        Hash256 hash;
        uint32_t size;
        uint32_t version;
        Hash256 previousBlockHash;
        Hash256 merkleRoot;
        uint64_t timestamp;
        uint64_t nonce;
        uint32_t index;
        uint8_t primaryIndex;
        Hash160 nextConsensus;
        std::vector<nlohmann::json> witnesses;
        std::vector<nlohmann::json> transactions;
    };
    
    explicit EpicChainGetBlockResponse(const nlohmann::json& json);
    
    Block getBlock() const;
};

/// Transaction response
class EpicChainGetRawTransactionResponse : public EpicChainResponse {
public:
    struct Transaction {
        Hash256 hash;
        uint32_t size;
        uint8_t version;
        uint32_t nonce;
        std::string sender;
        int64_t systemFee;
        int64_t networkFee;
        uint32_t validUntilBlock;
        std::vector<nlohmann::json> signers;
        std::vector<nlohmann::json> attributes;
        std::string script;
        std::vector<nlohmann::json> witnesses;
        uint32_t blockHash;
        uint32_t confirmations;
        uint64_t blockTime;
    };
    
    explicit EpicChainGetRawTransactionResponse(const nlohmann::json& json);
    
    Transaction getTransaction() const;
};

/// Application log response
class EpicChainGetApplicationLogResponse : public EpicChainResponse {
public:
    struct Execution {
        std::string trigger;
        std::string vmState;
        int64_t epicpulseConsumed;
        std::vector<nlohmann::json> stack;
        std::vector<nlohmann::json> notifications;
        std::string exception;
    };
    
    struct ApplicationLog {
        Hash256 txId;
        uint32_t blockHash;
        std::vector<Execution> executions;
    };
    
    explicit EpicChainGetApplicationLogResponse(const nlohmann::json& json);
    
    ApplicationLog getApplicationLog() const;
};

/// Contract state response
class EpicChainGetContractStateResponse : public EpicChainResponse {
public:
    struct ContractState {
        int id;
        uint32_t updateCounter;
        Hash160 hash;
        std::string nef;
        nlohmann::json manifest;
    };
    
    explicit EpicChainGetContractStateResponse(const nlohmann::json& json);
    
    ContractState getContractState() const;
};

/// XEP-17 balances response
class EpicChainGetXep17BalancesResponse : public EpicChainResponse {
public:
    struct Balance {
        Hash160 assetHash;
        std::string symbol;
        int decimals;
        std::string name;
        std::string amount;
        uint64_t lastUpdatedBlock;
    };
    
    struct Balances {
        std::string address;
        std::vector<Balance> balances;
    };
    
    explicit EpicChainGetXep17BalancesResponse(const nlohmann::json& json);
    
    Balances getBalances() const;
};

/// Invoke result response
class EpicChainInvokeResultResponse : public EpicChainResponse {
public:
    struct InvokeResult {
        std::string script;
        std::string state;
        int64_t epicpulseConsumed;
        std::string exception;
        std::vector<nlohmann::json> stack;
        std::vector<nlohmann::json> notifications;
        std::vector<nlohmann::json> diagnostics;
        std::string session;
    };
    
    explicit EpicChainInvokeResultResponse(const nlohmann::json& json);
    
    InvokeResult getResult() const;
};

/// Peers response
class EpicChainGetPeersResponse : public EpicChainResponse {
public:
    struct Peer {
        std::string address;
        int port;
    };
    
    struct Peers {
        std::vector<Peer> unconnected;
        std::vector<Peer> bad;
        std::vector<Peer> connected;
    };
    
    explicit EpicChainGetPeersResponse(const nlohmann::json& json);
    
    Peers getPeers() const;
};

/// UnclaimedEpicPulseresponse
class EpicChainGetUnclaimedGasResponse : public EpicChainResponse {
public:
    struct UnclaimedGas {
        std::string unclaimed;
        std::string address;
    };
    
    explicit EpicChainGetUnclaimedGasResponse(const nlohmann::json& json);
    
    UnclaimedGas getUnclaimedGas() const;
};

/// Wallet balance response
class EpicChainGetWalletBalanceResponse : public EpicChainResponse {
public:
    struct WalletBalance {
        std::string balance;
        std::string address;
        Hash160 assetHash;
    };
    
    explicit EpicChainGetWalletBalanceResponse(const nlohmann::json& json);
    
    WalletBalance getBalance() const;
};

} // namespace epicchaincpp