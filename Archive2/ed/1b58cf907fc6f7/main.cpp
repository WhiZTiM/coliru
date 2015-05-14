/*
 * PacketTagAttributes.hpp
 *
 *  Created on: Jul 1, 2013
 *      Author: bob
 *
 *  Last Changed on     : $Date: 2014-02-21 15:52:21 +0200 (Wed, 23 Apr 2014) $
 *  Last Changed Author : $Author: bob $
 *  File ID             : $Id: PacketTagAttributes.hpp 2434 2014-02-21 15:52:21Z bob $
 */
#ifndef _PACKET__TAG_ATTRIBUTES_HPP_
#define _PACKET__TAG_ATTRIBUTES_HPP_
#include "basetypes.h"

namespace packet {

class TagAttributes {
public:
    // --- Type Definitions
    typedef u_int32 frame_size_type;
    typedef u_int32 alignment_type;

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

} /* namespace packet */

inline bool operator==(const ::packet::TagAttributes & lhs, const ::packet::TagAttributes & rhs) {
    return lhs.equals(rhs);
}

inline bool operator!=(const ::packet::TagAttributes & lhs, const ::packet::TagAttributes & rhs) {
    return !lhs.equals(rhs);
}

#endif /* _PACKET__TAG_ATTRIBUTES_HPP_ */
