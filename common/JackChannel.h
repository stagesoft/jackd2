/*
Copyright (C) 2004-2008 Grame

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software 
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

*/

#ifndef __JackChannel__
#define __JackChannel__

#include "types.h"

namespace Jack
{

class JackClientInterface;
class JackClient;
class JackServer;
struct JackEngineControl;
class JackGraphManager;

namespace detail
{

/*!
\brief Inter process channel for server/client bidirectionnal communication : request and (receiving) notifications.
*/

class JackClientChannelInterface
{

    public:

        JackClientChannelInterface()
        {}
        virtual ~JackClientChannelInterface()
        {}

        // Open the Server/Client connection
        virtual int Open(const char* server_name, const char* name, char* name_res, JackClient* obj, jack_options_t options, jack_status_t* status)
        {
            return 0;
        }

        // Close the Server/Client connection
        virtual void Close()
        {}

        // Start listening for messages from the server
        virtual int Start()
        {
            return 0;
        }

        // Stop listening for messages from the server
        virtual void Stop()
        {}

        virtual int ServerCheck(const char* server_name)
        {
            return -1;
        }

        virtual void ClientCheck(const char* name, char* name_res, int protocol, int options, int* status, int* result)
        {}
        virtual void ClientOpen(const char* name, int pid, int* shared_engine, int* shared_client, int* shared_graph, int* result)
        {}
        virtual void ClientOpen(const char* name, int* ref, JackEngineControl** shared_engine, JackGraphManager** shared_manager, JackClientInterface* client, int* result)
        {}
        virtual void ClientClose(int refnum, int* result)
        {}

        virtual void ClientActivate(int refnum, int is_real_time, int* result)
        {}
        virtual void ClientDeactivate(int refnum, int* result)
        {}

        virtual void PortRegister(int refnum, const char* name, const char* type, unsigned int flags, unsigned int buffer_size, jack_port_id_t* port_index, int* result)
        {}
        virtual void PortUnRegister(int refnum, jack_port_id_t port_index, int* result)
        {}

        virtual void PortConnect(int refnum, const char* src, const char* dst, int* result)
        {}
        virtual void PortDisconnect(int refnum, const char* src, const char* dst, int* result)
        {}
        virtual void PortConnect(int refnum, jack_port_id_t src, jack_port_id_t dst, int* result)
        {}
        virtual void PortDisconnect(int refnum, jack_port_id_t src, jack_port_id_t dst, int* result)
        {}
        virtual void PortRename(int refnum, jack_port_id_t port, const char* name, int* result)
        {}

        virtual void SetBufferSize(jack_nframes_t buffer_size, int* result)
        {}
        virtual void SetFreewheel(int onoff, int* result)
        {}

        virtual void ReleaseTimebase(int refnum, int* result)
        {}

        virtual void SetTimebaseCallback(int refnum, int conditional, int* result)
        {}

        virtual void GetInternalClientName(int refnum, int int_ref, char* name_res, int* result)
        {}

        virtual void InternalClientHandle(int refnum, const char* client_name, int* status, int* int_ref, int* result)
        {}

        virtual void InternalClientLoad(int refnum, const char* client_name, const char* so_name, const char* objet_data, int options, int* status, int* int_ref, int* result)
        {}

        virtual void InternalClientUnload(int refnum, int int_ref, int* status, int* result)
        {}
        
};

}

} // end of namespace

#endif

