// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

const Ice = require("../Ice/ModuleRegistry").Ice;
Ice.__M.require(module, ["../Ice/Debug", "../Ice/LocalException"]);

class RetryException extends Error
{
    constructor(ex)
    {
        super();
        if(ex instanceof Ice.LocalException)
        {
            this._ex = ex;
        }
        else
        {
            Ice.Debug.assert(ex instanceof RetryException);
            this._ex = ex._ex;
        }
    }
    
    get inner()
    {
        return this._ex;
    }
}

Ice.RetryException = RetryException;
module.exports.Ice = Ice;
