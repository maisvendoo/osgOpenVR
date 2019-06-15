#include    "openvrdevice.h"

#include    <osg/Notify>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
OpenVRDevice::OpenVRDevice(float zNear,
                           float zFar,
                           const float worldUnitsPerMeter,
                           const int samples)
    : m_vrSystem(nullptr)
    , m_vrRenderModels(nullptr)
    , m_worldUnitsPerMeter(worldUnitsPerMeter)
{

    // Loading the SteamVR runtime
    vr::EVRInitError eError = vr::VRInitError_None;
    m_vrSystem = vr::VR_Init(&eError, vr::VRApplication_Scene);

    if (eError != vr::VRInitError_None)
    {
        m_vrSystem = nullptr;
        osg::notify(osg::WARN)
                << "Error: Unable to initialize the OpenVR library" << std::endl
                << "Reason: " << vr::VR_GetVRInitErrorAsEnglishDescription(eError)
                << std::endl;
    }

    if (!vr::VRCompositor())
    {
        m_vrSystem = nullptr;
        vr::VR_Shutdown();
        osg::notify(osg::WARN) << "Error: Compositor initialization failed" << std::endl;
        return;
    }

    m_vrRenderModels = static_cast<vr::IVRRenderModels *>(vr::VR_GetGenericInterface(vr::IVRRenderModels_Version, &eError));

    if (m_vrRenderModels == nullptr)
    {
        m_vrSystem = nullptr;
        vr::VR_Shutdown();
        osg::notify(osg::WARN)
                << "Error: Unable to get render model interface" << std::endl
                << "Reason: " << vr::VR_GetVRInitErrorAsEnglishDescription(eError)
                << std::endl;

        return;
    }

    std::string driverName = getDeviceProperty(vr::Prop_TrackingSystemName_String);
    std::string deviceSerialNumber = getDeviceProperty(vr::Prop_SerialNumber_String);

    osg::notify(osg::NOTICE) << "HMD driver name: " << driverName << std::endl;
    osg::notify(osg::NOTICE) << "HMD driver serial number: " << deviceSerialNumber << std::endl;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string OpenVRDevice::getDeviceProperty(vr::TrackedDeviceProperty prop)
{
    uint32_t bufferLen = m_vrSystem->GetStringTrackedDeviceProperty(vr::k_unTrackedDeviceIndex_Hmd, prop, NULL, 0);

    if (bufferLen == 0)
    {
        return "";
    }

    char *buffer = new char[bufferLen];
    bufferLen = m_vrSystem->GetStringTrackedDeviceProperty(vr::k_unTrackedDeviceIndex_Hmd, prop, buffer, bufferLen);
    std::string result = buffer;
    delete [] buffer;

    return result;
}


