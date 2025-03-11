///-----------------------------------------------------------------------------
//                              AMFITECH APS
//                          ALL RIGHTS RESERVED
//-----------------------------------------------------------------------------

#ifndef AMFITRACKNODES_H_
#define AMFITRACKNODES_H_

#include "project_conf.h"
#ifdef USE_ACTIVE_DEVICE_HANDLING

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <vector>
#include <memory>

#include "lib/hidapi/hidapi/hidapi.h"
#include "../lib/amfiprotapi/lib_AmfiProt.hpp"

class AmfitrackNode
{
private:
    uint8_t _tx_id;
    uint32_t _uuid[3];
    char *_dev_name;
    uint32_t _name_length;
    hid_device *_dev_handle;
    
    bool _is_hub = false;
    bool _is_usb = false;
    bool _is_rf = false;

    std::vector<std::shared_ptr<AmfitrackNode>> _child_nodes;

public:
    AmfitrackNode(uint8_t tx_id, uint32_t *uuid);
    AmfitrackNode(const char name[]);
    AmfitrackNode(hid_device *dev);
    AmfitrackNode();
    AmfitrackNode(const AmfitrackNode& node);
    ~AmfitrackNode();
    // Operator Overload
    AmfitrackNode& operator=(const AmfitrackNode& node);
    friend bool operator==(const AmfitrackNode& lhs, const AmfitrackNode& rhs);
    friend bool operator!=(const AmfitrackNode& lhs, const AmfitrackNode& rhs);
    friend std::ostream& operator<<(std::ostream& os, const AmfitrackNode& node);
    
    bool contains(const AmfitrackNode& node);
    std::shared_ptr<AmfitrackNode> find_match(const AmfitrackNode& node);

    // Accessor Functions
    uint8_t getTxID() const;
    uint32_t *getUUID() const;
    uint32_t getNameLength() const;
    char *getDevName() const;
    hid_device *getDeviceHandle() const;
    std::vector<std::shared_ptr<AmfitrackNode>> getChildNodes() const;
    // Mutator Functions
    void setTxID(uint8_t tx_id);
    void setUUID(uint32_t *uuid);
    void setNameLength(uint32_t name_length);
    void setDevName(const char name[], uint32_t name_length);
    void setDeviceHandle(hid_device *dev);
    void addChildNode(std::shared_ptr<AmfitrackNode> node);

    void setHubMode(bool is_hub);
    bool isHub() const;

    void setUSBMode(bool is_usb);
    bool isUSB() const;

    void setRFMode(bool is_rf);
    bool isRF() const;

};
#endif
#endif // AMFITRACKNODES_H_H
