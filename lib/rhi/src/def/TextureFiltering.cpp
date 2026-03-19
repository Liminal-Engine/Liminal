#include "def/TextureFiltering.hpp"

namespace rhi {
    namespace def {
        std::string toStr(const TextureFiltering &filtering) noexcept {
            switch (filtering) {
                case TextureFiltering::NEAREST: return "NEAREST";
                case TextureFiltering::LINEAR: return "LINEAR";
            }
            return "UNKNOWN";
        }
    } // namespace def
} // namespace rhi
