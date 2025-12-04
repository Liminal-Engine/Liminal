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

namespace renderer {
    namespace __private {
        
        class __VertexBuffer::__Impl {
            private:
                const __GPU &__relatedGPU;
                const vk::DeviceSize __vkGPUSize;
                vk::raii::Buffer __vkBuffer;
                vk::raii::DeviceMemory __vkGPUMemory;
                void *__CPUBuffer;

                static vk::raii::Buffer __createVKBuffer(const __GPU &gpu, const vk::DeviceSize &relatedGPUSize) {
                    logger::trace << "Buffer creating VK buffer create info for GPU " << gpu.getName() << std::endl;

                    std::set<uint32_t> queueIndicesSet{gpu.getGraphicsQueue().getFamilyIndex(), gpu.getPresentQueue().getFamilyIndex()};
                    std::vector<uint32_t> queueIndicesVec(queueIndicesSet.begin(), queueIndicesSet.end());

                    vk::BufferCreateInfo createInfo{};
                    createInfo.setFlags({})
                    .setSize(relatedGPUSize)
                    .setUsage(vk::BufferUsageFlagBits::eVertexBuffer)
                    .setSharingMode(queueIndicesVec.size() == 1 ? vk::SharingMode::eExclusive : vk::SharingMode::eConcurrent)
                    .setQueueFamilyIndices(queueIndicesVec);

                    logger::trace << "Buffer creating VK buffer for GPU " << gpu.getName() << std::endl;
                    auto [result, rawBuffer] = gpu.getRawVKLogicalDevice().createBuffer(createInfo);
                    if (result != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(gpu, result, "Buffer failed to create VK buffer");
                        return vk::raii::Buffer(nullptr);
                    }
                    return vk::raii::Buffer(gpu.getVKLogicalDevice(), rawBuffer);
                }

                // FIXME: this auto allocate and auto bind, have a custom mem handling and maybe keep auto bind
                static vk::raii::DeviceMemory __createDeviceMemory(const __GPU &gpu, const vk::raii::Buffer &relatedBuffer) {
                    logger::trace << "Buffer creating GPU memory alloc info for GPU " << gpu.getName() << std::endl;
                    vk::MemoryRequirements memRequirements = relatedBuffer.getMemoryRequirements();
                    vk::MemoryAllocateInfo allocInfo{};
                    allocInfo.setAllocationSize(memRequirements.size)
                    .setMemoryTypeIndex(gpu.getMemoryType(memRequirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent));

                    // auto allocate
                    logger::trace << "Buffer allocatingVK Buffer GPU memory for GPU " << gpu.getName() << std::endl;
                    auto [result, rawDeviceMemory] = gpu.getRawVKLogicalDevice().allocateMemory(allocInfo);
                    if (result != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(gpu, result, "Buffer failed to allocate GPU memory");
                        return vk::raii::DeviceMemory(nullptr);
                    }
                    // auto bind as well
                    vk::raii::DeviceMemory deviceMemory(gpu.getVKLogicalDevice(), rawDeviceMemory);
                    if (gpu.getRawVKLogicalDevice().bindBufferMemory(*relatedBuffer, *deviceMemory, 0) != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(gpu, result, "Buffer failed to bind device memory to buffer");
                        return vk::raii::DeviceMemory(nullptr);
                    }
                    return deviceMemory;
                }

                static void *__createCPUBuffer(
                    const __GPU &gpu,
                    const vk::raii::DeviceMemory &relatedGPUMemory,
                    const vk::DeviceSize &relatedGPUSize,
                    const std::vector<VERTEX> &relatedVerticies
                ) {
                    // FIXME : this will write the memory (e.g., write it in the GPU, is it a good thing ?)                    
                    auto [result, cpuBuffer] = gpu.getRawVKLogicalDevice().mapMemory(*relatedGPUMemory, 0, relatedGPUSize);
                    if (result != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(gpu, result, "Buffer failed to map GPU memory");
                        return nullptr;                        
                    }
                    if (memcpy(cpuBuffer, relatedVerticies.data(), static_cast<size_t>(relatedGPUSize)) == NULL) {
                        logger::error << "Failed to copy verticies data do CPU pointer for GPU: " << gpu.getName() << std::endl;
                        return nullptr;
                    }
                    gpu.getRawVKLogicalDevice().unmapMemory(*relatedGPUMemory);
                    return cpuBuffer;
                }

            public:
                __Impl(const __GPU &gpu, const std::vector<VERTEX> &vertices) :
                __relatedGPU(gpu),
                __vkGPUSize(vk::DeviceSize(sizeof(vertices[0]) * vertices.size())),
                __vkBuffer(__createVKBuffer(this->__relatedGPU, this->__vkGPUSize)),
                __vkGPUMemory(__createDeviceMemory(this->__relatedGPU, this->__vkBuffer)),
                __CPUBuffer(__createCPUBuffer(this->__relatedGPU, this->__vkGPUMemory, this->__vkGPUSize, vertices))
                {
                }


                const vk::raii::Buffer &getVKBuffer(void) const { return this->__vkBuffer; }


        };

        __VertexBuffer::__VertexBuffer(const __GPU &gpu, const std::vector<VERTEX> &vertices) :
        __impl(std::make_unique<__Impl>(gpu, vertices))
        {}

        __VertexBuffer::~__VertexBuffer() = default;

        const vk::raii::Buffer &__VertexBuffer::getVKBuffer(void) const { return this->__impl->getVKBuffer(); }

    } // namespace __private
} // namespace renderer
