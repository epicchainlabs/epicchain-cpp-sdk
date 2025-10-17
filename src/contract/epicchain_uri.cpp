#include "epicchaincpp/contract/epicchain_uri.hpp"
#include "epicchaincpp/contract/epicchain_token.hpp"
#include "epicchaincpp/contract/epicpulse_token.hpp"
#include "epicchaincpp/epicchain_swift_error.hpp"
#include "epicchaincpp/exceptions.hpp"
#include <sstream>
#include <vector>

namespace epicchaincpp {

const std::string EpicChainURI::EPICCHAIN_SCHEME = "epicchain";
const std::string EpicChainURI::EPICCHAIN_TOKEN_STRING = "epicchain";
const std::string EpicChainURI::EPICPULSE_TOKEN_STRING = "epicpulse";

EpicChainURI::EpicChainURI() = default;

EpicChainURI::EpicChainURI(std::shared_ptr<EpicChainCpp> epicchainCpp) : epicchainCpp_(std::move(epicchaincpp)) {}

EpicChainURI EpicChainURI::fromURI(const std::string& uriString) {
    // Check minimum length and scheme
    if (uriString.length() < MIN_XEP9_URI_LENGTH || uriString.substr(0, 4) != "epicchain:") {
        throw ValidationError("The provided string does not conform to the XEP-9 standard.");
    }

    // Split into base and query parts
    size_t queryPos = uriString.find('?');
    std::string base = queryPos != std::string::npos ? uriString.substr(0, queryPos) : uriString;
    
    // Extract address
    std::string address = base.substr(4); // Skip "neo:"
    
    // Create URI with recipient
    EpicChainURI EpicChainURI;
    EpicChainURI.to(Hash160::fromAddress(address));
    
    // Process query parameters if present
    if (queryPos != std::string::npos) {
        std::string query = uriString.substr(queryPos + 1);
        std::vector<std::string> params;
        
        // Split query by &
        size_t start = 0;
        size_t end = query.find('&');
        while (end != std::string::npos) {
            params.push_back(query.substr(start, end - start));
            start = end + 1;
            end = query.find('&', start);
        }
        params.push_back(query.substr(start));
        
        // Process each parameter
        for (const auto& param : params) {
            size_t equalPos = param.find('=');
            if (equalPos == std::string::npos) {
                throw ValidationError("This URI contains invalid queries.");
            }
            
            std::string key = param.substr(0, equalPos);
            std::string value = param.substr(equalPos + 1);
            
            if (key == "asset" && !EpicChainURI.token_) {
                EpicChainURI.token(value);
            } else if (key == "amount" && !EpicChainURI.amount_) {
                try {
                    EpicChainURI.amount(std::stod(value));
                } catch (const std::exception&) {
                    // Ignore invalid amount
                }
            }
        }
    }
    
    return EpicChainURI;
}

EpicChainURI& EpicChainURI::to(const Hash160& recipient) {
    recipient_ = recipient;
    return *this;
}

EpicChainURI& EpicChainURI::token(const Hash160& token) {
    token_ = token;
    return *this;
}

EpicChainURI& EpicChainURI::token(const std::string& token) {
    if (token == EPICCHAIN_TOKEN_STRING) {
        token_ = EpicChainToken::SCRIPT_HASH;
    } else if (token == EPICPULSE_TOKEN_STRING) {
        token_ = EpicPulseToken::SCRIPT_HASH;
    } else {
        token_ = Hash160(token);
    }
    return *this;
}

EpicChainURI& EpicChainURI::amount(double amount) {
    amount_ = amount;
    return *this;
}

EpicChainURI& EpicChainURI::epichainCpp(std::shared_ptr<EpicChainCpp> epicchainCpp) {
    epicchainCpp_ = std::move(epicchaincpp);
    return *this;
}

EpicChainURI& EpicChainURI::buildURI() {
    if (!recipient_) {
        throw ValidationError("Could not create a XEP-9 URI without a recipient address.");
    }
    
    std::string base = EPICCHAIN_SCHEME + ":" + recipient_->toAddress();
    std::string query = buildQueryPart();
    
    uri_ = base + (query.empty() ? "" : "?" + query);
    return *this;
}

std::string EpicChainURI::getURIString() const {
    return uri_;
}

std::string EpicChainURI::getRecipientAddress() const {
    return recipient_ ? recipient_->toAddress() : "";
}

std::string EpicChainURI::getTokenString() const {
    if (!token_) {
        return "";
    }
    
    if (isEpicChainToken(*token_)) {
        return EPICCHAIN_TOKEN_STRING;
    } else if (isEpicPulseToken(*token_)) {
        return EPICPULSE_TOKEN_STRING;
    } else {
        return token_->toString();
    }
}

std::string EpicChainURI::getTokenAddress() const {
    return token_ ? token_->toAddress() : "";
}

std::string EpicChainURI::getAmountString() const {
    if (!amount_) {
        return "";
    }
    
    std::ostringstream ss;
    ss << *amount_;
    return ss.str();
}

std::shared_ptr<EpicChainCpp> EpicChainURI::getEpicChainCpp() const {
    return epicchainCpp_;
}

const std::optional<Hash160>& EpicChainURI::getRecipient() const {
    return recipient_;
}

const std::optional<Hash160>& EpicChainURI::getToken() const {
    return token_;
}

std::optional<double> EpicChainURI::getAmount() const {
    return amount_;
}

bool EpicChainURI::isEpicChainToken(const Hash160& token) const {
    return token == EpicChainToken::SCRIPT_HASH;
}

bool EpicChainURI::isEpicPulseToken(const Hash160& token) const {
    return token == EpicPulseToken::SCRIPT_HASH;
}

std::string EpicChainURI::buildQueryPart() const {
    std::vector<std::string> query;
    
    if (token_) {
        if (isEpicChainToken(*token_)) {
            query.push_back("asset=" + EPICCHAIN_TOKEN_STRING);
        } else if (isEpicPulseToken(*token_)) {
            query.push_back("asset=" + EPICPULSE_TOKEN_STRING);
        } else {
            query.push_back("asset=" + token_->toString());
        }
    }
    
    if (amount_) {
        std::ostringstream ss;
        ss << *amount_;
        query.push_back("amount=" + ss.str());
    }
    
    if (query.empty()) {
        return "";
    }
    
    std::string result = query[0];
    for (size_t i = 1; i < query.size(); i++) {
        result += "&" + query[i];
    }
    
    return result;
}

} // namespace epicchaincpp