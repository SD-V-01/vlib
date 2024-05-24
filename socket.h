////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   socket.h
//  Version:     v1.00
//  Created:     30/04/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "cpp_compiler.h"
#include "base_types.h"

#ifndef _SOCKET_H_
#define _SOCKET_H_
namespace VLIB_NAMESPACE{
	void VSocketInit();

	struct uTxSock {


	private:
//        Data
		u32 Port;

	};

//    For the os specific parts
	i32 socketOsStartup();

}

#endif

