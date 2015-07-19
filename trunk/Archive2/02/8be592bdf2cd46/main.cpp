#ifndef PSIL_GC_H
#define PSIL_GC_H

#include <algorithm>

namespace psil {
    // Base GC object.
    struct GCObject;

    // Reference types.
    struct GCRef; struct GCWeakRef; struct GCVisitRef;

    // Code deduplication without virtual pointers.
#define PSIL_REF_BODY(C)                                                      \
        C() : obj(nullptr) { }                                                \
        C(GCObject* obj) : obj(obj) { if (obj) ref(); }                       \
        C(const GCRef& other);                                                \
        C(const GCWeakRef& other);                                            \
        C(const GCVisitRef& other);                                           \
        C& operator=(const C& other) { reset(other.obj); return *this; }      \
        C(C&& other) : obj(other.obj) { other.reset(); if (obj) ref(); }      \
        ~C() { reset(); }                                                     \
                                                                              \
        void swap(C& other) {                                                 \
            std::swap(obj, other.obj);                                        \
            if (bool(obj) == bool(other.obj)) return;                         \
            if (obj) { ref(); other.unref(); } else { unref(); other.ref(); } \
        }                                                                     \
                                                                              \
        void reset() { if (obj) { unref(); obj = nullptr; } }                 \
        void reset(GCObject* obj) {                                           \
            if (this->obj && !obj) unref();                                   \
            if (!this->obj && obj) ref();                                     \
            this->obj = obj;                                                  \
        }                                                                     \
                                                                              \
        GCObject* get() const { return obj; }                                 \
        explicit operator bool() const { return obj != nullptr; }             \
        GCObject& operator*() const { return *obj; }                          \
        GCObject* operator->() const { return obj; }                          \
                                                                              \
    private:                                                                  \
        mutable GCObject* obj;                                                \
                                                                              \
        friend class GC;
    
    // Outside reference to GC owned object.
    struct GCRef {
        PSIL_REF_BODY(GCRef)
        std::uint32_t ref_id;
        void ref(); void unref();
    };

    // Outside weak reference to GC owned object.
    struct GCWeakRef {
        PSIL_REF_BODY(GCWeakRef)
        std::uint32_t ref_id;
        void ref(); void unref();
    };
    
    // Reference to use inside GC types. Tracked by calling visit().
    struct GCVisitRef {
        void visit(bool weak=false) const;
        PSIL_REF_BODY(GCVisitRef);
        void ref() { } void unref() { }
    };
#undef PSIL_REF_BODY
}



// Implementation.
namespace psil {
    // More code deduplication for the reference types.
#define PSIL_REF_EXTRAS(C)                                                      \
    inline C::C(const GCRef& other) : obj(other.get()) { if (obj) ref(); }      \
    inline C::C(const GCWeakRef& other) : obj(other.get()) { if (obj) ref(); }  \
    inline C::C(const GCVisitRef& other) : obj(other.get()) { if (obj) ref(); } \
    inline bool operator==(const C& lhs, const C& rhs)                          \
        { return lhs.get() == rhs.get(); }                                      \
    inline bool operator==(const C& lhs, std::nullptr_t rhs)                    \
        { return lhs.get() == nullptr; }                                        \
    inline bool operator==(std::nullptr_t lhs, const C& rhs)                    \
        { return nullptr == rhs.get(); }                                        \
    inline bool operator!=(const C& lhs, const C& rhs)                          \
        { return !(lhs == rhs); }                                               \
    inline bool operator!=(const C& lhs, std::nullptr_t rhs)                    \
        { return !(lhs == rhs); }                                               \
    inline bool operator!=(std::nullptr_t lhs, const C& rhs)                    \
        { return !(lhs == rhs); }                                         
    
    PSIL_REF_EXTRAS(GCRef)
    PSIL_REF_EXTRAS(GCWeakRef)
    PSIL_REF_EXTRAS(GCVisitRef)
#undef PSIL_REF_EXTRAS
}

#endif