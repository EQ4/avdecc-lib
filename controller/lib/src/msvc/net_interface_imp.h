/*
 * Licensed under the MIT License (MIT)
 *
 * Copyright (c) 2013 AudioScience Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * net_interface_imp.h
 *
 * Network interface implementation class
 */

#pragma once

#define HAVE_REMOTE

#include <stdint.h>
#include <pcap.h>
#include "build.h"
#include "net_interface.h"

namespace avdecc_lib
{
    class net_interface_imp : public net_interface
    {
    private:
        pcap_if_t *all_devs;
        pcap_if_t *dev;
        uint64_t mac;
        uint32_t total_devs;
        pcap_t *pcap_interface;
        char err_buf[PCAP_ERRBUF_SIZE];
        const u_char *cmd_frame;
        uint8_t tx_frame[1500];	// Ethernet frame used to send packets

    public:
        net_interface_imp();

        ~net_interface_imp();

        /**
         * Call destructor for Network Interface used for destroying objects
         */
        void STDCALL destroy();

        /**
         * Count the number of devices.
         */
        uint32_t STDCALL devs_count();

        /**
         * Get the MAC address of the network interface.
         */
        uint64_t mac_addr();

        /**
         * Get the corresponding network interface description by index.
         */
        char * STDCALL get_dev_desc_by_index(size_t dev_index);

        /**
         * Select the corresponding interface by number.
         */
        int STDCALL select_interface_by_num(uint32_t interface_num);

        /**
         * Set packet filter for the network interface.
         */
        int set_capture_ether_type(uint16_t *ether_type, uint32_t count);

        /**
         * Capture a network packet.
         */
        int STDCALL capture_frame(const uint8_t **frame, uint16_t *frame_len);

        /**
         * Send a network packet.
         */
        int send_frame(uint8_t *frame, size_t frame_len);

    };

    extern net_interface_imp *net_interface_ref;
}

