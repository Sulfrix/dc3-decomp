#include "os/NetworkSocket.h"
#include "utl/Str.h"

NetAddress
NetworkSocket::SetIPPortFromHostPort(const char *c1, const char *c2, unsigned short port) {
    NetAddress addr;
    String str(c1);
    unsigned int idx = str.find(':');
    if (idx != FixedString::npos) {
        String str2 = str.substr(idx + 1);
        str = str.substr(0, idx);
        addr.mPort = strtol(str2.c_str(), 0, 0);
    } else {
        addr.mPort = port;
    }
    unsigned int ip = IPStringToInt(str);
    if (ip != -1) {
        addr.mIP = ip;
    }
    if (addr.mIP == 0) {
        if (c2) {
            str += ".";
            str += c2;
        }
        addr.mIP = ResolveHostName(str);
    }
    return addr;
}
