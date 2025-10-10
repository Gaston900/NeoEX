// license:BSD-3-Clause
// copyright-holders:Chris Kirmse, Mike Haaland, René Single, Mamesick

#include "winui.h"

/***************************************************************************
    private variables
 ***************************************************************************/

/* this has an entry for every folder eventually in the UI, including subfolders */
static TREEFOLDER **treeFolders = 0;
static UINT numFolders  = 0;        		/* Number of folder in the folder array */
static UINT next_folder_id = MAX_FOLDERS;
static UINT folderArrayLength = 0;  		/* Size of the folder array */
static LPTREEFOLDER lpCurrentFolder = 0;    /* Currently selected folder */
static UINT nCurrentFolder = 0;     		/* Current folder ID */
static WNDPROC g_lpTreeWndProc = 0;   		/* for subclassing the TreeView */
static HIMAGELIST hTreeSmall = 0;         	/* TreeView Image list of icons */
/* this only has an entry for each TOP LEVEL extra folder + SubFolders*/
LPEXFOLDERDATA ExtraFolderData[MAX_EXTRA_FOLDERS * MAX_EXTRA_SUBFOLDERS];
static int numExtraFolders = 0;
static int numExtraIcons = 0;
static char *ExtraFolderIcons[MAX_EXTRA_FOLDERS];
// built in folders and filters
static LPCFOLDERDATA  g_lpFolderData;
static LPCFILTER_ITEM g_lpFilterList;

/***************************************************************************
    private function prototypes
 ***************************************************************************/

static bool	InitFolders(void);
static bool CreateTreeIcons(void);
static void	CreateAllChildFolders(void);
static bool AddFolder(LPTREEFOLDER lpFolder);
static LPTREEFOLDER NewFolder(const char *lpTitle, UINT nFolderId, int nParent, UINT nIconId, DWORD dwFlags);
static void DeleteFolder(LPTREEFOLDER lpFolder);
static LRESULT CALLBACK TreeWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static int InitExtraFolders(void);
static void FreeExtraFolders(void);
static void SetExtraIcons(char *name, int *id);
static bool TryAddExtraFolderAndChildren(int parent_index);
static bool TrySaveExtraFolder(LPTREEFOLDER lpFolder);
static void LoadExternalFolders(int parent_index, const char *fname, int id);
static void SaveExternalFolders(int parent_index, const char *fname);
static bool FilterAvailable(int driver_index);

/***************************************************************************
    Functions to build builtin folder lists
 ***************************************************************************/

static void CreateManufacturerFolders(int parent_index);
static void CreateYearFolders(int parent_index);
static void CreateSourceFolders(int parent_index);
static void CreateDeficiencyFolders(int parent_index);
static void CreateBIOSFolders(int parent_index);
static void CreateCPUFolders(int parent_index);
static void CreateSoundFolders(int parent_index);
static void CreateScreenFolders(int parent_index);
static void CreateFPSFolders(int parent_index);
static void CreateResolutionFolders(int parent_index);
static void CreateSaveStateFolders(int parent_index);
static void CreateDumpingFolders(int parent_index);

/***************************************************************************
    public structures
 ***************************************************************************/

extern const FOLDERDATA g_folderData[] =
{
// Modified Code Source (EKMAME)
/*******************************************************************************************************************************************************************************************/
	// commented-out lines have parts not defined elsewhere
	{"All Games",       "allgames",          FOLDER_ALLGAMES,     IDI_FOLDER_ALLGAMES,      0,             0,            0, NULL,                       NULL,                    true },
	{"Available",       "available",         FOLDER_AVAILABLE,    IDI_FOLDER_AVAILABLE,     F_AVAILABLE,   0,            0, NULL,                       FilterAvailable,         true },
	{"Unavailable",     "unavailable",       FOLDER_UNAVAILABLE,  IDI_FOLDER_UNAVAILABLE,   0,             F_AVAILABLE,  0, NULL,                       FilterAvailable,         false },
	{"BIOS",            "bios",              FOLDER_BIOS,         IDI_FOLDER_BIOS,          0,             0,            1, CreateBIOSFolders,          DriverIsBios,            true },
	{"CD Conversion",   "cd conversion", 	 FOLDER_NEOGEOCD,     IDI_FOLDER_NEOGEOCD,		0,			   0, 		     0, CreateNEOGEOCDFolders },
    {"Darksoft",		"darksoft",		     FOLDER_DARKSOFT,	  IDI_FOLDER_DARKSOFT, 	    0,			   0,            0,	CreateDARKSOFTFolders },
	{"Decrypted C & P", "decrypted c & p",   FOLDER_DECRYPTED,    IDI_FOLDER_DECRYPTED,		0,			   0, 		     0, CreateDECRYPTEDFolders },
    {"Demo Music",		"demo music",	     FOLDER_MUSIC, 		  IDI_FOLDER_MUSIC,		    0,			   0, 		     0, CreateMUSICFolders },
	{"Earlier",         "earlier", 		     FOLDER_EARLIER,	  IDI_FOLDER_EARLIER,	    0,			   0, 		     0, CreateEARLIERFolders },
	{"Hack", 		    "hack",			     FOLDER_HACK,		  IDI_FOLDER_HACK,		    0,			   0, 		     0, CreateHACKFolders },
	{"HomeBrew", 	    "homebrew",			 FOLDER_HOMEBREW,	  IDI_FOLDER_HOMEBREW,	    0,			   0, 		     0, CreateHOMEBREWFolders },
    {"MGD2",	        "mgd2",		         FOLDER_MGD2,	      IDI_FOLDER_MGD2,		    0,			   0, 		     0, CreateMGD2Folders },
	{"NeoSD",	  	    "neosd",			 FOLDER_NEOSD,		  IDI_FOLDER_NEOSD,		    0,			   0, 		     0, CreateNEOSDFolders },
	{"Parents",         "originals",         FOLDER_ORIGINAL,     IDI_FOLDER_ORIGINALS,     F_ORIGINALS,   F_CLONES,     0, NULL,                       DriverIsClone,           false },
	{"Clones",          "clones",            FOLDER_CLONES,       IDI_FOLDER_CLONES,        F_CLONES,      F_ORIGINALS,  0, NULL,                       DriverIsClone,           true },
	{"Source",          "source",            FOLDER_SOURCE,       IDI_FOLDER_SOURCE,        0,             0,            0, CreateSourceFolders },
	{"Vertical",        "vertical",          FOLDER_VERTICAL,     IDI_FOLDER_VERTICAL,      F_VERTICAL,    F_HORIZONTAL, 0, NULL,                       DriverIsVertical,        true },	
	{"Horizontal",      "horizontal",        FOLDER_HORIZONTAL,   IDI_FOLDER_HORIZONTAL,    F_HORIZONTAL,  F_VERTICAL,   0, NULL,                       DriverIsVertical,        false },	
	{"Working",         "working",           FOLDER_WORKING,      IDI_FOLDER_WORKING,       F_WORKING,     F_NONWORKING, 0, NULL,                       DriverIsBroken,          false },
	{"Not Working",     "nonworking",        FOLDER_NONWORKING,   IDI_FOLDER_NONWORKING,    F_NONWORKING,  F_WORKING,    0, NULL,                       DriverIsBroken,          true },
	{"Imperfect",       "imperfect",         FOLDER_DEFICIENCY,   IDI_FOLDER_IMPERFECT,     0,             0,            0, CreateDeficiencyFolders },
	{"Year",            "year",              FOLDER_YEAR,         IDI_FOLDER_YEAR,          0,             0,            0, CreateYearFolders },
	{"Manufacturer",    "manufacturer",      FOLDER_MANUFACTURER, IDI_FOLDER_MANUFACTURER,  0,             0,            0, CreateManufacturerFolders },
//	{"CHD",             "harddisk",          FOLDER_HARDDISK,     IDI_FOLDER_HARDDISK,      0,             0,            0, NULL,                       DriverIsHarddisk,        true },
	{"CPU",             "cpu",               FOLDER_CPU,          IDI_FOLDER_CPU,           0,             0,            1, CreateCPUFolders },
	{"Lightgun",        "lightgun",          FOLDER_LIGHTGUN,     IDI_FOLDER_LIGHTGUN,      0,             0,            0, NULL,                       DriverUsesLightGun,      true },
	{"Trackball",       "trackball",         FOLDER_TRACKBALL,    IDI_FOLDER_TRACKBALL,     0,             0,            0, NULL,                       DriverUsesTrackball,     true },
	{"Raster",          "raster",            FOLDER_RASTER,       IDI_FOLDER_RASTER,        F_RASTER,      F_VECTOR,     0, NULL,                       DriverIsVector,          false },
	{"Vector",          "vector",            FOLDER_VECTOR,       IDI_FOLDER_VECTOR,        F_VECTOR,      F_RASTER,     0, NULL,                       DriverIsVector,          true },
	{"Savestate",       "savestate",         FOLDER_SAVESTATE,    IDI_FOLDER_SAVESTATE,     0,             0,            0, CreateSaveStateFolders },
	{"Dumping Status",  "dumping",           FOLDER_DUMPING,      IDI_FOLDER_DUMP,          0,             0,            1, CreateDumpingFolders },
	{"Mechanical",      "mechanical",        FOLDER_MECHANICAL,   IDI_FOLDER_MECHANICAL,    0,             0,            0, NULL,                       DriverIsMechanical,      true },
	//{"Non Mechanical",  "nonmechanical",     FOLDER_NONMECHANICAL,IDI_FOLDER,               0,             0,            0, NULL,                       DriverIsMechanical,      FALSE },
	{"Refresh",         "refresh",           FOLDER_FPS,          IDI_FOLDER_FPS,           0,             0,            1, CreateFPSFolders },
	{"Resolution",      "resolution",        FOLDER_RESOLUTION,   IDI_FOLDER_RESOL,         0,             0,            1, CreateResolutionFolders },
	{"Sound",           "sound",             FOLDER_SOUND,        IDI_FOLDER_SOUND,         0,             0,            1, CreateSoundFolders },
	{"Samples",         "samples",           FOLDER_SAMPLES,      IDI_FOLDER_SAMPLES,       0,             0,            0, NULL,                       DriverUsesSamples,       true },
	{"Screens",         "screens",           FOLDER_SCREENS,      IDI_FOLDER_MONITOR,       0,             0,            0, CreateScreenFolders },
	//{"Stereo",          "stereo",            FOLDER_STEREO,       IDI_FOLDER,               0,             0,            0, NULL,                       DriverIsStereo,          TRUE },
	{ NULL }
/*******************************************************************************************************************************************************************************************/
};

/* list of filter/control Id pairs */
extern const FILTER_ITEM g_filterList[] =
{
	{ F_CLONES,       IDC_FILTER_CLONES,      DriverIsClone, 		true },
	{ F_NONWORKING,   IDC_FILTER_NONWORKING,  DriverIsBroken, 		true },
	{ F_UNAVAILABLE,  IDC_FILTER_UNAVAILABLE, FilterAvailable, 		false },
	{ F_RASTER,       IDC_FILTER_RASTER,      DriverIsVector, 		false },
	{ F_VECTOR,       IDC_FILTER_VECTOR,      DriverIsVector, 		true },
	{ F_ORIGINALS,    IDC_FILTER_ORIGINALS,   DriverIsClone, 		false },
	{ F_WORKING,      IDC_FILTER_WORKING,     DriverIsBroken, 		false },
	{ F_AVAILABLE,    IDC_FILTER_AVAILABLE,   FilterAvailable, 		true },
	{ F_HORIZONTAL,   IDC_FILTER_HORIZONTAL,  DriverIsVertical, 	false },
	{ F_VERTICAL,     IDC_FILTER_VERTICAL,    DriverIsVertical, 	true },
	{ 0 }
};

static const TREEICON treeIconNames[] =
{
	{ IDI_FOLDER_OPEN,         "foldopen" },
	{ IDI_FOLDER,              "folder" },
	{ IDI_FOLDER_ALLGAMES,     "allgames" },
	{ IDI_FOLDER_AVAILABLE,    "foldavail" },
	{ IDI_FOLDER_BIOS,         "foldcsb" },
	{ IDI_FOLDER_CLONES,       "foldclone" },
	{ IDI_FOLDER_CPU,          "foldcsb" },
	{ IDI_FOLDER_DUMP,         "foldcsb" },
	{ IDI_FOLDER_FPS,      	   "foldfps" },
	{ IDI_FOLDER_HARDDISK,     "harddisk" },
	{ IDI_FOLDER_HORIZONTAL,   "horz" },
	{ IDI_FOLDER_IMPERFECT,    "foldimp" },
	{ IDI_FOLDER_LIGHTGUN,     "foldgun" },
	{ IDI_FOLDER_MANUFACTURER, "foldmanu" },
	{ IDI_FOLDER_MECHANICAL,   "mechanical" },
	{ IDI_FOLDER_MONITOR,      "multimon" },
	{ IDI_FOLDER_NONWORKING,   "nonwork" },
	{ IDI_FOLDER_ORIGINALS,    "foldorig" },
	{ IDI_FOLDER_RASTER,       "foldrast" },
	{ IDI_FOLDER_RESOL,        "foldres" },
	{ IDI_FOLDER_SAMPLES,      "foldsamp" },
	{ IDI_FOLDER_SAVESTATE,    "savestate" },
	{ IDI_FOLDER_SOUND,        "foldcsb" },
	{ IDI_FOLDER_SOURCE,       "foldsrc" },
	{ IDI_SOURCE,              "source" },
//  Modified Code Source (Gaston90)
/**********************************************/
    { IDI_FOLDER_NEOGEOCD,     "fold_neogeocd" },
	{ IDI_FOLDER_DARKSOFT,	   "fold_darksoft"},
 	{ IDI_FOLDER_DECRYPTED,	   "fold_decrypted"},
 	{ IDI_FOLDER_MUSIC,		   "fold_music"},
	{ IDI_FOLDER_EARLIER,      "fold_earlier" },
 	{ IDI_FOLDER_HACK,		   "fold_hack"},
    { IDI_FOLDER_HOMEBREW,	   "fold_hb" },
    { IDI_FOLDER_MGD2,	       "fold_mgd2" },
    { IDI_FOLDER_NEOSD,	       "fold_neosd" },
/**********************************************/
	{ IDI_FOLDER_TRACKBALL,    "foldball" },
	{ IDI_FOLDER_UNAVAILABLE,  "foldunav" },
	{ IDI_FOLDER_VECTOR,       "foldvect" },
	{ IDI_FOLDER_VERTICAL,     "vert" },
	{ IDI_FOLDER_WORKING,      "working" },
	{ IDI_FOLDER_YEAR,         "foldyear" },
	{ IDI_BIOS,                "bios" },
	{ IDI_CHIP,                "chip" },
	{ IDI_MANUFACTURER,        "manufact" },
	{ IDI_MONITOR,             "monitor" },
	{ IDI_YEAR,                "year" },
};

/***************************************************************************
    public functions
 ***************************************************************************/

/* De-allocate all folder memory */
void FreeFolders(void)
{
	if (treeFolders != NULL)
	{
		if (numExtraFolders)
		{
			FreeExtraFolders();
			numFolders -= numExtraFolders;
		}

		for (int i = numFolders - 1; i >= 0; i--)
		{
			DeleteFolder(treeFolders[i]);
			treeFolders[i] = NULL;
			numFolders--;
		}

		free(treeFolders);
		treeFolders = NULL;
	}

	numFolders = 0;
}

/* Reset folder filters */
void ResetFilters(void)
{
	if (treeFolders != 0)
		for (int i = 0; i < (int)numFolders; i++)
			treeFolders[i]->m_dwFlags &= ~F_MASK;
}

void InitTree(LPCFOLDERDATA lpFolderData, LPCFILTER_ITEM lpFilterList)
{
	g_lpFolderData = lpFolderData;
	g_lpFilterList = lpFilterList;

	InitFolders();
	/* this will subclass the treeview (where WM_DRAWITEM gets sent for the header control) */
	LONG_PTR l = GetWindowLongPtr(GetTreeView(), GWLP_WNDPROC);
	g_lpTreeWndProc = (WNDPROC)l;
	SetWindowLongPtr(GetTreeView(), GWLP_WNDPROC, (LONG_PTR)TreeWndProc);
}

void SetCurrentFolder(LPTREEFOLDER lpFolder)
{
	lpCurrentFolder = (lpFolder == 0) ? treeFolders[0] : lpFolder;
	nCurrentFolder = (lpCurrentFolder) ? lpCurrentFolder->m_nFolderId : 0;
}

LPTREEFOLDER GetCurrentFolder(void)
{
	return lpCurrentFolder;
}

UINT GetCurrentFolderID(void)
{
	return nCurrentFolder;
}

int GetNumFolders(void)
{
	return numFolders;
}

LPTREEFOLDER GetFolder(UINT nFolder)
{
	return (nFolder < numFolders) ? treeFolders[nFolder] : NULL;
}

LPTREEFOLDER GetFolderByID(UINT nID)
{
	for (int i = 0; i < numFolders; i++)
	{
		if (treeFolders[i]->m_nFolderId == nID)
			return treeFolders[i];
	}

	return (LPTREEFOLDER)0;
}

void AddGame(LPTREEFOLDER lpFolder, UINT nGame)
{
	if (lpFolder)
		SetBit(lpFolder->m_lpGameBits, nGame);
}

void RemoveGame(LPTREEFOLDER lpFolder, UINT nGame)
{
	ClearBit(lpFolder->m_lpGameBits, nGame);
}

int FindGame(LPTREEFOLDER lpFolder, int nGame)
{
	return FindBit(lpFolder->m_lpGameBits, nGame, true);
}

// Called to re-associate games with folders
void ResetWhichGamesInFolders(void)
{
	for (int i = 0; i < numFolders; i++)
	{
		LPTREEFOLDER lpFolder = treeFolders[i];
		// setup the games in our built-in folders
		for (int k = 0; g_lpFolderData[k].m_lpTitle; k++)
		{
			if (lpFolder->m_nFolderId == g_lpFolderData[k].m_nFolderId)
			{
				if (g_lpFolderData[k].m_pfnQuery || g_lpFolderData[k].m_bExpectedResult)
				{
					SetAllBits(lpFolder->m_lpGameBits, false);

					for (int jj = 0; jj < driver_list::total(); jj++)
					{
						// invoke the query function
						bool b = g_lpFolderData[k].m_pfnQuery ? g_lpFolderData[k].m_pfnQuery(jj) : true;

						// if we expect false, flip the result
						if (!g_lpFolderData[k].m_bExpectedResult)
							b = !b;

						// if we like what we hear, add the game
						if (b)
							AddGame(lpFolder, jj);
					}
				}
				break;
			}
		}
	}
}

/* Used to build the GameList */
bool GameFiltered(int nGame, DWORD dwMask)
{
	LPTREEFOLDER lpFolder = GetCurrentFolder();

	//Filter out the Bioses on all Folders, except for the Bios Folder
	if(lpFolder && lpFolder->m_nFolderId != FOLDER_BIOS)
	{
		if(DriverIsBios(nGame))
			return true;
	}

	if(driver_list::driver(nGame).name[0] == '_')
		return true;

	// Filter games--return true if the game should be HIDDEN in this view
	if(GetFilterInherit())
	{
		if(lpFolder)
		{
			LPTREEFOLDER lpParent = GetFolder(lpFolder->m_nParent);

			if(lpParent)
			{
				/* Check the Parent Filters and inherit them on child,
                * The inherited filters don't display on the custom Filter Dialog for the Child folder
                * No need to promote all games to parent folder, works as is */
				dwMask |= lpParent->m_dwFlags;
			}
		}
	}

	if (strlen(GetSearchText()) && _stricmp(GetSearchText(), SEARCH_PROMPT))
	{
// Modified Code Source (EKMAME)
/*******************************************************************************/
		if (MyStrStrI(GetDescriptionByIndex(nGame, GetUsekoreanList()), GetSearchText()) == NULL &&
			MyStrStrI(GetGameNameByIndex(nGame,GetUsekoreanList()), GetSearchText()) == NULL )
			return true;
/*******************************************************************************/
	}

// Modified Code Source (EKMAME)
/*******************************************************************************/	
	if (MyStrStrI(GetDescriptionByIndex(nGame, GetUsekoreanList()), GetFilterText()) == NULL &&
		MyStrStrI(GetGameNameByIndex(nGame,GetUsekoreanList()), GetFilterText()) == NULL &&
		MyStrStrI(GetDriverFileName(nGame), GetFilterText()) == NULL &&
		MyStrStrI(GetGameManufactureByIndex(nGame,GetUsekoreanList()), GetFilterText()) == NULL)
		return true;
/*******************************************************************************/

	// Are there filters set on this folder?
	if ((dwMask & F_MASK) == 0)
		return false;

	// Filter out clones?
	if (dwMask & F_CLONES && DriverIsClone(nGame))
		return true;

	for (int i = 0; g_lpFilterList[i].m_dwFilterType; i++)
		if (dwMask & g_lpFilterList[i].m_dwFilterType)
			if (g_lpFilterList[i].m_pfnQuery(nGame) == g_lpFilterList[i].m_bExpectedResult)
				return true;

	return false;
}

/* Get the parent of game in this view */
bool GetParentFound(int nGame)
{
	LPTREEFOLDER lpFolder = GetCurrentFolder();

	if(lpFolder)
	{
		int nParentIndex = GetParentIndex(&driver_list::driver(nGame));

		/* return false if no parent is there in this view */
		if( nParentIndex == -1)
			return false;

		/* return false if the folder should be HIDDEN in this view */
		if (TestBit(lpFolder->m_lpGameBits, nParentIndex) == 0)
			return false;

		/* return false if the game should be HIDDEN in this view */
		if (GameFiltered(nParentIndex, lpFolder->m_dwFlags))
			return false;

		return true;
	}

	return false;
}

LPCFILTER_ITEM GetFilterList(void)
{
	return g_lpFilterList;
}

/***************************************************************************
    private functions
 ***************************************************************************/


static void CreateSourceFolders(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);
	
	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		const char *source = GetDriverFileName(jj);

		// look for an existant source treefolder for this game
		// (likely to be the previous one, so start at the end)
		for (i = numFolders - 1; i >= start_folder; i--)
		{
			if (strcmp(treeFolders[i]->m_lpTitle, source) == 0)
			{
				AddGame(treeFolders[i], jj);
				break;
			}
		}

		if (i == start_folder - 1)
		{
			// nope, it's a source file we haven't seen before, make it.
			lpTemp = NewFolder(source, next_folder_id++, parent_index, IDI_SOURCE, GetFolderFlags(numFolders));
			AddFolder(lpTemp);
			AddGame(lpTemp, jj);
		}
	}

	SetNumOptionFolders(-1);
}

static void CreateManufacturerFolders(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		const char *made = GetDriverGameManufacturer(jj);

		// look for an existant manufacturer treefolder for this game
		// (likely to be the previous one, so start at the end)
		for (i = numFolders - 1; i >= start_folder; i--)
		{
			if (strcmp(treeFolders[i]->m_lpTitle, made) == 0)
			{
				AddGame(treeFolders[i], jj);
				break;
			}
		}

		if (i == start_folder - 1)
		{
			// nope, it's a manufacturer we haven't seen before, make it.
			lpTemp = NewFolder(made, next_folder_id++, parent_index, IDI_MANUFACTURER, GetFolderFlags(numFolders));
			AddFolder(lpTemp);
			AddGame(lpTemp, jj);
		}
	}
}


static void CreateDeficiencyFolders(int parent_index)
{
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpWrongCol, lpImpCol, lpImpGraph, lpMissSnd, lpImpSnd, lpIncomplete, lpNoSndHw;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);
	// create our subfolders
	lpWrongCol = NewFolder("Wrong Colors", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpImpCol = NewFolder("Imperfect Colors", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpImpGraph = NewFolder("Imperfect Graphics", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpMissSnd = NewFolder("Missing Sound", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpImpSnd = NewFolder("Imperfect Sound", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpIncomplete = NewFolder("Incomplete Prototype", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpNoSndHw = NewFolder("No Sound Hardware", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	AddFolder(lpWrongCol);
	AddFolder(lpImpCol);
	AddFolder(lpImpGraph);
	AddFolder(lpMissSnd);
	AddFolder(lpImpSnd);
	AddFolder(lpIncomplete);
	AddFolder(lpNoSndHw);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		uint32_t cache = GetDriverCacheLower(jj);
		if (BIT(cache, 21))
			AddGame(lpWrongCol, jj);

		if (BIT(cache, 20))
			AddGame(lpImpCol, jj);

		if (BIT(cache, 18))
			AddGame(lpImpGraph, jj);

		if (BIT(cache, 17))
			AddGame(lpMissSnd, jj);

		if (BIT(cache, 16))
			AddGame(lpImpSnd, jj);

		if (BIT(cache, 15))
			AddGame(lpIncomplete, jj);

		if (BIT(cache, 13))
			AddGame(lpNoSndHw, jj);
	}
}



static void CreateYearFolders(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		const char *year = GetDriverGameYear(jj);

		// look for an extant year treefolder for this game
		// (likely to be the previous one, so start at the end)
		for (i = numFolders - 1; i >= start_folder; i--)
		{
			if (strcmp(treeFolders[i]->m_lpTitle, year) == 0)
			{
				AddGame(treeFolders[i], jj);
				break;
			}
		}

		if (i == start_folder - 1)
		{
			// nope, it's a year we haven't seen before, make it.
			lpTemp = NewFolder(year, next_folder_id++, parent_index, IDI_YEAR, GetFolderFlags(numFolders));
			AddFolder(lpTemp);
			AddGame(lpTemp, jj);
		}
	}
}



static void CreateBIOSFolders(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	const game_driver *drv;
	int nParentIndex = -1;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		if (DriverIsClone(jj))
		{
			nParentIndex = GetParentIndex(&driver_list::driver(jj));

			if (nParentIndex < 0) 
				return;

			drv = &driver_list::driver(nParentIndex);
		}
		else
			drv = &driver_list::driver(jj);

		nParentIndex = GetParentIndex(drv);

		if (nParentIndex < 0 || !GetDriverGameTitle(nParentIndex))
			continue;

		for (i = numFolders - 1; i >= start_folder; i--)
		{
			if (strcmp(treeFolders[i]->m_lpTitle, GetDriverGameTitle(nParentIndex)) == 0)
			{
				AddGame(treeFolders[i], jj);
				break;
			}
		}

		if (i == start_folder - 1)
		{
			lpTemp = NewFolder(GetDriverGameTitle(nParentIndex), next_folder_id++, parent_index, IDI_BIOS, GetFolderFlags(numFolders));
			AddFolder(lpTemp);
			AddGame(lpTemp, jj);
		}
	}
}



static void CreateScreenFoldersIni(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		char screen[4];
		snprintf(screen, std::size(screen), "%d", DriverNumScreens(jj));

		// look for an existant screen treefolder for this game
		// (likely to be the previous one, so start at the end)
		for (i = numFolders - 1; i >= start_folder; i--)
		{
			if (strcmp(treeFolders[i]->m_lpTitle, screen) == 0)
			{
				AddGame(treeFolders[i], jj);
				break;
			}
		}

		if (i == start_folder - 1)
		{
			// nope, it's a screen we haven't seen before, make it.
			lpTemp = NewFolder(screen, next_folder_id++, parent_index, IDI_MONITOR, GetFolderFlags(numFolders));
			AddFolder(lpTemp);
			AddGame(lpTemp, jj);
		}
	}
}



static void CreateCPUFoldersIni(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		machine_config config(driver_list::driver(jj), MameUIGlobal());

		// enumerate through all devices
		for (device_execute_interface &device : execute_interface_enumerator(config.root_device()))
		{
			// get the name
			const char *cpu = device.device().name();

			// look for an existant CPU treefolder for this game
			// (likely to be the previous one, so start at the end)
			for (i = numFolders - 1; i >= start_folder; i--)
			{
				if (strcmp(treeFolders[i]->m_lpTitle, cpu) == 0)
				{
					AddGame(treeFolders[i], jj);
					break;
				}
			}

			if (i == start_folder - 1)
			{
				// nope, it's a CPU we haven't seen before, make it.
				lpTemp = NewFolder(cpu, next_folder_id++, parent_index, IDI_CHIP, GetFolderFlags(numFolders));
				AddFolder(lpTemp);
				AddGame(lpTemp, jj);
			}
		}
	}
}



static void CreateSoundFoldersIni(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		machine_config config(driver_list::driver(jj), MameUIGlobal());

		// enumerate through all devices
		for (device_sound_interface &device : sound_interface_enumerator(config.root_device()))
		{
			// get the name
			const char *sound = device.device().name();

			// look for an existant sound chip treefolder for this game
			// (likely to be the previous one, so start at the end)
			for (i = numFolders - 1; i >= start_folder; i--)
			{
				if (strcmp(treeFolders[i]->m_lpTitle, sound) == 0)
				{
					AddGame(treeFolders[i], jj);
					break;
				}
			}

			if (i == start_folder - 1)
			{
				// nope, it's a sound chip we haven't seen before, make it.
				lpTemp = NewFolder(sound, next_folder_id++, parent_index, IDI_CHIP, GetFolderFlags(numFolders));
				AddFolder(lpTemp);
				AddGame(lpTemp, jj);
			}
		}
	}
}



static void CreateSaveStateFolders(int parent_index)
{
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpSupported, lpUnsupported;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits,false);
	// create our two subfolders
	lpSupported = NewFolder("Supported", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpUnsupported = NewFolder("Unsupported", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	AddFolder(lpSupported);
	AddFolder(lpUnsupported);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		if (DriverSupportsSaveState(jj))
			AddGame(lpSupported, jj);
		else
			AddGame(lpUnsupported, jj);
	}
}



static void CreateResolutionFoldersIni(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp, lpVectorH, lpVectorV, lpScreenless;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);
	// create our two subfolders
	lpVectorH = NewFolder("Vector (H)", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpVectorV = NewFolder("Vector (V)", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpScreenless = NewFolder("Screenless", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	AddFolder(lpVectorH);
	AddFolder(lpVectorV);
	AddFolder(lpScreenless);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		machine_config config(driver_list::driver(jj), MameUIGlobal());
		char res[32];

		if (DriverIsVector(jj))
		{
			if (DriverIsVertical(jj))
			{
				AddGame(lpVectorV, jj);
				continue;
			}
			else
			{
				AddGame(lpVectorH, jj);
				continue;
			}
		}

		const screen_device *screen = screen_device_enumerator(config.root_device()).first();

		if (screen == nullptr)
		{
			AddGame(lpScreenless, jj);
			continue;
		}

		const rectangle &visarea = screen->visible_area();

		if (DriverIsVertical(jj))
			snprintf(res, std::size(res), "%d x %d (V)", visarea.width(), visarea.height());
		else
			snprintf(res, std::size(res), "%d x %d (H)", visarea.width(), visarea.height());

		// look for an existant resolution treefolder for this game
		// (likely to be the previous one, so start at the end)
		for (i = numFolders - 1; i >= start_folder; i--)
		{
			if (strcmp(treeFolders[i]->m_lpTitle, res) == 0)
			{
				AddGame(treeFolders[i], jj);
				break;
			}
		}

		if (i == start_folder - 1)
		{
			// nope, it's a resolution we haven't seen before, make it.
			lpTemp = NewFolder(res, next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
			AddFolder(lpTemp);
			AddGame(lpTemp, jj);
		}
	}
}



static void CreateFPSFoldersIni(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp, lpVector, lpScreenless;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);
	// create our two subfolders
	lpVector = NewFolder("Vector", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpScreenless = NewFolder("Screenless", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	AddFolder(lpVector);
	AddFolder(lpScreenless);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		machine_config config(driver_list::driver(jj), MameUIGlobal());
		char fps[16];
		
		if (DriverIsVector(jj))
		{
			AddGame(lpVector, jj);
			continue;
		}

		const screen_device *screen = screen_device_enumerator(config.root_device()).first();

		if (screen == nullptr)
		{
			AddGame(lpScreenless, jj);
			continue;
		}

		snprintf(fps, std::size(fps), "%f Hz", ATTOSECONDS_TO_HZ(screen->refresh_attoseconds()));

		// look for an existant refresh treefolder for this game
		// (likely to be the previous one, so start at the end)
		for (i = numFolders - 1; i >= start_folder; i--)
		{
			if (strcmp(treeFolders[i]->m_lpTitle, fps) == 0)
			{
				AddGame(treeFolders[i], jj);
				break;
			}
		}

		if (i == start_folder - 1)
		{
			// nope, it's a refresh we haven't seen before, make it.
			lpTemp = NewFolder(fps, next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
			AddFolder(lpTemp);
			AddGame(lpTemp, jj);
		}
	}
}


void CreateDumpingFoldersIni(int parent_index)
{
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpBadDump, lpNoDump, lpGoodDump;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits,false);
	// create our two subfolders
	lpNoDump = NewFolder("No Dump", next_folder_id, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpBadDump = NewFolder("Bad Dump", next_folder_id, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpGoodDump = NewFolder("Good Dump", next_folder_id, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	AddFolder(lpNoDump);
	AddFolder(lpBadDump);
	AddFolder(lpGoodDump);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		machine_config config(driver_list::driver(jj), MameUIGlobal());
		bool bBadDump = false;
		bool bNoDump = false;

		if (!DriverUsesRoms(jj))
			continue;

		for (device_t &device : device_enumerator(config.root_device()))
		{
			for (const rom_entry *region = rom_first_region(device); region != nullptr; region = rom_next_region(region))
			{
				for (const rom_entry *rom = rom_first_file(region); rom != nullptr; rom = rom_next_file(rom))
				{
					if (ROMREGION_ISROMDATA(region) || ROMREGION_ISDISKDATA(region))
					{
						util::hash_collection hashes(rom->hashdata());
						
						if (hashes.flag(util::hash_collection::FLAG_NO_DUMP))
							bNoDump = true;
						
						if (hashes.flag(util::hash_collection::FLAG_BAD_DUMP))
							bBadDump = true;
					}
				}
			}
		}

		if (bNoDump)
		{
			AddGame(lpNoDump, jj);
			continue;
		}

		if (bBadDump)
		{
			AddGame(lpBadDump, jj);
			continue;
		}

		AddGame(lpGoodDump, jj);
	}
}


static void CreateCPUFolders(int parent_index)
{
	const char *fname = "cpu.ini";

	if (RequiredDriverCache())
	{
		CreateCPUFoldersIni(parent_index);
		SaveExternalFolders(parent_index, fname);
	}
	else
		LoadExternalFolders(parent_index, fname, IDI_CHIP);

	SendMessage(GetProgressBar(), PBM_SETPOS, 20, 0);
}



static void CreateSoundFolders(int parent_index)
{
	const char *fname = "sound.ini";

	if (RequiredDriverCache())
	{
		CreateSoundFoldersIni(parent_index);
		SaveExternalFolders(parent_index, fname);
	}
	else
		LoadExternalFolders(parent_index, fname, IDI_CHIP);

	SendMessage(GetProgressBar(), PBM_SETPOS, 95, 0);
}




static void CreateScreenFolders(int parent_index)
{
	const char *fname = "screen.ini";

	if (RequiredDriverCache())
	{
		CreateScreenFoldersIni(parent_index);
		SaveExternalFolders(parent_index, fname);
	}
	else
		LoadExternalFolders(parent_index, fname, IDI_MONITOR);

	SendMessage(GetProgressBar(), PBM_SETPOS, 80, 0);
}



static void CreateResolutionFolders(int parent_index)
{
	const char *fname = "resolution.ini";

	if (RequiredDriverCache())
	{
		CreateResolutionFoldersIni(parent_index);
		SaveExternalFolders(parent_index, fname);
	}
	else
		LoadExternalFolders(parent_index, fname, IDI_FOLDER);

	SendMessage(GetProgressBar(), PBM_SETPOS, 65, 0);
}



static void CreateFPSFolders(int parent_index)
{
	const char *fname = "refresh.ini";

	if (RequiredDriverCache())
	{
		CreateFPSFoldersIni(parent_index);
		SaveExternalFolders(parent_index, fname);
	}
	else
		LoadExternalFolders(parent_index, fname, IDI_FOLDER);

	SendMessage(GetProgressBar(), PBM_SETPOS, 50, 0);
}



static void CreateDumpingFolders(int parent_index)
{
	const char *fname = "dumping.ini";

	if (RequiredDriverCache())
	{
		CreateDumpingFoldersIni(parent_index);
		SaveExternalFolders(parent_index, fname);
	}
	else
		LoadExternalFolders(parent_index, fname, IDI_FOLDER);

	SendMessage(GetProgressBar(), PBM_SETPOS, 35, 0);
}



static void LoadExternalFolders(int parent_index, const char *fname, int id)
{
	char readbuf[256];
	char filename[MAX_PATH];
	char *name = NULL;
	LPTREEFOLDER lpTemp = NULL;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];

	int current_id = lpFolder->m_nFolderId;
	snprintf(filename, std::size(filename), "%s\\%s", GetGuiDir(), fname);
	FILE *f = fopen(filename, "r");
 
	if (f == NULL)
		return;

	while (fgets(readbuf, 256, f))
	{
		//do we have [...] ?
		if (readbuf[0] == '[')
		{
			char *p = strchr(readbuf, ']');
			
			if (p == NULL)
				continue;

			*p = '\0';
			name = &readbuf[1];

			//is it [FOLDER_SETTINGS]?
			if (strcmp(name, "FOLDER_SETTINGS") == 0)
			{
				current_id = -1;
				continue;
			}
			else
			{
				//is it [ROOT_FOLDER]?
				if (!strcmp(name, "ROOT_FOLDER"))
				{
					current_id = lpFolder->m_nFolderId;
					lpTemp = lpFolder;
				}
				else
				{
					current_id = next_folder_id++;
					lpTemp = NewFolder(name, current_id, parent_index, id, GetFolderFlags(numFolders));
					AddFolder(lpTemp);
				}
			}
		}
		else if (current_id != -1)
		{
			//string on a line by itself -- game name
			name = strtok(readbuf, " \t\r\n");

			if (name == NULL)
			{
				current_id = -1;
				continue;
			}

			AddGame(lpTemp, GetGameNameIndex(name));
		}
	}

	fclose(f);
}



static void SaveExternalFolders(int parent_index, const char *fname)
{
	int i = 0;
	char filename[MAX_PATH];
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	TREEFOLDER *folder_data;

	snprintf(filename, std::size(filename), "%s\\%s", GetGuiDir(), fname);
	wchar_t *temp = win_wstring_from_utf8(GetGuiDir());
	CreateDirectory(temp, NULL);
	free(temp);
	FILE *f = fopen(filename, "w");

	if (f == NULL)
		return;

	fprintf(f, "[FOLDER_SETTINGS]\n");
	fprintf(f, "RootFolderIcon custom\n");
	fprintf(f, "SubFolderIcon custom\n");

	//need to loop over all our TREEFOLDERs--first the root one, then each child.
	//start with the root
	folder_data = lpFolder;
	fprintf(f, "\n[ROOT_FOLDER]\n");

	for (i = 0; i < driver_list::total(); i++)
	{
		if (TestBit(folder_data->m_lpGameBits, i))
			fprintf(f, "%s\n", GetDriverGameName(i));
	}

	//look through the custom folders for ones with our root as parent
	for (int jj = 0; jj < numFolders; jj++)
	{
		folder_data = treeFolders[jj];

		if (folder_data->m_nParent >= 0 && treeFolders[folder_data->m_nParent] == lpFolder)
		{
			fprintf(f, "\n[%s]\n", folder_data->m_lpTitle);

			for (i = 0; i < driver_list::total(); i++)
			{
				if (TestBit(folder_data->m_lpGameBits, i))
					fprintf(f, "%s\n", GetDriverGameName(i));
			}
		}
	}

	fclose(f);
}


// creates child folders of all the top level folders, including custom ones
void CreateAllChildFolders(void)
{
	int num_top_level_folders = numFolders;

	for (int i = 0; i < num_top_level_folders; i++)
	{
		LPTREEFOLDER lpFolder = treeFolders[i];
		LPCFOLDERDATA lpFolderData = NULL;

		for (int j = 0; g_lpFolderData[j].m_lpTitle; j++)
		{
			if (g_lpFolderData[j].m_nFolderId == lpFolder->m_nFolderId)
			{
				lpFolderData = &g_lpFolderData[j];
				break;
			}
		}

		if (lpFolderData)
		{
			if (lpFolderData->m_pfnCreateFolders)
				lpFolderData->m_pfnCreateFolders(i);
		}
		else
		{
			if ((lpFolder->m_dwFlags & F_CUSTOM) == 0)
				continue;

			// load the extra folder files, which also adds children
			if (TryAddExtraFolderAndChildren(i) == false)
				lpFolder->m_nFolderId = FOLDER_NONE;
		}
	}
}

// adds these folders to the treeview
void ResetTreeViewFolders(void)
{
	HWND hTreeView = GetTreeView();
	TVITEM tvi;
	TVINSERTSTRUCT tvs;

	// currently "cached" parent
	HTREEITEM hti_parent = NULL;
	int index_parent = -1;

	(void)TreeView_DeleteAllItems(hTreeView);
	tvs.hInsertAfter = TVI_LAST; // main items inserted according to g_folderData[] array

	for (int i = 0; i < numFolders; i++)
	{
		LPTREEFOLDER lpFolder = treeFolders[i];

		if (lpFolder->m_nParent == -1)
		{
			if (lpFolder->m_nFolderId < MAX_FOLDERS)
			{
				// it's a built in folder, let's see if we should show it
				if (GetShowFolder(lpFolder->m_nFolderId) == false)
					continue;
			}

			tvi.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
			tvs.hParent = TVI_ROOT;
			tvi.pszText = lpFolder->m_lptTitle;
			tvi.lParam = (LPARAM)lpFolder;
			tvi.iImage = GetTreeViewIconIndex(lpFolder->m_nIconId);
			tvi.iSelectedImage = 0;
			tvs.item = tvi;

			// Add root branch
			hti_parent = TreeView_InsertItem(hTreeView, &tvs);
			continue;
		}

		// not a top level branch, so look for parent
		if (treeFolders[i]->m_nParent != index_parent)
		{
			hti_parent = TreeView_GetRoot(hTreeView);

			while (1)
			{
				if (hti_parent == NULL)
					// couldn't find parent folder, so it's a built-in but
					// not shown folder
					break;

				tvi.hItem = hti_parent;
				tvi.mask = TVIF_PARAM;

				(void)TreeView_GetItem(hTreeView, &tvi);

				if (((LPTREEFOLDER)tvi.lParam) == treeFolders[treeFolders[i]->m_nParent])
					break;

				hti_parent = TreeView_GetNextSibling(hTreeView, hti_parent);
			}

			// if parent is not shown, then don't show the child either obviously!
			if (hti_parent == NULL)
				continue;

			index_parent = treeFolders[i]->m_nParent;
		}

		tvi.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		tvs.hParent = hti_parent;
		tvi.iImage = GetTreeViewIconIndex(treeFolders[i]->m_nIconId);
		tvi.iSelectedImage = 0;
		tvi.pszText = treeFolders[i]->m_lptTitle;
		tvi.lParam = (LPARAM)treeFolders[i];
		tvs.item = tvi;

		// Add it to this tree branch
		tvs.hInsertAfter = TVI_SORT; // sub items always sorted
		(void)TreeView_InsertItem(hTreeView, &tvs);
		tvs.hInsertAfter = TVI_LAST; // restore for next main item
	}
}

void SelectTreeViewFolder(int folder_id)
{
	HWND hTreeView = GetTreeView();
	HTREEITEM hti = TreeView_GetRoot(hTreeView);
	TVITEM tvi;

	memset(&tvi, 0, sizeof(TVITEM));

	while (hti != NULL)
	{
		tvi.hItem = hti;
		tvi.mask = TVIF_PARAM;

		(void)TreeView_GetItem(hTreeView, &tvi);

		if (((LPTREEFOLDER)tvi.lParam)->m_nFolderId == folder_id)
		{
			(void)TreeView_SelectItem(hTreeView,tvi.hItem);
			SetCurrentFolder((LPTREEFOLDER)tvi.lParam);
			return;
		}

		HTREEITEM hti_next = TreeView_GetChild(hTreeView, hti);

		if (hti_next == NULL)
		{
			hti_next = TreeView_GetNextSibling(hTreeView, hti);

			if (hti_next == NULL)
			{
				hti_next = TreeView_GetParent(hTreeView, hti);

				if (hti_next != NULL)
					hti_next = TreeView_GetNextSibling(hTreeView, hti_next);
			}
		}

		hti = hti_next;
	}

	// could not find folder to select
	// make sure we select something
	tvi.hItem = TreeView_GetRoot(hTreeView);
	tvi.mask = TVIF_PARAM;

	(void)TreeView_GetItem(hTreeView, &tvi);
	(void)TreeView_SelectItem(hTreeView, tvi.hItem);
	SetCurrentFolder((LPTREEFOLDER)tvi.lParam);

}

/*
 * Does this folder have an INI associated with it?
 * Currently only true for FOLDER_VECTOR and children
 * of FOLDER_SOURCE.
 */
static bool FolderHasIni(LPTREEFOLDER lpFolder) 
{
	if (FOLDER_RASTER == lpFolder->m_nFolderId || FOLDER_VECTOR == lpFolder->m_nFolderId ||
		FOLDER_VERTICAL == lpFolder->m_nFolderId || FOLDER_HORIZONTAL == lpFolder->m_nFolderId) 
			return true;

	if (lpFolder->m_nParent != -1 && FOLDER_SOURCE == treeFolders[lpFolder->m_nParent]->m_nFolderId) 
		return true;

	return false;
}


/* Add a folder to the list.  Does not allocate */
static bool AddFolder(LPTREEFOLDER lpFolder)
{
	TREEFOLDER **tmpTree = NULL;
	UINT oldFolderArrayLength = folderArrayLength;

	if (numFolders + 1 >= folderArrayLength)
	{
		folderArrayLength += 500;
		tmpTree = (TREEFOLDER **)malloc(sizeof(TREEFOLDER **) * folderArrayLength);
		memcpy(tmpTree, treeFolders, sizeof(TREEFOLDER **) * oldFolderArrayLength);

		if (treeFolders) 
			free(treeFolders);

		treeFolders = tmpTree;
	}

	/* Is there an folder.ini that can be edited? */
	if (FolderHasIni(lpFolder)) 
		lpFolder->m_dwFlags |= F_INIEDIT;

	treeFolders[numFolders] = lpFolder;
	numFolders++;
	return true;
}

/* Allocate and initialize a NEW TREEFOLDER */
static LPTREEFOLDER NewFolder(const char *lpTitle, UINT nFolderId, int nParent, UINT nIconId, DWORD dwFlags)
{
	LPTREEFOLDER lpFolder = (LPTREEFOLDER)malloc(sizeof(TREEFOLDER));
	memset(lpFolder, 0, sizeof(TREEFOLDER));
	lpFolder->m_lpTitle = (char *)malloc(strlen(lpTitle) + 1);
	strcpy((char *)lpFolder->m_lpTitle, lpTitle);
	lpFolder->m_lptTitle = win_wstring_from_utf8(lpFolder->m_lpTitle);
	lpFolder->m_lpGameBits = NewBits(driver_list::total());
	lpFolder->m_nFolderId = nFolderId;
	lpFolder->m_nParent = nParent;
	lpFolder->m_nIconId = nIconId;
	lpFolder->m_dwFlags = dwFlags;
	return lpFolder;
}

/* Deallocate the passed in LPTREEFOLDER */
static void DeleteFolder(LPTREEFOLDER lpFolder)
{
	if (lpFolder)
	{
		if (lpFolder->m_lpGameBits)
		{
			DeleteBits(lpFolder->m_lpGameBits);
			lpFolder->m_lpGameBits = 0;
		}

		free(lpFolder->m_lptTitle);
		lpFolder->m_lptTitle = 0;
		free(lpFolder->m_lpTitle);
		lpFolder->m_lpTitle = 0;
		free(lpFolder);
	}
}

/* Can be called to re-initialize the array of treeFolders */
static bool InitFolders(void)
{
	int i = 0;
	DWORD dwFolderFlags = 0;

	if (treeFolders)
	{
		for (i = numFolders - 1; i >= 0; i--)
		{
			DeleteFolder(treeFolders[i]);
			treeFolders[i] = 0;
			numFolders--;
		}
	}

	numFolders = 0;

	if (folderArrayLength == 0)
	{
		folderArrayLength = 200;
		treeFolders = (TREEFOLDER **)malloc(sizeof(TREEFOLDER **) * folderArrayLength);

		if (!treeFolders)
		{
			folderArrayLength = 0;
			return 0;
		}
		else
			memset(treeFolders, 0, sizeof(TREEFOLDER **) * folderArrayLength);
	}
	
	// built-in top level folders
	for (i = 0; g_lpFolderData[i].m_lpTitle; i++)
	{
		LPCFOLDERDATA fData = &g_lpFolderData[i];
		/* get the saved folder flags */
		dwFolderFlags = GetFolderFlags(numFolders);
		/* create the folder */
		AddFolder(NewFolder(fData->m_lpTitle, fData->m_nFolderId, -1, fData->m_nIconId, dwFolderFlags));
	}

	numExtraFolders = InitExtraFolders();

	for (i = 0; i < numExtraFolders; i++)
	{
		LPEXFOLDERDATA  fExData = ExtraFolderData[i];
		// OR in the saved folder flags
		dwFolderFlags = fExData->m_dwFlags | GetFolderFlags(numFolders);
		// create the folder
		AddFolder(NewFolder(fExData->m_szTitle, fExData->m_nFolderId, fExData->m_nParent, fExData->m_nIconId, dwFolderFlags));
	}

	CreateAllChildFolders();
	CreateTreeIcons();
	ResetWhichGamesInFolders();
	ResetTreeViewFolders();
	SelectTreeViewFolder(GetSavedFolderID());
	LoadFolderFlags();
	return true;
}

// create iconlist and Treeview control
static bool CreateTreeIcons(void)
{
	HICON hIcon = NULL;
	HINSTANCE hInst = GetModuleHandle(NULL);
	int numIcons = ICON_MAX + numExtraIcons;

	hTreeSmall = ImageList_Create (16, 16, ILC_COLORDDB | ILC_MASK, numIcons, numIcons);

	for (int i = 0; i < ICON_MAX; i++)
	{
		hIcon = LoadIconFromFile(treeIconNames[i].lpName);

		if (!hIcon)
			hIcon = LoadIcon(hInst, MAKEINTRESOURCE(treeIconNames[i].nResourceID));

		if (ImageList_AddIcon(hTreeSmall, hIcon) == -1)
		{
			ErrorMessageBox("Error creating icon on regular folder, %i %i", i, hIcon != NULL);
			return false;
		}
	}

	for (int i = 0; i < numExtraIcons; i++)
	{
		if ((hIcon = LoadIconFromFile(ExtraFolderIcons[i])) == 0)
			hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_FOLDER));

		if (ImageList_AddIcon(hTreeSmall, hIcon) == -1)
		{
			ErrorMessageBox("Error creating icon on extra folder, %i %i", i, hIcon != NULL);
			return false;
		}
	}

	// Be sure that all the small icons were added.
	if (ImageList_GetImageCount(hTreeSmall) < numIcons)
	{
		ErrorMessageBox("Error with icon list--too few images.  %i %i", ImageList_GetImageCount(hTreeSmall), numIcons);
		return false;
	}

	// Be sure that all the small icons were added.
	if (ImageList_GetImageCount (hTreeSmall) < ICON_MAX)
	{
		ErrorMessageBox("Error with icon list--too few images.  %i < %i", ImageList_GetImageCount(hTreeSmall), ICON_MAX);
		return false;
	}

	// Associate the image lists with the list view control.
	(void)TreeView_SetImageList(GetTreeView(), hTreeSmall, TVSIL_NORMAL);
	return true;
}

/* Header code - Directional Arrows */
static LRESULT CALLBACK TreeWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_KEYDOWN :
			if (wParam == VK_F2)
			{
				if (lpCurrentFolder->m_dwFlags & F_CUSTOM)
				{
					(void)TreeView_EditLabel(hWnd, TreeView_GetSelection(hWnd));
					return true;
				}
			}

			break;
	}

	/* message not handled */
	return CallWindowProc(g_lpTreeWndProc, hWnd, uMsg, wParam, lParam);
}

/*
 * Filter code - should be moved to filter.c/filter.h
 * Added 01/09/99 - MSH <mhaaland@hypertech.com>
 */

/* find a FOLDERDATA by folderID */
LPCFOLDERDATA FindFilter(DWORD folderID)
{
	for (int i = 0; g_lpFolderData[i].m_lpTitle; i++)
		if (g_lpFolderData[i].m_nFolderId == folderID)
			return &g_lpFolderData[i];

	return (LPFOLDERDATA) 0;
}

LPTREEFOLDER GetFolderByName(int nParentId, const char *pszFolderName)
{
	//First Get the Parent TreeviewItem
	//Enumerate Children
	for (int i = 0; i < numFolders; i++)
	{
		if (!strcmp(treeFolders[i]->m_lpTitle, pszFolderName))
		{
			int nParent = treeFolders[i]->m_nParent;

			if ((nParent >= 0) && treeFolders[nParent]->m_nFolderId == nParentId)
				return treeFolders[i];
		}
	}

	return NULL;
}

static int InitExtraFolders(void)
{
	WIN32_FIND_DATA FindFileData;
	int count = 0;
	char buf[256];
	char path[MAX_PATH];
	const char *dir = GetFolderDir();

	memset(ExtraFolderData, 0, (MAX_EXTRA_FOLDERS * MAX_EXTRA_SUBFOLDERS)* sizeof(LPEXFOLDERDATA));

	// Why create the directory if it doesn't exist, just return 0 folders.
	if (osd::directory::open(dir) == nullptr)
		return 0;

	snprintf(path, std::size(path), "%s\\*.*", dir);
	HANDLE hFind = winui_find_first_file_utf8(path, &FindFileData);

	for (int i = 0; i < MAX_EXTRA_FOLDERS; i++)
	{
		ExtraFolderIcons[i] = NULL;
	}

	numExtraIcons = 0;

	if (hFind != INVALID_HANDLE_VALUE)
	{
		while (FindNextFile (hFind, &FindFileData) != 0)
		{
			char *file = win_utf8_from_wstring(FindFileData.cFileName);
			char inifile[MAX_PATH];

			memset(&inifile, 0, sizeof(inifile));
			snprintf(inifile, std::size(inifile), "%s\\%s", dir, file);
			FILE *readfile = fopen(inifile, "r");

			if (readfile != NULL)
			{
				int icon[2] = { 0, 0 };

				while (fgets(buf, 256, readfile))
				{
					if (buf[0] == '[')
					{
						char *p = strchr(buf, ']');

						if (p == NULL)
							continue;

						*p = '\0';
						char *name = &buf[1];

						if (!strcmp(name, "FOLDER_SETTINGS"))
						{
							while (fgets(buf, 256, readfile))
							{
								name = strtok(buf, " =\r\n");

								if (name == NULL)
									break;

								if (!strcmp(name, "RootFolderIcon"))
								{
									name = strtok(NULL, " =\r\n");

									if (name != NULL)
										SetExtraIcons(name, &icon[0]);
								}
								if (!strcmp(name, "SubFolderIcon"))
								{
									name = strtok(NULL, " =\r\n");

									if (name != NULL)
										SetExtraIcons(name, &icon[1]);
								}
							}

							break;
						}
					}
				}

				fclose(readfile);
				strcpy(buf, file);
				char *ext = strrchr(buf, '.');
				free(file);

				if (ext && *(ext + 1) && !core_stricmp(ext + 1, "ini"))
				{
					ExtraFolderData[count] =(EXFOLDERDATA*) malloc(sizeof(EXFOLDERDATA));

					if (ExtraFolderData[count])
					{
						*ext = '\0';
						memset(ExtraFolderData[count], 0, sizeof(EXFOLDERDATA));
						strncpy(ExtraFolderData[count]->m_szTitle, buf, 63);
						ExtraFolderData[count]->m_nFolderId = next_folder_id++;
						ExtraFolderData[count]->m_nParent = -1;
						ExtraFolderData[count]->m_dwFlags = F_CUSTOM;
						ExtraFolderData[count]->m_nIconId = icon[0] ? -icon[0] : IDI_FOLDER;
						ExtraFolderData[count]->m_nSubIconId = icon[1] ? -icon[1] : IDI_FOLDER;
						count++;
					}
				}
			}
		}
	}

	return count;
}

void FreeExtraFolders(void)
{
	for (int i = 0; i < numExtraFolders; i++)
	{
		if (ExtraFolderData[i])
		{
			free(ExtraFolderData[i]);
			ExtraFolderData[i] = NULL;
		}
	}

	for (int i = 0; i < numExtraIcons; i++)
	{
		free(ExtraFolderIcons[i]);
	}

	numExtraIcons = 0;
}


static void SetExtraIcons(char *name, int *id)
{
	char *p = strchr(name, '.');

	if (p != NULL)
		*p = '\0';

	ExtraFolderIcons[numExtraIcons] = (char*)malloc(strlen(name) + 1);

	if (ExtraFolderIcons[numExtraIcons])
	{
		*id = ICON_MAX + numExtraIcons;
		strcpy(ExtraFolderIcons[numExtraIcons], name);
		numExtraIcons++;
	}
}


// Called to add child folders of the top level extra folders already created
bool TryAddExtraFolderAndChildren(int parent_index)
{
	char fname[MAX_PATH];
	char readbuf[256];
	char *name = NULL;
	LPTREEFOLDER lpTemp = NULL;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];

	int current_id = lpFolder->m_nFolderId;
	int id = lpFolder->m_nFolderId - MAX_FOLDERS;
	snprintf(fname, std::size(fname), "%s\\%s.ini", GetFolderDir(), ExtraFolderData[id]->m_szTitle);
	FILE *f = fopen(fname, "r");
 
	if (f == NULL)
		return false;

	while (fgets(readbuf, 256, f))
	{
		/* do we have [...] ? */
		if (readbuf[0] == '[')
		{
			char *p = strchr(readbuf, ']');

			if (p == NULL)
				continue;

			*p = '\0';
			name = &readbuf[1];

			/* is it [FOLDER_SETTINGS]? */
			if (strcmp(name, "FOLDER_SETTINGS") == 0)
			{
				current_id = -1;
				continue;
			}
			else
			{
				/* is it [ROOT_FOLDER]? */
				if (!strcmp(name, "ROOT_FOLDER"))
				{
					current_id = lpFolder->m_nFolderId;
					lpTemp = lpFolder;
				}
				else
				{
					/* must be [folder name] */
					current_id = next_folder_id++;
					/* create a new folder with this name,
					and the flags for this folder as read from the registry */
					lpTemp = NewFolder(name, current_id, parent_index, ExtraFolderData[id]->m_nSubIconId, GetFolderFlags(numFolders) | F_CUSTOM);
					ExtraFolderData[current_id] = (EXFOLDERDATA*)malloc(sizeof(EXFOLDERDATA));
					memset(ExtraFolderData[current_id], 0, sizeof(EXFOLDERDATA));
					ExtraFolderData[current_id]->m_nFolderId = current_id - MAX_EXTRA_FOLDERS;
					ExtraFolderData[current_id]->m_nIconId = ExtraFolderData[id]->m_nSubIconId;
					ExtraFolderData[current_id]->m_nParent = ExtraFolderData[id]->m_nFolderId;
					ExtraFolderData[current_id]->m_nSubIconId = -1;
					strcpy(ExtraFolderData[current_id]->m_szTitle, name);
					ExtraFolderData[current_id]->m_dwFlags = ExtraFolderData[id]->m_dwFlags;
					AddFolder(lpTemp);
				}
			}
		}
		else if (current_id != -1)
		{
			/* string on a line by itself -- game name */
			name = strtok(readbuf, " \t\r\n");

			if (name == NULL)
			{
				current_id = -1;
				continue;
			}

			/* IMPORTANT: This assumes that all driver names are lowercase! */
			for (int i = 0; name[i]; i++)
				name[i] = tolower(name[i]);

			if (lpTemp == NULL)
			{
				ErrorMessageBox("Error parsing %s: missing [folder name] or [ROOT_FOLDER]", fname);
				current_id = lpFolder->m_nFolderId;
				lpTemp = lpFolder;
			}

			AddGame(lpTemp, GetGameNameIndex(name));
		}
	}

	fclose(f);
	return true;
}


void GetFolders(TREEFOLDER ***folders,int *num_folders)
{
	*folders = treeFolders;
	*num_folders = numFolders;
}

static bool TryRenameCustomFolderIni(LPTREEFOLDER lpFolder, const char *old_name, const char *new_name)
{
	char filename[MAX_PATH];
	char new_filename[MAX_PATH];

	if (lpFolder->m_nParent >= 0)
	{
		//it is a custom SubFolder
		LPTREEFOLDER lpParent = GetFolder(lpFolder->m_nParent);

		if(lpParent)
		{
			snprintf(filename, std::size(filename), "%s\\%s\\%s.ini", GetIniDir(), lpParent->m_lpTitle, old_name);
			snprintf(new_filename, std::size(new_filename), "%s\\%s\\%s.ini", GetIniDir(), lpParent->m_lpTitle, new_name);
			winui_move_file_utf8(filename, new_filename);
		}
	}
	else
	{
		//Rename the File, if it exists
		snprintf(filename, std::size(filename), "%s\\%s.ini", GetIniDir(), old_name);
		snprintf(new_filename, std::size(new_filename), "%s\\%s.ini", GetIniDir(), new_name);
		winui_move_file_utf8(filename, new_filename);
		//Rename the Directory, if it exists
		snprintf(filename, std::size(filename), "%s\\%s", GetIniDir(), old_name);
		snprintf(new_filename, std::size(new_filename), "%s\\%s", GetIniDir(), new_name);
		winui_move_file_utf8(filename, new_filename);
	}

	return true;
}

bool TryRenameCustomFolder(LPTREEFOLDER lpFolder, const char *new_name)
{
	char filename[MAX_PATH];
	char new_filename[MAX_PATH];

	if (lpFolder->m_nParent >= 0)
	{
		// a child extra folder was renamed, so do the rename and save the parent
		// save old title
		char *old_title = lpFolder->m_lpTitle;
		// set new title
		lpFolder->m_lpTitle = (char *)malloc(strlen(new_name) + 1);
		strcpy(lpFolder->m_lpTitle, new_name);

		// try to save
		if (TrySaveExtraFolder(lpFolder) == false)
		{
			// failed, so free newly allocated title and restore old
			free(lpFolder->m_lpTitle);
			lpFolder->m_lpTitle = old_title;
			return false;
		}
		
		TryRenameCustomFolderIni(lpFolder, old_title, new_name);
		// successful, so free old title
		free(old_title);
		return true;
	}

	// a parent extra folder was renamed, so rename the file
	snprintf(new_filename, std::size(new_filename), "%s\\%s.ini", GetFolderDir(), new_name);
	snprintf(filename, std::size(filename), "%s\\%s.ini", GetFolderDir(), lpFolder->m_lpTitle);
	bool retval = winui_move_file_utf8(filename, new_filename);

	if (retval)
	{
		TryRenameCustomFolderIni(lpFolder, lpFolder->m_lpTitle, new_name);
		free(lpFolder->m_lpTitle);
		lpFolder->m_lpTitle = (char *)malloc(strlen(new_name) + 1);
		strcpy(lpFolder->m_lpTitle, new_name);
	}
	else
		ErrorMessageBox("Error while renaming custom file %s to %s", filename, new_filename);

	return retval;
}

void AddToCustomFolder(LPTREEFOLDER lpFolder, int driver_index)
{
	if ((lpFolder->m_dwFlags & F_CUSTOM) == 0)
	{
		ErrorMessageBox("Unable to add game to non-custom folder");
		return;
	}

	if (TestBit(lpFolder->m_lpGameBits, driver_index) == 0)
	{
		AddGame(lpFolder, driver_index);

		if (TrySaveExtraFolder(lpFolder) == false)
			RemoveGame(lpFolder, driver_index); 	// undo on error
	}
}

void RemoveFromCustomFolder(LPTREEFOLDER lpFolder, int driver_index)
{
	if ((lpFolder->m_dwFlags & F_CUSTOM) == 0)
	{
		ErrorMessageBox("Unable to remove game from non-custom folder");
		return;
	}

	if (TestBit(lpFolder->m_lpGameBits, driver_index) != 0)
	{
		RemoveGame(lpFolder, driver_index);

		if (TrySaveExtraFolder(lpFolder) == false)
			AddGame(lpFolder, driver_index); // undo on error
	}
}

bool TrySaveExtraFolder(LPTREEFOLDER lpFolder)
{
	char fname[MAX_PATH];
	bool error = false;
	LPTREEFOLDER root_folder = NULL;
	LPEXFOLDERDATA extra_folder = NULL;

	for (int i = 0; i < numExtraFolders; i++)
	{
		if (ExtraFolderData[i]->m_nFolderId == lpFolder->m_nFolderId)
		{
			root_folder = lpFolder;
			extra_folder = ExtraFolderData[i];
			break;
		}

		if (lpFolder->m_nParent >= 0 && ExtraFolderData[i]->m_nFolderId == treeFolders[lpFolder->m_nParent]->m_nFolderId)
		{
			root_folder = treeFolders[lpFolder->m_nParent];
			extra_folder = ExtraFolderData[i];
			break;
		}
	}

	if (extra_folder == NULL || root_folder == NULL)
	{
		ErrorMessageBox("Error finding custom file name to save");
		return false;
	}

	snprintf(fname, std::size(fname), "%s\\%s.ini", GetFolderDir(), extra_folder->m_szTitle);
	wchar_t *temp = win_wstring_from_utf8(GetFolderDir());
	CreateDirectory(temp, NULL);
	free(temp);  	
	FILE *f = fopen(fname, "w");

	if (f == NULL)
		error = true;
	else
	{
		TREEFOLDER *folder_data;

		fprintf(f, "[FOLDER_SETTINGS]\n");
		
		// negative values for icons means it's custom, so save 'em
		if (extra_folder->m_nIconId < 0)
			fprintf(f, "RootFolderIcon %s\n", ExtraFolderIcons[(-extra_folder->m_nIconId) - ICON_MAX]);

		if (extra_folder->m_nSubIconId < 0)
			fprintf(f, "SubFolderIcon %s\n", ExtraFolderIcons[(-extra_folder->m_nSubIconId) - ICON_MAX]);

		/* need to loop over all our TREEFOLDERs--first the root one, then each child.
		   start with the root */
		folder_data = root_folder;
		fprintf(f, "\n[ROOT_FOLDER]\n");

		for (int i = 0; i < driver_list::total(); i++)
		{
			if (TestBit(folder_data->m_lpGameBits, i))
				fprintf(f, "%s\n", GetDriverGameName(i));
		}

		/* look through the custom folders for ones with our root as parent */
		for (int j = 0; j < numFolders; j++)
		{
			folder_data = treeFolders[j];

			if (folder_data->m_nParent >= 0 && treeFolders[folder_data->m_nParent] == root_folder)
			{
				fprintf(f, "\n[%s]\n", folder_data->m_lpTitle);

				for (int i = 0; i < driver_list::total(); i++)
				{
					if (TestBit(folder_data->m_lpGameBits, i))
						fprintf(f, "%s\n", GetDriverGameName(i));
				}
			}
		}

		fclose(f);
	}

	if (error)
		ErrorMessageBox("Error while saving custom file %s", fname);

	return !error;
}

HIMAGELIST GetTreeViewIconList(void)
{
	return hTreeSmall;
}

// Modified Code Source (Gaston90)
/****************************************************************************/
void CreateEARLIERFolders(int parent_index)
{
	int jj;
	int nGames = GetNumGames();

	
	LPTREEFOLDER lpFolder = treeFolders[parent_index];

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits,FALSE);

	for (jj = 0; jj < nGames; jj++)
	{
		const char *s = GetDriverGameName(jj);

		if (s == NULL || s[0] == '\0')
			continue;

		if (!strcmp("2020bbe", s))			        AddGame(lpFolder, jj);
		if (!strcmp("3countbe", s))			        AddGame(lpFolder, jj);
		if (!strcmp("androdune", s))			    AddGame(lpFolder, jj);
		if (!strcmp("aof3e", s))			        AddGame(lpFolder, jj);
		if (!strcmp("bangbeade", s))			    AddGame(lpFolder, jj);
		if (!strcmp("blazstre", s))			        AddGame(lpFolder, jj);
		if (!strcmp("goalx3e", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kabukikle", s))	            AddGame(lpFolder, jj);
		if (!strcmp("lastbladhe", s))		        AddGame(lpFolder, jj);
		if (!strcmp("kizunae", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof95e", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kotm2e", s))			        AddGame(lpFolder, jj);
		if (!strcmp("magdrp3e", s))			        AddGame(lpFolder, jj);
		if (!strcmp("miexchnge", s))	            AddGame(lpFolder, jj);
		if (!strcmp("msluge", s))	                AddGame(lpFolder, jj);
		if (!strcmp("mslug4e", s))	                AddGame(lpFolder, jj);
		if (!strcmp("mslug5e", s))	                AddGame(lpFolder, jj);
		if (!strcmp("neobombee", s))			    AddGame(lpFolder, jj);
		if (!strcmp("neodrifte", s))			    AddGame(lpFolder, jj);
		if (!strcmp("ninjamse", s))			        AddGame(lpFolder, jj);
		if (!strcmp("pulstare", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ragnagrde", s))	            AddGame(lpFolder, jj);
		if (!strcmp("rbffspece", s))			    AddGame(lpFolder, jj);
		if (!strcmp("panicbome", s))			    AddGame(lpFolder, jj);
		if (!strcmp("roboarme", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsho3e", s))		            AddGame(lpFolder, jj);
		if (!strcmp("samsho4e", s))			        AddGame(lpFolder, jj);
		if (!strcmp("shocktrae", s))			    AddGame(lpFolder, jj);
		if (!strcmp("strhoope", s))			        AddGame(lpFolder, jj);
		if (!strcmp("sonicw3e", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ssidek4e", s))			        AddGame(lpFolder, jj);
		if (!strcmp("turfmste", s))			        AddGame(lpFolder, jj);
		if (!strcmp("twinspre", s))			        AddGame(lpFolder, jj);
		if (!strcmp("tws96e", s))			        AddGame(lpFolder, jj);
		if (!strcmp("wakuwk7e", s))			        AddGame(lpFolder, jj);
		if (!strcmp("wh1e", s))			            AddGame(lpFolder, jj);
		if (!strcmp("whpe", s))			            AddGame(lpFolder, jj);
		if (!strcmp("wjammere", s))			        AddGame(lpFolder, jj);
	}
}

void CreateNEOSDFolders(int parent_index)
{
	int jj;
	int nGames = GetNumGames();
	LPTREEFOLDER lpFolder = treeFolders[parent_index];

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits,FALSE);

	for (jj = 0; jj < nGames; jj++)
	{
		const char *s = GetDriverGameName(jj);

		if (s == NULL || s[0] == '\0')
			continue;

		if (!strcmp("3countbnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("2020bbnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("2020bbands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("2020bbhnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("alpham2nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("alpham2pnds", s))		            AddGame(lpFolder, jj);
		if (!strcmp("androdunnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("aodknds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("aofnds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("aof2nds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("aof2ands", s))			            AddGame(lpFolder, jj);
		if (!strcmp("aof3nds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("aof3knds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("b2bnds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("bakatononds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("bangbeadnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("bjourneynds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("bjourneyhnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("blazstarnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("breakersnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("breakrevnds", s))		            AddGame(lpFolder, jj);
		if (!strcmp("bstarsnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("bstarshnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("bstars2nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("burningfnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("burningfhnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("burningfpnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("burningfpands", s))			    AddGame(lpFolder, jj);
		if (!strcmp("crswd2blnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("crswordnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ct2k3sands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ct2k3spnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("cthd2003nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ctomadaynds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("cyberlipnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("diggermands", s))		            AddGame(lpFolder, jj);
		if (!strcmp("doubledrnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("dragonshnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("eightmannds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("fatfurspnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("fatfurspands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("fatfury1nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("fatfury2nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("fatfury3nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("fbfrenzynds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("fightfevnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("fightfevands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("flipshotnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("froman2bnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("fswordsnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("galaxyfgnds", s))		            AddGame(lpFolder, jj);
		if (!strcmp("ganryunds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("garounds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("garoublnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("garouhnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("garouhands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("garoupnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ghostlopnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("goalx3nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("gowcaizrnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("gpilotsnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("gpilotshnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("gururinnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ironcladnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ironcladonds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("irrmazends", s))		            AddGame(lpFolder, jj);
		if (!strcmp("janshinnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("jockeygpnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("jockeygpands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("joyjoynds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kabukiklnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("karnovrnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k2mpnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k2mp2nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k2plsnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k2plands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k3blnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k3blands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k3uplnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k3plnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kizunands", s))		            AddGame(lpFolder, jj);
		if (!strcmp("kof2000nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof2000nnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof2001nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof2001hnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof2002nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof2002bnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof2003nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof2003hnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof10thnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf10thepnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k5uninds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof2k4sends", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof94nds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("kof95nds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("kof95hnds", s))		            AddGame(lpFolder, jj);
		if (!strcmp("kof96nds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("kof96hnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof97nds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("kof97hnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof97knds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof97plsnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof97oronds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof98nds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("kof98hnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof98knds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof98kands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof99nds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("kof99ends", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof99hnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof99knds", s))		            AddGame(lpFolder, jj);
		if (!strcmp("kof99kands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof99pnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kognds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("kotmnds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("kotmhnds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("kotm2nds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("kotm2ands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kotm2pnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("lans2004nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("lastbladnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("lastbladhnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("lastsolnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("lasthopends", s))			        AddGame(lpFolder, jj);
		if (!strcmp("lastbld2nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("lbowlingnds", s))		            AddGame(lpFolder, jj);
		if (!strcmp("legendosnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("lresortnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("lresortpnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("magdrop2nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("magdrop3nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("maglordnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("maglordhnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mahretsunds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("marukodqnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("matrimnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("miexchngnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("minasannds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("moshouginds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ms4plusnsd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("ms5plusnsd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ms5pcbdnsd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslugnsd", s))			            AddGame(lpFolder, jj);
		if (!strcmp("mslug2nsd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug2tnsd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug3nsd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug3hnsd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug3b6nsd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug4nsd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug4hnsd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug5nsd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug5hnsd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslugxnsd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mutnatnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("nam1975nds", s))		            AddGame(lpFolder, jj);
		if (!strcmp("ncombatnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ncombathnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ncommandnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("neobombends", s))			        AddGame(lpFolder, jj);
		if (!strcmp("neocup98nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("neodriftnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("neomrdonds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ninjamasnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("nitdnds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("nitdblnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("overtopnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("panicbomnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("pbobbl2nnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("pbobblennds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("pbobblenbnds", s))		            AddGame(lpFolder, jj);
		if (!strcmp("pgoalnds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("pnyaands", s))			            AddGame(lpFolder, jj);
		if (!strcmp("pnyaaands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("popbouncnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("preisle2nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("pspikes2nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("pulstarnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("puzzldprnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("puzzledpnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("quizdai2nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("quizdaisnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("quizdaisknds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("quizkofnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("quizkofknds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ragnagrnds", s))		            AddGame(lpFolder, jj);
		if (!strcmp("rbff1nds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("rbff1ands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("rbff1knds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("rbff2nds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("rbff2hnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("rbff2knds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("rbffspecnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("rbffspecknds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ridheronds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ridherohnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("roboarmynds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("roboarmyands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("rotdnds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("rotdhnds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("s1945pnds", s))		            AddGame(lpFolder, jj);
		if (!strcmp("samsh5spnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsh5sphnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsh5sphonds", s))			    AddGame(lpFolder, jj);
		if (!strcmp("samshonds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samshohnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsho2nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsho2knds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsho2kands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsho3nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsho3hnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsho4nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsho4knds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsho5nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsho5hnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsho5bnds", s))		            AddGame(lpFolder, jj);
		if (!strcmp("savagerends", s))			        AddGame(lpFolder, jj);
		if (!strcmp("sbpnds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("sdodgebnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("sengokunds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("sengokuhnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("sengoku2nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("sengoku3nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("sengoku3ands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("shocktr2nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("shocktronds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("shocktroands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("socbrawlnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("socbrawlhnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("sonicwi2nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("sonicwi3nds", s))		            AddGame(lpFolder, jj);
		if (!strcmp("spinmastnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ssidekinds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ssideki2nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ssideki3nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ssideki4nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("stakwinnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("stakwin2nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("strhoopnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("superspynds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("svcnds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("svcbootnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("svcplusnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("svcplusands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("svcsplusnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("svcpcbnds", s))		            AddGame(lpFolder, jj);
		if (!strcmp("svcpcbands", s))			        AddGame(lpFolder, jj);
		if (!strcmp("tophuntrnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("tophuntrhnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("tpgolfnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("trallynds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("turfmastnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("twinsprinds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("twsoc96nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("viewpoinnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("wakuwak7nds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("wh1nds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("wh1hnds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("wh1hands", s))			            AddGame(lpFolder, jj);
		if (!strcmp("wh2nds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("wh2hnds", s))		                AddGame(lpFolder, jj);
		if (!strcmp("wh2jnds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("whpnds", s))			            AddGame(lpFolder, jj);
		if (!strcmp("wjammersnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("zedbladends", s))			        AddGame(lpFolder, jj);
		if (!strcmp("zintrckbnds", s))			        AddGame(lpFolder, jj);
		if (!strcmp("zupapands", s))			        AddGame(lpFolder, jj);
	}
}

void CreateHOMEBREWFolders(int parent_index)
{
	int jj;
	int nGames = GetNumGames();

	
	LPTREEFOLDER lpFolder = treeFolders[parent_index];

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits,FALSE);

	for (jj = 0; jj < nGames; jj++)
	{
		const char *s = GetDriverGameName(jj);

		if (s == NULL || s[0] == '\0')
			continue;

	    if (!strcmp("19yy", s))			            AddGame(lpFolder, jj);
		if (!strcmp("19yyo", s))			        AddGame(lpFolder, jj);
		if (!strcmp("240ptest", s))			        AddGame(lpFolder, jj);
		if (!strcmp("4play", s))			        AddGame(lpFolder, jj);
		if (!strcmp("abyssal", s))			        AddGame(lpFolder, jj);
		if (!strcmp("amazonn", s))			        AddGame(lpFolder, jj);
		if (!strcmp("badapple", s))			        AddGame(lpFolder, jj);
		if (!strcmp("bdudes", s))		            AddGame(lpFolder, jj);
		if (!strcmp("beast", s))			        AddGame(lpFolder, jj);
		if (!strcmp("bpanicdx", s))			        AddGame(lpFolder, jj);
		if (!strcmp("bonusstage", s))			    AddGame(lpFolder, jj);
		if (!strcmp("cabalng", s))			        AddGame(lpFolder, jj);
		if (!strcmp("cakefght", s))			        AddGame(lpFolder, jj);
		if (!strcmp("caravan", s))			        AddGame(lpFolder, jj);
		if (!strcmp("cbarrel", s))			        AddGame(lpFolder, jj);
		if (!strcmp("cnbe", s))			            AddGame(lpFolder, jj);
		if (!strcmp("cnbe2018", s))		            AddGame(lpFolder, jj);
		if (!strcmp("cphd", s))			            AddGame(lpFolder, jj);
		if (!strcmp("columnsn", s))			        AddGame(lpFolder, jj);
		if (!strcmp("cyborg", s))			        AddGame(lpFolder, jj);
		if (!strcmp("doubled1", s))			        AddGame(lpFolder, jj);
		if (!strcmp("flapchck", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ffeast", s))			        AddGame(lpFolder, jj);
		if (!strcmp("gladmort", s))			        AddGame(lpFolder, jj);
		if (!strcmp("goldaxen", s))		            AddGame(lpFolder, jj);
		if (!strcmp("horekidb3", s))	            AddGame(lpFolder, jj);
		if (!strcmp("hypernoid", s))			    AddGame(lpFolder, jj);
		if (!strcmp("inthehunt", s))			    AddGame(lpFolder, jj);
		if (!strcmp("iocero", s))			        AddGame(lpFolder, jj);
		if (!strcmp("jurl", s))			            AddGame(lpFolder, jj);
		if (!strcmp("karnovn", s))			        AddGame(lpFolder, jj);
		if (!strcmp("knightsch", s))			    AddGame(lpFolder, jj);
		if (!strcmp("lhcdb", s))			        AddGame(lpFolder, jj);
		if (!strcmp("looptris", s))			        AddGame(lpFolder, jj);
		if (!strcmp("looptrsp", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ltorb", s))		            AddGame(lpFolder, jj);
		if (!strcmp("mslug3x", s))			        AddGame(lpFolder, jj);
		if (!strcmp("nblktiger", s))			    AddGame(lpFolder, jj);
		if (!strcmp("neo2500", s))			        AddGame(lpFolder, jj);
		if (!strcmp("neo2048", s))			        AddGame(lpFolder, jj);
		if (!strcmp("neopang", s))			        AddGame(lpFolder, jj);
		if (!strcmp("neo3d", s))			        AddGame(lpFolder, jj);
		if (!strcmp("neocstlv", s))			        AddGame(lpFolder, jj);
		if (!strcmp("neodemo", s))			        AddGame(lpFolder, jj);
		if (!strcmp("neogal1", s))			        AddGame(lpFolder, jj);
		if (!strcmp("neogal1t", s))		            AddGame(lpFolder, jj);
		if (!strcmp("neonopon", s))			        AddGame(lpFolder, jj);
		if (!strcmp("neopong", s))			        AddGame(lpFolder, jj);
		if (!strcmp("neoponga", s))			        AddGame(lpFolder, jj);
		if (!strcmp("neothund", s))			        AddGame(lpFolder, jj);
		if (!strcmp("neotris", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ngcdtdd0", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ngem2k", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ngftdemo", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ngmontst", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ngtetris", s))		            AddGame(lpFolder, jj);
		if (!strcmp("nsmbd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("nsmb", s))			            AddGame(lpFolder, jj);
		if (!strcmp("poknight", s))			        AddGame(lpFolder, jj);
		if (!strcmp("santabll", s))			        AddGame(lpFolder, jj);
		if (!strcmp("sgz", s))			            AddGame(lpFolder, jj);
		if (!strcmp("shinobin", s))			        AddGame(lpFolder, jj);
		if (!strcmp("seafight", s))			        AddGame(lpFolder, jj);
		if (!strcmp("syscheck", s))			        AddGame(lpFolder, jj);
		if (!strcmp("teot", s))			            AddGame(lpFolder, jj);
		if (!strcmp("timesup", s))		            AddGame(lpFolder, jj);
		if (!strcmp("timesupd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("totc", s))			            AddGame(lpFolder, jj);
		if (!strcmp("ww2demo", s))			        AddGame(lpFolder, jj);
		if (!strcmp("yoyoshkn", s))			        AddGame(lpFolder, jj);
		if (!strcmp("xeviousn", s))			        AddGame(lpFolder, jj);
		if (!strcmp("xeno", s))			            AddGame(lpFolder, jj);
	}
}

void CreateHACKFolders(int parent_index)
{
	int jj;
	int nGames = GetNumGames();
	LPTREEFOLDER lpFolder = treeFolders[parent_index];

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits,FALSE);

	for (jj = 0; jj < nGames; jj++)
	{
		const char *s = GetDriverFileName(jj);

		if (s == NULL || s[0] == '\0')
			continue;

		if (!strcmp("neogeo_noslothb.cpp", s))               AddGame(lpFolder, jj);
	}
}

void CreateDECRYPTEDFolders(int parent_index)
{
	int jj;
	int nGames = GetNumGames();
	LPTREEFOLDER lpFolder = treeFolders[parent_index];

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits,FALSE);

	for (jj = 0; jj < nGames; jj++)
	{
		const char *s = GetDriverGameName(jj);

		if (s == NULL || s[0] == '\0')
			continue;

		if (!strcmp("bangbedd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("cthd2k3d", s))			        AddGame(lpFolder, jj);
		if (!strcmp("cthd2k3da", s))			    AddGame(lpFolder, jj);
		if (!strcmp("cthd2k3a", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ct2k3spd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ganryud", s))			        AddGame(lpFolder, jj);
		if (!strcmp("garoud", s))			        AddGame(lpFolder, jj);
		if (!strcmp("garouhd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("jckeygpd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof96ep", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof97pla", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof97orop", s))	            AddGame(lpFolder, jj);
		if (!strcmp("kof99d", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof99kd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof2kd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof2knd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof2k1d", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof2k1hd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof2k1nd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k1pls", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k1plse", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k1plsd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("kf2k1pla", s))		            AddGame(lpFolder, jj);
		if (!strcmp("kf2k1plae", s))	            AddGame(lpFolder, jj);
		if (!strcmp("kf2k1plad", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k1plap", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kof2k2d", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof2k2nd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k2plae", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k2plad", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k2plap", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k2plbe", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k2plbd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k2plbp", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k2plc", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k2plce", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k2plcd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k2pld", s))		            AddGame(lpFolder, jj);
		if (!strcmp("kf2k2plde", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k2pldd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k2ple", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k2plee", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k2pled", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k2plep", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k2mpl", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k2mpp", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k2mpe", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k2mpd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k2mp2e", s))		        AddGame(lpFolder, jj);
		if (!strcmp("kf2k2mp2d", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k2mp2p", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kof2k3d", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k3bd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof2k3hd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof2k3nd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k3pcd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k3pd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k3upd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kogd", s))			            AddGame(lpFolder, jj);
		if (!strcmp("kogplusd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("kof10thd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof10thp", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf10thepp", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kof10thu", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k5unid", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kofse2k4", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kofse2k4e", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kofse2k4d", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kofse2k4p", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k4pls", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kf2k4plse", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k4plsd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k4plsp", s))			    AddGame(lpFolder, jj);
		if (!strcmp("lans2k4d", s))			        AddGame(lpFolder, jj);
		if (!strcmp("matrimd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("matrimbd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("matrimnd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("msboot", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ms3b6boot", s))			    AddGame(lpFolder, jj);
		if (!strcmp("ms4boot", s))		            AddGame(lpFolder, jj);
		if (!strcmp("ms5boot", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ms5pcbd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ms4plusa", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ms4plusd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ms5plusa", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ms5plusc", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ms5plusd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug2t", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug3d", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug3hd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("mslug3nd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug3b6d", s))			    AddGame(lpFolder, jj);
		if (!strcmp("mslug3b6e", s))			    AddGame(lpFolder, jj);
		if (!strcmp("mslug4d", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug4hd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug4nd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug5d", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug5hd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug5n", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug5nd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("mslug5b2", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug5b3", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug5b4", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug5b5", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug5b6", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug5b7", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug5b8", s))		            AddGame(lpFolder, jj);
		if (!strcmp("mslugxb", s))			        AddGame(lpFolder, jj);
		if (!strcmp("nitdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("pbobblendx", s))			    AddGame(lpFolder, jj);
		if (!strcmp("pnyaad", s))			        AddGame(lpFolder, jj);
		if (!strcmp("pnyaand", s))			        AddGame(lpFolder, jj);
		if (!strcmp("preisl2d", s))			        AddGame(lpFolder, jj);
		if (!strcmp("rotdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("rotdnd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("rotdndd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("s1945pd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsh3hb", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsh5bd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsh5d", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsh5hd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsh5nd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("ssh5spn", s))			        AddGame(lpFolder, jj);
		if (!strcmp("sams5spd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("sams5sod", s))			        AddGame(lpFolder, jj);
		if (!strcmp("sams5shd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samsh5sphd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("samsh5spnd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("samsh5spp", s))			    AddGame(lpFolder, jj);
		if (!strcmp("sengok3d", s))			        AddGame(lpFolder, jj);
		if (!strcmp("svcda", s))			        AddGame(lpFolder, jj);
		if (!strcmp("svcd", s))			            AddGame(lpFolder, jj);
		if (!strcmp("svcnd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("svcbp", s))			        AddGame(lpFolder, jj);
		if (!strcmp("svcplusb", s))			        AddGame(lpFolder, jj);
		if (!strcmp("svcplusd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("svcplusp", s))			        AddGame(lpFolder, jj);
		if (!strcmp("svcplusap", s))			    AddGame(lpFolder, jj);
		if (!strcmp("svcsplusp", s))			    AddGame(lpFolder, jj);
		if (!strcmp("svcpcbd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("zupapad", s))			        AddGame(lpFolder, jj);
		if (!strcmp("zupapand", s))			        AddGame(lpFolder, jj);
	}
}


void CreateMUSICFolders(int parent_index)
{
	int jj;
	int nGames = GetNumGames();
	LPTREEFOLDER lpFolder = treeFolders[parent_index];

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits,FALSE);

	for (jj = 0; jj < nGames; jj++)
	{
		const char *s = GetDriverGameName(jj);

		if (s == NULL || s[0] == '\0')
			continue;

		if (!strcmp("cndi", s))			        AddGame(lpFolder, jj);
		if (!strcmp("dti", s))			        AddGame(lpFolder, jj);
		if (!strcmp("dwi", s))			        AddGame(lpFolder, jj);
		if (!strcmp("dwia", s))			        AddGame(lpFolder, jj);
		if (!strcmp("gbi", s))			        AddGame(lpFolder, jj);
		if (!strcmp("rci", s))			        AddGame(lpFolder, jj);
		if (!strcmp("smi", s))			        AddGame(lpFolder, jj);
		if (!strcmp("tmnti", s))			    AddGame(lpFolder, jj);
		if (!strcmp("tmntia", s))		        AddGame(lpFolder, jj);
	}
}

void CreateMGD2Folders(int parent_index)
{
	int jj;
	int nGames = GetNumGames();
	LPTREEFOLDER lpFolder = treeFolders[parent_index];

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits,FALSE);

	for (jj = 0; jj < nGames; jj++)
	{
		const char *s = GetDriverGameName(jj);

		if (s == NULL || s[0] == '\0')
			continue;

		if (!strcmp("3countbd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("2020bbd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("alpham2d", s))			        AddGame(lpFolder, jj);
		if (!strcmp("androdund", s))		        AddGame(lpFolder, jj);
		if (!strcmp("aofd", s))			            AddGame(lpFolder, jj);
		if (!strcmp("bakatonod", s))	            AddGame(lpFolder, jj);
		if (!strcmp("bstarsd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("burningfd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("crswordd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("cyberlipd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("eightmand", s))	            AddGame(lpFolder, jj);
		if (!strcmp("fatfury1d", s))			    AddGame(lpFolder, jj);
		if (!strcmp("fbfrenzyd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("gpilotsd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("joyjoyd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kotmd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("lbowlingd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("lresortd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("maglordd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("minasand", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mutnatd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ncombatd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ncommandd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("ridherod", s))		            AddGame(lpFolder, jj);
		if (!strcmp("roboarmyd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("sengokud", s))			        AddGame(lpFolder, jj);
		if (!strcmp("sengoku2d", s))			    AddGame(lpFolder, jj);
		if (!strcmp("socbrawld", s))			    AddGame(lpFolder, jj);
		if (!strcmp("superspyd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("tpgolfd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("trallyd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("wh1d", s))			            AddGame(lpFolder, jj);
	}
}

void CreateNEOGEOCDFolders(int parent_index)
{
	int jj;
	int nGames = GetNumGames();
	LPTREEFOLDER lpFolder = treeFolders[parent_index];

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits,FALSE);

	for (jj = 0; jj < nGames; jj++)
	{
		const char *s = GetDriverGameName(jj);

		if (s == NULL || s[0] == '\0')
			continue;

		if (!strcmp("2020bbcd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("crswd2bl", s))			        AddGame(lpFolder, jj);
		if (!strcmp("gpilotcd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ironcladcd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("joyjoycd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("lbowlingcd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("pbobblencd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("pspikes2cd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("sengokucd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("ssidekicd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("strhoopcd", s))		   	    AddGame(lpFolder, jj);
		if (!strcmp("superspycd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("tpgolfcd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("trallycd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("zintrkcd", s))			        AddGame(lpFolder, jj);
	}
}

void CreateDARKSOFTFolders(int parent_index)
{
	int jj;
	int nGames = GetNumGames();
	LPTREEFOLDER lpFolder = treeFolders[parent_index];

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits,FALSE);

	for (jj = 0; jj < nGames; jj++)
	{
		const char *s = GetDriverGameName(jj);

		if (s == NULL || s[0] == '\0')
			continue;

		if (!strcmp("3countbdd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("2020bbdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("2020bbadd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("2020bbhdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("alpham2dd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("alpham2pdd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("androdundd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("aodkdd", s))		   	        AddGame(lpFolder, jj);
		if (!strcmp("aofdd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("aof2dd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("aof2add", s))			        AddGame(lpFolder, jj);
		if (!strcmp("aof3dd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("aof3kdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("b2bdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("bakatonodd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("bangbeadd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("bjourneydd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("bjourneyhdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("blazstardd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("breakersdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("breakrevdd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("bstarsdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("bstarshdd", s))		   	    AddGame(lpFolder, jj);
		if (!strcmp("bstars2dd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("burningfdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("burningfhdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("burningfpdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("burningfpadd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("crswd2bldd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("crsworddd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("ct2k3sadd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("ct2k3spdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("cthd2003dd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("ctomadaydd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("cyberlipdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("diggermadd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("doubledrdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("dragonshdd", s))		   	    AddGame(lpFolder, jj);
		if (!strcmp("eightmandd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("fatfurspdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("fatfurspadd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("fatfury1dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("fatfury2dd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("fatfury3dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("fbfrenzydd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("fightfevdd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("fightfevadd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("flipshotdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("froman2bdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("fswordsdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("galaxyfgdd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("ganryudd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("garoudd", s))		   	        AddGame(lpFolder, jj);
		if (!strcmp("garoubldd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("garouhdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("garouhadd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("garoupdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("ghostlopdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("goalx3dd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("gowcaizrdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("gpilotsdd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("gpilotshdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("gururindd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("ironcladd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("ironcladod", s))	            AddGame(lpFolder, jj);
		if (!strcmp("irrmazedd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("janshindd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("jockeygpdd", s))		   	    AddGame(lpFolder, jj);
		if (!strcmp("jockeygpadd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("joyjoydd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kabukikldd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("karnovrdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k2mpdd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("kf2k2mp2dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k2plsdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k2pladd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("kf2k3bldd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf2k3bladd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("kf2k3upldd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("kf2k3pldd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("kizunadd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("kof2000dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kof2000ndd", s))		   	    AddGame(lpFolder, jj);
		if (!strcmp("kof2001dd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("kof2001hdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kof2002dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kof2002bdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kof2003dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kof2003hdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kof10thdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kf10thepdd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("kf2k5unidd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kof2k4sedd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("kof94dd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("kof95dd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("kof95hdd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("kof96dd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof96hdd", s))		   	        AddGame(lpFolder, jj);
		if (!strcmp("kof97dd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("kof97hdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof97kdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof97plsdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kof97orodd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kof98dd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof98hdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kof98kdd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("kof98kadd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kof99dd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("kof99edd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("kof99hdd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("kof99kdd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("kof99kadd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("kof99pdd", s))		   	        AddGame(lpFolder, jj);
		if (!strcmp("kogdd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("kotmdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kotmhdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kotm2dd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kotm2add", s))			        AddGame(lpFolder, jj);
		if (!strcmp("kotm2pdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("lans2004dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("lastbladdd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("lastbladhdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("lastsoldd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("lasthopedd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("lastbld2dd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("lbowlingdd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("legendosdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("lresortdd", s))		   	    AddGame(lpFolder, jj);
		if (!strcmp("lresortpdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("magdrop2dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("magdrop3dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("maglorddd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("maglordhdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("mahretsudd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("marukodqdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("matrimdd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("miexchngdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("minasandd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("moshougidd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("ms5pcbdd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("ms4plusdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("ms5plusdd", s))		   	    AddGame(lpFolder, jj);
		if (!strcmp("mslugdd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("mslug2dd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug2tdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("mslug3dd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug3hdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("mslug3b6dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("mslug4dd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug4hdd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("mslug5dd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("mslug5hdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("mslugxdd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("mutnatdd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("nam1975dd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("ncombatdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("ncombathdd", s))		   	    AddGame(lpFolder, jj);
		if (!strcmp("ncommanddd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("neobombedd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("neocup98dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("neodriftdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("neomrdodd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("ninjamasdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("nitddd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("nitdbldd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("overtopdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("panicbomdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("pbobbl2ndd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("pbobblendd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("pbobblenbdd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("pgoaldd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("pnyaadd", s))		   	        AddGame(lpFolder, jj);
		if (!strcmp("pnyaaadd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("popbouncdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("preisle2dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("pspikes2dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("pulstardd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("puzzldprdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("puzzledpdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("quizdai2dd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("quizdaisdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("quizdaiskdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("quizkofdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("quizkofkdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("ragnagrdd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("rbff1dd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("rbff1add", s))		   	        AddGame(lpFolder, jj);
		if (!strcmp("rbff1kdd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("rbff2dd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("rbff2hdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("rbff2kdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("rbffspecdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("rbffspeckdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("ridherodd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("ridherohdd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("roboarmydd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("roboarmyadd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("rotddd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("rotdhdd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("s1945pdd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("samsh5spdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("samsh5sphdd", s))		   	    AddGame(lpFolder, jj);
		if (!strcmp("samsh5sphodd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("samshodd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("samshohdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("samsho2dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("samsho2kdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("samsho2kadd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("samsho3dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("samsho3hdd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("samsho4dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("samsho4kdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("samsho5dd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("samsho5hdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("samsho5bdd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("savageredd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("sbpdd", s))		   	        AddGame(lpFolder, jj);
		if (!strcmp("sdodgebdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("sengokudd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("sengokuhdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("sengoku2dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("sengoku3dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("sengoku3add", s))			    AddGame(lpFolder, jj);
		if (!strcmp("shocktr2dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("shocktrodd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("shocktroadd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("socbrawldd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("socbrawlhdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("sonicwi2dd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("sonicwi3dd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("spinmastdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("ssidekidd", s))		   	    AddGame(lpFolder, jj);
		if (!strcmp("ssideki2dd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("ssideki3dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("ssideki4dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("stakwindd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("stakwin2dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("strhoopdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("superspydd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("svcdd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("svcbootdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("svcplusdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("svcplusadd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("svcsplusdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("svcpcbdd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("svcpcbadd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("tophuntrdd", s))		   	    AddGame(lpFolder, jj);
		if (!strcmp("tophuntrhdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("tpgolfdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("trallydd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("turfmastdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("twinspridd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("twsoc96dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("viewpoindd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("wakuwak7dd", s))		        AddGame(lpFolder, jj);
		if (!strcmp("wh1dd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("wh1hdd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("wh1hadd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("wh2dd", s))	                AddGame(lpFolder, jj);
		if (!strcmp("wh2hdd", s))		            AddGame(lpFolder, jj);
		if (!strcmp("wh2jdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("whpdd", s))		   	        AddGame(lpFolder, jj);
		if (!strcmp("wjammersdd", s))	            AddGame(lpFolder, jj);
		if (!strcmp("zedbladedd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("zintrckbdd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("zupapadd", s))			        AddGame(lpFolder, jj);
	}
}

/****************************************************************************/

int GetTreeViewIconIndex(int icon_id)
{
	if (icon_id < 0)
		return -icon_id;

	for (int i = 0; i < std::size(treeIconNames); i++)
	{
		if (icon_id == treeIconNames[i].nResourceID)
			return i;
	}

	return -1;
}

static bool FilterAvailable(int driver_index)
{
	if (!DriverUsesRoms(driver_index))
	{
		if (GetDisplayNoRomsGames())
			return true;
		else
			return false;
	}

	return IsAuditResultYes(GetRomAuditResults(driver_index));
}
