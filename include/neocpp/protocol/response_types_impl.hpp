#pragma once

#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include "epicchaincpp/types/types.hpp"
#include "epicchaincpp/types/hash256.hpp"
#include "epicchaincpp/types/hash160.hpp"

namespace epicchaincpp {

// Forward declarations
class StackItem;
using StackItemPtr = std::shared_ptr<StackItem>;

/// Version response
class EpicChainGetVersionResponse {
public:
    void parseJson(const nlohmann::json& json);
    
    int getTcpPort() const { return tcpPort_; }
    int getWsPort() const { return wsPort_; }
    uint32_t getNonce() const { return nonce_; }
    const std::string& getUserAgent() const { return userAgent_; }
    const nlohmann::json& getProtocol() const { return protocol_; }
    const nlohmann::json& getRawJson() const { return rawJson_; }
    
private:
    int tcpPort_ = 0;
    int wsPort_ = 0;
    uint32_t nonce_ = 0;
    std::string userAgent_;
    nlohmann::json protocol_;
    nlohmann::json rawJson_;
};

/// Peers response
class EpicChainGetPeersResponse {
public:
    void parseJson(const nlohmann::json& json);
    
    const nlohmann::json& getConnected() const { return connected_; }
    const nlohmann::json& getUnconnected() const { return unconnected_; }
    const nlohmann::json& getBad() const { return bad_; }
    const nlohmann::json& getRawJson() const { return rawJson_; }
    
private:
    nlohmann::json connected_;
    nlohmann::json unconnected_;
    nlohmann::json bad_;
    nlohmann::json rawJson_;
};

/// Block response
class EpicChainGetBlockResponse {
public:
    void parseJson(const nlohmann::json& json);
    
    const Hash256& getHash() const { return hash_; }
    int getSize() const { return size_; }
    int getVersion() const { return version_; }
    const Hash256& getPreviousBlockHash() const { return previousBlockHash_; }
    const Hash256& getMerkleRoot() const { return merkleRoot_; }
    uint64_t getTime() const { return time_; }
    uint32_t getIndex() const { return index_; }
    const std::string& getNextConsensus() const { return nextConsensus_; }
    const nlohmann::json& getWitnesses() const { return witnesses_; }
    const nlohmann::json& getTransactions() const { return transactions_; }
    int getConfirmations() const { return confirmations_; }
    const Hash256& getNextBlockHash() const { return nextBlockHash_; }
    bool hasNextBlockHash() const { return hasNextBlockHash_; }
    const nlohmann::json& getRawJson() const { return rawJson_; }
    
private:
    Hash256 hash_;
    int size_ = 0;
    int version_ = 0;
    Hash256 previousBlockHash_;
    Hash256 merkleRoot_;
    uint64_t time_ = 0;
    uint32_t index_ = 0;
    std::string nextConsensus_;
    nlohmann::json witnesses_;
    nlohmann::json transactions_;
    int confirmations_ = 0;
    Hash256 nextBlockHash_;
    bool hasNextBlockHash_ = false;
    nlohmann::json rawJson_;
};

/// Raw transaction response
class EpicChainGetRawTransactionResponse {
public:
    void parseJson(const nlohmann::json& json);
    
    const Hash256& getHash() const { return hash_; }
    int getSize() const { return size_; }
    int getVersion() const { return version_; }
    uint32_t getNonce() const { return nonce_; }
    const std::string& getSender() const { return sender_; }
    const std::string& getSysfee() const { return sysfee_; }
    const std::string& getNetfee() const { return netfee_; }
    uint32_t getValidUntilBlock() const { return validUntilBlock_; }
    const nlohmann::json& getSigners() const { return signers_; }
    const nlohmann::json& getAttributes() const { return attributes_; }
    const nlohmann::json& getWitnesses() const { return witnesses_; }
    const std::string& getScript() const { return script_; }
    const Hash256& getBlockHash() const { return blockHash_; }
    int getConfirmations() const { return confirmations_; }
    uint64_t getBlockTime() const { return blockTime_; }
    const nlohmann::json& getRawJson() const { return rawJson_; }
    
private:
    Hash256 hash_;
    int size_ = 0;
    int version_ = 0;
    uint32_t nonce_ = 0;
    std::string sender_;
    std::string sysfee_;
    std::string netfee_;
    uint32_t validUntilBlock_ = 0;
    nlohmann::json signers_;
    nlohmann::json attributes_;
    nlohmann::json witnesses_;
    std::string script_;
    Hash256 blockHash_;
    int confirmations_ = 0;
    uint64_t blockTime_ = 0;
    nlohmann::json rawJson_;
};

/// Application log response
class EpicChainGetApplicationLogResponse {
public:
    void parseJson(const nlohmann::json& json);
    
    const std::string& getTxId() const { return txid_; }
    const nlohmann::json& getExecutions() const { return executions_; }
    const nlohmann::json& getRawJson() const { return rawJson_; }
    
private:
    std::string txid_;
    nlohmann::json executions_;
    nlohmann::json rawJson_;
};

/// Contract state response
class EpicChainGetContractStateResponse {
public:
    void parseJson(const nlohmann::json& json);
    
    int getId() const { return id_; }
    int getUpdateCounter() const { return updateCounter_; }
    const Hash160& getHash() const { return hash_; }
    const nlohmann::json& getNef() const { return nef_; }
    const nlohmann::json& getManifest() const { return manifest_; }
    const nlohmann::json& getRawJson() const { return rawJson_; }
    
private:
    int id_ = 0;
    int updateCounter_ = 0;
    Hash160 hash_;
    nlohmann::json nef_;
    nlohmann::json manifest_;
    nlohmann::json rawJson_;
};

/// XEP-17 balance
struct EpicChainNep17Balance {
    Hash160 assetHash;
    std::string amount;
    uint32_t lastUpdatedBlock;
};

/// XEP-17 balances response
class EpicChainGetXep17BalancesResponse {
public:
    void parseJson(const nlohmann::json& json);
    
    const std::string& getAddress() const { return address_; }
    const std::vector<EpicChainNep17Balance>& getBalances() const { return balances_; }
    const nlohmann::json& getRawJson() const { return rawJson_; }
    
private:
    std::string address_;
    std::vector<EpicChainNep17Balance> balances_;
    nlohmann::json rawJson_;
};

/// Invoke result response
class EpicChainInvokeResultResponse {
public:
    void parseJson(const nlohmann::json& json);
    
    const std::string& getScript() const { return script_; }
    const std::string& getState() const { return state_; }
    const std::string& getEpicPulseConsumed() const { return epicpulseConsumed_; }
    const std::string& getException() const { return exception_; }
    bool hasException() const { return hasException_; }
    const std::vector<StackItemPtr>& getStack() const { return stack_; }
    const std::string& getTx() const { return tx_; }
    const nlohmann::json& getNotifications() const { return notifications_; }
    const nlohmann::json& getDiagnostics() const { return diagnostics_; }
    const nlohmann::json& getRawJson() const { return rawJson_; }
    
private:
    std::string script_;
    std::string state_;
    std::string epicpulseConsumed_;
    std::string exception_;
    bool hasException_ = false;
    std::vector<StackItemPtr> stack_;
    std::string tx_;
    nlohmann::json notifications_;
    nlohmann::json diagnostics_;
    nlohmann::json rawJson_;
};

/// Unclaimed epicpulse response
class EpicChainGetUnclaimedGasResponse {
public:
    void parseJson(const nlohmann::json& json);
    
    const std::string& getUnclaimed() const { return unclaimed_; }
    const std::string& getAddress() const { return address_; }
    const nlohmann::json& getRawJson() const { return rawJson_; }
    
private:
    std::string unclaimed_;
    std::string address_;
    nlohmann::json rawJson_;
};

/// Wallet balance response
class EpicChainGetWalletBalanceResponse {
public:
    void parseJson(const nlohmann::json& json);
    
    const std::string& getBalance() const { return balance_; }
    const nlohmann::json& getRawJson() const { return rawJson_; }
    
private:
    std::string balance_;
    nlohmann::json rawJson_;
};

} // namespace epicchaincpp