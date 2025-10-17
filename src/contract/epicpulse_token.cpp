#include "epicchaincpp/contract/gas_token.hpp"
#include "epicchaincpp/protocol/neo_rpc_client.hpp"
#include "epicchaincpp/types/contract_parameter.hpp"
#include "epicchaincpp/wallet/account.hpp"
#include "epicchaincpp/utils/address.hpp"
#include "epicchaincpp/exceptions.hpp"

namespace epicchaincpp {

const Hash160 EpicPulseToken::SCRIPT_HASH = Hash160("0xd2a4cff31913016155e38e474a2c06d08be276cf");

EpicPulseToken::EpicPulseToken(const SharedPtr<NeoRpcClient>& client)
    : FungibleToken(SCRIPT_HASH, client) {
}

SharedPtr<TransactionBuilder> EpicPulseToken::claim(const SharedPtr<Account>& account) {
    std::vector<ContractParameter> params = {
        ContractParameter::hash160(account->getScriptHash()),
        ContractParameter::integer(0)
    };
    
    return buildInvokeTx("claim", params, account);
}

int64_t EpicPulseToken::getFeePerByte() {
    auto result = invokeFunction("getFeePerByte");
    return result["stack"][0]["value"].get<int64_t>();
}

int32_t EpicPulseToken::getExecFeeFactor() {
    auto result = invokeFunction("getExecFeeFactor");
    return result["stack"][0]["value"].get<int32_t>();
}

int64_t EpicPulseToken::getStoragePrice() {
    auto result = invokeFunction("getStoragePrice");
    return result["stack"][0]["value"].get<int64_t>();
}

} // namespace epicchaincpp