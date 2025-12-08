/**
 * @file __Buffer.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-12-04
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#include "__private/__vkConfig.hpp"
#include "__private/__errors.hpp"
#include "__private/__Buffer.hpp"

#include <logger/logger.hpp>

namespace renderer {
    namespace __private {

        class __Buffer::__Impl {
            private:
                const __GPU &__relatedGPU;
                const vk::DeviceSize __vkSize;
                vk::raii::Buffer __vkBuffer;
                vk::raii::DeviceMemory __vkMemory;
                void *__data;
                bool __isMapped;

                static vk::raii::Buffer __createVKBuffer(
                    const __GPU &gpu,
                    const vk::DeviceSize &deviceSize,
                    const vk::BufferUsageFlags &usageFlags,
                    const std::set<uint32_t> &queueFamilyIndices
                ) {
                    logger::trace << "Buffer transforming given queue family indices to VK compatible data for GPU " << gpu.getName() << std::endl;
                    if (queueFamilyIndices.empty()) {
                        logger::error << "No queues given for buffer creation for GPU "  << gpu.getName() << std::endl;
                        return vk::raii::Buffer(nullptr);
                    }
                    std::vector<uint32_t> queueFamilyIndicesVec(queueFamilyIndices.begin(), queueFamilyIndices.end());
                    
                    logger::trace << "Buffer creating VK buffer create info for GPU " << gpu.getName() << std::endl;
                    vk::BufferCreateInfo createInfo{};
                    createInfo.setFlags({})
                    .setSize(deviceSize)
                    .setUsage(usageFlags)
                    .setSharingMode(queueFamilyIndicesVec.size() == 1 ? vk::SharingMode::eExclusive : vk::SharingMode::eConcurrent)
                    .setQueueFamilyIndices(queueFamilyIndicesVec);

                    logger::trace << "Buffer creating VK buffer for GPU " << gpu.getName() << std::endl;
                    auto [result, rawBuffer] = gpu.getRawVKLogicalDevice().createBuffer(createInfo);
                    if (result != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(gpu, result, "Buffer failed to create VK buffer");
                        return vk::raii::Buffer(nullptr);
                    }
                    return vk::raii::Buffer(gpu.getVKLogicalDevice(), rawBuffer);
                }

                static vk::raii::DeviceMemory __createVKMemory(
                    const __GPU &gpu,
                    const vk::raii::Buffer &buffer,
                    const vk::MemoryPropertyFlags &memPropsFlags
                ) {
                    logger::trace << "Buffer creating GPU memory alloc info for GPU " << gpu.getName() << std::endl;
                    vk::MemoryRequirements bufferMemRequirements(buffer.getMemoryRequirements());
                    vk::MemoryAllocateInfo allocInfo{};
                    allocInfo.setAllocationSize(bufferMemRequirements.size)
                    .setMemoryTypeIndex(gpu.getMemoryType(bufferMemRequirements.memoryTypeBits, memPropsFlags));

                    logger::trace << "Buffer allocating VK buffer for GPU " << gpu.getName() << std::endl;
                    auto [allocResult, rawDeviceMemory] = gpu.getRawVKLogicalDevice().allocateMemory(allocInfo);
                    if (allocResult != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(gpu, allocResult, "Buffer failed to allocate GPU memory");
                        return vk::raii::DeviceMemory(nullptr);
                    }
                    vk::raii::DeviceMemory res(gpu.getVKLogicalDevice(), rawDeviceMemory);

                    logger::trace << "Buffer binding memory for GPU " << gpu.getName() << std::endl;
                    if (vk::Result bindResult; (bindResult = gpu.getRawVKLogicalDevice().bindBufferMemory(*buffer, *res, 0)) != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(gpu, bindResult, "Buffer failed to bind buffer to it's memory");
                        return vk::raii::DeviceMemory(nullptr);
                    }
                    return res;
                }

            public:

                __Impl(
                    const __GPU &gpu,
                    const size_t &size,
                    const vk::BufferUsageFlags &usageFlags,
                    const vk::MemoryPropertyFlags &memPropsFlags,
                    const std::set<uint32_t> &queueFamilyIndices,
                    const void *inputData = nullptr
                ) :
                __relatedGPU(gpu),
                __vkSize(size),
                __vkBuffer(__createVKBuffer(this->__relatedGPU, this->__vkSize, usageFlags, queueFamilyIndices)),
                __vkMemory(__createVKMemory(this->__relatedGPU, this->__vkBuffer, memPropsFlags)),
                __data([&]() -> void * {
                    logger::trace << "Buffer creating CPU data for GPU " <<  this->__relatedGPU.getName() << std::endl;
                    if (inputData == nullptr) return nullptr;

                    if (this->mapToGPU(inputData) != __Status::E_OK) {
                        logger::error << "Buffer failed to create input data for GPU " << this->__relatedGPU.getName() << std::endl;
                    }
                    return this->__data;
                }()),
                __isMapped(this->__data != nullptr)
                {}

                const vk::DeviceSize &getSize(void) const { return this->__vkSize; }
                const vk::raii::Buffer &getVKBuffer(void) const { return this->__vkBuffer; }
                const vk::raii::DeviceMemory &getVKMemory(void) const { return this->__vkMemory; }

                __Status mapToGPU(const void *inputData) {
                    logger::trace << "Buffer checking input data value for GPU " << this->__relatedGPU.getName() << std::endl;
                    if (inputData == nullptr) {
                        logger::error << "Input data is null, cannot map data for GPU " << this->__relatedGPU.getName() << std::endl;
                        return __Status::E_PTR_NULL;
                    }

                    logger::trace << "Buffer mapping GPU memory to CPU memory for GPU " << this->__relatedGPU.getName() << std::endl;
                    auto [result, gpuPtr] = this->__relatedGPU.getRawVKLogicalDevice().mapMemory(*this->__vkMemory, 0, this->__vkSize);
                    if (result != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(this->__relatedGPU, result, "Buffer failed to map GPU data");
                        return __Status::E_BUFFER_MAPPING;
                    }
                    logger::trace << "Copying data to CPU memory for GPU " << this->__relatedGPU.getName() << std::endl;
                    memcpy(gpuPtr, inputData, (size_t)this->__vkSize); // C doc specify that memcpy never fail and never return NULL (will have undefined behavior if somethiing went wrong)
                    logger::trace << "Copying data to GPU memory for GPU " << this->__relatedGPU.getName() << std::endl;
                    this->__relatedGPU.getRawVKLogicalDevice().unmapMemory(*this->__vkMemory);
                    this->__data = gpuPtr;
                    this->__isMapped = true;
                    return __Status::E_OK;
                }

                const void *getData(void) const { return this->__data; }
                const bool &isMapped(void) const { return this->__isMapped; }

                
                __Status copy(
                    const __Buffer &other,
                    const vk::raii::CommandPool &transferCommandPool
                ) {
                    // 1. Create command buffer
                    vk::CommandBufferAllocateInfo allocInfo{};
                    allocInfo.setCommandPool(*transferCommandPool)
                    .setCommandBufferCount(1);
                    const auto [commandBufferAllocResult, rawCommandBuffers] = this->__relatedGPU.getRawVKLogicalDevice().allocateCommandBuffers(allocInfo);
                    if (commandBufferAllocResult != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(this->__relatedGPU, commandBufferAllocResult, "VertexBuffer failed to allocate copy command buffer");
                        return __Status::E_ALLOC_BUFFER;
                    }
                    vk::raii::CommandBuffer commandBuffer(this->__relatedGPU.getVKLogicalDevice(), rawCommandBuffers[0], *transferCommandPool);
                    // 2. record command buffer
                    vk::CommandBufferBeginInfo beginInfo{};
                    beginInfo.setFlags(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
                    commandBuffer.begin(beginInfo); // returns void
                    vk::BufferCopy bufferCopy{};
                    bufferCopy.setSize(this->__vkSize);
                    commandBuffer.copyBuffer(*other.getVKBuffer(), *this->__vkBuffer, bufferCopy);
                    commandBuffer.end();
                    // 3. Start command buffer
                    vk::SubmitInfo submitInfo{};
                    submitInfo.setCommandBufferCount(1)
                    .setCommandBuffers(*commandBuffer);
                    this->__relatedGPU.getTransferQueue().getVKQueue().submit(submitInfo);
                    this->__relatedGPU.getTransferQueue().getVKQueue().waitIdle();
                    this->__isMapped = true;
                    this->__data = const_cast<void *>(other.getData());
                    return __Status::E_OK;
                }
        };

        __Buffer::__Buffer(
            const __GPU &gpu,
            const size_t &size,
            const vk::BufferUsageFlags &usageFlags,
            const vk::MemoryPropertyFlags &memPropsFlags,
            const std::set<uint32_t> &queueFamilyIndices,
            const void *inputData
        ) :
        __impl(std::make_unique<__Impl>(gpu, size, usageFlags, memPropsFlags, queueFamilyIndices, inputData))
        {}
        __Buffer::~__Buffer() = default;

        const vk::DeviceSize &__Buffer::getSize(void) const { return this->__impl->getSize(); }
        const vk::raii::Buffer &__Buffer::getVKBuffer(void) const { return this->__impl->getVKBuffer(); }
        const vk::raii::DeviceMemory &__Buffer::getVKMemory(void) const { return this->__impl->getVKMemory(); }
        __Status __Buffer::mapToGPU(const void *data) { return this->__impl->mapToGPU(data); }
        const void *__Buffer::getData(void) const { return this->__impl->getData(); }
        const bool &__Buffer::isMapped(void) const { return this->__impl->isMapped(); }
        
        __Status __Buffer::copy(const __Buffer &other, const vk::raii::CommandPool &transferCommandPool) { return this->__impl->copy(other, transferCommandPool); }

    } // namespace __private
} // namespace renderer
