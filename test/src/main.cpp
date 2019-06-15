#include    "main.h"

int main(int argc, char *argv[])
{
    osg::ref_ptr<OpenVRDevice> vrDevice = new OpenVRDevice(0.1, 100, 1.0, 16);


    return 0;
}
