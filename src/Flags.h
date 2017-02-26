#ifndef FLAGS_H_0099701e_0717_43a3_af27_83c111ea5574
#define FLAGS_H_0099701e_0717_43a3_af27_83c111ea5574

#include <type_traits>

template <typename T>
class Flags {
public:
    using Enum = T;
    using Storagetype = typename std::underlying_type<T>::type;

    Flags();
    Flags(T flag);
private:
};

#endif
