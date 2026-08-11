/*************************************************************************/
/*	File : CKVideoPlugin.h							 					 */
/*	Author :  Leïla AIT KACI											 */	
/*																		 */	
/*	Virtools SDK 														 */	 
/*	Copyright (c) Virtools 2005, All Rights Reserved.					 */	
/*************************************************************************/
#ifndef CKVIDEOPLUGIN_H
// {secret}
#define CKVIDEOPLUGIN_H "$Id:$"

#include "CKAll.h"
#include "CKVideo.h"

////////////////////////////////////////////////////////////////////////
// This Class is not documented to the user
// It is used for internal implementation
////////////////////////////////////////////////////////////////////////
#ifdef DOCJETDUMMY // DOCJET secret macro
#else

/*******************************************************************
Name: CK_VIDEOMANAGER_CAPS
Summary: Video Capabilities of the current manager
{Group:Video Engine}
See also: CKVideoManager, CKVideo
*********************************************************************/
typedef enum CK_VIDEOPLUGIN_CAPS 
{
	CK_VIDEOCAPS_FILE		= 0x00000001,	// Support video files
	CK_VIDEOCAPS_LIVE		= 0x00000002,	// Support live video
	CK_VIDEOCAPS_STREAM		= 0x00000004,	// Support streamed video
	CK_VIDEOCAPS_TEXTURE	= 0x00000008,	// Can play video on a texture
	CK_VIDEOCAPS_SCREEN		= 0x00000010,	// Can play video on the screen as overlay

	CK_VIDEOCAPS_SEEK		= 0x00000020,	// Can we seek in the video
	CK_VIDEOCAPS_SPEED		= 0x00000040,	// Can we change the video speed

	CK_VIDEOCAPS_RESERVED0	= 0x00000080,	// Reserved for future use
	CK_VIDEOCAPS_RESERVED1	= 0x00000100,	// Reserved for future use
	CK_VIDEOCAPS_RESERVED2	= 0x00000200,	// Reserved for future use
	CK_VIDEOCAPS_RESERVED3	= 0x00000400,	// Reserved for future use
	CK_VIDEOCAPS_RESERVED4	= 0x00000800	// Reserved for future use

} CK_VIDEOPLUGIN_CAPS;


/*******************************************************************
Name: CKVideoPlugin
Summary: Video Engine plugin abstract class defining implementation methods.
{Group:Video Engine}
Remarks:
+ The implementation plugins are implemented as external plugins.

See also: CKContext::GetVideoManager,CKVideo
*********************************************************************/
class CKVideoPlugin : public CKBaseManager
{
public :

	/*******************************************************************
	Name: UPDATE_FLAGS
	Summary: Description for UpdateSource
	{Group:Video Engine}
	See also: CKVideoManager::UpdateSource
	*********************************************************************/
	typedef enum UPDATE_FLAGS
	{
		UPDATE_TEXTUREOPTIONS,
		UPDATE_DESTINATION,
		UPDATE_BORDERCOLOR,
		UPDATE_FILLTEXTURE,
		UPDATE_LIMITTIMES,
		UPDATE_BALANCE,
		UPDATE_VOLUME,
		UPDATE_SPEED,
		UPDATE_LOOP,
		UPDATE_PRIORITY,

		UPDATE_RESERVED0,
		UPDATE_RESERVED1,
		UPDATE_RESERVED2,
		UPDATE_RESERVED3,
		UPDATE_RESERVED4,
	} UPDATE_FLAGS;

	/*************************************************
	Summary: Return a unique ID among possible sound engines
	{Group:Video Engine}
	Return Value: engine ID
	Remark: 0-10 are reserved, don't use them.
	See also: CKVideoPlugin
	**************************************************/
	virtual int GetEngineID() = 0;
	
	/*************************************************
	Summary: Get implementation error description
	Return value: The requested info
	Remarks: 
		+ The video need to be loaded to get these informations
		+ This method is thread safe. Never not access the variable directly.
	{Group:General}
	See also: CKVideoManager, CKVideo
	*************************************************/
	virtual XString GetErrorDescrition(int iError) = 0;

	/*************************************************
	Summary: Get the video capabilities of the current video manager
	{Group:Video Engine}
	Return Value: video caps
	See also: CKVideoPlugin,CK_VIDEOMANAGER_CAPS
	*************************************************/
	virtual CK_VIDEOPLUGIN_CAPS GetCaps(CKContext* iCtx) = 0;

	/*************************************************
	Summary: Get the number of video type that are supported
	{Group:Video Engine}
	Return Value: video caps
	See also: CKVideoPlugin,CK_VIDEOMANAGER_CAPS
	*************************************************/
	virtual int GetSupportedExtensionCount() = 0;

	/*************************************************
	Summary: Get the ith supported file extension that is supported
	{Group:Video Engine}
	Return Value: video caps
	See also: CKVideoPlugin,CK_VIDEOMANAGER_CAPS
	*************************************************/
	virtual CKBOOL GetSupportedExtension(int iIndex, XString& oName, XString& oExtension) = 0;

	/*************************************************
	Summary: Get information about the given video
	{Group:Video Engine}
	Input Arguments:
		iVideo: video to get information from.
	Output Arguments:
		oInfo: information on the video.
	Return Value: video caps
	See also: CKVideoPlugin,CK_VIDEOMANAGER_CAPS
	*************************************************/
	virtual CKBOOL GetVideoInfo(CKVideo* iVideo, CKVideoInfo* oInfo) = 0;

	/*************************************************
	Summary: Get the number of live source available on the current computer
	{Group:Video Engine}
	Return Value:
		+ Input filter count
	See also: CKVideoPlugin::CreateSource, CKVideoPlugin::HasSource, CKVideo
	*************************************************/
	virtual int	GetVideoInputCount() = 0;

	/*************************************************
	Summary: Get the ID of the live source with the given name
	{Group:Video Engine}
	Input Arguments:
		+ iName: name of the live source
	Return Value:
		+ Live source ID, -1 if not found.
	See also: CKVideoPlugin::CreateSource, CKVideoPlugin::HasSource, CKVideo
	*************************************************/
	virtual int	GetVideoInputID(XString& iName) = 0;

	/*************************************************
	Summary: Get a readeable name for the a video live source
	{Group:Video Engine}
	Input Arguments:
		+ iLiveID: index of the live source in the manager list
	Output Aguments:
		+ oName: name of the live source
	Return Value:
		+ Error description
	See also: CKVideoPlugin::CreateSource, CKVideoPlugin::HasSource, CKVideo
	*************************************************/
	virtual CKERROR GetVideoInputName(int iLiveID, XString& oName) = 0;

	/*************************************************
	Summary: Get the number of live source available on the current computer
	{Group:Video Engine}
	Return Value:
		+ Input filter count
	See also: CKVideoPlugin::CreateSource, CKVideoPlugin::HasSource, CKVideo
	*************************************************/
	virtual int	GetAudioInputCount() = 0;

	/*************************************************
	Summary: Get the ID of the live source with the given name
	{Group:Video Engine}
	Input Arguments:
		+ iName: name of the live source
	Return Value:
		+ Live source ID, -1 if not found.
	See also: CKVideoPlugin::CreateSource, CKVideoPlugin::HasSource, CKVideo
	*************************************************/
	virtual int	GetAudioInputID(XString& iName) = 0;

	/*************************************************
	Summary: Get a readeable name for the a video live source
	{Group:Video Engine}
	Input Arguments:
		+ iLiveID: index of the live source in the manager list
	Output Arguments:
		+ oName: name of the live source
	Return Value:
		+ Error description
	See also: CKVideoPlugin::CreateSource, CKVideoPlugin::HasSource, CKVideo
	*************************************************/
	virtual CKERROR GetAudioInputName(int iLiveID, XString& oName) = 0;

	/*************************************************
	Summary: Creates the source for the given video.
	{Group:Video Engine}
	Argument:
		+ iSource: source to get information from
	Return Value:
		+ CK_OK if success,
		+ Any video error otherwise.
	Remark:
		+ The video source is the object that implement the video management.
		+ The source is memorized in the m_Source variable of the video,
		+ The source depends on the current video manager used
		+ This method updates all video information parameters
	See also: CKVideoPlugin::DeleteSource, CKVideoPlugin::HasSource, CKVideo
	*************************************************/
	virtual CKERROR CreateSource(CKVideo* iVideo, void* iPreviewWindow=NULL) = 0;

	/*************************************************
	Summary: Delete the source of the given video.
	{Group:Video Engine}
	Argument:
		+ iSource: source to get information from
	Return Value:
		+ CK_OK if success,
		+ Any video error otherwise.
	Remark:
		+ The video source is the object that implement the video management.
		+ The source depends on the current video manager used.
		+ This methods reset all video information parameters
	See also: CKVideoPlugin::CreateSource, CKVideoPlugin::HasSource, CKVideo
	*************************************************/
	virtual CKERROR	DeleteSource(void* iSource, CKBOOL iForceSync) = 0;

	/*************************************************
	Summary: Abort request to halt the current source task as quickly as
			 possible.
	{Group:Video Engine}
	Argument:
		+ iSource: source to get information from
		+ iTexture: texture where to save the captures image
	Return Value:
		+ CK_OK if success,
		+ Any video error otherwise.
	Remark:
		+ This method should not change the target texture format, if needed,
		  we must warn the user by documenting it or returning a value saying
		  so.
	See also: CKVideoPlugin::CreateSource, CKVideoPlugin::HasSource, CKVideo
	*************************************************/
	virtual CKERROR AbortSource(void* iSource) = 0;

	/*************************************************
	Summary: Update a video source after a modification on the given video
	{Group:Video Engine}
	Argument:
		+ iSource: source to get information from
		+ iFlag: flag describing the change that was done. Can be any of
				 CKVideoManager::UPDATE_FLAGS
	Return Value:
		+ CK_OK if success,
		+ Any video error otherwise.
	Remark:
		+ The video source is the object that implement the video management.
		+ The source depends on the current video manager used.
	See also: CKVideoPlugin::CreateSource, CKVideoPlugin::HasSource, CKVideo
	*************************************************/
	virtual CKERROR UpdateSource(void* iSource, UPDATE_FLAGS iFlag) = 0;

	/*************************************************
	Summary: Play a video source
	{Group:Video Engine}
	Argument:
		+ iSource: source to get information from
	Return Value:
		+ CK_OK if success,
		+ Any video error otherwise.
	Remark:
		+ The video source is the object that implement the video management.
		+ The source depends on the current video manager used.
	See also: CKVideoPlugin::CreateSource, CKVideoPlugin::HasSource, CKVideo
	*************************************************/
	virtual CKERROR PlaySource(void* iSource) = 0;

	/*************************************************
	Summary: Pause a video sources
	{Group:Video Engine}
	Argument:
		+ iSource: source to get information from
	Return Value:
		+ CK_OK if success,
		+ Any video error otherwise.
	Remark:
		+ The video source is the object that implement the video management.
		+ The source depends on the current video manager used.
	See also: CKVideoPlugin::CreateSource, CKVideoPlugin::HasSource, CKVideo
	*************************************************/
	virtual CKERROR PauseSource(void* iSource) = 0;

	/*************************************************
	Summary: Stop a video sources
	{Group:Video Engine}
	Argument:
		+ iSource: source to get information from
	Return Value:
		+ CK_OK if success,
		+ Any video error otherwise.
	Remark:
		+ The video source is the object that implement the video management.
		+ The source depends on the current video manager used.
	See also: CKVideoPlugin::CreateSource, CKVideoPlugin::HasSource, CKVideo
	*************************************************/
	virtual CKERROR StopSource(void* iSource) = 0;

	/*************************************************
	Summary: Seek a video source
	{Group:Video Engine}
	Argument:
		+ iSource: source to get information from
		+ iTime: time position (in ms) where to seek to.
	Return Value:
		+ CK_OK if success,
		+ Any video error otherwise.
	Remark:
		+ The video source is the object that implement the video management.
		+ The source depends on the current video manager used.
	See also: CKVideoPlugin::CreateSource, CKVideoPlugin::HasSource, CKVideo
	*************************************************/
	virtual CKERROR SeekSource(void* iSource, float iTime) = 0;

	/*************************************************
	Summary: Get the current position of a video source.
	{Group:Video Engine}
	Argument:
		+ iSource: source to get information from
	Return Value:
		+ Current position (time in ms)
	Remark:
		+ The video source is the object that implement the video management.
		+ The source depends on the current video manager used.
	See also: CKVideoPlugin::CreateSource, CKVideoPlugin::HasSource, CKVideo
	*************************************************/
	virtual float GetSourceTime(void* iSource) = 0;
	
	/*************************************************
	Summary: Capture the current video image in the given texture.
	{Group:Video Engine}
	Argument:
		+ iSource: source to get information from
		+ iTexture: texture where to save the captures image
	Return Value:
		+ CK_OK if success,
		+ Any video error otherwise.
	Remark:
		+ This method should not change the target texture format, if needed,
		  we must warn the user by documenting it or returning a value saying
		  so.
	See also: CKVideoPlugin::CreateSource, CKVideoPlugin::HasSource, CKVideo
	*************************************************/
	virtual CKERROR CaptureImage(void* iSource, CKTexture* iTarget) = 0;

	////////////////////////////////////////////////////////////////////////
	// User Undocumented Variables
	////////////////////////////////////////////////////////////////////////
	//{secret}
	CKVideoPlugin(CKContext *iCtx, CKGUID iGuid, CKSTRING iName) : CKBaseManager(iCtx, iGuid, iName) {};
	//{secret}
	virtual ~CKVideoPlugin() {};
};


#endif // DOCJET secret macro
#endif
