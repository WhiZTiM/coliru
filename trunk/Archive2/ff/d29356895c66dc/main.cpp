#include <iostream>

namespace packet {

class TagAttributes {
public:
    // --- Type Definitions
    typedef int frame_size_type;
    typedef int alignment_type;

    TagAttributes(frame_size_type myLength, alignment_type myAlignment) :
                    length(myLength), alignment(myAlignment) {
        // --- nothing to do
    }

    /**
     * Default Constructor (for client convenience)
     */
    TagAttributes() :
                    length(0), alignment(0) {
        // --- nothing to do
    }

    ~TagAttributes() throw() {
        // --- nothing to do
    }

    const frame_size_type & GetLength() const throw() {
        return this->length;
    }

    const alignment_type & GetAlignment() const throw() {
        return this->alignment;
    }

    bool equals(const TagAttributes & other) const {
        return other.length == this->length && other.alignment == this->alignment;
    }

private:
    frame_size_type length;

    alignment_type alignment;

};

struct test {};
inline bool operator==(test const&, test const&) { return true; }
inline bool operator!=(test const&, test const&) { return false; }

} /* namespace packet */

inline bool operator==(const ::packet::TagAttributes & lhs, const ::packet::TagAttributes & rhs) {
    return lhs.equals(rhs);
}

inline bool operator!=(const ::packet::TagAttributes & lhs, const ::packet::TagAttributes & rhs) {
    return !lhs.equals(rhs);
}

int main() {
    packet::TagAttributes a;
    packet::TagAttributes b;
    std::cout << (a == b);
}
