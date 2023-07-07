#ifndef AEB776EB_BAF2_447A_BF1E_FE3AC87DF2CC
#define AEB776EB_BAF2_447A_BF1E_FE3AC87DF2CC

#include <stdexcept>

namespace z1dg {
    class DungeonGenException : public std::runtime_error {
        public:
            DungeonGenException(char const *const message) noexcept: std::runtime_error(message) {}
    };
}

#endif /* AEB776EB_BAF2_447A_BF1E_FE3AC87DF2CC */
