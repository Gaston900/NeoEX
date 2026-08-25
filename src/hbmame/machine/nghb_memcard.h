// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
/*********************************************************************

    nghb_memcard.h

    NEOGEO Memory card functions.

*********************************************************************/

#pragma once

#ifndef __NGHB_MEMCARD_H__
#define __NGHB_MEMCARD_H__

/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/
#include "imagedev/memcard.h"

// ======================> ng_memcard_device

class nghb_memcard_device :  public device_t, public device_memcard_image_interface
{
public:
	// construction/destruction
	nghb_memcard_device(const machine_config &mconfig, const char *tag, device_t *owner, u32 clock = 0);

	virtual bool is_reset_on_load() const noexcept override { return false; }
	virtual const char *file_extensions() const noexcept override { return "neo"; }

	virtual std::pair<std::error_condition, std::string> call_load() override;
	virtual void call_unload() override;
	virtual std::pair<std::error_condition, std::string> call_create(int format_type, util::option_resolution *format_options) override;

	// device-level overrides
	virtual void device_start() override;

	u8 read(offs_t offset);
	void write(offs_t offset, u8 data);

	/* returns the index of the current memory card, or -1 if none */
	int present() { return is_loaded() ? 0 : -1; }
private:
	u8 m_memcard_data[0x800]{};
};


// device type definition
DECLARE_DEVICE_TYPE(NGHB_MEMCARD, nghb_memcard_device)


#endif  /* __NGHB_MEMCARD_H__ */
