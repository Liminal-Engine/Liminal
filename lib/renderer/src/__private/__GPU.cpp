/**
 * @file __GPU.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-07
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#include "__private/__vkConfig.hpp"
#include "__private/__GPU.hpp"
#include "__private/__Context.hpp"
#include "__private/__errors.hpp"
#include "temp_consts_need_to_remove_this.hpp"

#include <logger/logger.hpp>
#include <parseop/parseop.hpp>

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>

namespace renderer {
    namespace __private {
        class __GPU::__Impl {
            private:
                std::string __name;
                const vk::raii::PhysicalDevice __vkGPU;
                vk::PhysicalDeviceProperties __properties;
                vk::PhysicalDeviceFeatures __features;
                std::vector<std::string> __extensionNames;
                vk::SurfaceCapabilitiesKHR __surfaceCapabilities;
                __SurfaceSupport __surfaceSupport;
                std::vector<vk::QueueFamilyProperties> __availableQueueFamilies;
                // std::unordered_map<std::string, __Queue> __queues;
                std::set<uint32_t> __queueIndices;
                vk::raii::Device __logicalDevice;
                __Queue __graphicsQueue;
                __Queue __presentQueue;
                __Queue __transferQueue;
                bool __created;

                static std::vector<__GPU> __getSuitableOnlyGPUs(std::vector<__GPU> &&availableGPUs, const vk::raii::SurfaceKHR &VKSurface) {
                    std::vector<__GPU> suitableGPUs;
                    for (__GPU &availableGPU : availableGPUs) {
                        // 1. Checking extensions
                        if ( !parseop::containsAll(availableGPU.getExtensionNames(), REQUIRED_DEVICE_EXTENSION_NAMES)) {
                            logger::warn << "GPU " << availableGPU.getName() << " does not have the required device extensions"
                            << " available device extensions for this device are:\n"
                            << parseop::prettify(availableGPU.getExtensionNames()) << std::endl;
                            continue;
                        }
                        // 2. SwapChain adequation
                        if (availableGPU.getSurfaceSupport().getFormats().empty()) {
                            logger::warn << "GPU " << availableGPU.getName() << " does not have any surface format available." << std::endl;
                            continue;
                        }
                        if (availableGPU.getSurfaceSupport().getPresentModes().empty()) {
                            logger::warn << "GPU " << availableGPU.getName() << " does not have any surface present mode available" << std::endl;
                            continue;
                        }
                        // 3. Check for graphics family
                        if (availableGPU.getAvailableQueueFamilyIndicesSupportingFlags(vk::QueueFlagBits::eGraphics, vk::QueueFlagBits{}).empty()) {
                            logger::warn << "GPU " << availableGPU.getName() << " does not have any queue family suppporting GRAPHICS" << std::endl;
                            continue;
                        }
                        // 4. Check for present support
                        if (availableGPU.getAvailableQueueFamilyIndicesSupportingSurface(VKSurface).empty()) {
                            logger::warn << "GPU " << availableGPU.getName() << " does not have any queue family supporting the given surface" << std::endl;
                            continue;
                        }
                        suitableGPUs.push_back(std::move(availableGPU));
                    }
                    if (suitableGPUs.empty()) logger::fatal << "No suitable GPU was found" << std::endl;
                    else {
                        logger::info << "Found the following suitable GPUs:\n";
                        for (const __GPU &suitableGPU : suitableGPUs) logger::info << "- " << suitableGPU.getName() << '\n';
                        logger::info << std::endl;
                    }
                    return suitableGPUs;
                }

                static std::string __queuFamiliesToString(const std::vector<vk::QueueFamilyProperties> &queueFamilies) {
                    std::stringstream ss;
                    for (size_t i = 0; i < queueFamilies.size(); i++) {
                        ss << "Queue family " << i << ":\n";
                        ss << "\t- Flags:\n";
                        if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics) ss << "\t\t- GRAPHICS\n";
                        if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eCompute)  ss << "\t\t- COMPUTE\n";
                        if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eTransfer) ss << "\t\t- TRANSFER\n";
                        if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eSparseBinding) ss << "\t\t- SPARSE_BINDING\n";
                        if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eProtected) ss << "\t\t- PROTECTED\n";
                        if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eOpticalFlowNV) ss << "\t\t- OPTICAL FLOW NV\n";
                        if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eVideoDecodeKHR) ss << "\t\t- VIDEO DECODE\n";
                        if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eVideoEncodeKHR) ss << "\t\t- VIDEO ENCODE\n";
                        ss << "\t- Count: " << queueFamilies[i].queueCount << '\n';
                        ss << "\t- Timestamp valid bits: " << queueFamilies[i].timestampValidBits << '\n';
                        ss << "\t- Minimum image transfer granularity:\n";
                        ss << "\t\t- Width: " << queueFamilies[i].minImageTransferGranularity.width << '\n';
                        ss << "\t\t- Height: " << queueFamilies[i].minImageTransferGranularity.height << '\n';
                        ss << "\t\t- Depth: " << queueFamilies[i].minImageTransferGranularity.depth << '\n';
                    }
                    return ss.str();
                }


            public:
                __Impl(const vk::raii::PhysicalDevice &vkGPU, const vk::raii::SurfaceKHR &surface) :
                __name([&]() {
                    std::string res(vkGPU.getProperties().deviceName);
                    logger::trace << "Found GPU: " <<  res << std::endl;
                    return res;
                }()),
                __vkGPU([&]() {
                    logger::trace << "\tLoading Vulkan object for GPU " << this->__name << std::endl;                
                    return vkGPU;
                }()),
                __properties([&](){
                    vk::PhysicalDeviceProperties res(this->__vkGPU.getProperties());
                    std::stringstream ss;
                    ss << "\tLoading properties for GPU " << this->__name << '\n'
                    << "- Vendor ID: 0x" << std::hex << res.vendorID << std::dec << '\n'
                    << "- Device ID: 0x" << std::hex << res.deviceID << std::dec << '\n'
                    << "- Device Type: " << vk::to_string(res.deviceType) << '\n'
                    << "- Driver Version: " << res.driverVersion;
                    logger::trace << ss.str() << std::endl;
                    return res;
                }()),
                __features([&]() {
                    logger::trace << "\tLoading features for GPU " << this->__name << std::endl;
                    return this->__vkGPU.getFeatures();
                }()),
                __extensionNames([&]() {
                    logger::trace << "\tLoading extension names for GPU" << this->__name << std::endl;
                    std::vector<vk::ExtensionProperties> vkGPUExtensions(this->__vkGPU.enumerateDeviceExtensionProperties());
                    std::vector<std::string> res;
                    res.reserve(vkGPUExtensions.size());
                    std::transform(
                        vkGPUExtensions.begin(),
                        vkGPUExtensions.end(),
                        std::back_inserter(res),
                        [](const vk::ExtensionProperties &vkGPUExtension) { return std::string(vkGPUExtension.extensionName); }
                    );
                    return res;
                }()),
                __surfaceSupport([&]() {
                    logger::trace << "\tLoading surface support for GPU " << this->__name << std::endl;
                    return __SurfaceSupport(this->__vkGPU, surface);
                }()),
                __availableQueueFamilies([&]() {
                    logger::trace << "\tLoading queue family properties for GPU " << this->__name << std::endl;
                    return this->__vkGPU.getQueueFamilyProperties();
                }()),
                __logicalDevice(nullptr),
                __created(false)
                {
                }

                ~__Impl() = default;

                static std::vector<__GPU> listAvailableGPUs(
                    const vk::raii::Instance &VKInstance,
                    const vk::raii::SurfaceKHR &VKSurface,
                    const bool &suitableOnly
                ) {
                    logger::trace << "Loading available GPUs" << std::endl;
                    auto [result, rawPhysicalDevices] = (*VKInstance).enumeratePhysicalDevices();
                    if (result != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(result, "GPU failed to enumerate available physical devices");
                        return std::vector<__GPU>{};
                    }
                    std::vector<__GPU> availableGPUs;
                    availableGPUs.reserve(rawPhysicalDevices.size());
                    std::transform(
                        rawPhysicalDevices.begin(),
                        rawPhysicalDevices.end(),
                        std::back_inserter(availableGPUs),
                        [&](const vk::PhysicalDevice &rawPhysicalDevice) -> __GPU { return __GPU(vk::raii::PhysicalDevice(VKInstance, rawPhysicalDevice), VKSurface); }
                    );
                    return suitableOnly ? __getSuitableOnlyGPUs(std::move(availableGPUs), VKSurface) : std::move(availableGPUs);
                }

                std::vector<uint32_t> getAvailableQueueFamilyIndicesSupportingFlags(
                    const vk::QueueFlags &requiredFlags,
                    const vk::QueueFlags &excludedFlags
                ) const {
                    std::vector<uint32_t> res;

                    for (uint32_t i = 0; i < this->__availableQueueFamilies.size(); i++) {
                        if (
                            (this->__availableQueueFamilies[i].queueFlags & requiredFlags) == requiredFlags &&
                            (this->__availableQueueFamilies[i].queueFlags & excludedFlags) == vk::QueueFlags{}
                        ) {
                            res.push_back(i);
                        }
                    }
                    return res;
                }

                std::vector<uint32_t> getAvailableQueueFamilyIndicesSupportingSurface(const vk::raii::SurfaceKHR &VKSurface) const {
                    std::vector<uint32_t> res;
                    for (uint32_t i = 0; i < this->__availableQueueFamilies.size(); i++) {
                        if (this->__vkGPU.getSurfaceSupportKHR(i, *VKSurface) == vk::True) res.push_back(i);
                    }
                    return res;
                }


                __Status setup(const vk::raii::SurfaceKHR &vkSurface) {
                    logger::trace << "GPU creating logical device for GPU " << this->__name << std::endl;
                    // 1. Check whether GPU is already created
                    if (this->__created) {
                        logger::error << "GPU " << this->__name << " is already created" << std::endl;
                        return __Status::E_ALREADY_EXISTS;
                    }
                    logger::trace << "Available queue families for GPU " << this->__name << ":\n" << __queuFamiliesToString(this->__availableQueueFamilies) << std::endl;

                    // 2. Create logical device
                    // 2.1 Determine graphics, present and transfer queues
                    /**
                     * The algorithm is hardcoced for now since the rules are always the same.
                     * We'll think about the possibility to set it up in the config later but
                     * it may not be relevant since this algorith may always be the same.
                     * The rules are :
                     * 1. If the graphics and the present queues CAN be the same, they MUST be the same, otherwise, they'll be 2 different queues
                     * 2. The transfer queue should be a one containing TRANSFER_BIT and NOT COMPUTE, GRAPHICS, VIDEO_ENCODE nor VIDEO_DECODE.
                     * If not found, the transfer queue will be the same as the graphics queue, who implicitly always containt TRANSFER_BIT
                     * https://www.reddit.com/r/vulkan/comments/1pccr6i/comment/nrx1w5r/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button
                     */
                    // 2.1.1 Setup present and graphics queue families, by default graphics and present queue families are the first value of the available ones
                    std::vector<uint32_t> availableGraphicsQueueIndicies(this->getAvailableQueueFamilyIndicesSupportingFlags(vk::QueueFlagBits::eGraphics, {}));
                    if (availableGraphicsQueueIndicies.empty()) {
                        logger::error << "No available graphics queue family found" << std::endl;
                        return __Status::E_NO_GRAPHICS_QUEUE_FAMILY;
                    }
                    uint32_t graphicsIndex = availableGraphicsQueueIndicies[0];
                    std::vector<uint32_t> availablePresentQueueIndicies(this->getAvailableQueueFamilyIndicesSupportingSurface(vkSurface));
                    if (availablePresentQueueIndicies.empty()) {
                        logger::error << "No available present present queue family found" << std::endl;
                        return __Status::E_NO_PRESENT_QUEUE_FAMILY;
                    }
                    uint32_t presentIndex = availablePresentQueueIndicies[0];
                    // 2.1.2 If they can be the same, let them be the same
                    // 2.1.2.1 If they are not already the same (which is often the case in gaming GPU), then loop to try to find the same
                    if (graphicsIndex != presentIndex) {
                        for (uint32_t availableGraphicsQueueIndex : availableGraphicsQueueIndicies) {
                            if (std::find(
                                availablePresentQueueIndicies.begin(),
                                availablePresentQueueIndicies.end(),
                                availableGraphicsQueueIndex
                            ) != availablePresentQueueIndicies.end()) {
                                graphicsIndex = availableGraphicsQueueIndex;
                                presentIndex = graphicsIndex;
                                break;
                            }
                        }

                    }                    
                    // 2.1.3 Set transfer queue family, if a dedicated trasnfer only queue family is found, set it, otherwise, set to graphics queue
                    std::vector<uint32_t> availableTransferQueueIndicies(this->getAvailableQueueFamilyIndicesSupportingFlags(vk::QueueFlagBits::eTransfer, vk::QueueFlagBits::eGraphics | vk::QueueFlagBits::eCompute | vk::QueueFlagBits::eVideoEncodeKHR | vk::QueueFlagBits::eVideoDecodeKHR));
                    uint32_t transferIndex = availableTransferQueueIndicies.empty() ? graphicsIndex : availableTransferQueueIndicies[0];
                    // 2.1.4 Create a set to remove duplicates to create only the right number of queues
                    logger::trace << "Graphics queue family index: " << graphicsIndex << std::endl;
                    logger::trace << "Present queue family index: " << presentIndex << std::endl;
                    logger::trace << "Transfer queue family index: " << transferIndex << std::endl;
                    this->__queueIndices = {graphicsIndex, presentIndex, transferIndex};
                    // 2.2 Create queueCreateInfos
                    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
                    // queueCreateInfos.reserve(this->__queueIndices.size());
                    std::vector<float> priorities{1.0f};
                    for (const uint32_t &queueIndex : this->__queueIndices) {
                        vk::DeviceQueueCreateInfo queueCreateInfo;
                        queueCreateInfo.setFlags({})
                        .setQueueFamilyIndex(queueIndex)
                        .setQueueCount(1)
                        .setQueuePriorities(priorities);
                        queueCreateInfos.push_back(queueCreateInfo);
                    }
                    // 2.3 Create logical device
                    // 2.3.1 Create deviceCreateInfo
                    std::vector<const char *> requiredDeviceExtensionNames = parseop::toCStrVector(REQUIRED_DEVICE_EXTENSION_NAMES);
                    vk::DeviceCreateInfo deviceCreateInfo;
                    deviceCreateInfo.setFlags({})
                    .setQueueCreateInfos(queueCreateInfos)
                    .setPEnabledExtensionNames(requiredDeviceExtensionNames);
                    // 2.3.2 Create logical device
                    logger::trace << "GPU creating logical device for GPU " << this->__name << std::endl;
                    auto [result, rawLogicalDevice] = (*this->__vkGPU).createDevice(deviceCreateInfo);
                    if (result != vk::Result::eSuccess) {
                        logger::error << "GPU failed to create logical device for GPU " << this->__name << std::endl;
                        return __Status::E_LOGICAL_DEVICE_CREATION;
                    }
                    this->__logicalDevice = vk::raii::Device(this->__vkGPU, rawLogicalDevice);
                    // 3. Register queues
                    logger::trace << "Registering queues for GPU " << this->__name << std::endl;
                    this-> __graphicsQueue = __GPU::__Queue(this->__logicalDevice, "GRAPHICS", graphicsIndex);
                    this->__presentQueue = __GPU::__Queue(this->__logicalDevice, "PRESENT", presentIndex);
                    this->__transferQueue = __GPU::__Queue(this->__logicalDevice, "TRANSFER", transferIndex);
                    this->__created = true;
                    return __Status::E_OK;
                }

                const vk::raii::PhysicalDevice &getVKPhysicalDevice(void) const { return this->__vkGPU; }
                const std::string &getName(void) const { return this->__name; }
                const vk::PhysicalDeviceProperties &getProperties(void) const { return this->__properties; }
                const vk::PhysicalDeviceFeatures &getFeatures(void) const { return this->__features; }
                const std::vector<std::string> &getExtensionNames(void) const { return this->__extensionNames; }
                __SurfaceSupport &getSurfaceSupport(void) { return this->__surfaceSupport; }
                const std::vector<vk::QueueFamilyProperties> &getQueueFamilies(void) const { return this->__availableQueueFamilies; }
                const vk::raii::Device &getVKLogicalDevice(void) const { return this->__logicalDevice; }
                const vk::Device &getRawVKLogicalDevice(void) const { return *this->__logicalDevice; }
                const __GPU::__Queue &getGraphicsQueue(void) const { return this->__graphicsQueue; }
                const __GPU::__Queue &getPresentQueue(void) const { return this->__presentQueue; }
                const __GPU::__Queue &getTransferQueue(void) const { return this->__transferQueue; }
                const std::set<uint32_t> &getQueueIndices(void) const { return this->__queueIndices; }
        };


        __GPU::__GPU(const vk::raii::PhysicalDevice &vkGPU, const vk::raii::SurfaceKHR &surface) : __impl(std::make_unique<__GPU::__Impl>(vkGPU, surface)) {}
        __GPU::__GPU(__GPU&&) noexcept = default;
        __GPU& __GPU::operator=(__GPU&&) noexcept = default;
        __GPU::~__GPU() = default;

        std::vector<__GPU> __GPU::listAvailableGPUs(
            const vk::raii::Instance &VKInstance,
            const vk::raii::SurfaceKHR &VKSurface,
            const bool &suitableOnly
        ) { return __GPU::__Impl::listAvailableGPUs(VKInstance, VKSurface, suitableOnly); }

        const vk::raii::PhysicalDevice &__GPU::getVKPhysicalDevice(void) const { return this->__impl->getVKPhysicalDevice(); }
        const vk::Device &__GPU::getRawVKLogicalDevice(void) const { return this->__impl->getRawVKLogicalDevice(); }
        const std::string &__GPU::getName(void) const { return this->__impl->getName(); }
        const vk::PhysicalDeviceProperties &__GPU::getProperties(void) const { return this->__impl->getProperties(); }
        const vk::PhysicalDeviceFeatures &__GPU::getFeatures(void) const { return this->__impl->getFeatures(); }
        const std::vector<std::string> &__GPU::getExtensionNames(void) const { return this->__impl->getExtensionNames(); }
        __GPU::__SurfaceSupport &__GPU::getSurfaceSupport(void) { return this->__impl->getSurfaceSupport(); }
        const std::vector<vk::QueueFamilyProperties> &__GPU::getQueueFamilies(void) const { return this->__impl->getQueueFamilies(); }
        const vk::raii::Device &__GPU::getVKLogicalDevice(void) const { return this->__impl->getVKLogicalDevice(); }

        std::vector<uint32_t> __GPU::getAvailableQueueFamilyIndicesSupportingFlags(const vk::QueueFlags &requiredFlags, const vk::QueueFlags &excludedFlags) const { return this->__impl->getAvailableQueueFamilyIndicesSupportingFlags(requiredFlags, excludedFlags); }
        std::vector<uint32_t> __GPU::getAvailableQueueFamilyIndicesSupportingSurface(const vk::raii::SurfaceKHR &VKSurface) const { return this->__impl->getAvailableQueueFamilyIndicesSupportingSurface(VKSurface); }

        __Status __GPU::setup(const vk::raii::SurfaceKHR &vkSurface) { return this->__impl->setup(vkSurface); }
        const __GPU::__Queue &__GPU::getGraphicsQueue(void) const { return this->__impl->getGraphicsQueue(); }
        const __GPU::__Queue &__GPU::getPresentQueue(void) const { return this->__impl->getPresentQueue(); }
        const __GPU::__Queue &__GPU::getTransferQueue(void) const { return this->__impl->getTransferQueue(); }
        const std::set<uint32_t> &__GPU::getQueueIndices(void) const { return this->__impl->getQueueIndices(); }
    } // namespace __private
} // namespace renderer
