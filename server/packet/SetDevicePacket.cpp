#include "Global.h"
#include "Protocol.h"
#include "Packet.h"
#include "packet/SetDevicePacket.h"

int SetDevicePacket::parser(const char* buff, const int size)
{
    DeviceType deviceType = *((int *) buff);
    char* macAddr = buff + 4;

    if (this->mDev != NULL) {
        this->mDev->setMacAddr(macAddr);
        this->mDev->setDeviceType(deviceType);
    }

    vector<Device> &devs = this->mGroups[macAddr];
    devs.push_back(this->mDev);

    cout << "Group ID : " << macAddr << endl;
    for (vector<Device>::iterator iter = devs.begin(); iter != devs.end(); iter++) {
        cout << "DeviceType : " << iter->getDeviceType() << endl;
        cout << "IP:PORT : " << iter->getIpAddr() << ":" << iter->getPort() << endl << endl;
    }

    this->mGroups.insert(pair<string, vector<Device>>(macAddr, devs));
    return 0;
}

char* SetDevicePacket::encode(int* size)
{
    return NULL;
}

int SetDevicePacket::execute()
{
    return 0;
}

