// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceSSL/Config.h>

#ifdef ICE_OS_WINRT

#include <IceSSL/SSLEngine.h>
#include <Ice/Communicator.h>
#include <Ice/Properties.h>
#include <IceUtil/Shared.h>

#include <string>

IceUtil::Shared* IceSSL::upCast(IceSSL::WinRTEngine* p) { return p; }

using namespace std;
using namespace IceSSL;

WinRTEngine::WinRTEngine(const Ice::CommunicatorPtr& communicator) : SSLEngine(communicator)
{
}

void
WinRTEngine::initialize()
{
    lock_guard<mutex> lock(_mutex);
    if(_initialized)
    {
        return;
    }

    SSLEngine::initialize();

    const auto properties = communicator()->getProperties();

    //
    // Load client certificate
    //
    string findCert = properties->getProperty("IceSSL.FindCert");
    if(!findCert.empty())
    {
        auto certs = findCertificates(properties->getPropertyWithDefault("IceSSL.CertStore", "My"), findCert);
        if(certs->Size > 0)
        {
            _certificate = make_shared<IceSSL::Certificate>(certs->GetAt(0));
        }
    }
    _initialized = true;
}

bool
WinRTEngine::initialized() const
{
    return _initialized;
}

shared_ptr<Certificate>
WinRTEngine::certificate()
{
    return _certificate;
}

void
WinRTEngine::destroy()
{
}

#endif

