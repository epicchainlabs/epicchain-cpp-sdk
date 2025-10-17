#include "epicchaincpp/transaction/epicchain_transaction.hpp"
#include "epicchaincpp/crypto/hash.hpp"
#include "epicchaincpp/utils/hex.hpp"
#include "epicchaincpp/serialization/binary_writer.hpp"
#include "epicchaincpp/serialization/binary_reader.hpp"
#include <algorithm>

namespace epicchaincpp {

EpicChainTransaction::EpicChainTransaction(
    std::shared_ptr<EpicChainCpp> epicchainCpp,
    uint8_t version,
    uint32_t nonce,
    uint32_t validUntilBlock,
    std::vector<Signer> signers,
    int64_t systemFee,
    int64_t networkFee,
    std::vector<TransactionAttribute> attributes,
    Bytes script,
    std::vector<Witness> witnesses,
    std::optional<uint32_t> blockCountWhenSent
) : epicchainCpp_(epicchaincpp),
    version_(version),
    nonce_(nonce),
    validUntilBlock_(validUntilBlock),
    signers_(std::move(signers)),
    systemFee_(systemFee),
    networkFee_(networkFee),
    attributes_(std::move(attributes)),
    script_(std::move(script)),
    witnesses_(std::move(witnesses)),
    blockCountWhenSent_(blockCountWhenSent) {
}

Bytes EpicChainTransaction::getHash() const {
    // Proper implementation following EpicChain protocol
    // Transaction hash is SHA256 of the transaction without witnesses, reversed
    Bytes serialized = serializeWithoutWitnesses();
    Bytes hash = Hash::sha256(serialized);
    // Reverse the hash bytes for EpicChain format
    std::reverse(hash.begin(), hash.end());
    return hash;
}

Bytes EpicChainTransaction::serializeWithoutWitnesses() const {
    BinaryWriter writer;
    
    // Write version byte
    writer.writeByte(version_);
    
    // Write nonce as UInt32
    writer.writeUInt32(nonce_);
    
    // Write system fee as Int64
    writer.writeInt64(systemFee_);
    
    // Write network fee as Int64
    writer.writeInt64(networkFee_);
    
    // Write valid until block as UInt32
    writer.writeUInt32(validUntilBlock_);
    
    // Write signers as variable length array
    writer.writeVarInt(signers_.size());
    for (const auto& signer : signers_) {
        signer.serialize(writer);
    }
    
    // Write attributes as variable length array
    writer.writeVarInt(attributes_.size());
    for (const auto& attribute : attributes_) {
        attribute.serialize(writer);
    }
    
    // Write script as variable length bytes
    writer.writeVarBytes(script_);
    
    return writer.toArray();
}

Bytes EpicChainTransaction::serialize() const {
    BinaryWriter writer;
    
    // First serialize everything except witnesses
    Bytes withoutWitnesses = serializeWithoutWitnesses();
    writer.writeBytes(withoutWitnesses);
    
    // Then add witnesses
    writer.writeVarInt(witnesses_.size());
    for (const auto& witness : witnesses_) {
        witness.serialize(writer);
    }
    
    return writer.toArray();
}

std::string EpicChainTransaction::getHashHex() const {
    return Hex::encode(getHash());
}

void EpicChainTransaction::addWitness(const Witness& witness) {
    witnesses_.push_back(witness);
}

void EpicChainTransaction::setWitnesses(const std::vector<Witness>& witnesses) {
    witnesses_ = witnesses;
}

std::shared_ptr<epicchaincpp> EpicChainTransaction::getepicchaincpp() const {
    return epicchainCpp_;
}

uint8_t EpicChainTransaction::getVersion() const {
    return version_;
}

uint32_t EpicChainTransaction::getNonce() const {
    return nonce_;
}

uint32_t EpicChainTransaction::getValidUntilBlock() const {
    return validUntilBlock_;
}

const std::vector<Signer>& EpicChainTransaction::getSigners() const {
    return signers_;
}

int64_t EpicChainTransaction::getSystemFee() const {
    return systemFee_;
}

int64_t EpicChainTransaction::getNetworkFee() const {
    return networkFee_;
}

const std::vector<TransactionAttribute>& EpicChainTransaction::getAttributes() const {
    return attributes_;
}

const Bytes& EpicChainTransaction::getScript() const {
    return script_;
}

const std::vector<Witness>& EpicChainTransaction::getWitnesses() const {
    return witnesses_;
}

std::optional<uint32_t> EpicChainTransaction::getBlockCountWhenSent() const {
    return blockCountWhenSent_;
}

void EpicChainTransaction::setBlockCountWhenSent(uint32_t blockCount) {
    blockCountWhenSent_ = blockCount;
}

} // namespace epicchaincpp