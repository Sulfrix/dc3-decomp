#pragma once
#include "utl/Str.h"

class NetAddress {
public:
    NetAddress(unsigned int ip, unsigned short port) : mIP(ip), mPort(port) {}
    NetAddress() : mIP(0), mPort(0) {}
    unsigned int mIP;
    unsigned int mPort;
};

class NetworkSocket {
public:
    NetworkSocket() {}
    virtual ~NetworkSocket() {}
    virtual bool Connect(unsigned int, unsigned short) = 0;
    virtual bool Fail() const = 0;
    virtual void Disconnect() = 0;
    virtual void Bind(unsigned short) = 0;
    virtual int InqBoundPort(unsigned short &) const = 0;
    virtual void Listen() = 0;
    virtual NetworkSocket *Accept() = 0;
    virtual void GetRemoteIP(unsigned int &, unsigned short &) = 0;
    virtual bool CanSend() const = 0;
    virtual bool CanRead() const = 0;
    virtual int Send(const void *, unsigned int) = 0;
    virtual int Recv(void *, unsigned int) = 0;
    virtual int SendTo(const void *, unsigned int, unsigned int, unsigned short) = 0;
    virtual int BroadcastTo(const void *, unsigned int, unsigned short) = 0;
    virtual int RecvFrom(void *, unsigned int, unsigned int &, unsigned short &) = 0;
    virtual bool SetNoDelay(bool) = 0;

    static String GetHostName();
    static NetworkSocket *Create(bool);
    static NetAddress SetIPPortFromHostPort(const char *, const char *, unsigned short);
    static unsigned int IPStringToInt(const String &);
    static unsigned int ResolveHostName(String);
};
