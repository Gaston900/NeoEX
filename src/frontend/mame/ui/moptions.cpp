// license:BSD-3-Clause
// copyright-holders:Maurizio Petrarota
/***************************************************************************

    ui/moptions.cpp

    UI main options manager.

***************************************************************************/

#include "emu.h"
#include "options.h"
#include "ui/moptions.h"


//**************************************************************************
//  UI EXTRA OPTIONS
//**************************************************************************

const options_entry ui_options::s_option_entries[] =
{
	// search path options
	{ nullptr,                              nullptr,            option_type::HEADER,     "UI SEARCH PATH OPTIONS" },
	{ OPTION_HISTORY_PATH,                  "support/history;dats;.",   option_type::MULTIPATH,  "path to system/software info files" }, // 修改的 (加斯顿90)
	{ OPTION_CATEGORYINI_PATH,              "support/folders",          option_type::MULTIPATH,  "path to category ini files" }, // 修改的 (加斯顿90)
	{ OPTION_CABINETS_PATH,                 "support/cabinets;cabdevs", option_type::MULTIPATH,  "path to cabinets / devices image" }, // 修改的 (加斯顿90)
	{ OPTION_CPANELS_PATH,                  "support/cpanel",           option_type::MULTIPATH,  "path to control panel image" }, // 修改的 (加斯顿90)
	{ OPTION_PCBS_PATH,                     "support/pcb",              option_type::MULTIPATH,  "path to pcbs image" }, // 修改的 (加斯顿90)
	{ OPTION_FLYERS_PATH,                   "support/flyers",           option_type::MULTIPATH,  "path to flyers image" }, // 修改的 (加斯顿90)
	{ OPTION_TITLES_PATH,                   "support/titles",           option_type::MULTIPATH,  "path to titles image" }, // 修改的 (加斯顿90)
	{ OPTION_ENDS_PATH,                     "support/ends",             option_type::MULTIPATH,  "path to ends image" }, // 修改的 (加斯顿90)
	{ OPTION_MARQUEES_PATH,                 "support/marquees",         option_type::MULTIPATH,  "path to marquees image" }, // 修改的 (加斯顿90)
	{ OPTION_ARTPREV_PATH,                  "support/artwork preview;artpreview",  option_type::MULTIPATH,  "path to artwork preview image" }, // 修改的 (加斯顿90)
	{ OPTION_BOSSES_PATH,                   "support/bosses",           option_type::MULTIPATH,  "path to bosses image" }, // 修改的 (加斯顿90)
	{ OPTION_LOGOS_PATH,                    "support/logo",             option_type::MULTIPATH,  "path to logos image" }, // 修改的 (加斯顿90)
	{ OPTION_SCORES_PATH,                   "support/scores",           option_type::MULTIPATH,  "path to scores image" }, // 修改的 (加斯顿90)
	{ OPTION_VERSUS_PATH,                   "support/versus",           option_type::MULTIPATH,  "path to versus image" }, // 修改的 (加斯顿90)
	{ OPTION_GAMEOVER_PATH,                 "support/gameover",         option_type::MULTIPATH,  "path to gameover image" }, // 修改的 (加斯顿90)
	{ OPTION_HOWTO_PATH,                    "support/howto",            option_type::MULTIPATH,  "path to howto image" }, // 修改的 (加斯顿90)
	{ OPTION_SELECT_PATH,                   "support/select",           option_type::MULTIPATH,  "path to select image" }, // 修改的 (加斯顿90)
	{ OPTION_ICONS_PATH,                    "support/icons",            option_type::MULTIPATH,  "path to ICOns image" }, // 修改的 (加斯顿90)
	{ OPTION_COVER_PATH,                    "support/covers",           option_type::MULTIPATH,  "path to software cover image" }, // 修改的 (加斯顿90)
	{ OPTION_UI_PATH,                       "config/ui",               option_type::MULTIPATH,  "path to UI files" }, // 修改的 (加斯顿90)

	// misc options
	{ nullptr,                              nullptr,            option_type::HEADER,     "UI MISC OPTIONS" },
	{ OPTION_SYSTEM_NAMES,                  "",                 option_type::MULTIPATH,  "translated system names file" },
	{ OPTION_SKIP_WARNINGS,                 "0",                option_type::BOOLEAN,    "display fewer repeated warnings about imperfect emulation" },
	{ OPTION_UNTHROTTLE_MUTE,               "0",                option_type::BOOLEAN,    "mute audio when running unthrottled or when fast-forwarding" },
	{ OPTION_MENU_PAUSE,                    "1",                option_type::BOOLEAN,    "automatically pause when showing menus" }, // 修改的 代码来源 (加斯顿90)
	{ OPTION_UI_FOLLOW_FOCUS,               "0",                option_type::BOOLEAN,    "open menus in active window" },

	// UI options
	{ nullptr,                              nullptr,            option_type::HEADER,      "UI OPTIONS" },
	{ OPTION_INFOS_SIZE "(0.20-1.00)",      "0.75",             option_type::FLOAT,       "UI right panel infos text size (0.20 - 1.00)" },
	{ OPTION_FONT_ROWS "(25-40)",           "30",               option_type::INTEGER,     "UI font lines per screen (25 - 40)" },
	// MAMEFX colours changed, Mamesick 2016-08-31
	{ OPTION_UI_BORDER_COLOR,               "ffb41010",         option_type::STRING,      "UI border color (ARGB)" }, // 修改的 (加斯顿90)
	{ OPTION_UI_BACKGROUND_COLOR,           "ef161616",         option_type::STRING,      "UI background color (ARGB)" }, // 修改的 (加斯顿90)
	{ OPTION_UI_CLONE_COLOR,                "ffc6c6c6",         option_type::STRING,      "UI clone color (ARGB)" }, // 修改的 (加斯顿90)
	{ OPTION_UI_DIPSW_COLOR,                "ff7f7f7f",         option_type::STRING,      "UI dipswitch color (ARGB)" },
	{ OPTION_UI_GFXVIEWER_BG_COLOR,         "ef000000",         option_type::STRING,      "UI gfx viewer color (ARGB)" },
	{ OPTION_UI_MOUSEDOWN_BG_COLOR,         "ef00a2e8",         option_type::STRING,      "UI mouse down bg color (ARGB)" },
	{ OPTION_UI_MOUSEDOWN_COLOR,            "fffff200",         option_type::STRING,      "UI mouse down color (ARGB)" },
	{ OPTION_UI_MOUSEOVER_BG_COLOR,         "ef00a2e8",         option_type::STRING,      "UI mouse over bg color (ARGB)" },
	{ OPTION_UI_MOUSEOVER_COLOR,            "fffff200",         option_type::STRING,      "UI mouse over color (ARGB)" },
	{ OPTION_UI_SELECTED_BG_COLOR,          "ef3f48cc",         option_type::STRING,      "UI selected bg color (ARGB)" },
	{ OPTION_UI_SELECTED_COLOR,             "fffff200",         option_type::STRING,      "UI selected color (ARGB)" },
	{ OPTION_UI_SLIDER_COLOR,               "efffffff",         option_type::STRING,      "UI slider color (ARGB)" }, // 修改的 (加斯顿90)
	{ OPTION_UI_SUBITEM_COLOR,              "efffffff",         option_type::STRING,      "UI subitem color (ARGB)" }, // 修改的 (加斯顿90)
	{ OPTION_UI_TEXT_BG_COLOR,              "efefefef",         option_type::STRING,      "UI text bg color (ARGB)" },
	{ OPTION_UI_TEXT_COLOR,                 "ffffffff",         option_type::STRING,      "UI text color (ARGB)" }, // 修改的 (加斯顿90)
	{ OPTION_UI_UNAVAILABLE_COLOR,          "ff7f7f7f",         option_type::STRING,      "UI unavailable color (ARGB)" },

	// system/software selection menu options
	{ nullptr,                              nullptr,            option_type::HEADER,     "SYSTEM/SOFTWARE SELECTION MENU OPTIONS" },
	{ OPTION_HIDE_PANELS "(0-3)",           "0",                option_type::INTEGER,    "UI hide left/right panel in main view (0 = Show all, 1 = hide left, 2 = hide right, 3 = hide both" },
	{ OPTION_USE_BACKGROUND,                "1",                option_type::BOOLEAN,    "enable background image in main view" },
	{ OPTION_SKIP_BIOS_MENU,                "1",                option_type::BOOLEAN,    "skip bios submenu, start with configured or default" }, // 修改的 代码来源 (加斯顿90)
	{ OPTION_SKIP_PARTS_MENU,               "0",                option_type::BOOLEAN,    "skip parts submenu, start with first part" },
	{ OPTION_REMEMBER_LAST,                 "1",                option_type::BOOLEAN,    "initially select last used system in main menu" },
	{ OPTION_LAST_USED_MACHINE,             "",                 option_type::STRING,     "last selected system" },
	{ OPTION_LAST_USED_FILTER,              "",                 option_type::STRING,     "last used system filter" },
	{ OPTION_SYSTEM_RIGHT_PANEL,            "image",            option_type::STRING,     "selected system right panel tab" },
	{ OPTION_SOFTWARE_RIGHT_PANEL,          "image",            option_type::STRING,     "selected software right panel tab" },
	{ OPTION_SYSTEM_RIGHT_IMAGE,            "snap",             option_type::STRING,     "selected system right panel image" },
	{ OPTION_SOFTWARE_RIGHT_IMAGE,          "snap",             option_type::STRING,     "selected software right panel image" },
	{ OPTION_ENLARGE_SNAPS,                 "1",                option_type::BOOLEAN,    "enlarge images in right panel (keeping aspect ratio)" },
	{ OPTION_FORCED4X3,                     "0",                option_type::BOOLEAN,    "force 4:3 aspect ratio for snapshots in the software menu" }, // 修改的 代码来源 (加斯顿90)
	{ OPTION_INFO_AUTO_AUDIT,               "0",                option_type::BOOLEAN,    "automatically audit media for the general info panel" },
	{ OPTION_HIDE_ROMLESS,                  "1",                option_type::BOOLEAN,    "hide systems that don't require ROMs in the available system filter" },

	// sentinel
	{ nullptr }
};

//-------------------------------------------------
//  ui_options - constructor
//-------------------------------------------------

ui_options::ui_options() : core_options()
{
	add_entries(ui_options::s_option_entries);
}

//-------------------------------------------------
//  rgb_value - decode an RGB option
//-------------------------------------------------

rgb_t ui_options::rgb_value(const char *option) const
{
	// find the entry
	core_options::entry::shared_const_ptr entry = get_entry(option);

	// look up the value, and sanity check the result
	const char *value = entry->value();
	int len = strlen(value);
	if (len != 8)
		value = entry->default_value().c_str();

	// convert to an rgb_t
	return rgb_t((uint32_t)strtoul(value, nullptr, 16));
}
