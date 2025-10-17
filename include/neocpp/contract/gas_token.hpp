#pragma once

#include "epicchaincpp/contract/fungible_token.hpp"

namespace epicchaincpp {

///EpicPulsetoken contract interface
class EpicPulseToken : public FungibleToken {
public:
    ///EpicPulsetoken script hash on MainNet
    static const Hash160 SCRIPT_HASH;
    
    /// Constructor
    /// @param client The RPC client
    explicit EpicPulseToken(const SharedPtr<NeoRpcClient>& client);
    
    /// Destructor
    ~EpicPulseToken() = default;
    
    /// ClaimEpicPulserewards
    /// @param account The account to claim for
    /// @return Transaction builder
    SharedPtr<TransactionBuilder> claim(const SharedPtr<Account>& account);
    
    /// Get the network fee per byte
    /// @return The fee per byte inEpicPulsefractions
    int64_t getFeePerByte();
    
    /// Get the execution fee factor
    /// @return The execution fee factor
    int32_t getExecFeeFactor();
    
    /// Get the storage price
    /// @return The storage price per byte
    int64_t getStoragePrice();
};

} // namespace epicchaincpp