#include "def/TextureWrapping.hpp"

namespace rhi {
    namespace def {
        std::string toStr(const TextureWrapping &wrapping) noexcept {
            switch (wrapping) {
                case TextureWrapping::REPEAT: return "REPEAT";
                case TextureWrapping::MIRRORED_REPEAT: return "MIRRORED_REPEAT";
                case TextureWrapping::CLAMP_TO_EDGE: return "CLAMP_TO_EDGE";
                case TextureWrapping::CLAMP_TO_BORDER: return "CLAMP_TO_BORDER";
            }
            return "UNKNOWN";
        }
    } // namespace def
} // namespace rhi
