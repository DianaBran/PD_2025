#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>
#include <iostream>

#pragma comment(lib, "setupapi.lib")

int main() {
    GUID guid = GUID_DEVCLASS_USB; // Clasa USB
    HDEVINFO hDevInfo = SetupDiGetClassDevs(&guid, NULL, NULL, DIGCF_PRESENT | DIGCF_PROFILE);

    if (hDevInfo == INVALID_HANDLE_VALUE) {
        std::cerr << "Eroare la obținerea dispozitivelor USB.\n";
        return 1;
    }

    SP_DEVINFO_DATA DeviceInfoData;
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); ++i) {
        TCHAR buffer[1024];
        DWORD buffersize = 0;

        if (SetupDiGetDeviceRegistryProperty(
            hDevInfo,
            &DeviceInfoData,
            SPDRP_DEVICEDESC,
            NULL,
            (PBYTE)buffer,
            sizeof(buffer),
            &buffersize)) {
            std::wcout << L"Dispozitiv USB: " << buffer << std::endl;
        }
    }

    SetupDiDestroyDeviceInfoList(hDevInfo);
    return 0;
}
