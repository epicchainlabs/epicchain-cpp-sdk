#include "epicchaincpp/protocol/neo_cpp.hpp"
#include "epicchaincpp/protocol/neo_rpc_client.hpp"
#include "epicchaincpp/protocol/http_service.hpp"
#include "epicchaincpp/transaction/transaction.hpp"
#include "epicchaincpp/exceptions.hpp"

namespace epicchaincpp {

EpicChainCpp::EpicChainCpp(const EpicChainCppConfig& config, SharedPtr<HttpService> httpService)
    : config_(config), httpService_(httpService) {
    if (!httpService) {
        throw IllegalArgumentException("HTTP service cannot be null");
    }
    // Extract base URL from HTTP service if needed
    rpcClient_ = std::make_shared<NeoRpcClient>(httpService->getUrl());
}

EpicChainCpp::EpicChainCpp(const std::string& url)
    : config_(EpicChainCppConfig()) {
    if (url.empty()) {
        throw IllegalArgumentException("URL cannot be empty");
    }
    httpService_ = std::make_shared<HttpService>(url);
    rpcClient_ = std::make_shared<NeoRpcClient>(url);
}

SharedPtr<epicchaincpp> EpicChainCpp::build(SharedPtr<HttpService> httpService, const EpicChainCppConfig& config) {
    return std::make_shared<epicchaincpp>(config, httpService);
}

SharedPtr<epicchaincpp> EpicChainCpp::build(const std::string& url, const EpicChainCppConfig& config) {
    auto httpService = std::make_shared<HttpService>(url);
    return std::make_shared<epicchaincpp>(config, httpService);
}

// Convenience methods that delegate to RPC client

uint32_t EpicChainCpp::getBlockCount() {
    return rpcClient_->getBlockCount();
}

Hash256 EpicChainCpp::getBestBlockHash() {
    return rpcClient_->getBestBlockHash();
}

SharedPtr<NeoGetBlockResponse> EpicChainCpp::getBlock(const Hash256& hash, bool verbose) {
    return rpcClient_->getBlock(hash, verbose);
}

SharedPtr<NeoGetBlockResponse> EpicChainCpp::getBlock(uint32_t index, bool verbose) {
    return rpcClient_->getBlock(index, verbose);
}

SharedPtr<NeoGetRawTransactionResponse> EpicChainCpp::getTransaction(const Hash256& txId, bool verbose) {
    return rpcClient_->getRawTransaction(txId, verbose);
}

SharedPtr<NeoGetContractStateResponse> EpicChainCpp::getContractState(const Hash160& scriptHash) {
    return rpcClient_->getContractState(scriptHash);
}

SharedPtr<NeoGetNep17BalancesResponse> EpicChainCpp::getNep17Balances(const std::string& address) {
    return rpcClient_->getNep17Balances(address);
}

SharedPtr<NeoInvokeResultResponse> EpicChainCpp::invokeFunction(const Hash160& scriptHash,
                                                          const std::string& method,
                                                          const nlohmann::json& params,
                                                          const nlohmann::json& signers) {
    return rpcClient_->invokeFunction(scriptHash, method, params, signers);
}

Hash256 EpicChainCpp::sendRawTransaction(const SharedPtr<Transaction>& transaction) {
    return rpcClient_->sendRawTransaction(transaction);
}

nlohmann::json EpicChainCpp::validateAddress(const std::string& address) {
    return rpcClient_->validateAddress(address);
}

SharedPtr<NeoGetVersionResponse> EpicChainCpp::getVersion() {
    return rpcClient_->getVersion();
}

} // namespace epicchaincpp