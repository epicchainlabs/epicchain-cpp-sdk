#pragma once

#include "epicchaincpp/wallet/account.hpp"
#include <nlohmann/json.hpp>

namespace epicchaincpp {

/// XEP-6 standard account implementation
class Nep6Account : public Account {
private:
    nlohmann::json extra_;
    
public:
    /// Constructor from key pair
    /// @param keyPair The EC key pair
    /// @param label Optional label for the account
    explicit Nep6Account(const SharedPtr<ECKeyPair>& keyPair, const std::string& label = "");
    
    /// Get extra data
    const nlohmann::json& getExtra() const { return extra_; }
    
    /// Set extra data
    void setExtra(const nlohmann::json& extra) { extra_ = extra; }
    
    /// Convert account to XEP-6 JSON
    /// @return The XEP-6 JSON representation
    nlohmann::json toJson() const;
    
    /// Create account from XEP-6 JSON
    /// @param json The XEP-6 JSON
    /// @param password Optional password for decryption
    /// @return The account
    static SharedPtr<Nep6Account> fromJson(const nlohmann::json& json, const std::string& password = "");
};

} // namespace epicchaincpp