/**
 * @file __IndexBuffer.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2026-02-24
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#include "__private/__IndexBuffer.hpp"

#include <logger/logger.hpp>

namespace renderer {
    namespace __private {
        class __IndexBuffer::__Impl {            
            private:
                const __GPU &__relatedGPU;
                const vk::raii::CommandPool &__relatedTransferCommandPool;
                const size_t __size;
                const std::set<uint32_t> __relatedQueueFamilies;

                __Buffer __stagingBuffer;
                __Buffer __buffer;

                static __Buffer __createBuffer(
                    const __GPU &gpu,
                    const size_t &size,
                    const vk::BufferUsageFlags &bufferUsageFlags,
                    const vk::MemoryPropertyFlags &memPropFlags,
                    const std::set<uint32_t> &queueFamilyIndices,
                    const void *inputData = nullptr
                ) {
                    logger::trace << "IndexBuffer creating Buffer for GPU " << gpu.getName() << std::endl;
                    return __Buffer(gpu, size, bufferUsageFlags, memPropFlags, queueFamilyIndices, inputData);
                }

            public:
                __Impl(
                    const __GPU &gpu,
                    const std::vector<uint16_t> &indices,
                    const vk::raii::CommandPool &transferCommandPool

                ) :
                __relatedGPU(gpu),
                __relatedTransferCommandPool(transferCommandPool),
                __size(sizeof(indices[0]) * indices.size()),
                __relatedQueueFamilies(std::set<uint32_t>{gpu.getPresentQueue().getFamilyIndex(), gpu.getGraphicsQueue().getFamilyIndex()}),
                __stagingBuffer(
                    __createBuffer(
                        gpu,
                        this->__size,
                        vk::BufferUsageFlagBits::eTransferSrc,
                        vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
                        this->__relatedQueueFamilies,
                        (void *)indices.data()
                    )
                ),
                __buffer(
                    __createBuffer(
                        gpu,
                        this->__size,
                        vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eIndexBuffer,
                        vk::MemoryPropertyFlagBits::eDeviceLocal,
                        this->__relatedQueueFamilies
                    )
                )
                {
                    logger::trace << "IndexBuffer copying VK staging buffer to VK buffer for GPU " << this->__relatedGPU.getName() << std::endl;
                    if (
                        __Status copyStatus;
                        (copyStatus = this->__buffer.copy(this->__stagingBuffer, this->__relatedTransferCommandPool)) != __Status::E_OK
                    ) {
                        logger::error << "IndexBuffer failed to copy VK staging buffer to VK buffer for GPU " << this->__relatedGPU.getName() << std::endl;
                    }
                }

                __Status mapToGPU(const void *inputData) { return this->__buffer.mapToGPU(inputData); }

                const vk::raii::Buffer &getVKBuffer(void) const { return this->__buffer.getVKBuffer(); }

                const __Buffer &getBuffer(void) const { return this->__buffer; }

                const bool &isMapped(void) const { return this->__buffer.isMapped(); }
        };


        __IndexBuffer::__IndexBuffer(
            const __GPU &gpu,
            const std::vector<uint16_t> &indices,
            const vk::raii::CommandPool &transferCommandPool
        ) :
        __impl(std::make_unique<__Impl>(gpu, indices, transferCommandPool))
        {}

        __IndexBuffer::~__IndexBuffer() = default;

        __Status __IndexBuffer::mapToGPU(const void *inputData) { return this->__impl->mapToGPU(inputData); }
        const vk::raii::Buffer &__IndexBuffer::getVKBuffer(void) const { return this->__impl->getVKBuffer(); }
        const __Buffer & __IndexBuffer::getBuffer(void) const { return this->__impl->getBuffer(); }
        const bool &__IndexBuffer::isMapped(void) const { return this->__impl->isMapped(); }
    } // namespace __private 
} // namespace renderer 