#ifndef     OPENVRDEVICE_H
#define     OPENVRDEVICE_H

#include    <openvr/openvr.h>

#include    <osg/Referenced>

class OpenVRDevice  : public osg::Referenced
{
public:

    OpenVRDevice(float zNear, float zFar, const float worldUnitsPerMeter, const int samples);

protected:

    ~OpenVRDevice() {}


    vr::IVRSystem           *m_vrSystem;
    vr::IVRRenderModels     *m_vrRenderModels;
    const float             m_worldUnitsPerMeter;

private:

    std::string getDeviceProperty(vr::TrackedDeviceProperty prop);
};

#endif // OPENVRDEVICE_H
