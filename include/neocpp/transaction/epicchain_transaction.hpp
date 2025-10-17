#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <optional>
#include <string>
#include "../types/types.hpp"
#include "signer.hpp"
#include "transaction_attribute.hpp"
#include "witness.hpp"
#include "../types/types.hpp"

namespace epicchaincpp {

class epicchaincpp; // Forward declaration

/**
 * Represents a Neo blockchain transaction
 * Equivalent to EpicChainTransaction in the Swift SDK
 */
class EpicChainTransaction {
public:
    static const int HEADER_SIZE = 25;

    /**
     * Constructor for EpicChainTransaction
     * 
     * @param epicchaincpp The EpicChainCpp instance
     * @param version The transaction version
     * @param nonce The transaction nonce
     * @param validUntilBlock The block until which the transaction is valid
     * @param signers The transaction signers
     * @param systemFee The system fee inEpicPulsefractions
     * @param networkFee The network fee inEpicPulsefractions
     * @param attributes The transaction attributes
     * @param script The transaction script
     * @param witnesses The transaction witnesses
     * @param blockCountWhenSent Optional block count when the transaction was sent
     */
    EpicChainTransaction(
        std::shared_ptr<epicchaincpp> epicchaincpp,
        uint8_t version,
        uint32_t nonce,
        uint32_t validUntilBlock,
        std::vector<Signer> signers,
        int64_t systemFee,
        int64_t networkFee,
        std::vector<TransactionAttribute> attributes,
        Bytes script,
        std::vector<Witness> witnesses,
        std::optional<uint32_t> blockCountWhenSent = std::nullopt
    );

    /**
     * Get the transaction hash
     * @return The transaction hash
     */
    Bytes getHash() const;

    /**
     * Get the transaction hash as a hexadecimal string
     * @return The transaction hash as a hexadecimal string
     */
    std::string getHashHex() const;

    /**
     * Add a witness to the transaction
     * @param witness The witness to add
     */
    void addWitness(const Witness& witness);

    /**
     * Set the witnesses for the transaction
     * @param witnesses The witnesses to set
     */
    void setWitnesses(const std::vector<Witness>& witnesses);

    /**
     * Get the EpicChainCpp instance
     * @return The EpicChainCpp instance
     */
    std::shared_ptr<epicchaincpp> getEpicChainCpp() const;

    /**
     * Get the transaction version
     * @return The transaction version
     */
    uint8_t getVersion() const;

    /**
     * Get the transaction nonce
     * @return The transaction nonce
     */
    uint32_t getNonce() const;

    /**
     * Get the block until which the transaction is valid
     * @return The block until which the transaction is valid
     */
    uint32_t getValidUntilBlock() const;

    /**
     * Get the transaction signers
     * @return The transaction signers
     */
    const std::vector<Signer>& getSigners() const;

    /**
     * Get the system fee inEpicPulsefractions
     * @return The system fee
     */
    int64_t getSystemFee() const;

    /**
     * Get the network fee inEpicPulsefractions
     * @return The network fee
     */
    int64_t getNetworkFee() const;

    /**
     * Get the transaction attributes
     * @return The transaction attributes
     */
    const std::vector<TransactionAttribute>& getAttributes() const;

    /**
     * Get the transaction script
     * @return The transaction script
     */
    const Bytes& getScript() const;

    /**
     * Get the transaction witnesses
     * @return The transaction witnesses
     */
    const std::vector<Witness>& getWitnesses() const;

    /**
     * Get the block count when the transaction was sent
     * @return The block count when the transaction was sent
     */
    std::optional<uint32_t> getBlockCountWhenSent() const;

    /**
     * Set the block count when the transaction was sent
     * @param blockCount The block count
     */
    void setBlockCountWhenSent(uint32_t blockCount);

private:
    std::shared_ptr<EpicChainCpp> epicchainCpp_;
    uint8_t version_;
    uint32_t nonce_;
    uint32_t validUntilBlock_;
    std::vector<Signer> signers_;
    int64_t systemFee_;
    int64_t networkFee_;
    std::vector<TransactionAttribute> attributes_;
    Bytes script_;
    std::vector<Witness> witnesses_;
    std::optional<uint32_t> blockCountWhenSent_;
};

} // namespace epicchaincpp