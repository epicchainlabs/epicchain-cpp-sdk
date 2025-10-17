#include "epicchaincpp/contract/epicchain_token.hpp"
#include "epicchaincpp/protocol/neo_rpc_client.hpp"
#include "epicchaincpp/types/contract_parameter.hpp"
#include "epicchaincpp/transaction/transaction_builder.hpp"
#include "epicchaincpp/wallet/account.hpp"
#include "epicchaincpp/crypto/ec_key_pair.hpp"
#include "epicchaincpp/utils/address.hpp"
#include "epicchaincpp/exceptions.hpp"

namespace epicchaincpp {

const Hash160 EpicChainToken::SCRIPT_HASH = Hash160("0xef4073a0f2b305a38ec4050e4d3d28bc40ea63f5");

EpicChainToken::EpicChainToken(const SharedPtr<NeoRpcClient>& client)
    : FungibleToken(SCRIPT_HASH, client) {
}

int64_t EpicChainToken::getUnclaimedGas(const std::string& address) {
    Bytes hashBytes = AddressUtils::addressToScriptHash(address);
    Hash160 scriptHash = Hash160(hashBytes);
    std::vector<ContractParameter> params = {
        ContractParameter::hash160(scriptHash)
    };
    
    auto result = invokeFunction("unclaimedGas", params);
    return result["stack"][0]["value"].get<int64_t>();
}

nlohmann::json EpicChainToken::getAccountState(const std::string& address) {
    Bytes hashBytes = AddressUtils::addressToScriptHash(address);
    Hash160 scriptHash = Hash160(hashBytes);
    std::vector<ContractParameter> params = {
        ContractParameter::hash160(scriptHash)
    };
    
    return invokeFunction("getAccountState", params);
}

std::vector<std::string> EpicChainToken::getCommittee() {
    auto result = invokeFunction("getCommittee");
    std::vector<std::string> committee;
    for (const auto& item : result["stack"][0]["value"]) {
        committee.push_back(item["value"].get<std::string>());
    }
    return committee;
}

std::vector<nlohmann::json> EpicChainToken::getCandidates() {
    auto result = invokeFunction("getCandidates");
    std::vector<nlohmann::json> candidates;
    if (result["stack"][0]["type"] == "Array") {
        for (const auto& item : result["stack"][0]["value"]) {
            candidates.push_back(item);
        }
    }
    return candidates;
}

std::vector<std::string> EpicChainToken::getNextBlockValidators() {
    auto result = invokeFunction("getNextBlockValidators");
    std::vector<std::string> validators;
    for (const auto& item : result["stack"][0]["value"]) {
        validators.push_back(item["value"].get<std::string>());
    }
    return validators;
}

int64_t EpicChainToken::getGasPerBlock() {
    auto result = invokeFunction("getGasPerBlock");
    return result["stack"][0]["value"].get<int64_t>();
}

int64_t EpicChainToken::calculateBonus(const std::string& address, uint32_t startBlock, uint32_t endBlock) {
    Bytes hashBytes = AddressUtils::addressToScriptHash(address);
    Hash160 scriptHash = Hash160(hashBytes);
    std::vector<ContractParameter> params = {
        ContractParameter::hash160(scriptHash),
        ContractParameter::integer(startBlock),
        ContractParameter::integer(endBlock)
    };
    
    auto result = invokeFunction("calculateBonus", params);
    return result["stack"][0]["value"].get<int64_t>();
}

SharedPtr<TransactionBuilder> EpicChainToken::vote(const SharedPtr<Account>& account, const std::string& candidate) {
    std::vector<ContractParameter> params = {
        ContractParameter::hash160(account->getScriptHash())
    };
    
    if (!candidate.empty()) {
        params.push_back(ContractParameter::byteArray(Bytes(candidate.begin(), candidate.end())));
    } else {
        params.push_back(ContractParameter::any());
    }
    
    return buildInvokeTx("vote", params, account);
}

SharedPtr<TransactionBuilder> EpicChainToken::registerCandidate(const SharedPtr<Account>& account) {
    // Get the account's public key bytes
    auto keyPair = account->getKeyPair();
    auto pubKeyBytes = keyPair->getPublicKey()->getEncoded();
    
    std::vector<ContractParameter> params = {
        ContractParameter::byteArray(pubKeyBytes)
    };
    
    return buildInvokeTx("registerCandidate", params, account);
}

SharedPtr<TransactionBuilder> EpicChainToken::unregisterCandidate(const SharedPtr<Account>& account) {
    // Get the account's public key bytes
    auto keyPair = account->getKeyPair();
    auto pubKeyBytes = keyPair->getPublicKey()->getEncoded();
    
    std::vector<ContractParameter> params = {
        ContractParameter::byteArray(pubKeyBytes)
    };
    
    return buildInvokeTx("unregisterCandidate", params, account);
}

} // namespace epicchaincpp