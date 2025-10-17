#pragma once

#include <string>
#include <optional>
#include <memory>
#include "../types/hash160.hpp"
#include "../neo_swift_error.hpp"

namespace epicchaincpp {

class epicchaincpp; // Forward declaration

/**
 * Wrapper class to generate XEP-9 compatible URI schemes for XEP-17 Token transfers.
 * Equivalent to EpicChainURI in the Swift SDK
 */
class EpicChainURI {
public:
    static const std::string EPICCHAIN_SCHEME;
    static const int MIN_XEP9_URI_LENGTH = 38;
    static const std::string EPICCHAIN_TOKEN_STRING;
    static const std::string EPICPULSE_TOKEN_STRING;

    /**
     * Default constructor
     */
    EpicChainURI();

    /**
     * Constructor with EpicChainCpp instance
     * @param epicchainCpp The EpicChainCpp instance
     */
    explicit EpicChainURI(std::shared_ptr<epicchaincpp> epicchainCpp);

    /**
     * Creates a EpicChainURI from a XEP-9 URI String
     * @param uriString A XEP-9 URI String
     * @return A EpicChainURI object
     * @throws EpicChainSwiftError if the URI string is invalid
     */
    static EpicChainURI fromURI(const std::string& uriString);

    /**
     * Sets the recipient's script hash
     * @param recipient The recipient's script hash
     * @return This EpicChainURI object
     */
    EpicChainURI& to(const Hash160& recipient);

    /**
     * Sets the token
     * @param token The token hash
     * @return This EpicChainURI object
     */
    EpicChainURI& token(const Hash160& token);

    /**
     * Sets the token
     * @param token The token hash, 'neo' or 'gas'
     * @return This EpicChainURI object
     * @throws EpicChainSwiftError if the token string is invalid
     */
    EpicChainURI& token(const std::string& token);

    /**
     * Sets the amount
     * @param amount The amount
     * @return This EpicChainURI object
     */
    EpicChainURI& amount(double amount);

    /**
     * Sets the EpicChainCpp instance
     * @param epicchainCpp The EpicChainCpp instance
     * @return This EpicChainURI object
     */
    EpicChainURI& epicchainCpp(std::shared_ptr<epicchaincpp> epicchainCpp);

    /**
     * Builds a XEP-9 URI from the set variables
     * @return This EpicChainURI object
     * @throws EpicChainSwiftError if required fields are missing
     */
    EpicChainURI& buildURI();

    /**
     * Get the XEP-9 URI as string
     * @return The URI string or empty if not built
     */
    std::string getURIString() const;

    /**
     * Get the recipient address
     * @return The recipient address or empty if not set
     */
    std::string getRecipientAddress() const;

    /**
     * Get the token as a string
     * @return The token as a string or empty if not set
     */
    std::string getTokenString() const;

    /**
     * Get the token as an address
     * @return The token as an address or empty if not set
     */
    std::string getTokenAddress() const;

    /**
     * Get the amount as a string
     * @return The amount as a string or empty if not set
     */
    std::string getAmountString() const;

    /**
     * Get the EpicChainCpp instance
     * @return The EpicChainCpp instance
     */
    std::shared_ptr<epicchaincpp> getEpicChainCpp() const;

    /**
     * Get the recipient
     * @return The recipient
     */
    const std::optional<Hash160>& getRecipient() const;

    /**
     * Get the token
     * @return The token
     */
    const std::optional<Hash160>& getToken() const;

    /**
     * Get the amount
     * @return The amount
     */
    std::optional<double> getAmount() const;

private:
    std::string uri_;
    std::shared_ptr<EpicChainCpp> epicchainCpp_;
    std::optional<Hash160> recipient_;
    std::optional<Hash160> token_;
    std::optional<double> amount_;

    bool isNeoToken(const Hash160& token) const;
    bool isEpicPulseToken(const Hash160& token) const;
    std::string buildQueryPart() const;
};

} // namespace epicchaincpp