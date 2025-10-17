#pragma once

// Main header file for EpicChainCpp SDK
// Include all necessary components

// Core types
#include "epicchaincpp/types/types.hpp"
#include "epicchaincpp/types/hash160.hpp"
#include "epicchaincpp/types/hash256.hpp"
#include "epicchaincpp/types/call_flags.hpp"
#include "epicchaincpp/types/contract_parameter.hpp"
#include "epicchaincpp/types/contract_parameter_type.hpp"
#include "epicchaincpp/types/neo_vm_state_type.hpp"
#include "epicchaincpp/types/node_plugin_type.hpp"

// Constants
#include "epicchaincpp/epicchain_constants.hpp"

// Crypto
#include "epicchaincpp/crypto/ec_key_pair.hpp"
#include "epicchaincpp/crypto/ec_point.hpp"
#include "epicchaincpp/crypto/ecdsa_signature.hpp"
#include "epicchaincpp/crypto/hash.hpp"
#include "epicchaincpp/crypto/sign.hpp"
#include "epicchaincpp/crypto/wif.hpp"
#include "epicchaincpp/crypto/xep2.hpp"
#include "epicchaincpp/crypto/scrypt_params.hpp"
#include "epicchaincpp/crypto/bip32_ec_key_pair.hpp"

// Wallet
#include "epicchaincpp/wallet/wallet.hpp"
#include "epicchaincpp/wallet/account.hpp"
#include "epicchaincpp/wallet/nep6_wallet.hpp"
#include "epicchaincpp/wallet/nep6_account.hpp"

// Transaction
#include "epicchaincpp/transaction/transaction.hpp"
#include "epicchaincpp/transaction/signer.hpp"
#include "epicchaincpp/transaction/witness.hpp"
#include "epicchaincpp/transaction/witness_scope.hpp"
#include "epicchaincpp/transaction/witness_rule.hpp"
#include "epicchaincpp/transaction/transaction_attribute.hpp"

// Script
#include "epicchaincpp/script/script_builder.hpp"
#include "epicchaincpp/script/op_code.hpp"

// Serialization
#include "epicchaincpp/serialization/binary_writer.hpp"
#include "epicchaincpp/serialization/binary_reader.hpp"
#include "epicchaincpp/serialization/neo_serializable.hpp"

// Protocol/RPC
#include "epicchaincpp/protocol/neo_cpp.hpp"
#include "epicchaincpp/protocol/neo_rpc_client.hpp"
#include "epicchaincpp/protocol/http_service.hpp"
#include "epicchaincpp/protocol/response_types_impl.hpp"
#include "epicchaincpp/protocol/stack_item.hpp"

// Utils
#include "epicchaincpp/utils/base58.hpp"
#include "epicchaincpp/utils/base64.hpp"
#include "epicchaincpp/utils/hex.hpp"
#include "epicchaincpp/utils/address.hpp"

// Exceptions
#include "epicchaincpp/exceptions.hpp"

namespace epicchaincpp {
    // Version information
    constexpr const char* VERSION = "1.0.0";
    constexpr int VERSION_MAJOR = 1;
    constexpr int VERSION_MINOR = 0;
    constexpr int VERSION_PATCH = 0;
}