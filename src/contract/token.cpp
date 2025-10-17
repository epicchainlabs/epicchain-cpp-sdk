#include "epicchaincpp/contract/token.hpp"

namespace epicchaincpp {

Token::Token(const Hash160& scriptHash, const SharedPtr<NeoRpcClient>& client)
    : SmartContract(scriptHash, client) {
}

} // namespace epicchaincpp