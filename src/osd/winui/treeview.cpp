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
	{"Parents",         "originals",         FOLDER_ORIGINAL,     IDI_FOLDER_ORIGINALS,     F_ORIGINALS,   F_CLONES,     0, NULL,                       DriverIsClone,           false },
	{"Clones",          "clones",            FOLDER_CLONES,       IDI_FOLDER_CLONES,        F_CLONES,      F_ORIGINALS,  0, NULL,                       DriverIsClone,           true },
	{"Source",          "source",            FOLDER_SOURCE,       IDI_FOLDER_SOURCE,        0,             0,            0, CreateSourceFolders },
	{"NeoGeo",          "neogeo", 	         FOLDER_NEOGEO,       IDI_FOLDER_NEOGEO,		0,			   0, 		     0, CreateNEOGEOFolders },
    {"Capcom",		    "Capcom",		     FOLDER_CAPCOM,	      IDI_FOLDER_CAPCOM, 	    0,			   0,            0,	CreateCAPCOMFolders },
	{"Vertical",        "vertical",          FOLDER_VERTICAL,     IDI_FOLDER_VERTICAL,      F_VERTICAL,    F_HORIZONTAL, 0, NULL,                       DriverIsVertical,        true },	
	{"Horizontal",      "horizontal",        FOLDER_HORIZONTAL,   IDI_FOLDER_HORIZONTAL,    F_HORIZONTAL,  F_VERTICAL,   0, NULL,                       DriverIsVertical,        false },	
	{"Working",         "working",           FOLDER_WORKING,      IDI_FOLDER_WORKING,       F_WORKING,     F_NONWORKING, 0, NULL,                       DriverIsBroken,          false },
	{"Not Working",     "nonworking",        FOLDER_NONWORKING,   IDI_FOLDER_NONWORKING,    F_NONWORKING,  F_WORKING,    0, NULL,                       DriverIsBroken,          true },
	{"Imperfect",       "imperfect",         FOLDER_DEFICIENCY,   IDI_FOLDER_IMPERFECT,     0,             0,            0, CreateDeficiencyFolders },
	{"Year",            "year",              FOLDER_YEAR,         IDI_FOLDER_YEAR,          0,             0,            0, CreateYearFolders },
	{"Manufacturer",    "manufacturer",      FOLDER_MANUFACTURER, IDI_FOLDER_MANUFACTURER,  0,             0,            0, CreateManufacturerFolders },
	{"CHD",             "harddisk",          FOLDER_HARDDISK,     IDI_FOLDER_HARDDISK,      0,             0,            0, NULL,                       DriverIsHarddisk,        true },
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
    { IDI_FOLDER_NEOGEO,       "fold_neogeo" },
	{ IDI_FOLDER_CAPCOM,	   "fold_darksoft"},
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
void CreateNEOGEOFolders(int parent_index)
{
	int jj;
	int nGames = GetNumGames();
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
    LPTREEFOLDER lpNeoGeoBT, lpNeoGeoCD, lpNeoGeoDS, lpNeoGeoDC, lpNeoGeoDM, lpNeoGeoEL, lpNeoGeoHC, lpNeoGeoHB, lpNeoGeoST, lpNeoGeoMG, lpNeoSD;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits,FALSE);

	// create our two subfolders
    lpNeoGeoBT = NewFolder("Bootleg", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpNeoGeoCD = NewFolder("CD Conversion", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
    lpNeoGeoDS = NewFolder("Darksoft", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpNeoGeoDC = NewFolder("Decrypted C", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpNeoGeoDM = NewFolder("Demo Music", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
    lpNeoGeoEL = NewFolder("Earlier", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpNeoGeoHC = NewFolder("Hack", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
    lpNeoGeoHB = NewFolder("HomeBrew", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
    lpNeoGeoST = NewFolder("NeoGeo", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
    lpNeoGeoMG = NewFolder("MGD2", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
    lpNeoSD = NewFolder("NeoSD", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));

	AddFolder(lpNeoGeoBT);
	AddFolder(lpNeoGeoCD);
	AddFolder(lpNeoGeoDS);
	AddFolder(lpNeoGeoDC);
	AddFolder(lpNeoGeoDM);	
	AddFolder(lpNeoGeoEL);
	AddFolder(lpNeoGeoHC);
	AddFolder(lpNeoGeoHB);
	AddFolder(lpNeoGeoST);
	AddFolder(lpNeoGeoMG);
	AddFolder(lpNeoSD);	

	for (jj = 0; jj < nGames; jj++)
	{
		const char *s = GetDriverGameName(jj);

		if (s == NULL || s[0] == '\0')
			continue;


        // Bootleg
		if (!strcmp("kof97pls", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kof97oro", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kog", s))			            AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kogplus", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("garoubl", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("mslug3b6", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("cthd2003", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("ct2k3sp", s))		            AddGame(lpNeoGeoBT, jj);
		if (!strcmp("ct2k3sa", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kof2002b", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kf2k2pls", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kf2k2pla", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kf2k2mp", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kf2k2mp2", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kof10th", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kf10thep", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kf2k5uni", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kof2k4se", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("ms5plus", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("mslug5b1", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("svcboot", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("svcplus", s))		            AddGame(lpNeoGeoBT, jj);
		if (!strcmp("svcplusa", s))		            AddGame(lpNeoGeoBT, jj);
		if (!strcmp("svcsplus", s))	                AddGame(lpNeoGeoBT, jj);
		if (!strcmp("samsho5b", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kf2k3bl", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kf2k3bla", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kf2k3pl", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kf2k3upl", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("zintrckb", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("crswd2bl", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("nitdbl", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("ironclado", s))			    AddGame(lpNeoGeoBT, jj);
		if (!strcmp("lans2004", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("pbobblenb", s))		        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("froman2b", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("ms4plus", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("matrimbl", s))		            AddGame(lpNeoGeoBT, jj);
		if (!strcmp("lasthope", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kof96ep", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("kof97pla", s))			        AddGame(lpNeoGeoBT, jj);
		if (!strcmp("samsho3en", s))			    AddGame(lpNeoGeoBT, jj);
		if (!strcmp("pbobblendx", s))		        AddGame(lpNeoGeoBT, jj);

        // CD Conversion
		if (!strcmp("19yy", s))			            AddGame(lpNeoGeoCD, jj);
		if (!strcmp("19yyo", s))                    AddGame(lpNeoGeoCD, jj);
		if (!strcmp("2020bbcd", s))			        AddGame(lpNeoGeoCD, jj);
		if (!strcmp("columnsncd", s))               AddGame(lpNeoGeoCD, jj);
		if (!strcmp("fr2cd", s))			        AddGame(lpNeoGeoCD, jj);
		if (!strcmp("crswd2bl", s))			        AddGame(lpNeoGeoCD, jj);
		if (!strcmp("gpilotcd", s))			        AddGame(lpNeoGeoCD, jj);
		if (!strcmp("ironcladcd", s))		        AddGame(lpNeoGeoCD, jj);
		if (!strcmp("joyjoycd", s))			        AddGame(lpNeoGeoCD, jj);
		if (!strcmp("lbowlingcd", s))	            AddGame(lpNeoGeoCD, jj);
        if (!strcmp("lhcdb", s))	                AddGame(lpNeoGeoCD, jj);
		if (!strcmp("ng4ptest", s))	                AddGame(lpNeoGeoCD, jj);
		if (!strcmp("pbobblencd", s))	            AddGame(lpNeoGeoCD, jj);
		if (!strcmp("pspikes2cd", s))	            AddGame(lpNeoGeoCD, jj);
		if (!strcmp("sengokucd", s))		        AddGame(lpNeoGeoCD, jj);
		if (!strcmp("ssidekicd", s))			    AddGame(lpNeoGeoCD, jj);
		if (!strcmp("strhoopcd", s))		   	    AddGame(lpNeoGeoCD, jj);
		if (!strcmp("superspycd", s))	            AddGame(lpNeoGeoCD, jj);
		if (!strcmp("tpgolfcd", s))			        AddGame(lpNeoGeoCD, jj);
		if (!strcmp("trallycd", s))			        AddGame(lpNeoGeoCD, jj);
		if (!strcmp("zintrkcd", s))			        AddGame(lpNeoGeoCD, jj);

        // Darksoft
		if (!strcmp("3countbdd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("2020bbdd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("2020bbadd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("2020bbhdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("alpham2dd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("alpham2pdd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("androdundd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("aodkdd", s))		   	        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("aofdd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("aof2dd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("aof2add", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("aof3dd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("aof3kdd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("b2bdd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("bakatonodd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("bangbeadd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("bjourneydd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("bjourneyhdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("blazstardd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("breakersdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("breakrevdd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("bstarsdd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("bstarshdd", s))		   	    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("bstars2dd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("burningfdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("burningfhdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("burningfpdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("burningfpadd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("crswd2bldd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("crsworddd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ct2k3sadd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ct2k3spdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("cthd2003dd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ctomadaydd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("cyberlipdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("diggermadd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("doubledrdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("dragonshdd", s))		   	    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("eightmandd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("fatfurspdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("fatfurspadd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("fatfury1dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("fatfury2dd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("fatfury3dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("fbfrenzydd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("fightfevdd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("fightfevadd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("flipshotdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("froman2bdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("fswordsdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("galaxyfgdd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ganryudd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("garoudd", s))		   	        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("garoubldd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("garouhdd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("garouhadd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("garoupdd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ghostlopdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("goalx3dd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("gowcaizrdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("gpilotsdd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("gpilotshdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("gururindd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ironcladd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ironcladod", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("irrmazedd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("janshindd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("jockeygpdd", s))		   	    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("jockeygpadd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("joyjoydd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kabukikldd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("karnovrdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kf2k2mpdd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kf2k2mp2dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kf2k2plsdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kf2k2pladd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kf2k3bldd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kf2k3bladd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kf2k3upldd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kf2k3pldd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kizunadd", s))		            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof2000dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof2000ndd", s))		   	    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof2001dd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof2001hdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof2002dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof2002bdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof2003dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof2003hdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof10thdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kf10thepdd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kf2k5unidd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof2k4sedd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof94dd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof95dd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof95hdd", s))		            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof96dd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof96hdd", s))		   	        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof97dd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof97hdd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof97kdd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof97plsdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof97orodd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof98dd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof98hdd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof98kdd", s))		            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof98kadd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof99dd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof99edd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof99hdd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof99kdd", s))		            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof99kadd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kof99pdd", s))		   	        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kogdd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kotmdd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kotmhdd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kotm2dd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kotm2add", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("kotm2pdd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("lans2004dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("lastbladdd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("lastbladhdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("lastsoldd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("lasthopedd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("lastbld2dd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("lbowlingdd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("legendosdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("lresortdd", s))		   	    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("lresortpdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("magdrop2dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("magdrop3dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("maglorddd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("maglordhdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("mahretsudd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("marukodqdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("matrimdd", s))		            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("miexchngdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("minasandd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("moshougidd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ms5pcbdd", s))		            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ms4plusdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ms5plusdd", s))		   	    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("mslugdd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("mslug2dd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("mslug2tdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("mslug3dd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("mslug3hdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("mslug3b6dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("mslug4dd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("mslug4hdd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("mslug5dd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("mslug5hdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("mslugxdd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("mutnatdd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("nam1975dd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ncombatdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ncombathdd", s))		   	    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ncommanddd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("neobombedd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("neocup98dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("neodriftdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("neomrdodd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ninjamasdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("nitddd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("nitdbldd", s))		            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("overtopdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("panicbomdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("pbobbl2ndd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("pbobblendd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("pbobblenbdd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("pgoaldd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("pnyaadd", s))		   	        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("pnyaaadd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("popbouncdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("preisle2dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("pspikes2dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("pulstardd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("puzzldprdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("puzzledpdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("quizdai2dd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("quizdaisdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("quizdaiskdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("quizkofdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("quizkofkdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ragnagrdd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("rbff1dd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("rbff1add", s))		   	        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("rbff1kdd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("rbff2dd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("rbff2hdd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("rbff2kdd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("rbffspecdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("rbffspeckdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ridherodd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ridherohdd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("roboarmydd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("roboarmyadd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("rotddd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("rotdhdd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("s1945pdd", s))		            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("samsh5spdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("samsh5sphdd", s))		   	    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("samsh5sphodd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("samshodd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("samshohdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("samsho2dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("samsho2kdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("samsho2kadd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("samsho3dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("samsho3hdd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("samsho4dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("samsho4kdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("samsho5dd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("samsho5hdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("samsho5bdd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("savageredd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("sbpdd", s))		   	        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("sdodgebdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("sengokudd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("sengokuhdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("sengoku2dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("sengoku3dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("sengoku3add", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("shocktr2dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("shocktrodd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("shocktroadd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("socbrawldd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("socbrawlhdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("sonicwi2dd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("sonicwi3dd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("spinmastdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ssidekidd", s))		   	    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ssideki2dd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ssideki3dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("ssideki4dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("stakwindd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("stakwin2dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("strhoopdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("superspydd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("svcdd", s))		            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("svcbootdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("svcplusdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("svcplusadd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("svcsplusdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("svcpcbdd", s))		            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("svcpcbadd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("tophuntrdd", s))		   	    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("tophuntrhdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("tpgolfdd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("trallydd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("turfmastdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("twinspridd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("twsoc96dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("viewpoindd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("vlinerdd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("vliner7edd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("vliner6edd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("vliner54dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("vliner53dd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("wakuwak7dd", s))		        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("wh1dd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("wh1hdd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("wh1hadd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("wh2dd", s))	                AddGame(lpNeoGeoDS, jj);
		if (!strcmp("wh2hdd", s))		            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("wh2jdd", s))			        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("whpdd", s))		   	        AddGame(lpNeoGeoDS, jj);
		if (!strcmp("wjammersdd", s))	            AddGame(lpNeoGeoDS, jj);
		if (!strcmp("zedbladedd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("zintrckbdd", s))			    AddGame(lpNeoGeoDS, jj);
		if (!strcmp("zupapadd", s))			        AddGame(lpNeoGeoDS, jj);

        // Decrypted C & P
		if (!strcmp("bangbedd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("cthd2k3d", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("cthd2k3da", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("cthd2k3a", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("ct2k3spd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("ganryud", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("garoud", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("garouhd", s))		            AddGame(lpNeoGeoDC, jj);
		if (!strcmp("jockygpd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kof96ep", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kof97pla", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kof97orod", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kof99d", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kof99kd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kof2kd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kof2knd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kof2k1d", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kof2k1hd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k1bh", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k1pls", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k1plse", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k1plsd", s))		        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k1pla", s))		            AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k1plae", s))	            AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k1plad", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k1plap", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kof2k2d", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kof2k2nd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2plae", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2plad", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2plap", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2plbe", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2plbd", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2plbp", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2plc", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2plce", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2plcd", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2pld", s))		            AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2plde", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2pldd", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2ple", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2plee", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2pled", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2plep", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2mpl", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2mpp", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2mpe", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2mpd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2mp2e", s))		        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2mp2d", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k2mp2p", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kof2k3d", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k3bd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kof2k3hd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kof2k3nd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k3pcd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k3pd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k3upd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kogd", s))			            AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kogplusd", s))		            AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kof10thd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf10thepp", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kof10thu", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k5unid", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kofse2k4", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kofse2k4e", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kofse2k4d", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kofse2k4p", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k4pls", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k4plse", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k4plsd", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("kf2k4plsp", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("lans2k4d", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("matrimd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("matrimbd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("msboot", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("ms3b6boot", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("ms4boot", s))		            AddGame(lpNeoGeoDC, jj);
		if (!strcmp("ms5boot", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("ms5pcbd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("ms4pluse", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("ms4plusd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("ms5pluse", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("ms5plusd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("ms5plusnd", s))	            AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug2t", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug3d", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug3hd", s))		            AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug3b6d", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug3b6e", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug4d", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug4hd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug4nd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug5d", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug5hd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug5nd", s))		            AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug5b2", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug5b3", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug5b4", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug5b5", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug5b6", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug5b7", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslug5b8", s))		            AddGame(lpNeoGeoDC, jj);
		if (!strcmp("mslugxb", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("nitdd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("pbobblendx", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("pnyaad", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("preisl2d", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("rotdd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("rotdhd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("s1945pd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("samsho3en", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("samsh5bd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("samsh5d", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("samsh5hd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("samsh5nd", s))		            AddGame(lpNeoGeoDC, jj);
		if (!strcmp("sams5spd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("sams5sod", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("sams5shd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("sams5sond", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("sams5shnd", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("sengok3d", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("svcd", s))			            AddGame(lpNeoGeoDC, jj);
		if (!strcmp("svcnd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("svcbp", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("svcplusp", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("svcsplusp", s))			    AddGame(lpNeoGeoDC, jj);
		if (!strcmp("svcpcbd", s))			        AddGame(lpNeoGeoDC, jj);
		if (!strcmp("zupapad", s))			        AddGame(lpNeoGeoDC, jj);

        // Demo Music
		if (!strcmp("akiradmo", s))			        AddGame(lpNeoGeoDM, jj);
		if (!strcmp("cndi", s))			            AddGame(lpNeoGeoDM, jj);
		if (!strcmp("didemo", s))			        AddGame(lpNeoGeoDM, jj);
		if (!strcmp("dti", s))			            AddGame(lpNeoGeoDM, jj);
		if (!strcmp("dwi", s))			            AddGame(lpNeoGeoDM, jj);
		if (!strcmp("dwia", s))			            AddGame(lpNeoGeoDM, jj);
		if (!strcmp("gbi", s))			            AddGame(lpNeoGeoDM, jj);
		if (!strcmp("rci", s))			            AddGame(lpNeoGeoDM, jj);
		if (!strcmp("smi", s))			            AddGame(lpNeoGeoDM, jj);
		if (!strcmp("tmnti", s))			        AddGame(lpNeoGeoDM, jj);
		if (!strcmp("tmntia", s))		            AddGame(lpNeoGeoDM, jj);

        // Earlier
		if (!strcmp("2020bbe", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("3countbe", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("androdune", s))			    AddGame(lpNeoGeoEL, jj);
		if (!strcmp("aof3e", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("bangbeade", s))			    AddGame(lpNeoGeoEL, jj);
		if (!strcmp("blazstre", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("fatfury3e", s))			    AddGame(lpNeoGeoEL, jj);
		if (!strcmp("goalx3e", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("kabukikle", s))	            AddGame(lpNeoGeoEL, jj);
		if (!strcmp("lastbladhe", s))		        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("kizunae", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("kof95e", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("kotm2e", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("magdrp3e", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("miexchnge", s))	            AddGame(lpNeoGeoEL, jj);
		if (!strcmp("msluge", s))	                AddGame(lpNeoGeoEL, jj);
		if (!strcmp("mslug4e", s))	                AddGame(lpNeoGeoEL, jj);
		if (!strcmp("mslug5e", s))	                AddGame(lpNeoGeoEL, jj);
		if (!strcmp("neobombee", s))			    AddGame(lpNeoGeoEL, jj);
		if (!strcmp("neodrifte", s))			    AddGame(lpNeoGeoEL, jj);
		if (!strcmp("ninjamse", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("pulstare", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("ragnagrde", s))	            AddGame(lpNeoGeoEL, jj);
		if (!strcmp("rbffspece", s))			    AddGame(lpNeoGeoEL, jj);
		if (!strcmp("pgoale", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("panicbome", s))			    AddGame(lpNeoGeoEL, jj);
		if (!strcmp("rbff1e", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("roboarme", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("samsho3e", s))		            AddGame(lpNeoGeoEL, jj);
		if (!strcmp("samsho4e", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("shocktrae", s))			    AddGame(lpNeoGeoEL, jj);
		if (!strcmp("strhoope", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("sengoku2e", s))    	        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("sonicw3e", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("ssidek4e", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("turfmste", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("twinspre", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("tws96e", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("wakuwk7e", s))			        AddGame(lpNeoGeoEL, jj);
		if (!strcmp("wh1e", s))			            AddGame(lpNeoGeoEL, jj);
		if (!strcmp("whpe", s))			            AddGame(lpNeoGeoEL, jj);
		if (!strcmp("wjammere", s))			        AddGame(lpNeoGeoEL, jj);

        // HomeBrew
	    if (!strcmp("19yy", s))			            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("19yyo", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("68kng", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("240ptest", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("4play", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("abyssal", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("amazonn", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("badapple", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("baddudesn", s))		        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("bbb2", s))		    	        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("beast", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("bpanicdx", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("bonusstage", s))			    AddGame(lpNeoGeoHB, jj);
		if (!strcmp("cabalng", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("cakefght", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("caravan", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("cbarrel", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("chelnovn", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("cnbe", s))			            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("cnbe2018", s))		            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("cphd", s))			            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("columnsn", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("cyborg", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("ddsprdmo", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("didemo", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("doubled1", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("flapchck", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("ffeast", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("fr2", s))			            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("foodfn", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("galaxiann", s))		        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("gladmort", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("goldaxen", s))		            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("gxg", s))		                AddGame(lpNeoGeoHB, jj);
		if (!strcmp("horekidb3", s))	            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("hypernoid", s))			    AddGame(lpNeoGeoHB, jj);
		if (!strcmp("igla", s))			            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("inthehunt", s))			    AddGame(lpNeoGeoHB, jj);
		if (!strcmp("iocero", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("jumpnrund", s))			    AddGame(lpNeoGeoHB, jj);
        if (!strcmp("jurl", s))			            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("karnovn", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("knightsch", s))			    AddGame(lpNeoGeoHB, jj);
		if (!strcmp("lernit", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("lhcdb", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("looptris", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("looptrsp", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("ltorb", s))		            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("mslug3x", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("nblktiger", s))			    AddGame(lpNeoGeoHB, jj);
		if (!strcmp("knacki", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("ndo_a_td", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("neo2500", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("neo2048", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("neopang", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("neo3d", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("neocstlv", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("neodemo", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("neofight", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("neogal1", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("neogal1t", s))		            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("neonopon", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("neopl", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("neopong", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("neoponga", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("neoromjb", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("neotest", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("neothund", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("neotris", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("ngcdtdd0", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("ng4ptest", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("ng4psyschk", s))		        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("ngem2k", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("ngftdemo", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("ngmontst", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("ngtd2", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("ngtetris", s))		            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("ngym2610", s))		            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("nsmbd", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("nsmb", s))			            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("nyan", s))			            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("pcmademo", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("pcmbdemo", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("poknight", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("pown", s))			            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("raroggame", s))			    AddGame(lpNeoGeoHB, jj);
		if (!strcmp("samantha", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("santabll", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("sgz", s))			            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("shaman24", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("shinobin", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("seafight", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("snddemo", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("spkick", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("spriteex", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("syscheck", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("teot", s))			            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("timesup", s))		            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("timesupd", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("totc", s))			            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("twister", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("vaporous", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("violentv", s))			        AddGame(lpNeoGeoHB, jj);
        if (!strcmp("vlad2000", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("wrldracr", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("ww2demo", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("yoyoshkn", s))			        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("xeviousng", s))		        AddGame(lpNeoGeoHB, jj);
		if (!strcmp("xeno", s))			            AddGame(lpNeoGeoHB, jj);
		if (!strcmp("xmas2017", s))			        AddGame(lpNeoGeoHB, jj);
	    if (!strcmp("zetsuxeving", s))		        AddGame(lpNeoGeoHB, jj);

        // NeoGeo
		if (!strcmp("2020bb", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("2020bba", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("2020bbh", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("3countb", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("alpham2", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("alpham2p", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("androdun", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("aodk", s))		   	            AddGame(lpNeoGeoST, jj);
		if (!strcmp("aof", s))	                    AddGame(lpNeoGeoST, jj);
		if (!strcmp("aof2", s))			            AddGame(lpNeoGeoST, jj);
		if (!strcmp("aof2a", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("aof3", s))			            AddGame(lpNeoGeoST, jj);
		if (!strcmp("aof3k", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("b2b", s))			            AddGame(lpNeoGeoST, jj);
		if (!strcmp("bakatono", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("bangbead", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("bjourney", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("bjourneyh", s))	            AddGame(lpNeoGeoST, jj);
		if (!strcmp("blazstar", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("breakers", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("breakrev", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("bstars", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("bstars2", s))		   	        AddGame(lpNeoGeoST, jj);
		if (!strcmp("bstarsh", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("burningf", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("burningfh", s))			    AddGame(lpNeoGeoST, jj);
		if (!strcmp("burningfp", s))			    AddGame(lpNeoGeoST, jj);
		if (!strcmp("burningfpa", s))	            AddGame(lpNeoGeoST, jj);
		if (!strcmp("burningfpb", s))			    AddGame(lpNeoGeoST, jj);
		if (!strcmp("crswd2bl", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("crsword", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("ct2k3sa", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("ct2k3sp", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("cthd2003", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("ctomaday", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("cyberlip", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("diggerma", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("doubledr", s))		   	        AddGame(lpNeoGeoST, jj);
		if (!strcmp("dragonsh", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("eightman", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("fatfursp", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("fatfurspa", s))			    AddGame(lpNeoGeoST, jj);
		if (!strcmp("fatfury1", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("fatfury2", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("fatfury2a", s))			    AddGame(lpNeoGeoST, jj);
		if (!strcmp("fatfury3", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("fatfury3a", s))			    AddGame(lpNeoGeoST, jj);
		if (!strcmp("fbfrenzy", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("fightfev", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("fightfeva", s))	            AddGame(lpNeoGeoST, jj);
		if (!strcmp("flipshot", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("froman2b", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("fswords", s))		   	        AddGame(lpNeoGeoST, jj);
		if (!strcmp("galaxyfg", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("ganryu", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("garou", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("garoubl", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("garouh", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("garouha", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("garoup", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("ghostlop", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("goalx3", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("gowcaizr", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("gpilots", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("gpilotsh", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("gpilotsp", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("gururin", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("ironclad", s))		   	        AddGame(lpNeoGeoST, jj);
		if (!strcmp("ironclado", s))	            AddGame(lpNeoGeoST, jj);
		if (!strcmp("irrmaze", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("janshin", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("jockeygp", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("jockeygpa", s))		        AddGame(lpNeoGeoST, jj);
		if (!strcmp("joyjoy", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kabukikl", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("karnovr", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("kf10thep", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kf2k3pcb", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("kf2k2mp", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("kf2k2mp2", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("kf2k2pla", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("kf2k2pls", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kf2k3bl", s))		   	        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kf2k3bla", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("kf2k3pl", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kf2k3upl", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kf2k5uni", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kizuna", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kizuna4p", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof10th", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof2000", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof2000n", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof2001", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof2001h", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof2002", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof2002b", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof2003", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof2003h", s))		   	        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof2k4se", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof94", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof95", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof95a", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof95h", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof96", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof96a", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof96h", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof97", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof97h", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof97k", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof97oro", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof97pls", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof98", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof98a", s))		   	        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof98h", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof98k", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof98ka", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof99", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof99e", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof99h", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof99k", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof99ka", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("kof99p", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kog", s))	                    AddGame(lpNeoGeoST, jj);
		if (!strcmp("kogplus", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("kotm", s))	                    AddGame(lpNeoGeoST, jj);
		if (!strcmp("kotm2", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("kotm2a", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kotm2p", s))		   	        AddGame(lpNeoGeoST, jj);
		if (!strcmp("kotmh", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("lans2004", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("lastblad", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("lastblada", s))			    AddGame(lpNeoGeoST, jj);
		if (!strcmp("lastbladh", s))			    AddGame(lpNeoGeoST, jj);
		if (!strcmp("lastbld2", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("lasthope", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("lastsold", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("lbowling", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("legendos", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("lresort", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("lresortp", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("magdrop2", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("magdrop3", s))		   	        AddGame(lpNeoGeoST, jj);
		if (!strcmp("maglord", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("maglordh", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("mahretsu", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("marukodq", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("matrim", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("matrimbl", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("miexchng", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("minasan", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("moshougi", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("ms5pcb", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("ms4plus", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("ms5plus", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("mslug", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("mslug2", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("mslug3", s))		   	        AddGame(lpNeoGeoST, jj);
		if (!strcmp("mslug3a", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("mslug3h", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("mslug3b6", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("mslug4", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("mslug4h", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("mslug5", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("mslug5h", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("mslug5b1", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("mslugx", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("mutnat", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("nam1975", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("ncombat", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("ncombath", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("ncommand", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("neobombe", s))		   	        AddGame(lpNeoGeoST, jj);
		if (!strcmp("neocup98", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("neodrift", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("neomrdo", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("ninjamas", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("nitd", s))			            AddGame(lpNeoGeoST, jj);
		if (!strcmp("nitdbl", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("overtop", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("panicbom", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("pbobbl2n", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("pbobblen", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("pbobblenb", s))	            AddGame(lpNeoGeoST, jj);
		if (!strcmp("pgoal", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("pnyaa", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("pnyaaa", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("popbounc", s))		   	        AddGame(lpNeoGeoST, jj);
		if (!strcmp("preisle2", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("pspikes2", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("pulstar", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("pulstara", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("puzzldpr", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("puzzledp", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("quizdai2", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("quizdais", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("quizdaisk", s))			    AddGame(lpNeoGeoST, jj);
		if (!strcmp("quizkof", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("quizkofk", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("ragnagrd", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("rbff1", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("rbff1a", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("rbff1k", s))		   	        AddGame(lpNeoGeoST, jj);
		if (!strcmp("rbff1ka", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("rbff2", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("rbff2h", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("rbff2k", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("rbffspec", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("rbffspeck", s))			    AddGame(lpNeoGeoST, jj);
		if (!strcmp("ridhero", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("ridheroh", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("roboarmy", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("roboarmya", s))	            AddGame(lpNeoGeoST, jj);
		if (!strcmp("rotd", s))	                    AddGame(lpNeoGeoST, jj);
		if (!strcmp("rotdh", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("s1945p", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("samsh5sp", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("samsh5sph", s))		   	    AddGame(lpNeoGeoST, jj);
		if (!strcmp("samsh5spho", s))	            AddGame(lpNeoGeoST, jj);
		if (!strcmp("samsho", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("samshoh", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("samshoa", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("samsho2", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("samsho2k", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("samsho2ka", s))			    AddGame(lpNeoGeoST, jj);
		if (!strcmp("samsho3", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("samsho3h", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("samsho4", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("samsho4k", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("samsho5", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("samsho5a", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("samsho5h", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("samsho5b", s))		   	        AddGame(lpNeoGeoST, jj);
		if (!strcmp("savagere", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("sbp", s))			            AddGame(lpNeoGeoST, jj);
		if (!strcmp("sdodgeb", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("sengoku", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("sengokuh", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("sengoku2", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("sengoku3", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("sengoku3a", s))		        AddGame(lpNeoGeoST, jj);
		if (!strcmp("shocktr2", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("shocktro", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("shocktroa", s))	            AddGame(lpNeoGeoST, jj);
		if (!strcmp("socbrawl", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("socbrawlh", s))		        AddGame(lpNeoGeoST, jj);
		if (!strcmp("sonicwi2", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("sonicwi3", s))		   	        AddGame(lpNeoGeoST, jj);
		if (!strcmp("spinmast", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("ssideki", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("ssideki2", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("ssideki3", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("ssideki4", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("stakwin", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("stakwindev", s))			    AddGame(lpNeoGeoST, jj);
		if (!strcmp("stakwin2", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("strhoop", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("superspy", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("svcpcb", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("svcpcba", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("svc", s))		                AddGame(lpNeoGeoST, jj);
		if (!strcmp("svcboot", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("svcplus", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("svcplusa", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("svcsplus", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("tophuntr", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("tophuntrh", s))			    AddGame(lpNeoGeoST, jj);
		if (!strcmp("tpgolf", s))		   	        AddGame(lpNeoGeoST, jj);
		if (!strcmp("trally", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("turfmast", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("twinspri", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("twsoc96", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("viewpoin", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("viewpoinp", s))			    AddGame(lpNeoGeoST, jj);
		if (!strcmp("vliner", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("vliner7e", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("vliner6e", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("vliner54", s))		            AddGame(lpNeoGeoST, jj);
		if (!strcmp("vliner53", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("wakuwak7", s))		   	        AddGame(lpNeoGeoST, jj);
		if (!strcmp("wh1", s))	                    AddGame(lpNeoGeoST, jj);
		if (!strcmp("wh1h", s))			            AddGame(lpNeoGeoST, jj);
		if (!strcmp("wh1ha", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("wh2", s))			            AddGame(lpNeoGeoST, jj);
		if (!strcmp("wh2h", s))			            AddGame(lpNeoGeoST, jj);
		if (!strcmp("wh2j", s))			            AddGame(lpNeoGeoST, jj);
		if (!strcmp("wh2ja", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("whp", s))		                AddGame(lpNeoGeoST, jj);
		if (!strcmp("wjammers", s))			        AddGame(lpNeoGeoST, jj);
		if (!strcmp("zedblade", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("zintrckb", s))	                AddGame(lpNeoGeoST, jj);
		if (!strcmp("zupapa", s))	                AddGame(lpNeoGeoST, jj);

        //MGD2
		if (!strcmp("3countbd", s))			        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("2020bbd", s))			        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("alpham2d", s))			        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("androdund", s))		        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("aofd", s))			            AddGame(lpNeoGeoMG, jj);
		if (!strcmp("bakatonod", s))	            AddGame(lpNeoGeoMG, jj);
		if (!strcmp("bstarsd", s))			        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("burningfd", s))		        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("crswordd", s))		            AddGame(lpNeoGeoMG, jj);
		if (!strcmp("cyberlipd", s))		        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("eightmand", s))	            AddGame(lpNeoGeoMG, jj);
		if (!strcmp("fatfury1d", s))			    AddGame(lpNeoGeoMG, jj);
		if (!strcmp("fbfrenzyd", s))			    AddGame(lpNeoGeoMG, jj);
		if (!strcmp("gpilotsd", s))			        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("joyjoyd", s))			        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("kotmd", s))			        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("lbowlingd", s))			    AddGame(lpNeoGeoMG, jj);
		if (!strcmp("lresortd", s))			        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("maglordd", s))			        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("minasand", s))			        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("mutnatd", s))			        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("ncombatd", s))			        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("ncommandd", s))			    AddGame(lpNeoGeoMG, jj);
		if (!strcmp("ridherod", s))		            AddGame(lpNeoGeoMG, jj);
		if (!strcmp("roboarmyd", s))			    AddGame(lpNeoGeoMG, jj);
		if (!strcmp("sengokud", s))			        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("sengoku2d", s))			    AddGame(lpNeoGeoMG, jj);
		if (!strcmp("socbrawld", s))			    AddGame(lpNeoGeoMG, jj);
		if (!strcmp("superspyd", s))			    AddGame(lpNeoGeoMG, jj);
		if (!strcmp("tpgolfd", s))			        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("trallyd", s))			        AddGame(lpNeoGeoMG, jj);
		if (!strcmp("wh1d", s))			            AddGame(lpNeoGeoMG, jj);

        // NeoSD
		if (!strcmp("3countbnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("2020bbnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("2020bbands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("2020bbhnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("alpham2nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("alpham2pnds", s))		        AddGame(lpNeoSD, jj);
		if (!strcmp("androdunnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("aodknds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("aofnds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("aof2nds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("aof2ands", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("aof3nds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("aof3knds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("b2bnds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("bakatononds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("bangbeadnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("bjourneynds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("bjourneyhnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("blazstarnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("breakersnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("breakrevnds", s))		        AddGame(lpNeoSD, jj);
		if (!strcmp("bstarsnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("bstarshnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("bstars2nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("burningfnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("burningfhnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("burningfpnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("burningfpands", s))			AddGame(lpNeoSD, jj);
		if (!strcmp("crswd2blnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("crswordnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ct2k3sands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ct2k3spnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("cthd2003nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ctomadaynds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("cyberlipnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("diggermands", s))		        AddGame(lpNeoSD, jj);
		if (!strcmp("doubledrnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("dragonshnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("eightmannds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("fatfurspnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("fatfurspands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("fatfury1nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("fatfury2nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("fatfury3nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("fbfrenzynds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("fightfevnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("fightfevands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("flipshotnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("froman2bnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("fswordsnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("galaxyfgnds", s))		        AddGame(lpNeoSD, jj);
		if (!strcmp("ganryunds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("garounds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("garoublnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("garouhnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("garouhands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("garoupnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ghostlopnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("goalx3nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("gowcaizrnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("gpilotsnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("gpilotshnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("gururinnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ironcladnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ironcladonds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("irrmazends", s))		        AddGame(lpNeoSD, jj);
		if (!strcmp("janshinnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("jockeygpnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("jockeygpands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("joyjoynds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kabukiklnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("karnovrnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kf2k2mpnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kf2k2mp2nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kf2k2plsnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kf2k2plands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kf2k3blnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kf2k3blands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kf2k3uplnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kf2k3plnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kizunands", s))		        AddGame(lpNeoSD, jj);
		if (!strcmp("kof2000nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof2000nnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof2001nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof2001hnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof2002nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof2002bnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof2003nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof2003hnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof10thnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kf10thepnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kf2k5uninds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof2k4sends", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof94nds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("kof95nds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("kof95hnds", s))		        AddGame(lpNeoSD, jj);
		if (!strcmp("kof96nds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("kof96hnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof97nds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("kof97hnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof97knds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof97plsnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof97oronds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof98nds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("kof98hnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof98knds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof98kands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof99nds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("kof99ends", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof99hnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof99knds", s))		        AddGame(lpNeoSD, jj);
		if (!strcmp("kof99kands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kof99pnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kognds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("kotmnds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("kotmhnds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("kotm2nds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("kotm2ands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("kotm2pnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("lans2004nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("lastbladnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("lastbladhnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("lastsolnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("lasthopends", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("lastbld2nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("lbowlingnds", s))		        AddGame(lpNeoSD, jj);
		if (!strcmp("legendosnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("lresortnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("lresortpnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("magdrop2nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("magdrop3nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("maglordnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("maglordhnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("mahretsunds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("marukodqnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("matrimnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("miexchngnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("minasannds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("moshouginds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ms4plusnsd", s))		        AddGame(lpNeoSD, jj);
		if (!strcmp("ms5plusnsd", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ms5pcbdnsd", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("mslugnsd", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("mslug2nsd", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("mslug2tnsd", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("mslug3nsd", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("mslug3hnsd", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("mslug3b6nsd", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("mslug4nsd", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("mslug4hnsd", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("mslug5nsd", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("mslug5hnsd", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("mslugxnsd", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("mutnatnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("nam1975nds", s))		        AddGame(lpNeoSD, jj);
		if (!strcmp("ncombatnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ncombathnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ncommandnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("neobombends", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("neocup98nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("neodriftnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("neomrdonds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ninjamasnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("nitdnds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("nitdblnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("overtopnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("panicbomnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("pbobbl2nnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("pbobblennds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("pbobblenbnds", s))		        AddGame(lpNeoSD, jj);
		if (!strcmp("pgoalnds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("pnyaands", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("pnyaaands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("popbouncnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("preisle2nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("pspikes2nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("pulstarnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("puzzldprnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("puzzledpnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("quizdai2nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("quizdaisnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("quizdaisknds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("quizkofnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("quizkofknds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ragnagrnds", s))		        AddGame(lpNeoSD, jj);
		if (!strcmp("rbff1nds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("rbff1ands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("rbff1knds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("rbff2nds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("rbff2hnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("rbff2knds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("rbffspecnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("rbffspecknds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ridheronds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ridherohnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("roboarmynds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("roboarmyands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("rotdnds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("rotdhnds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("s1945pnds", s))		        AddGame(lpNeoSD, jj);
		if (!strcmp("samsh5spnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("samsh5sphnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("samsh5sphonds", s))			AddGame(lpNeoSD, jj);
		if (!strcmp("samshonds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("samshohnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("samsho2nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("samsho2knds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("samsho2kands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("samsho3nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("samsho3hnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("samsho4nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("samsho4knds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("samsho5nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("samsho5hnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("samsho5bnds", s))		        AddGame(lpNeoSD, jj);
		if (!strcmp("savagerends", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("sbpnds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("sdodgebnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("sengokunds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("sengokuhnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("sengoku2nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("sengoku3nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("sengoku3ands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("shocktr2nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("shocktronds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("shocktroands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("socbrawlnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("socbrawlhnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("sonicwi2nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("sonicwi3nds", s))		        AddGame(lpNeoSD, jj);
		if (!strcmp("spinmastnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ssidekinds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ssideki2nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ssideki3nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("ssideki4nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("stakwinnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("stakwin2nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("strhoopnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("superspynds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("svcnds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("svcbootnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("svcplusnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("svcplusands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("svcsplusnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("svcpcbnds", s))		        AddGame(lpNeoSD, jj);
		if (!strcmp("svcpcbands", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("tophuntrnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("tophuntrhnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("tpgolfnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("trallynds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("turfmastnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("twinsprinds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("twsoc96nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("viewpoinnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("vlinernds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("vliner7ends", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("vliner6ends", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("vliner54nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("vliner53nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("wakuwak7nds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("wh1nds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("wh1hnds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("wh1hands", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("wh2nds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("wh2hnds", s))		            AddGame(lpNeoSD, jj);
		if (!strcmp("wh2jnds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("whpnds", s))			        AddGame(lpNeoSD, jj);
		if (!strcmp("wjammersnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("zedbladends", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("zintrckbnds", s))			    AddGame(lpNeoSD, jj);
		if (!strcmp("zupapands", s))			    AddGame(lpNeoSD, jj);
	}

	for (jj = 0; jj < nGames; jj++)
	{
		const char *s = GetDriverFileName(jj);

		if (s == NULL || s[0] == '\0')
			continue;

		if (!strcmp("neogeo_noslothb.cpp", s))      AddGame(lpNeoGeoHC, jj);
	}
}

void CreateCAPCOMFolders(int parent_index)
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
		if (!strcmp("vlinerdd", s))			        AddGame(lpFolder, jj);
		if (!strcmp("vliner7edd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("vliner6edd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("vliner54dd", s))			    AddGame(lpFolder, jj);
		if (!strcmp("vliner53dd", s))			    AddGame(lpFolder, jj);
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
