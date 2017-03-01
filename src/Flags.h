#ifndef FLAGS_H_0099701e_0717_43a3_af27_83c111ea5574
#define FLAGS_H_0099701e_0717_43a3_af27_83c111ea5574

#include <type_traits>
#include <initializer_list>

namespace flags {

template <typename T>
class Flags {
public:
    using Enum = T;
    using StorageType = typename std::underlying_type<T>::type;

    constexpr Flags() = default;
    constexpr Flags(T flag);
    constexpr Flags(std::initializer_list<T> flags);
    ~Flags() = default;

    constexpr Flags(const Flags& other) = default;
    constexpr Flags(Flags&& other) noexcept = default;
    constexpr Flags& operator =(const Flags& other) = default;
    constexpr Flags& operator =(Flags&& other) noexcept = default;

    constexpr bool operator ==(const Flags<T>& flags) const;
    constexpr bool operator !=(const Flags<T>& flags) const;
    constexpr bool operator ==(T flags) const;
    constexpr bool operator !=(T flags) const;

    constexpr Flags<T> operator |(const Flags<T>& rhs) const;
    constexpr Flags<T> operator &(const Flags<T>& rhs) const;
    constexpr Flags<T> operator ^(const Flags<T>& rhs) const;
    constexpr Flags<T> operator ~() const;

    constexpr Flags<T>& operator |=(const Flags<T>& rhs);
    constexpr Flags<T>& operator &=(const Flags<T>& rhs);
    constexpr Flags<T>& operator ^=(const Flags<T>& rhs);

    constexpr void set_flag(T flag);
    constexpr bool has_flag(T flag) const;
    constexpr void clear_flag(T flag);
    constexpr void toggle_flag(T flag);

    constexpr StorageType get_value() const;

    static constexpr Flags<T> from_value(StorageType value);
    static constexpr Flags<T> empty();
private:
    StorageType m_value = 0x0;    
};

template<typename T>
inline constexpr Flags<T>::Flags(T flag):
    m_value(static_cast<StorageType>(flag))
{
}
 
template<typename T>
inline constexpr Flags<T>::Flags(std::initializer_list<T> flags) {
    for(auto& f : flags) {
        set_flag(f);
    } 
}
 
template<typename T>
inline constexpr bool Flags<T>::operator==(const Flags<T>& flags) const {
    return m_value == flags.m_value;
}
 
template<typename T>
inline constexpr bool Flags<T>::operator!=(const Flags<T>& flags) const {
    return !(*this == flags); 
}
 
template<typename T>
inline constexpr bool Flags<T>::operator==(T flags) const {
    return m_value == static_cast<StorageType>(flags); 
}
 
template<typename T>
inline constexpr bool Flags<T>::operator!=(T flags) const {
    return !(*this == flags);
 
}
 
template<typename T>
inline constexpr Flags<T> Flags<T>::operator|(const Flags<T>& rhs) const {
    return Flags::from_value(m_value | rhs.m_value); 
}
 
template<typename T>
inline constexpr Flags<T> Flags<T>::operator&(const Flags<T>& rhs) const {
    return Flags::from_value(m_value & rhs.m_value); 
}

template<typename T>
inline constexpr Flags<T> Flags<T>::operator^(const Flags<T>& rhs) const {
    return Flags::from_value(m_value ^ rhs.m_value); 
}
 
template<typename T>
inline constexpr Flags<T> Flags<T>::operator~() const {
    return Flags::from_value(~m_value); 
}
 
template<typename T>
inline constexpr Flags<T>& Flags<T>::operator|=(const Flags<T>& rhs) {
    m_value |= rhs.m_value;
    return *this; 
}
 
template<typename T>
inline constexpr Flags<T>& Flags<T>::operator&=(const Flags<T>& rhs) {
    m_value &= rhs.m_value;
    return *this; 
}
 
template<typename T>
inline constexpr Flags<T>& Flags<T>::operator^=(const Flags<T>& rhs) {
    m_value ^= rhs.m_value;
    return *this; 
}
 
template<typename T>
inline constexpr void Flags<T>::set_flag(T flag) {
    m_value |= static_cast<StorageType>(flag);
}

template<typename T>
inline constexpr bool Flags<T>::has_flag(T flag) const {
    return (m_value & static_cast<StorageType>(flag)) != 0;
}
 
template<typename T>
inline constexpr void Flags<T>::clear_flag(T flag) {
    m_value &= ~static_cast<StorageType>(flag); 
}
 
template<typename T>
inline constexpr void Flags<T>::toggle_flag(T flag) {
    m_value ^= static_cast<StorageType>(flag); 
}
 
template<typename T>
inline constexpr typename Flags<T>::StorageType Flags<T>::get_value() const {
    return m_value;
}
 
template<typename T>
inline constexpr Flags<T> Flags<T>::from_value(Flags::StorageType value) {
    auto val = Flags<T>();
    val.m_value = value;
    return val;
}
 
template<typename T>
inline constexpr Flags<T> Flags<T>::empty() {
    return Flags<T>(); 
}
 
}

#endif
