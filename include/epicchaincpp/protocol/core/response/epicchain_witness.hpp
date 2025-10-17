#pragma once

#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include "epicchaincpp/types/types.hpp"

namespace epicchaincpp {

/// NeoWitness response type
class NeoWitness {
private:
    nlohmann::json data_;
    
public:
    /// Constructor
    NeoWitness() = default;
    
    /// Constructor from JSON
    explicit NeoWitness(const nlohmann::json& json) : data_(json) {}
    
    /// Get raw JSON data
    const nlohmann::json& getRawJson() const { return data_; }
    
    /// Convert to JSON
    nlohmann::json toJson() const { return data_; }
    
    /// Create from JSON
    static SharedPtr<NeoWitness> fromJson(const nlohmann::json& json) {
        return std::make_shared<NeoWitness>(json);
    }
};

} // namespace epicchaincpp
