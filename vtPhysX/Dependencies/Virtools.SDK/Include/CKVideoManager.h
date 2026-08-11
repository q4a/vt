/*************************************************************************/
/*	File : CKVideoManager.h							 					 */
/*	Author :  Leïla AIT KACI											 */	
/*																		 */	
/*	Virtools SDK 														 */	 
/*	Copyright (c) Virtools 2005, All Rights Reserved.					 */	
/*************************************************************************/
#ifndef CKVIDEOMANAGER_H
// {secret}
#define CKVIDEOMANAGER_H "$Id:$"

#include "CKVideoPlugin.h"

// {secret}
#define VIDEO_MANAGER_GUID			CKGUID(0x708e5583,0x5fb76e88)
// {secret}
#define CKPGUID_VIDEOCAPTURE		CKGUID(0x2b6b0813,0x1a8060a)
// {secret}
#define CKPGUID_AUDIOCAPTURE		CKGUID(0x476d205c,0x1c7375e)
// {secret}
#define CKPGUID_VIDEOINTYPE			CKGUID(0x58e654b5,0x6a0b5336)
// {secret}
#define CKPGUID_VIDEOOUTTYPE		CKGUID(0x40904f0,0x39d50d96)
// {secret}
#define CKPGUID_VIDEOSTATE			CKGUID(0xb510214,0x16c12ee3)
// {secret}
#define VIDEOVAR_SAVEOPTIONS		"File Options/Videos"
// {secret}
#define VIDEOVAR_ENGINE				"Video/Engine"
// {secret}
#define VIDEOVAR_PRIORITY			"Video/Priority"
// {secret}
#define VIDEOVAR_FPS				"Video/Rate Limit For Screen"
// {secret}
#define VIDEOVAR_EXPORTGRAPH		"Video/Export Decompression Graph"
// {secret}
#define VIDEO_MAX_WAIT				4000	// Max wait time is 4s
// {secret}
#define VIDEO_STEP_WAIT				 100	// Step wait time is 100ms
// {secret} Max size for a video url or file path {secret}
#define VIDEO_MAX_PATH				512		// {secret}

/*******************************************************************
Name: CKVideoManager
Summary: Video Plugin Manager.
{Group:Video Engine}
Remarks:
+ The video manager is implemented by an external plugin.
+ The currently used instance of this class may be retrieved through the 
  CKContext::GetVideoManager() method

See also: CKContext::GetVideoManager,CKVideo
*********************************************************************/
class CKVideoManager :	public CKBaseManager,
						public CKVariableManager::Watcher
{
public :

////////////////////////////////////////////////////////////////////////
// User Documented Methods
////////////////////////////////////////////////////////////////////////

	/*************************************************
	Summary: Get the video capabilities of the current video manager
	{Group:General}
	Return Value: video caps
	See also: CKVideoManager,CK_VIDEOMANAGER_CAPS
	*************************************************/
	static CKGUID GetGUID()	{ return VIDEO_MANAGER_GUID; };
	
	/*************************************************
	Summary: Create a new CKVideo.
	Return value: The requested info
	Remark:
		+ This method is implemented for VSL Binding.
	{Group:General}
	See also: CKVideoManager, CKVideo
	*************************************************/
	virtual CKVideo* CreateVideo(CKSTRING iName, CK_OBJECTCREATION_OPTIONS iOptions);

	/*************************************************
	Summary: Register a new video object
	{Group:Video Management}
	Input Arguments:
		iVideo: video object to register
	Remark: Called at CKVideo creation
	See also: CKVideo::CKVideo
	*************************************************/
	virtual CKERROR RegisterVideo(CKVideo* iVideo);

	/*************************************************
	Summary: Unregister a video object
	{Group:Video Management}
	Input Arguments:
		iVideo: video object to register
	Remark: Called at CKVideo destruction
	See also: CKVideo::~CKVideo
	*************************************************/
	virtual CKERROR UnregisterVideo(CKVideo* iVideo);

	/*************************************************
	Summary: Get the number of registered videos
	{Group:Video Management}
	See also: CKVideo::CKVideo
	*************************************************/
	virtual int GetVideoCount();

	/*************************************************
	Summary: Get the number of registered videos
	{Group:Video Management}
	Input Arguments:
		iIndex: Video to retrieve
	See also: CKVideo::CKVideo
	*************************************************/
	virtual CKVideo* GetVideo(int iIndex);

	/*************************************************
	Summary: Register a new video implementation Plugin 
	{Group:Plugin Management}
	Input Arguments:
		iPlugin: plugin implementing the video
	See also: CKVideoPlugin
	*************************************************/
	virtual CKERROR RegisterVideoPlugin(CKVideoPlugin* iPlugin);

	/*************************************************
	Summary: Unregister a video implementation plugin 
	{Group:Plugin Management}
	Input Arguments:
		iPlugin: plugin implementing the video
	See also: CKVideoPlugin
	*************************************************/
	virtual CKERROR UnregisterVideoPlugin(CKVideoPlugin* iPlugin);

	/*************************************************
	Summary: Get a video plugin. Give 0 for best plugin.
	{Group:Plugin Management}
	Return Value: A video plugin
	Remark: If several are available, returns the first one.
	See also: CKVideoPlugin
	*************************************************/
	virtual CKVideoPlugin* GetVideoPlugin(int iIndex=0);

	/*************************************************
	Summary: Get a video plugin from its name
	{Group:Plugin Management}
	Return Value: A video plugin
	Remark: If several are available, returns the first one.
	See also: CKVideoPlugin
	*************************************************/
	virtual CKVideoPlugin* GetVideoPluginByName(XString& iName);

	/*************************************************
	Summary: Get a video plugin from its GUID
	{Group:Plugin Management}
	Return Value: a video plugin
	See also: CKVideoPlugin
	*************************************************/
	virtual CKVideoPlugin* GetVideoPluginByGuid(CKGUID iGuid);

	/*************************************************
	Summary: Get the currently selected video plugin
	{Group:Plugin Management}
	Return Value: A video plugin
	See also: CKVideoPlugin
	*************************************************/
	virtual CKVideoPlugin* GetActivePlugin();

	/*************************************************
	Summary: Get the video global save options
	{Group:Options}
	Return Value: saving options
	See also: CKVideoPlugin
	*************************************************/
	virtual CK_VIDEO_SAVEOPTION	GetSaveOptions();

	/*************************************************
	Summary: Set the video global save options
	{Group:Options}
	Return Value: saving options
	See also: CKVideoPlugin
	*************************************************/
	virtual void SetSaveOptions(CK_VIDEO_SAVEOPTION iOptions);

	/*************************************************
	Summary: Get the current process rate limitation in
			 the screen mode.
	{Group:Options}
	Return Value: 
		+ Rate Limitation. A <=0 value means that no behavior
		  rate limitation is set in screen mode.
	See also: CKVideoPlugin
	*************************************************/
	virtual float GetFrameRateForScreenMode();

	/*************************************************
	Summary: Set a process rate limitation in the screen mode.
	{Group:Options}
	Input Arguments:
		iFPS: rate limitation. When this value is <=0, no 
		  limitation is set.
	See also: CKVideoPlugin
	*************************************************/
	virtual void SetFrameRateForScreenMode(float iFPS);

	/*************************************************
	Summary: Unload all videos' sources and/or preview
	{Group:Video Management}
	Input Arguments:
		iSource: Should we unload the sources
		iPreview: Should we unload the previews
		iForceSync: when this parameter is true, we force a synchronous 
		  unloading whatever syncrhonous parameter is set on the video.
	See also: CKVideoPlugin
	*************************************************/
	virtual void UnloadAllVideos(CKBOOL iSource, CKBOOL iPreview, CKBOOL iForceSync=FALSE);
	
////////////////////////////////////////////////////////////////////////
// User Undocumented Methods
////////////////////////////////////////////////////////////////////////
#ifdef DOCJETDUMMY // DOCJET secret macro
#else
	CKVideoManager(CKContext *iCtx);
	virtual ~CKVideoManager();

	////////////////////////////////////////////////////////////////////////
	// User Undocumented Methods
	////////////////////////////////////////////////////////////////////////
	static void			RegisterCKVideo			();
	virtual void		PostWrite				(const char* iName);
	virtual void		BindForVSL				(CKContext* iCtx);

	virtual CKERROR		OnCKInit				();
	virtual CKERROR		OnCKEnd					();
	virtual CKERROR		OnCKPlay				();
	virtual CKERROR		OnCKReset				();
	virtual CKERROR		OnCKPause				();
	virtual CKERROR		PreProcess				();
	virtual CKERROR		SequenceToBeDeleted		(CK_ID *objids,int count);

	CKDWORD	GetValidFunctionsMask() 
	{
		return	CKMANAGER_FUNC_OnCKInit					|
				CKMANAGER_FUNC_OnCKEnd					|
				CKMANAGER_FUNC_OnCKPlay					|
				CKMANAGER_FUNC_OnCKPause				|
				CKMANAGER_FUNC_OnCKReset				|
				CKMANAGER_FUNC_PreProcess				|
				CKMANAGER_FUNC_OnSequenceToBeDeleted	;
	};

	virtual int GetFunctionPriority(CKMANAGER_FUNCTIONS Function)
	{  
        if (Function==CKMANAGER_FUNC_OnCKInit) 
			return (-MAX_MANAGERFUNC_PRIORITY); // latest Priority
		else
	        return 0;
	}

	////////////////////////////////////////////////////////////////////////
	// User Undocumented Variables
	////////////////////////////////////////////////////////////////////////
	XArray<CKVideo*>			m_Videos;					// List of existing videos

	XArray<CKVideoPlugin*>		m_VideoPlugins;				// List of available video plugin
	XString						m_PluginDescription;		// Description for the variable manager
	int							m_ActivePlugin;				// Video engine that is currently active
	int							m_SelectedPlugin;			// Video engine currently selected

	XString						m_SaveOptionsDescription;	// Description for the variable manager
	int							m_SelectedSaveOptions;		// Global video saving option

	XString						m_PriorityDescription;		// Description for the variable manager
	int							m_SelectedPriority;			// Default priority for asynchronous videos

	float						m_ScreenFrameRate;			// FPS to use when in screen mode.
	CKBOOL						m_ExportGraph;				// Export the decompression graph

#endif // DOCJET secret macro
};

#endif
