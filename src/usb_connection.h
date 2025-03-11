///-----------------------------------------------------------------------------
//                              AMFITECH APS
//                          ALL RIGHTS RESERVED
//-----------------------------------------------------------------------------

#ifndef USB_CONNECTION_H_
#define USB_CONNECTION_H_

#include "project_conf.h"
#ifdef USE_USB

#define USE_HID
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <iostream>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <memory>
#include "lib/hidapi/hidapi/hidapi.h"
#include "AmfitrackNode.h"

#ifdef __cplusplus
extern "C"
{
#endif
#include "../lib/lib_queue/lib_Queue.h"
#include "../lib/lib_crc/lib_CRC.h"
#ifdef __cplusplus
}
#endif // __cplusplus

#include "../lib/amfiprotapi/lib_AmfiProt_API.hpp"

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
// #define USB_CONNECTION_DEBUG_INFO

#define USB_REPORT_LENGTH 64

//-----------------------------------------------------------------------------
// Type declarations
//-----------------------------------------------------------------------------
typedef struct USB_frame USB_frame_t;

//-----------------------------------------------------------------------------
// Variables and constants
//-----------------------------------------------------------------------------
struct USB_frame
{
	uint8_t data[USB_REPORT_LENGTH];
};

using namespace std;

class usb_connection
{
private:
    usb_connection();
    ~usb_connection();

    uint16_t _vid;
    uint16_t _pid;

    uint8_t _usb_report_id;
    #ifdef USE_HID
    hid_device *_DeviceHandle = NULL;
    #else
    libusb_context *_ctx = NULL;
    libusb_device_handle *_DeviceHandle = NULL;
    libusb_device_descriptor _DeviceDescriptor;
    #endif

    std::vector<std::shared_ptr<AmfitrackNode>> _nodes;

    time_t CheckForDevice_Timer;

public:
    static usb_connection& getInstance()
    {
        static usb_connection instance;
        return instance;
    }

    bool usb_connect_device(uint16_t vid, uint16_t pid);
    bool usb_disconnect_device(uint16_t vid, uint16_t pid);

    int read_blocking(hid_device *dev_handle, void *pData, uint8_t length);
    int read_timeout(hid_device *dev_handle, void *pData, uint8_t length, int timeout);
    int write_blocking(hid_device *dev_handle, void const *pData, uint8_t length);
    int set_nonblocking(bool enable);

    std::vector<std::shared_ptr<AmfitrackNode>> find_nodes(void);
    
    hid_device *get_device_handle(uint8_t tx_id);

    void usb_init(void);
    void usb_run(void);
};

#endif
#endif // USB_CONNECTION_H_
