#pragma once

#include <string>
#include <stdexcept>

namespace epicchaincpp {

/// Base exception class for EpicChain SDK
class EpicChainException : public std::runtime_error {
public:
    explicit EpicChainException(const std::string& message) 
        : std::runtime_error(message) {}
};

/// Exception thrown when a method is not yet implemented
class NotImplementedException : public EpicChainException {
public:
    explicit NotImplementedException(const std::string& message)
        : EpicChainException("Not implemented: " + message) {}
    
    NotImplementedException()
        : EpicChainException("Method not yet implemented") {}
};

/// Exception for illegal arguments
class IllegalArgumentException : public EpicChainException {
public:
    explicit IllegalArgumentException(const std::string& message)
        : EpicChainException("Illegal argument: " + message) {}
};

/// Exception for illegal state
class IllegalStateException : public EpicChainException {
public:
    explicit IllegalStateException(const std::string& message)
        : EpicChainException("Illegal state: " + message) {}
};

/// Exception for runtime errors
class RuntimeException : public EpicChainException {
public:
    explicit RuntimeException(const std::string& message)
        : EpicChainException("Runtime error: " + message) {}
};

/// Exception for unsupported operations
class UnsupportedOperationException : public EpicChainException {
public:
    explicit UnsupportedOperationException(const std::string& message)
        : EpicChainException("Unsupported operation: " + message) {}
};

/// Exception for invalid format
class InvalidFormatException : public EpicChainException {
public:
    explicit InvalidFormatException(const std::string& message)
        : EpicChainException("Invalid format: " + message) {}
};

/// Exception for deserialization errors
class DeserializationException : public EpicChainException {
public:
    explicit DeserializationException(const std::string& message)
        : EpicChainException("Deserialization error: " + message) {}
};

/// Exception for serialization errors
class SerializationException : public EpicChainException {
public:
    explicit SerializationException(const std::string& message)
        : EpicChainException("Serialization error: " + message) {}
};

/// Exception for script errors
class ScriptException : public EpicChainException {
public:
    explicit ScriptException(const std::string& message)
        : EpicChainException("Script error: " + message) {}
};

/// Exception for transaction errors
class TransactionException : public EpicChainException {
public:
    explicit TransactionException(const std::string& message)
        : EpicChainException("Transaction error: " + message) {}
};

/// Exception for wallet errors
class WalletException : public EpicChainException {
public:
    explicit WalletException(const std::string& message)
        : EpicChainException("Wallet error: " + message) {}
};

/// Exception for network errors
class NetworkException : public EpicChainException {
public:
    explicit NetworkException(const std::string& message)
        : EpicChainException("Network error: " + message) {}
};

/// Exception for cryptographic errors
class CryptoException : public EpicChainException {
public:
    explicit CryptoException(const std::string& message)
        : EpicChainException("Crypto error: " + message) {}
};

/// Exception for XEP-2 operations
class XEP2Exception : public EpicChainException {
public:
    explicit XEP2Exception(const std::string& message)
        : EpicChainException("XEP-2 error: " + message) {}
};

/// Exception for signing operations
class SignException : public EpicChainException {
public:
    explicit SignException(const std::string& message)
        : EpicChainException("Sign error: " + message) {}
};

/// Exception for RPC operations
class RpcException : public EpicChainException {
public:
    explicit RpcException(const std::string& message)
        : EpicChainException("RPC error: " + message) {}
};

} // namespace epicchaincpp