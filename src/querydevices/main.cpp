#include <iostream>
#include <vlk/PhysicalDevice.h>

using namespace astu;

int main()
{
    std::cout << "Hello world!" << std::endl;

    auto devices = PhysicalDevice::GetVulkanDevices();

    return 0;
}