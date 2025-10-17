#pragma once

#include "epicchaincpp/wallet/wallet.hpp"
#include <nlohmann/json.hpp>

namespace epicchaincpp {

/// XEP-6 standard wallet implementation
class Xep6Wallet : public Wallet {
private:
    nlohmann::json extra_;
    std::vector<nlohmann::json> tokens_;
    
public:
    /// Constructor
    /// @param name The wallet name
    /// @param version The wallet version
    explicit Xep6Wallet(const std::string& name = "EpicChainCpp Wallet", const std::string& version = "1.0");
    
    /// Destructor
    ~Xep6Wallet() = default;
    
    /// Get extra data
    const nlohmann::json& getExtra() const { return extra_; }
    
    /// Set extra data
    void setExtra(const nlohmann::json& extra) { extra_ = extra; }
    
    /// Get tokens
    const std::vector<nlohmann::json>& getTokens() const { return tokens_; }
    
    /// Add a token
    void addToken(const nlohmann::json& token) { tokens_.push_back(token); }
    
    /// Save wallet to XEP-6 JSON format
    /// @param filepath The file path to save to
    /// @param password Optional password for encryption
    void save(const std::string& filepath, const std::string& password = "") const override;
    
    /// Convert wallet to XEP-6 JSON
    /// @return The XEP-6 JSON representation
    nlohmann::json toJson() const;
    
    /// Load wallet from XEP-6 JSON
    /// @param json The XEP-6 JSON
    /// @param password Optional password for decryption
    /// @return The loaded wallet
    static SharedPtr<Xep6Wallet> fromJson(const nlohmann::json& json, const std::string& password = "");
    
    /// Load wallet from file
    /// @param filepath The file path to load from
    /// @param password Optional password for decryption
    /// @return The loaded wallet
    static SharedPtr<Xep6Wallet> load(const std::string& filepath, const std::string& password = "");
};

} // namespace epicchaincpp