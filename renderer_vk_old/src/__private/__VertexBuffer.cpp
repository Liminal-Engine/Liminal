/**
 * @file __VertexBuffer.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-12-03
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#include "__private/__vkConfig.hpp"
#include "__private/__errors.hpp"
#include "__private/__VertexBuffer.hpp"

#include <logger/logger.hpp>

#include <set>
#include <vector>

namespace renderer_vk_old {
    namespace __private {
        
        class __VertexBuffer::__Impl {
            private:
                const __GPU &__relatedGPU;
                const vk::raii::CommandPool &__relatedTransferCommandPool;
                const size_t __size;
                const std::set<uint32_t> __relatedQueueFamilies;
                // it's better in terms of performance to use a __buffer with device local bit, so we have a staging buffer whose content is copied in device local buffer
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
                    logger::trace << "VertexBuffer creating Buffer for GPU " << gpu.getName() << std::endl;
                    return __Buffer(gpu, size, bufferUsageFlags, memPropFlags, queueFamilyIndices, inputData);
                }

            public:
                __Impl(
                    const __GPU &gpu,
                    const std::vector<VERTEX> &vertices,
                    const vk::raii::CommandPool &transferCommandPool
                ) :
                __relatedGPU(gpu),
                __relatedTransferCommandPool(transferCommandPool),
                __size(sizeof(vertices[0]) * vertices.size()),
                __relatedQueueFamilies(std::set<uint32_t>{gpu.getPresentQueue().getFamilyIndex(), gpu.getGraphicsQueue().getFamilyIndex()}),
                __stagingBuffer(
                    __createBuffer(
                        gpu,
                        this->__size,
                        vk::BufferUsageFlagBits::eTransferSrc,
                        vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
                        this->__relatedQueueFamilies,
                        (void *)vertices.data()
                    )
                ),
                __buffer(
                    __createBuffer(
                        gpu,
                        this->__size,
                        vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer,
                        vk::MemoryPropertyFlagBits::eDeviceLocal,
                        this->__relatedQueueFamilies
                    )
                )
                {
                    logger::trace << "VertexBuffer copying VK staging buffer to VK buffer for GPU " << this->__relatedGPU.getName() << std::endl;
                    if (
                        __Status copyStatus;
                        (copyStatus = this->__buffer.copy(this->__stagingBuffer, this->__relatedTransferCommandPool)) != __Status::E_OK
                    ) {
                        logger::error << "VertexBuffer failed to copy VK staging buffer to VK buffer for GPU " << this->__relatedGPU.getName() << std::endl;
                    }
                }

                __Status mapToGPU(const void *inputData) { return this->__buffer.mapToGPU(inputData); }

                const vk::raii::Buffer &getVKBuffer(void) const { return this->__buffer.getVKBuffer(); }

                const __Buffer &getBuffer(void) const { return this->__buffer; }

                const bool &isMapped(void) const { return this->__buffer.isMapped(); }

        };

        __VertexBuffer::__VertexBuffer(
            const __GPU &gpu,
            const std::vector<VERTEX> &vertices,
            const vk::raii::CommandPool &transferCommandPool
        ) :
        __impl(std::make_unique<__Impl>(gpu, vertices, transferCommandPool))
        {}

        __VertexBuffer::~__VertexBuffer() = default;

        __Status __VertexBuffer::mapToGPU(const void *inputData) { return this->__impl->mapToGPU(inputData); }
        const vk::raii::Buffer &__VertexBuffer::getVKBuffer(void) const { return this->__impl->getVKBuffer(); }
        const __Buffer & __VertexBuffer::getBuffer(void) const { return this->__impl->getBuffer(); }
        const bool &__VertexBuffer::isMapped(void) const { return this->__impl->isMapped(); }

    } // namespace __private
} // namespace renderer_vk_old
