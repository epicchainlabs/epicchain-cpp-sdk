#pragma once

#include <string>
#include <stdexcept>

namespace epicchaincpp {

/// Base error class for EpicChain SDK
class EpicChainSwiftError : public std::runtime_error {
public:
    explicit EpicChainSwiftError(const std::string& message) 
        : std::runtime_error(message) {}
};

/// Contract error
class ContractError : public EpicChainSwiftError {
public:
    enum class ErrorType {
        INVALID_NEO_NAME,
        INVALID_NNS_ROOT,
        UNEXPECTED_RETURN_TYPE,
        UNRESOLVABLE_DOMAIN,
        GENERIC
    };

    explicit ContractError(const std::string& message) 
        : EpicChainSwiftError("Contract error: " + message), type_(ErrorType::GENERIC) {}
    
    ContractError(ErrorType type, const std::string& message)
        : EpicChainSwiftError("Contract error: " + message), type_(type) {}

    ErrorType getType() const { return type_; }

    std::string getTypeString() const {
        switch (type_) {
            case ErrorType::INVALID_NEO_NAME:
                return "INVALID_NEO_NAME";
            case ErrorType::INVALID_NNS_ROOT:
                return "INVALID_NNS_ROOT";
            case ErrorType::UNEXPECTED_RETURN_TYPE:
                return "UNEXPECTED_RETURN_TYPE";
            case ErrorType::UNRESOLVABLE_DOMAIN:
                return "UNRESOLVABLE_DOMAIN";
            case ErrorType::GENERIC:
            default:
                return "GENERIC";
        }
    }

    static ContractError invalidNeoName(const std::string& name) {
        return ContractError(ErrorType::INVALID_NEO_NAME, "'" + name + "' is not a valid NNS name.");
    }

    static ContractError invalidNNSRoot(const std::string& root) {
        return ContractError(ErrorType::INVALID_NNS_ROOT, "'" + root + "' is not a valid NNS root.");
    }

    static ContractError unexpectedReturnType(const std::string& message) {
        return ContractError(ErrorType::UNEXPECTED_RETURN_TYPE, message);
    }

    static ContractError unresolvableDomain(const std::string& domain) {
        return ContractError(ErrorType::UNRESOLVABLE_DOMAIN, "Could not resolve domain '" + domain + "'.");
    }

private:
    ErrorType type_ = ErrorType::GENERIC;
};

/// Transaction error
class TransactionError : public EpicChainSwiftError {
public:
    explicit TransactionError(const std::string& message) 
        : EpicChainSwiftError("Transaction error: " + message) {}
};

/// Protocol error
class ProtocolError : public EpicChainSwiftError {
public:
    explicit ProtocolError(const std::string& message) 
        : EpicChainSwiftError("Protocol error: " + message) {}
        
    /// Create a ProtocolError for RPC response errors
    /// @param error The error message from the RPC response
    static ProtocolError rpcResponseError(const std::string& error) {
        return ProtocolError("The Neo node responded with an error: " + error);
    }
    
    /// Create a ProtocolError for VM invocation faults
    /// @param error The fault error message
    static ProtocolError invocationFaultState(const std::string& error) {
        return ProtocolError("The invocation resulted in a FAULT VM state. The VM exited due to the following exception: " + error);
    }
    
    /// Create a ProtocolError for client connection errors
    /// @param message The connection error message
    static ProtocolError clientConnection(const std::string& message) {
        return ProtocolError(message);
    }
    
    /// Create a ProtocolError for stack item casting errors
    /// @param itemJson The JSON representation of the stack item
    /// @param target The target type that couldn't be cast to
    static ProtocolError stackItemCastError(const std::string& itemJson, const std::string& target) {
        return ProtocolError("Cannot cast stack item " + itemJson + " to a " + target + ".");
    }
};

/// Wallet error
class WalletError : public EpicChainSwiftError {
public:
    explicit WalletError(const std::string& message) 
        : EpicChainSwiftError("Wallet error: " + message) {}
        
    /// Create a WalletError for account state errors
    /// @param message The account state error message
    static WalletError accountState(const std::string& message) {
        return WalletError(message); // Note: This doesn't add the "Wallet error: " prefix
    }
};

/// Crypto error
class CryptoError : public EpicChainSwiftError {
public:
    explicit CryptoError(const std::string& message) 
        : EpicChainSwiftError("Crypto error: " + message) {}
};

/// XEP2 error
class XEP2Error : public CryptoError {
public:
    explicit XEP2Error(const std::string& message) 
        : CryptoError("XEP2: " + message) {}
};

/// Sign error
class SignError : public CryptoError {
public:
    explicit SignError(const std::string& message) 
        : CryptoError("Sign: " + message) {}
        
    /// Create a SignError for header byte out of range
    /// @param header The header byte that is out of range
    explicit SignError(uint8_t header) 
        : CryptoError("Sign: Header byte out of range: " + std::to_string(header)) {}
        
    /// Create a SignError for public key recovery failure
    static SignError recoverFailed() {
        return SignError("Could not recover public key from signature");
    }
};

/// Script error
class ScriptError : public EpicChainSwiftError {
public:
    explicit ScriptError(const std::string& message) 
        : EpicChainSwiftError("Script error: " + message) {}
};

/// Serialization error
class SerializationError : public EpicChainSwiftError {
public:
    explicit SerializationError(const std::string& message) 
        : EpicChainSwiftError("Serialization error: " + message) {}
};

/// Validation error
class ValidationError : public EpicChainSwiftError {
public:
    explicit ValidationError(const std::string& message) 
        : EpicChainSwiftError("Validation error: " + message) {}
};

/// Network error
class NetworkError : public EpicChainSwiftError {
public:
    explicit NetworkError(const std::string& message) 
        : EpicChainSwiftError("Network error: " + message) {}
};

/// RPC error
class RpcError : public NetworkError {
public:
    RpcError(int code, const std::string& message) 
        : NetworkError("RPC error " + std::to_string(code) + ": " + message), 
          code_(code) {}
    
    int getCode() const { return code_; }
    
private:
    int code_;
};

} // namespace epicchaincpp