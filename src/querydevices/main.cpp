// C++ Standard Library includes
#include <iostream>

// AST Utilities includes
#include <AstUtils.h>
#include <vlk/VulkanInstance.h>
#include <vlk/PhysicalDevice.h>

using namespace astu;
using namespace std;

int main()
{
    SayVersion();
    SayCopyright();
    cout << endl;

    auto instance = VulkanInstanceBuilder().Build();
    auto devices = PhysicalDevice::GetVulkanDevices(*instance);

    cout << "Found " << devices.size() << " Vulkan devices" << endl;
    int cnt = 0;
    for (const auto & device : devices) {
        cout << "  - " << device.GetName() << endl;
    }

    return 0;
}