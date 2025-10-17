#pragma once

#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include "epicchaincpp/types/types.hpp"

namespace epicchaincpp {

/// NameState response type
class NameState {
private:
    nlohmann::json data_;
    
public:
    /// Constructor
    NameState() = default;
    
    /// Constructor from JSON
    explicit NameState(const nlohmann::json& json) : data_(json) {}
    
    /// Get raw JSON data
    const nlohmann::json& getRawJson() const { return data_; }
    
    /// Convert to JSON
    nlohmann::json toJson() const { return data_; }
    
    /// Create from JSON
    static SharedPtr<NameState> fromJson(const nlohmann::json& json) {
        return std::make_shared<NameState>(json);
    }
};

} // namespace epicchaincpp
