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
                std::unordered_map<std::string, __Queue> __queues;
                vk::raii::Device __logicalDevice;
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
                        if (availableGPU.getAvailableQueueFamilyIndicesSupportingFlags(vk::QueueFlagBits::eGraphics).empty()) {
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

                static std::vector<vk::DeviceQueueCreateInfo> __getDeviceQueueCreateInfos(const QueuesCreationMap_t &queuesCreationMap) {
                    logger::trace << "Creating device queues create info" << std::endl;
                    std::vector<vk::DeviceQueueCreateInfo> res;
                    for (const auto &[name, queueCreateInfo] : queuesCreationMap) {
                        res.push_back(vk::DeviceQueueCreateInfo({}, std::get<0>(queueCreateInfo), std::get<1>(queueCreateInfo)));
                    }
                    return res;
                }

                static __Queue __createQueue(
                    const vk::raii::Device &vkLogicalDevice,
                    const std::string &name,
                    const vk::DeviceQueueCreateInfo &createInfo
                ) {
                    return __Queue(vkLogicalDevice, name, createInfo);
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
                    vk::PhysicalDeviceProperties res(vkGPU.getProperties());
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
                    return vkGPU.getFeatures();
                }()),
                __extensionNames([&]() {
                    logger::trace << "\tLoading extension names for GPU" << this->__name << std::endl;
                    std::vector<vk::ExtensionProperties> vkGPUExtensions(vkGPU.enumerateDeviceExtensionProperties());
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
                    return __SurfaceSupport(vkGPU, surface);
                }()),
                __availableQueueFamilies([&]() {
                    logger::trace << "\tLoading queue family properties for GPU " << this->__name << std::endl;
                    return vkGPU.getQueueFamilyProperties();
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

                std::vector<uint32_t> getAvailableQueueFamilyIndicesSupportingFlags(const vk::QueueFlags &flags) const {
                    std::vector<uint32_t> res;
                    for (uint32_t i = 0; i < this->__availableQueueFamilies.size(); i++) {
                        if ( (this->__availableQueueFamilies[i].queueFlags & flags) == flags) res.push_back(i);
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


                __Status create(const QueuesCreationMap_t &queuesCreationMap) {
                    logger::trace << "Creating logical device forGPU " << this->__name << "..." << std::endl;
                    if (this->__created) {
                        logger::error << "GPU " << this->__name << " is already created" << std::endl;
                        return __Status::E_ALREADY_EXISTS;
                    }

                    // 1. Create logical device
                    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos = __getDeviceQueueCreateInfos(queuesCreationMap);
                    std::vector<const char *> requiredDeviceExtensionNames = parseop::toCStrVector(REQUIRED_DEVICE_EXTENSION_NAMES);
                    logger::trace << "Creating device create info for GPU " << this->__name << std::endl;
                    vk::DeviceCreateInfo deviceCreateInfo(
                        {},
                        queueCreateInfos,
                        {}, // we don't do device specific layers anymore
                        requiredDeviceExtensionNames,
                        {}
                    );
                    logger::trace << "Creating logical device for GPU " << this->__name << std::endl;
                    auto [result, rawLogicalDevice] = (*this->__vkGPU).createDevice(deviceCreateInfo);
                    if (result != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(*this, result, "GPU failed to create it's VK logical device");
                        return __Status::E_LOGICAL_DEVICE_CREATION;
                    }
                    this->__logicalDevice = vk::raii::Device(this->__vkGPU, rawLogicalDevice);
                    // 2. Register queues
                    logger::trace << "Registering queues for GPU " << this->__name << std::endl;
                    for (const auto &[name, info] : queuesCreationMap) {
                        logger::trace << "\tRegistering queue " << name << " with index " << std::get<0>(info) << " for GPU " << this->__name << std::endl;
                        vk::DeviceQueueCreateInfo queueCreateInfo({}, std::get<0>(info), std::get<1>(info));
                        this->__queues.emplace(name, __GPU::__Queue(this->__logicalDevice, name, queueCreateInfo));
                    }
                    this->__created = true;
                    return __Status::E_OK;
                }

                std::optional<std::reference_wrapper<__GPU::__Queue>> getQueue(const std::string &name) {
                    auto it = this->__queues.find(name);
                    if (it == this->__queues.end()) return std::nullopt;
                    return std::ref(it->second);
                }

                std::vector<uint32_t> getQueuesIndicies(void) const {
                    std::vector<uint32_t> res(this->__queues.size());
                    std::transform(
                        this->__queues.begin(),
                        this->__queues.end(),
                        res.begin(),
                        [](const auto &pair) { return pair.second.getIndex(); }
                    );
                    return res;
                }

                const vk::raii::PhysicalDevice &getVKPhysicalDevice(void) const { return this->__vkGPU; }
                const std::string &getName(void) const { return this->__name; }
                const vk::PhysicalDeviceProperties &getProperties(void) const { return this->__properties; }
                const vk::PhysicalDeviceFeatures &getFeatures(void) const { return this->__features; }
                const std::vector<std::string> &getExtensionNames(void) const { return this->__extensionNames; }
                const __SurfaceSupport &getSurfaceSupport(void) const { return this->__surfaceSupport; }
                const std::vector<vk::QueueFamilyProperties> &getQueueFamilies(void) const { return this->__availableQueueFamilies; }
                const vk::raii::Device &getVKLogicalDevice(void) const { return this->__logicalDevice; }
                const vk::Device &getRawVKLogicalDevice(void) const { return *this->__logicalDevice; }
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
        const __GPU::__SurfaceSupport &__GPU::getSurfaceSupport(void) const { return this->__impl->getSurfaceSupport(); }
        const std::vector<vk::QueueFamilyProperties> &__GPU::getQueueFamilies(void) const { return this->__impl->getQueueFamilies(); }
        const vk::raii::Device &__GPU::getVKLogicalDevice(void) const { return this->__impl->getVKLogicalDevice(); }

        std::vector<uint32_t> __GPU::getAvailableQueueFamilyIndicesSupportingFlags(const vk::QueueFlags &flags) const { return this->__impl->getAvailableQueueFamilyIndicesSupportingFlags(flags); }
        std::vector<uint32_t> __GPU::getAvailableQueueFamilyIndicesSupportingSurface(const vk::raii::SurfaceKHR &VKSurface) const { return this->__impl->getAvailableQueueFamilyIndicesSupportingSurface(VKSurface); }

        __Status __GPU::create(const QueuesCreationMap_t &queuesCreationMap) { return this->__impl->create(queuesCreationMap); }
        std::optional<std::reference_wrapper<__GPU::__Queue>> __GPU::getQueue(const std::string &name) { return this->__impl->getQueue(name); }
        std::vector<uint32_t> __GPU::getQueuesIndicies(void) const { return this->__impl->getQueuesIndicies(); }
    } // namespace __private
} // namespace renderer
