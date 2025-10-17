#include "epicchaincpp/serialization/neo_serializable.hpp"
#include "epicchaincpp/serialization/binary_writer.hpp"

namespace epicchaincpp {

Bytes NeoSerializable::toArray() const {
    BinaryWriter writer;
    serialize(writer);
    return writer.toArray();
}

} // namespace epicchaincpp