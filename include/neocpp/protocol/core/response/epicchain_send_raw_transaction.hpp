#pragma once

#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include "epicchaincpp/types/types.hpp"

namespace epicchaincpp {

/// NeoSendRawTransaction response type
class NeoSendRawTransaction {
private:
    nlohmann::json data_;
    
public:
    /// Constructor
    NeoSendRawTransaction() = default;
    
    /// Constructor from JSON
    explicit NeoSendRawTransaction(const nlohmann::json& json) : data_(json) {}
    
    /// Get raw JSON data
    const nlohmann::json& getRawJson() const { return data_; }
    
    /// Convert to JSON
    nlohmann::json toJson() const { return data_; }
    
    /// Create from JSON
    static SharedPtr<NeoSendRawTransaction> fromJson(const nlohmann::json& json) {
        return std::make_shared<NeoSendRawTransaction>(json);
    }
};

} // namespace epicchaincpp
