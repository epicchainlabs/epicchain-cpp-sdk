#include "epicchaincpp/contract/role_management.hpp"
#include "epicchaincpp/protocol/neo_rpc_client.hpp"
#include "epicchaincpp/types/contract_parameter.hpp"
#include "epicchaincpp/transaction/transaction_builder.hpp"
#include "epicchaincpp/utils/hex.hpp"
#include "epicchaincpp/exceptions.hpp"

namespace epicchaincpp {

const Hash160 RoleManagement::SCRIPT_HASH = Hash160("0x49cf4e5378ffcd4dec034fd98a174c5491e395e2");
const std::string RoleManagement::NAME = "RoleManagement";

RoleManagement::RoleManagement(const SharedPtr<NeoRpcClient>& client)
    : SmartContract(SCRIPT_HASH, client) {
}

SharedPtr<RoleManagement> RoleManagement::create(const SharedPtr<NeoRpcClient>& client) {
    return std::make_shared<RoleManagement>(client);
}

std::vector<std::string> RoleManagement::getDesignatedByRole(Role role, uint32_t blockIndex) {
    std::vector<ContractParameter> params = {
        ContractParameter::integer(static_cast<uint8_t>(role)),
        ContractParameter::integer(blockIndex)
    };
    
    auto result = invokeFunction("getDesignatedByRole", params);
    std::vector<std::string> publicKeys;
    
    if (result["stack"][0]["type"] == "Array") {
        for (const auto& item : result["stack"][0]["value"]) {
            publicKeys.push_back(item["value"].get<std::string>());
        }
    }
    
    return publicKeys;
}

SharedPtr<TransactionBuilder> RoleManagement::designateAsRole(Role role, const std::vector<std::string>& publicKeys) {
    auto builder = std::make_shared<TransactionBuilder>(client_);
    
    // Convert public keys to ByteArray parameters
    std::vector<ContractParameter> keyParams;
    for (const auto& pubKey : publicKeys) {
        auto keyBytes = Hex::decode(pubKey);
        keyParams.push_back(ContractParameter::byteArray(keyBytes));
    }
    
    std::vector<ContractParameter> params = {
        ContractParameter::integer(static_cast<int>(role)),
        ContractParameter::array(keyParams)
    };
    
    builder->callContract(SCRIPT_HASH, "designateAsRole", params);
    
    return builder;
}

} // namespace epicchaincpp