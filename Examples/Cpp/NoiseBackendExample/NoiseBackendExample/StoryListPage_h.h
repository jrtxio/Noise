/* Header file automatically generated from StoryListPage.idl */
/*
 * File built with Microsoft(R) MIDLRT Compiler Engine Version 10.00.0231 
 */

#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

/* verify that the <rpcsal.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCSAL_H_VERSION__
#define __REQUIRED_RPCSAL_H_VERSION__ 100
#endif

#include <rpc.h>
#include <rpcndr.h>

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#include <ole2.h>
#endif /*COM_NO_WINDOWS_H*/
#ifndef __StoryListPage_h_h__
#define __StoryListPage_h_h__
#ifndef __StoryListPage_h_p_h__
#define __StoryListPage_h_p_h__


#pragma once

// Ensure that the setting of the /ns_prefix command line switch is consistent for all headers.
// If you get an error from the compiler indicating "warning C4005: 'CHECK_NS_PREFIX_STATE': macro redefinition", this
// indicates that you have included two different headers with different settings for the /ns_prefix MIDL command line switch
#if !defined(DISABLE_NS_PREFIX_CHECKS)
#define CHECK_NS_PREFIX_STATE "never"
#endif // !defined(DISABLE_NS_PREFIX_CHECKS)


#pragma push_macro("MIDL_CONST_ID")
#undef MIDL_CONST_ID
#define MIDL_CONST_ID const __declspec(selectany)


// Header files for imported files
#include "winrtbase.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0.18362\Microsoft.Foundation.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0.18362\Microsoft.Graphics.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0\Microsoft.UI.Text.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0.18362\Microsoft.UI.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0\Microsoft.UI.Xaml.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0\Microsoft.Web.WebView2.Core.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0\Microsoft.Windows.ApplicationModel.DynamicDependency.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0\Microsoft.Windows.ApplicationModel.Resources.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0\Microsoft.Windows.ApplicationModel.WindowsAppRuntime.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0\Microsoft.Windows.AppLifecycle.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0\Microsoft.Windows.AppNotifications.Builder.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0\Microsoft.Windows.AppNotifications.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0\Microsoft.Windows.Management.Deployment.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0\Microsoft.Windows.PushNotifications.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0\Microsoft.Windows.Security.AccessControl.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0\Microsoft.Windows.System.Power.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0\Microsoft.Windows.System.h"
#include "D:\Codes\Noise\Examples\Cpp\NoiseBackendExample\packages\Microsoft.WindowsAppSDK.1.5.240311000\lib\uap10.0\Microsoft.Windows.Widgets.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.AI.Actions.ActionsContract\8.0.0.0\Windows.AI.Actions.ActionsContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.AI.Agents.AgentsContract\2.0.0.0\Windows.AI.Agents.AgentsContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.AI.MachineLearning.MachineLearningContract\5.0.0.0\Windows.AI.MachineLearning.MachineLearningContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.AI.MachineLearning.Preview.MachineLearningPreviewContract\2.0.0.0\Windows.AI.MachineLearning.Preview.MachineLearningPreviewContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.Activation.ActivatedEventsContract\1.0.0.0\Windows.ApplicationModel.Activation.ActivatedEventsContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.Activation.ActivationCameraSettingsContract\1.0.0.0\Windows.ApplicationModel.Activation.ActivationCameraSettingsContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.Activation.ContactActivatedEventsContract\1.0.0.0\Windows.ApplicationModel.Activation.ContactActivatedEventsContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.Activation.WebUISearchActivatedEventsContract\1.0.0.0\Windows.ApplicationModel.Activation.WebUISearchActivatedEventsContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.Background.BackgroundAlarmApplicationContract\1.0.0.0\Windows.ApplicationModel.Background.BackgroundAlarmApplicationContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.Calls.Background.CallsBackgroundContract\4.0.0.0\Windows.ApplicationModel.Calls.Background.CallsBackgroundContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.Calls.CallsPhoneContract\7.0.0.0\Windows.ApplicationModel.Calls.CallsPhoneContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.Calls.CallsVoipContract\5.0.0.0\Windows.ApplicationModel.Calls.CallsVoipContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.Calls.LockScreenCallContract\1.0.0.0\Windows.ApplicationModel.Calls.LockScreenCallContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.CommunicationBlocking.CommunicationBlockingContract\2.0.0.0\Windows.ApplicationModel.CommunicationBlocking.CommunicationBlockingContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.FullTrustAppContract\2.0.0.0\Windows.ApplicationModel.FullTrustAppContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.Preview.InkWorkspace.PreviewInkWorkspaceContract\1.0.0.0\Windows.ApplicationModel.Preview.InkWorkspace.PreviewInkWorkspaceContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.Preview.Notes.PreviewNotesContract\2.0.0.0\Windows.ApplicationModel.Preview.Notes.PreviewNotesContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.Resources.Management.ResourceIndexerContract\2.0.0.0\Windows.ApplicationModel.Resources.Management.ResourceIndexerContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.Search.Core.SearchCoreContract\1.0.0.0\Windows.ApplicationModel.Search.Core.SearchCoreContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.Search.SearchContract\1.0.0.0\Windows.ApplicationModel.Search.SearchContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.SocialInfo.SocialInfoContract\2.0.0.0\Windows.ApplicationModel.SocialInfo.SocialInfoContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.StartupTaskContract\3.0.0.0\Windows.ApplicationModel.StartupTaskContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.ApplicationModel.Wallet.WalletContract\2.0.0.0\Windows.ApplicationModel.Wallet.WalletContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Devices.Custom.CustomDeviceContract\1.0.0.0\Windows.Devices.Custom.CustomDeviceContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Devices.DevicesLowLevelContract\3.0.0.0\Windows.Devices.DevicesLowLevelContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Devices.Portable.PortableDeviceContract\1.0.0.0\Windows.Devices.Portable.PortableDeviceContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Devices.Power.PowerGridApiContract\1.0.0.0\Windows.Devices.Power.PowerGridApiContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Devices.Printers.Extensions.ExtensionsContract\2.0.0.0\Windows.Devices.Printers.Extensions.ExtensionsContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Devices.Printers.PrintersContract\1.0.0.0\Windows.Devices.Printers.PrintersContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Devices.Scanners.ScannerDeviceContract\1.0.0.0\Windows.Devices.Scanners.ScannerDeviceContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Devices.SmartCards.SmartCardBackgroundTriggerContract\3.0.0.0\Windows.Devices.SmartCards.SmartCardBackgroundTriggerContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Devices.SmartCards.SmartCardEmulatorContract\6.0.0.0\Windows.Devices.SmartCards.SmartCardEmulatorContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Devices.Sms.LegacySmsApiContract\1.0.0.0\Windows.Devices.Sms.LegacySmsApiContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Foundation.FoundationContract\4.0.0.0\Windows.Foundation.FoundationContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Foundation.UniversalApiContract\19.0.0.0\Windows.Foundation.UniversalApiContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Gaming.Input.GamingInputPreviewContract\2.0.0.0\Windows.Gaming.Input.GamingInputPreviewContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Gaming.Preview.GamesEnumerationContract\2.0.0.0\Windows.Gaming.Preview.GamesEnumerationContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Gaming.UI.GameChatOverlayContract\1.0.0.0\Windows.Gaming.UI.GameChatOverlayContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Gaming.UI.GamingUIProviderContract\1.0.0.0\Windows.Gaming.UI.GamingUIProviderContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Gaming.XboxLive.StorageApiContract\1.0.0.0\Windows.Gaming.XboxLive.StorageApiContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Globalization.GlobalizationJapanesePhoneticAnalyzerContract\1.0.0.0\Windows.Globalization.GlobalizationJapanesePhoneticAnalyzerContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Graphics.Printing3D.Printing3DContract\4.0.0.0\Windows.Graphics.Printing3D.Printing3DContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Management.Deployment.Preview.DeploymentPreviewContract\1.0.0.0\Windows.Management.Deployment.Preview.DeploymentPreviewContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Management.Deployment.SharedPackageContainerContract\1.0.0.0\Windows.Management.Deployment.SharedPackageContainerContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Management.Update.WindowsUpdateContract\2.1.0.0\Windows.Management.Update.WindowsUpdateContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Management.Workplace.WorkplaceSettingsContract\1.0.0.0\Windows.Management.Workplace.WorkplaceSettingsContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Media.AppBroadcasting.AppBroadcastingContract\1.0.0.0\Windows.Media.AppBroadcasting.AppBroadcastingContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Media.AppRecording.AppRecordingContract\1.0.0.0\Windows.Media.AppRecording.AppRecordingContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Media.Capture.AppBroadcastContract\2.0.0.0\Windows.Media.Capture.AppBroadcastContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Media.Capture.AppCaptureContract\4.0.0.0\Windows.Media.Capture.AppCaptureContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Media.Capture.AppCaptureMetadataContract\1.0.0.0\Windows.Media.Capture.AppCaptureMetadataContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Media.Capture.CameraCaptureUIContract\1.0.0.0\Windows.Media.Capture.CameraCaptureUIContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Media.Capture.GameBarContract\1.0.0.0\Windows.Media.Capture.GameBarContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Media.Devices.CallControlContract\1.0.0.0\Windows.Media.Devices.CallControlContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Media.MediaControlContract\1.0.0.0\Windows.Media.MediaControlContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Media.Playlists.PlaylistsContract\1.0.0.0\Windows.Media.Playlists.PlaylistsContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Media.Protection.ProtectionRenewalContract\1.0.0.0\Windows.Media.Protection.ProtectionRenewalContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Networking.Connectivity.WwanContract\3.0.0.0\Windows.Networking.Connectivity.WwanContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Networking.NetworkOperators.LegacyNetworkOperatorsContract\1.0.0.0\Windows.Networking.NetworkOperators.LegacyNetworkOperatorsContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Networking.Sockets.ControlChannelTriggerContract\3.0.0.0\Windows.Networking.Sockets.ControlChannelTriggerContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Networking.XboxLive.XboxLiveSecureSocketsContract\1.0.0.0\Windows.Networking.XboxLive.XboxLiveSecureSocketsContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Perception.Automation.Core.PerceptionAutomationCoreContract\1.0.0.0\Windows.Perception.Automation.Core.PerceptionAutomationCoreContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Security.EnterpriseData.EnterpriseDataContract\5.0.0.0\Windows.Security.EnterpriseData.EnterpriseDataContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Security.ExchangeActiveSyncProvisioning.EasContract\1.0.0.0\Windows.Security.ExchangeActiveSyncProvisioning.EasContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Security.Isolation.Isolatedwindowsenvironmentcontract\5.0.0.0\Windows.Security.Isolation.Isolatedwindowsenvironmentcontract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Services.Maps.GuidanceContract\3.0.0.0\Windows.Services.Maps.GuidanceContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Services.Maps.LocalSearchContract\4.0.0.0\Windows.Services.Maps.LocalSearchContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Services.Store.StoreContract\4.0.0.0\Windows.Services.Store.StoreContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Services.TargetedContent.TargetedContentContract\1.0.0.0\Windows.Services.TargetedContent.TargetedContentContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Storage.Provider.CloudFilesContract\7.0.0.0\Windows.Storage.Provider.CloudFilesContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.System.Power.Thermal.PowerThermalApiContract\1.0.0.0\Windows.System.Power.Thermal.PowerThermalApiContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\windows.system.profile.platformautomaticappsignincontract\1.0.0.0\windows.system.profile.platformautomaticappsignincontract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.System.Profile.ProfileHardwareTokenContract\1.0.0.0\Windows.System.Profile.ProfileHardwareTokenContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.System.Profile.ProfileRetailInfoContract\1.0.0.0\Windows.System.Profile.ProfileRetailInfoContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.System.Profile.ProfileSharedModeContract\2.0.0.0\Windows.System.Profile.ProfileSharedModeContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.System.Profile.SystemManufacturers.SystemManufacturersContract\3.0.0.0\Windows.System.Profile.SystemManufacturers.SystemManufacturersContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.System.SystemManagementContract\7.0.0.0\Windows.System.SystemManagementContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.System.UserProfile.UserProfileContract\2.0.0.0\Windows.System.UserProfile.UserProfileContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.System.UserProfile.UserProfileLockScreenContract\1.0.0.0\Windows.System.UserProfile.UserProfileLockScreenContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.UI.ApplicationSettings.ApplicationsSettingsContract\1.0.0.0\Windows.UI.ApplicationSettings.ApplicationsSettingsContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.UI.Core.AnimationMetrics.AnimationMetricsContract\1.0.0.0\Windows.UI.Core.AnimationMetrics.AnimationMetricsContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.UI.Core.CoreWindowDialogsContract\1.0.0.0\Windows.UI.Core.CoreWindowDialogsContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.UI.Input.Preview.Text.PreviewTextContract\1.0.0.0\Windows.UI.Input.Preview.Text.PreviewTextContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.UI.Shell.SecurityAppManagerContract\1.0.0.0\Windows.UI.Shell.SecurityAppManagerContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.UI.Shell.WindowTabManagerContract\1.0.0.0\Windows.UI.Shell.WindowTabManagerContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.UI.UIAutomation.UIAutomationContract\2.0.0.0\Windows.UI.UIAutomation.UIAutomationContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.UI.ViewManagement.ViewManagementViewScalingContract\1.0.0.0\Windows.UI.ViewManagement.ViewManagementViewScalingContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.UI.Xaml.Core.Direct.XamlDirectContract\5.0.0.0\Windows.UI.Xaml.Core.Direct.XamlDirectContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.UI.Xaml.Hosting.HostingContract\5.0.0.0\Windows.UI.Xaml.Hosting.HostingContract.h"
#include "C:\Program Files (x86)\Windows Kits\10\References\10.0.26100.0\Windows.Web.Http.Diagnostics.HttpDiagnosticsContract\2.0.0.0\Windows.Web.Http.Diagnostics.HttpDiagnosticsContract.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_NoiseBackendExample_CIStoryItem_FWD_DEFINED__
#define ____x_NoiseBackendExample_CIStoryItem_FWD_DEFINED__

namespace NoiseBackendExample {
    interface IStoryItem;
} /* NoiseBackendExample */
#define __x_NoiseBackendExample_CIStoryItem NoiseBackendExample::IStoryItem

#endif // ____x_NoiseBackendExample_CIStoryItem_FWD_DEFINED__

#ifndef ____x_NoiseBackendExample_CIStoryItemFactory_FWD_DEFINED__
#define ____x_NoiseBackendExample_CIStoryItemFactory_FWD_DEFINED__

namespace NoiseBackendExample {
    interface IStoryItemFactory;
} /* NoiseBackendExample */
#define __x_NoiseBackendExample_CIStoryItemFactory NoiseBackendExample::IStoryItemFactory

#endif // ____x_NoiseBackendExample_CIStoryItemFactory_FWD_DEFINED__

#ifndef ____x_NoiseBackendExample_CIStoryListPage_FWD_DEFINED__
#define ____x_NoiseBackendExample_CIStoryListPage_FWD_DEFINED__

namespace NoiseBackendExample {
    interface IStoryListPage;
} /* NoiseBackendExample */
#define __x_NoiseBackendExample_CIStoryListPage NoiseBackendExample::IStoryListPage

#endif // ____x_NoiseBackendExample_CIStoryListPage_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions


#ifndef DEF___FIIterator_1_IInspectable_USE
#define DEF___FIIterator_1_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("44a94f2d-04f8-5091-b336-be7892dd10be"))
IIterator<IInspectable*> : IIterator_impl<IInspectable*> 
{
    static const wchar_t* z_get_rc_name_impl() 
    {
        return L"Windows.Foundation.Collections.IIterator`1<Object>"; 
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<IInspectable*> __FIIterator_1_IInspectable_t;
#define __FIIterator_1_IInspectable Windows::Foundation::Collections::__FIIterator_1_IInspectable_t
/* Collections */ } /* Foundation */ } /* Windows */ } 

////  Define an alias for the C version of the interface for compatibility purposes.
//#define __FIIterator_1_IInspectable Windows::Foundation::Collections::IIterator<IInspectable*>
//#define __FIIterator_1_IInspectable_t Windows::Foundation::Collections::IIterator<IInspectable*>
#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_IInspectable_USE */





#ifndef DEF___FIIterable_1_IInspectable_USE
#define DEF___FIIterable_1_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("092b849b-60b1-52be-a44a-6fe8e933cbe4"))
IIterable<IInspectable*> : IIterable_impl<IInspectable*> 
{
    static const wchar_t* z_get_rc_name_impl() 
    {
        return L"Windows.Foundation.Collections.IIterable`1<Object>"; 
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<IInspectable*> __FIIterable_1_IInspectable_t;
#define __FIIterable_1_IInspectable Windows::Foundation::Collections::__FIIterable_1_IInspectable_t
/* Collections */ } /* Foundation */ } /* Windows */ } 

////  Define an alias for the C version of the interface for compatibility purposes.
//#define __FIIterable_1_IInspectable Windows::Foundation::Collections::IIterable<IInspectable*>
//#define __FIIterable_1_IInspectable_t Windows::Foundation::Collections::IIterable<IInspectable*>
#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_IInspectable_USE */





#ifndef DEF___FIVectorView_1_IInspectable_USE
#define DEF___FIVectorView_1_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("a6487363-b074-5c60-ab16-866dce4ee54d"))
IVectorView<IInspectable*> : IVectorView_impl<IInspectable*> 
{
    static const wchar_t* z_get_rc_name_impl() 
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Object>"; 
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<IInspectable*> __FIVectorView_1_IInspectable_t;
#define __FIVectorView_1_IInspectable Windows::Foundation::Collections::__FIVectorView_1_IInspectable_t
/* Collections */ } /* Foundation */ } /* Windows */ } 

////  Define an alias for the C version of the interface for compatibility purposes.
//#define __FIVectorView_1_IInspectable Windows::Foundation::Collections::IVectorView<IInspectable*>
//#define __FIVectorView_1_IInspectable_t Windows::Foundation::Collections::IVectorView<IInspectable*>
#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_IInspectable_USE */





#ifndef DEF___FIVector_1_IInspectable_USE
#define DEF___FIVector_1_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("b32bdca4-5e52-5b27-bc5d-d66a1a268c2a"))
IVector<IInspectable*> : IVector_impl<IInspectable*> 
{
    static const wchar_t* z_get_rc_name_impl() 
    {
        return L"Windows.Foundation.Collections.IVector`1<Object>"; 
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<IInspectable*> __FIVector_1_IInspectable_t;
#define __FIVector_1_IInspectable Windows::Foundation::Collections::__FIVector_1_IInspectable_t
/* Collections */ } /* Foundation */ } /* Windows */ } 

////  Define an alias for the C version of the interface for compatibility purposes.
//#define __FIVector_1_IInspectable Windows::Foundation::Collections::IVector<IInspectable*>
//#define __FIVector_1_IInspectable_t Windows::Foundation::Collections::IVector<IInspectable*>
#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_IInspectable_USE */





#ifndef DEF___FVectorChangedEventHandler_1_IInspectable_USE
#define DEF___FVectorChangedEventHandler_1_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("b423a801-d35e-56b9-813b-00889536cb98"))
VectorChangedEventHandler<IInspectable*> : VectorChangedEventHandler_impl<IInspectable*> 
{
    static const wchar_t* z_get_rc_name_impl() 
    {
        return L"Windows.Foundation.Collections.VectorChangedEventHandler`1<Object>"; 
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef VectorChangedEventHandler<IInspectable*> __FVectorChangedEventHandler_1_IInspectable_t;
#define __FVectorChangedEventHandler_1_IInspectable Windows::Foundation::Collections::__FVectorChangedEventHandler_1_IInspectable_t
/* Collections */ } /* Foundation */ } /* Windows */ } 

////  Define an alias for the C version of the interface for compatibility purposes.
//#define __FVectorChangedEventHandler_1_IInspectable Windows::Foundation::Collections::VectorChangedEventHandler<IInspectable*>
//#define __FVectorChangedEventHandler_1_IInspectable_t Windows::Foundation::Collections::VectorChangedEventHandler<IInspectable*>
#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FVectorChangedEventHandler_1_IInspectable_USE */





#ifndef DEF___FIObservableVector_1_IInspectable_USE
#define DEF___FIObservableVector_1_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("7b81c56a-0985-518d-baa9-0da9ae009f65"))
IObservableVector<IInspectable*> : IObservableVector_impl<IInspectable*> 
{
    static const wchar_t* z_get_rc_name_impl() 
    {
        return L"Windows.Foundation.Collections.IObservableVector`1<Object>"; 
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IObservableVector<IInspectable*> __FIObservableVector_1_IInspectable_t;
#define __FIObservableVector_1_IInspectable Windows::Foundation::Collections::__FIObservableVector_1_IInspectable_t
/* Collections */ } /* Foundation */ } /* Windows */ } 

////  Define an alias for the C version of the interface for compatibility purposes.
//#define __FIObservableVector_1_IInspectable Windows::Foundation::Collections::IObservableVector<IInspectable*>
//#define __FIObservableVector_1_IInspectable_t Windows::Foundation::Collections::IObservableVector<IInspectable*>
#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIObservableVector_1_IInspectable_USE */






namespace NoiseBackendExample {
    class StoryItem;
} /* NoiseBackendExample */



/*
 *
 * Interface NoiseBackendExample.IStoryItem
 *
 * Interface is a part of the implementation of type NoiseBackendExample.StoryItem
 *
 *
 * The IID for this interface was automatically generated by MIDLRT.
 *
 * Interface IID generation seed: NoiseBackendExample.IStoryItem:HRESULT get_Id(UInt64*);HRESULT get_Title(String*);HRESULT get_CommentCount(UInt64*);
 *
 *
 */
#if !defined(____x_NoiseBackendExample_CIStoryItem_INTERFACE_DEFINED__)
#define ____x_NoiseBackendExample_CIStoryItem_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_NoiseBackendExample_IStoryItem[] = L"NoiseBackendExample.IStoryItem";

namespace NoiseBackendExample {
    /* [uuid("4cc4441f-bd5e-5bd2-87f8-7a7e686d4c9a"), version, object, exclusiveto] */
    MIDL_INTERFACE("4cc4441f-bd5e-5bd2-87f8-7a7e686d4c9a")
    IStoryItem : public IInspectable
    {
    public:
        /* [propget] */virtual HRESULT STDMETHODCALLTYPE get_Id(
            /* [out, retval] */unsigned __int64 * value
            ) = 0;
        /* [propget] */virtual HRESULT STDMETHODCALLTYPE get_Title(
            /* [out, retval] */HSTRING * value
            ) = 0;
        /* [propget] */virtual HRESULT STDMETHODCALLTYPE get_CommentCount(
            /* [out, retval] */unsigned __int64 * value
            ) = 0;
        
    };

    MIDL_CONST_ID IID & IID_IStoryItem=__uuidof(IStoryItem);
    
} /* NoiseBackendExample */

EXTERN_C const IID IID___x_NoiseBackendExample_CIStoryItem;
#endif /* !defined(____x_NoiseBackendExample_CIStoryItem_INTERFACE_DEFINED__) */


/*
 *
 * Interface NoiseBackendExample.IStoryItemFactory
 *
 * Interface is a part of the implementation of type NoiseBackendExample.StoryItem
 *
 *
 * The IID for this interface was automatically generated by MIDLRT.
 *
 * Interface IID generation seed: NoiseBackendExample.IStoryItemFactory:HRESULT CreateInstance(UInt64,String,UInt64,NoiseBackendExample.StoryItem**);
 *
 *
 */
#if !defined(____x_NoiseBackendExample_CIStoryItemFactory_INTERFACE_DEFINED__)
#define ____x_NoiseBackendExample_CIStoryItemFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_NoiseBackendExample_IStoryItemFactory[] = L"NoiseBackendExample.IStoryItemFactory";

namespace NoiseBackendExample {
    /* [uuid("558f2bc6-d4be-5d65-aed3-32b851cf2bf7"), version, object, exclusiveto] */
    MIDL_INTERFACE("558f2bc6-d4be-5d65-aed3-32b851cf2bf7")
    IStoryItemFactory : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
            /* [in] */unsigned __int64 id,
            /* [in] */HSTRING title,
            /* [in] */unsigned __int64 commentCount,
            /* [retval, out] */NoiseBackendExample::IStoryItem * * value
            ) = 0;
        
    };

    MIDL_CONST_ID IID & IID_IStoryItemFactory=__uuidof(IStoryItemFactory);
    
} /* NoiseBackendExample */

EXTERN_C const IID IID___x_NoiseBackendExample_CIStoryItemFactory;
#endif /* !defined(____x_NoiseBackendExample_CIStoryItemFactory_INTERFACE_DEFINED__) */


/*
 *
 * Class NoiseBackendExample.StoryItem
 *
 * RuntimeClass can be activated.
 *
 * Class implements the following interfaces:
 *    NoiseBackendExample.IStoryItem ** Default Interface **
 *    Windows.UI.Xaml.Data.INotifyPropertyChanged
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */

#ifndef RUNTIMECLASS_NoiseBackendExample_StoryItem_DEFINED
#define RUNTIMECLASS_NoiseBackendExample_StoryItem_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_NoiseBackendExample_StoryItem[] = L"NoiseBackendExample.StoryItem";
#endif


namespace NoiseBackendExample {
    class StoryListPage;
} /* NoiseBackendExample */



/*
 *
 * Interface NoiseBackendExample.IStoryListPage
 *
 * Interface is a part of the implementation of type NoiseBackendExample.StoryListPage
 *
 *
 * The IID for this interface was automatically generated by MIDLRT.
 *
 * Interface IID generation seed: NoiseBackendExample.IStoryListPage:HRESULT get_Stories(Windows.Foundation.Collections.IObservableVector`1<Object>**);
 *
 *
 */
#if !defined(____x_NoiseBackendExample_CIStoryListPage_INTERFACE_DEFINED__)
#define ____x_NoiseBackendExample_CIStoryListPage_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_NoiseBackendExample_IStoryListPage[] = L"NoiseBackendExample.IStoryListPage";

namespace NoiseBackendExample {
    /* [uuid("60515a0f-a38d-52cd-9a25-f18aa659b881"), version, object, exclusiveto] */
    MIDL_INTERFACE("60515a0f-a38d-52cd-9a25-f18aa659b881")
    IStoryListPage : public IInspectable
    {
    public:
        /* [propget] */virtual HRESULT STDMETHODCALLTYPE get_Stories(
            /* [out, retval] */__FIObservableVector_1_IInspectable * * value
            ) = 0;
        
    };

    MIDL_CONST_ID IID & IID_IStoryListPage=__uuidof(IStoryListPage);
    
} /* NoiseBackendExample */

EXTERN_C const IID IID___x_NoiseBackendExample_CIStoryListPage;
#endif /* !defined(____x_NoiseBackendExample_CIStoryListPage_INTERFACE_DEFINED__) */


/*
 *
 * Class NoiseBackendExample.StoryListPage
 *
 * RuntimeClass can be activated.
 *
 * Class implements the following interfaces:
 *    NoiseBackendExample.IStoryListPage ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */

#ifndef RUNTIMECLASS_NoiseBackendExample_StoryListPage_DEFINED
#define RUNTIMECLASS_NoiseBackendExample_StoryListPage_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_NoiseBackendExample_StoryListPage[] = L"NoiseBackendExample.StoryListPage";
#endif


#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_NoiseBackendExample_CIStoryItem_FWD_DEFINED__
#define ____x_NoiseBackendExample_CIStoryItem_FWD_DEFINED__
typedef interface __x_NoiseBackendExample_CIStoryItem __x_NoiseBackendExample_CIStoryItem;

#endif // ____x_NoiseBackendExample_CIStoryItem_FWD_DEFINED__

#ifndef ____x_NoiseBackendExample_CIStoryItemFactory_FWD_DEFINED__
#define ____x_NoiseBackendExample_CIStoryItemFactory_FWD_DEFINED__
typedef interface __x_NoiseBackendExample_CIStoryItemFactory __x_NoiseBackendExample_CIStoryItemFactory;

#endif // ____x_NoiseBackendExample_CIStoryItemFactory_FWD_DEFINED__

#ifndef ____x_NoiseBackendExample_CIStoryListPage_FWD_DEFINED__
#define ____x_NoiseBackendExample_CIStoryListPage_FWD_DEFINED__
typedef interface __x_NoiseBackendExample_CIStoryListPage __x_NoiseBackendExample_CIStoryListPage;

#endif // ____x_NoiseBackendExample_CIStoryListPage_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#if !defined(____FIIterator_1_IInspectable_INTERFACE_DEFINED__)
#define ____FIIterator_1_IInspectable_INTERFACE_DEFINED__

typedef interface __FIIterator_1_IInspectable __FIIterator_1_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_IInspectable;

typedef struct __FIIterator_1_IInspectableVtbl
{
    BEGIN_INTERFACE

    HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
        __RPC__in __FIIterator_1_IInspectable * This,
        /* [in] */ __RPC__in REFIID riid,
        /* [annotation][iid_is][out] */ 
        _COM_Outptr_  void **ppvObject);
    ULONG ( STDMETHODCALLTYPE *AddRef )(__RPC__in __FIIterator_1_IInspectable * This);
    ULONG ( STDMETHODCALLTYPE *Release )(__RPC__in __FIIterator_1_IInspectable * This);
    HRESULT ( STDMETHODCALLTYPE *GetIids )(__RPC__in __FIIterator_1_IInspectable * This,
        /* [out] */ __RPC__out ULONG *iidCount,
        /* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*iidCount) IID **iids);

    HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )(__RPC__in __FIIterator_1_IInspectable * This, /* [out] */ __RPC__deref_out_opt HSTRING *className);
    HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )(__RPC__in __FIIterator_1_IInspectable * This, /* [out] */ __RPC__out TrustLevel *trustLevel);

    /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Current )(__RPC__in __FIIterator_1_IInspectable * This, /* [retval][out] */ __RPC__out IInspectable * *current);
    /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasCurrent )(__RPC__in __FIIterator_1_IInspectable * This, /* [retval][out] */ __RPC__out boolean *hasCurrent);
    HRESULT ( STDMETHODCALLTYPE *MoveNext )(__RPC__in __FIIterator_1_IInspectable * This, /* [retval][out] */ __RPC__out boolean *hasCurrent);
    HRESULT ( STDMETHODCALLTYPE *GetMany )(__RPC__in __FIIterator_1_IInspectable * This,
        /* [in] */ unsigned int capacity,
        /* [size_is][length_is][out] */ __RPC__out_ecount_part(capacity, *actual) IInspectable * *items,
        /* [retval][out] */ __RPC__out unsigned int *actual);

    END_INTERFACE
} __FIIterator_1_IInspectableVtbl;

interface __FIIterator_1_IInspectable
{
    CONST_VTBL struct __FIIterator_1_IInspectableVtbl *lpVtbl;
};



#ifdef COBJMACROS


#define __FIIterator_1_IInspectable_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIIterator_1_IInspectable_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIIterator_1_IInspectable_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIIterator_1_IInspectable_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIIterator_1_IInspectable_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIIterator_1_IInspectable_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIIterator_1_IInspectable_get_Current(This,current)	\
    ( (This)->lpVtbl -> get_Current(This,current) ) 

#define __FIIterator_1_IInspectable_get_HasCurrent(This,hasCurrent)	\
    ( (This)->lpVtbl -> get_HasCurrent(This,hasCurrent) ) 

#define __FIIterator_1_IInspectable_MoveNext(This,hasCurrent)	\
    ( (This)->lpVtbl -> MoveNext(This,hasCurrent) ) 

#define __FIIterator_1_IInspectable_GetMany(This,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,capacity,items,actual) ) 

#endif /* COBJMACROS */


#endif // ____FIIterator_1_IInspectable_INTERFACE_DEFINED__



#if !defined(____FIIterable_1_IInspectable_INTERFACE_DEFINED__)
#define ____FIIterable_1_IInspectable_INTERFACE_DEFINED__

typedef interface __FIIterable_1_IInspectable __FIIterable_1_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_IInspectable;

typedef  struct __FIIterable_1_IInspectableVtbl
{
    BEGIN_INTERFACE

    HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
        __RPC__in __FIIterable_1_IInspectable * This,
        /* [in] */ __RPC__in REFIID riid,
        /* [annotation][iid_is][out] */ 
        _COM_Outptr_  void **ppvObject);

    ULONG ( STDMETHODCALLTYPE *AddRef )(__RPC__in __FIIterable_1_IInspectable * This);

    ULONG ( STDMETHODCALLTYPE *Release )(__RPC__in __FIIterable_1_IInspectable * This);

    HRESULT ( STDMETHODCALLTYPE *GetIids )(__RPC__in __FIIterable_1_IInspectable * This,
                                           /* [out] */ __RPC__out ULONG *iidCount,
                                           /* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*iidCount) IID **iids);

    HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )(__RPC__in __FIIterable_1_IInspectable * This, /* [out] */ __RPC__deref_out_opt HSTRING *className);

    HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )(__RPC__in __FIIterable_1_IInspectable * This, /* [out] */ __RPC__out TrustLevel *trustLevel);

    HRESULT ( STDMETHODCALLTYPE *First )(__RPC__in __FIIterable_1_IInspectable * This, /* [retval][out] */ __RPC__deref_out_opt __FIIterator_1_IInspectable **first);

    END_INTERFACE
} __FIIterable_1_IInspectableVtbl;

interface __FIIterable_1_IInspectable
{
    CONST_VTBL struct __FIIterable_1_IInspectableVtbl *lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_IInspectable_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIIterable_1_IInspectable_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIIterable_1_IInspectable_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIIterable_1_IInspectable_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIIterable_1_IInspectable_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIIterable_1_IInspectable_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIIterable_1_IInspectable_First(This,first)	\
    ( (This)->lpVtbl -> First(This,first) ) 

#endif /* COBJMACROS */


#endif // ____FIIterable_1_IInspectable_INTERFACE_DEFINED__



#if !defined(____FIVectorView_1_IInspectable_INTERFACE_DEFINED__)
#define ____FIVectorView_1_IInspectable_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_IInspectable __FIVectorView_1_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_IInspectable;

typedef struct __FIVectorView_1_IInspectableVtbl
{
    BEGIN_INTERFACE

    HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
        __RPC__in __FIVectorView_1_IInspectable * This,
        /* [in] */ __RPC__in REFIID riid,
        /* [annotation][iid_is][out] */ 
        _COM_Outptr_  void **ppvObject);

    ULONG ( STDMETHODCALLTYPE *AddRef )( __RPC__in __FIVectorView_1_IInspectable * This);

    ULONG ( STDMETHODCALLTYPE *Release )( __RPC__in __FIVectorView_1_IInspectable * This);

    HRESULT ( STDMETHODCALLTYPE *GetIids )( __RPC__in __FIVectorView_1_IInspectable * This,
                                            /* [out] */ __RPC__out ULONG *iidCount,
                                            /* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*iidCount) IID **iids);

    HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
        __RPC__in __FIVectorView_1_IInspectable * This,
            /* [out] */ __RPC__deref_out_opt HSTRING *className);

    HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
        __RPC__in __FIVectorView_1_IInspectable * This,
            /* [out] */ __RPC__out TrustLevel *trustLevel);

    HRESULT ( STDMETHODCALLTYPE *GetAt )( 
                                         __RPC__in __FIVectorView_1_IInspectable * This,
                                         /* [in] */ unsigned int index,
                                         /* [retval][out] */ __RPC__out IInspectable * *item);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            __RPC__in __FIVectorView_1_IInspectable * This,
            /* [retval][out] */ __RPC__out unsigned int *size);

        HRESULT ( STDMETHODCALLTYPE *IndexOf )( 
                                               __RPC__in __FIVectorView_1_IInspectable * This,
            /* [in] */ IInspectable * item,
            /* [out] */ __RPC__out unsigned int *index,
            /* [retval][out] */ __RPC__out boolean *found);

        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
                                               __RPC__in __FIVectorView_1_IInspectable * This,
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __RPC__out_ecount_part(capacity, *actual) IInspectable * *items,
            /* [retval][out] */ __RPC__out unsigned int *actual);

        END_INTERFACE
} __FIVectorView_1_IInspectableVtbl;

interface __FIVectorView_1_IInspectable
{
    CONST_VTBL struct __FIVectorView_1_IInspectableVtbl *lpVtbl;
};



#ifdef COBJMACROS


#define __FIVectorView_1_IInspectable_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIVectorView_1_IInspectable_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIVectorView_1_IInspectable_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIVectorView_1_IInspectable_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIVectorView_1_IInspectable_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIVectorView_1_IInspectable_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIVectorView_1_IInspectable_GetAt(This,index,item)	\
    ( (This)->lpVtbl -> GetAt(This,index,item) ) 

#define __FIVectorView_1_IInspectable_get_Size(This,size)	\
    ( (This)->lpVtbl -> get_Size(This,size) ) 

#define __FIVectorView_1_IInspectable_IndexOf(This,item,index,found)	\
    ( (This)->lpVtbl -> IndexOf(This,item,index,found) ) 

#define __FIVectorView_1_IInspectable_GetMany(This,startIndex,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,startIndex,capacity,items,actual) ) 

#endif /* COBJMACROS */



#endif // ____FIVectorView_1_IInspectable_INTERFACE_DEFINED__



#if !defined(____FIVector_1_IInspectable_INTERFACE_DEFINED__)
#define ____FIVector_1_IInspectable_INTERFACE_DEFINED__

typedef interface __FIVector_1_IInspectable __FIVector_1_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_IInspectable;

typedef struct __FIVector_1_IInspectableVtbl
{
    BEGIN_INTERFACE

    HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
        __RPC__in __FIVector_1_IInspectable * This,
            /* [in] */ __RPC__in REFIID riid,
            /* [annotation][iid_is][out] */ 
        _COM_Outptr_  void **ppvObject);

    ULONG ( STDMETHODCALLTYPE *AddRef )(__RPC__in __FIVector_1_IInspectable * This);
    ULONG ( STDMETHODCALLTYPE *Release )(__RPC__in __FIVector_1_IInspectable * This);
    HRESULT ( STDMETHODCALLTYPE *GetIids )(__RPC__in __FIVector_1_IInspectable * This,
        /* [out] */ __RPC__out ULONG *iidCount,
        /* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*iidCount) IID **iids);

    HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )(__RPC__in __FIVector_1_IInspectable * This, /* [out] */ __RPC__deref_out_opt IInspectable * *className);
    HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )(__RPC__in __FIVector_1_IInspectable * This, /* [out] */ __RPC__out TrustLevel *trustLevel);

    HRESULT ( STDMETHODCALLTYPE *GetAt )(__RPC__in __FIVector_1_IInspectable * This,
        /* [in] */ unsigned int index,
        /* [retval][out] */ __RPC__deref_out_opt IInspectable * *item);

    /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
        __RPC__in __FIVector_1_IInspectable * This,
        /* [retval][out] */ __RPC__out unsigned int *size);

    HRESULT ( STDMETHODCALLTYPE *GetView )(__RPC__in __FIVector_1_IInspectable * This, /* [retval][out] */ __RPC__deref_out_opt __FIVectorView_1_IInspectable **view);

    HRESULT ( STDMETHODCALLTYPE *IndexOf )(__RPC__in __FIVector_1_IInspectable * This,
        /* [in] */ __RPC__in IInspectable * item,
        /* [out] */ __RPC__out unsigned int *index,
        /* [retval][out] */ __RPC__out boolean *found);

    HRESULT ( STDMETHODCALLTYPE *SetAt )(__RPC__in __FIVector_1_IInspectable * This,
        /* [in] */ unsigned int index,
        /* [in] */ __RPC__in IInspectable * item);

    HRESULT ( STDMETHODCALLTYPE *InsertAt )(__RPC__in __FIVector_1_IInspectable * This,
        /* [in] */ unsigned int index,
        /* [in] */ __RPC__in IInspectable * item);

    HRESULT ( STDMETHODCALLTYPE *RemoveAt )(__RPC__in __FIVector_1_IInspectable * This, /* [in] */ unsigned int index);
    HRESULT ( STDMETHODCALLTYPE *Append )(__RPC__in __FIVector_1_IInspectable * This, /* [in] */ __RPC__in IInspectable * item);
    HRESULT ( STDMETHODCALLTYPE *RemoveAtEnd )(__RPC__in __FIVector_1_IInspectable * This);
    HRESULT ( STDMETHODCALLTYPE *Clear )(__RPC__in __FIVector_1_IInspectable * This);
    HRESULT ( STDMETHODCALLTYPE *GetMany )(__RPC__in __FIVector_1_IInspectable * This,
        /* [in] */ unsigned int startIndex,
        /* [in] */ unsigned int capacity,
        /* [size_is][length_is][out] */ __RPC__out_ecount_part(capacity, *actual) IInspectable * *items,
        /* [retval][out] */ __RPC__out unsigned int *actual);

    HRESULT ( STDMETHODCALLTYPE *ReplaceAll )(__RPC__in __FIVector_1_IInspectable * This,
        /* [in] */ unsigned int count,
        /* [size_is][in] */ __RPC__in_ecount_full(count) IInspectable * *value);

    END_INTERFACE
} __FIVector_1_IInspectableVtbl;

interface __FIVector_1_IInspectable
{
    CONST_VTBL struct __FIVector_1_IInspectableVtbl *lpVtbl;
};



#ifdef COBJMACROS


#define __FIVector_1_IInspectable_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIVector_1_IInspectable_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIVector_1_IInspectable_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIVector_1_IInspectable_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIVector_1_IInspectable_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIVector_1_IInspectable_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIVector_1_IInspectable_GetAt(This,index,item)	\
    ( (This)->lpVtbl -> GetAt(This,index,item) ) 

#define __FIVector_1_IInspectable_get_Size(This,size)	\
    ( (This)->lpVtbl -> get_Size(This,size) ) 

#define __FIVector_1_IInspectable_GetView(This,view)	\
    ( (This)->lpVtbl -> GetView(This,view) ) 

#define __FIVector_1_IInspectable_IndexOf(This,item,index,found)	\
    ( (This)->lpVtbl -> IndexOf(This,item,index,found) ) 

#define __FIVector_1_IInspectable_SetAt(This,index,item)	\
    ( (This)->lpVtbl -> SetAt(This,index,item) ) 

#define __FIVector_1_IInspectable_InsertAt(This,index,item)	\
    ( (This)->lpVtbl -> InsertAt(This,index,item) ) 

#define __FIVector_1_IInspectable_RemoveAt(This,index)	\
    ( (This)->lpVtbl -> RemoveAt(This,index) ) 

#define __FIVector_1_IInspectable_Append(This,item)	\
    ( (This)->lpVtbl -> Append(This,item) ) 

#define __FIVector_1_IInspectable_RemoveAtEnd(This)	\
    ( (This)->lpVtbl -> RemoveAtEnd(This) ) 

#define __FIVector_1_IInspectable_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define __FIVector_1_IInspectable_GetMany(This,startIndex,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,startIndex,capacity,items,actual) ) 

#define __FIVector_1_IInspectable_ReplaceAll(This,count,value)	\
    ( (This)->lpVtbl -> ReplaceAll(This,count,value) ) 

#endif /* COBJMACROS */



#endif // ____FIVector_1_IInspectable_INTERFACE_DEFINED__



#if !defined(____FVectorChangedEventHandler_1_IInspectable_INTERFACE_DEFINED__)
#define ____FVectorChangedEventHandler_1_IInspectable_INTERFACE_DEFINED__

typedef interface __FVectorChangedEventHandler_1_IInspectable __FVectorChangedEventHandler_1_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FVectorChangedEventHandler_1_IInspectable;

typedef interface __FIObservableVector_1_IInspectable __FIObservableVector_1_IInspectable;

typedef struct __FVectorChangedEventHandler_1_IInspectableVtbl
{
    BEGIN_INTERFACE
    HRESULT ( STDMETHODCALLTYPE *QueryInterface )(__RPC__in __FVectorChangedEventHandler_1_IInspectable * This,
        /* [in] */ __RPC__in REFIID riid,
        /* [annotation][iid_is][out] */ 
        _COM_Outptr_  void **ppvObject);
    ULONG ( STDMETHODCALLTYPE *AddRef )(__RPC__in __FVectorChangedEventHandler_1_IInspectable * This);
    ULONG ( STDMETHODCALLTYPE *Release )(__RPC__in __FVectorChangedEventHandler_1_IInspectable * This);

    HRESULT ( STDMETHODCALLTYPE *Invoke )(__RPC__in __FVectorChangedEventHandler_1_IInspectable * This,
        /* [in] */ __RPC__in_opt __FIObservableVector_1_IInspectable *sender,
        /* [in] */ __RPC__in_opt __x_Windows_CFoundation_CCollections_CIVectorChangedEventArgs *e);
    END_INTERFACE
} __FVectorChangedEventHandler_1_IInspectableVtbl;

interface __FVectorChangedEventHandler_1_IInspectable
{
    CONST_VTBL struct __FVectorChangedEventHandler_1_IInspectableVtbl *lpVtbl;
};

#ifdef COBJMACROS
#define __FVectorChangedEventHandler_1_IInspectable_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 
#define __FVectorChangedEventHandler_1_IInspectable_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 
#define __FVectorChangedEventHandler_1_IInspectable_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 

#define __FVectorChangedEventHandler_1_IInspectable_Invoke(This,sender,e)	\
    ( (This)->lpVtbl -> Invoke(This,sender,e) ) 
#endif /* COBJMACROS */


#endif // ____FVectorChangedEventHandler_1_IInspectable_INTERFACE_DEFINED__



#if !defined(____FIObservableVector_1_IInspectable_INTERFACE_DEFINED__)
#define ____FIObservableVector_1_IInspectable_INTERFACE_DEFINED__

typedef interface __FIObservableVector_1_IInspectable __FIObservableVector_1_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIObservableVector_1_IInspectable;

typedef struct __FIObservableVector_1_IInspectableVtbl
{
    BEGIN_INTERFACE
    HRESULT ( STDMETHODCALLTYPE *QueryInterface )(__RPC__in __FIObservableVector_1_IInspectable * This,
        /* [in] */ __RPC__in REFIID riid,
        /* [annotation][iid_is][out] */ 
        _COM_Outptr_  void **ppvObject);
    ULONG ( STDMETHODCALLTYPE *AddRef )(__RPC__in __FIObservableVector_1_IInspectable * This);
    ULONG ( STDMETHODCALLTYPE *Release )(__RPC__in __FIObservableVector_1_IInspectable * This);

    HRESULT ( STDMETHODCALLTYPE *GetIids )(__RPC__in __FIObservableVector_1_IInspectable * This,
        /* [out] */ __RPC__out ULONG *iidCount,
        /* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*iidCount) IID **iids);
    HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )(__RPC__in __FIObservableVector_1_IInspectable * This, /* [out] */ __RPC__deref_out_opt HSTRING *className);
    HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )(__RPC__in __FIObservableVector_1_IInspectable * This, /* [out] */ __RPC__out TrustLevel *trustLevel);

    HRESULT ( STDMETHODCALLTYPE *add_VectorChanged )(__RPC__in __FIObservableVector_1_IInspectable * This,
        /* [in] */ __RPC__in_opt __FVectorChangedEventHandler_1_IInspectable *handler,
        /* [retval][out] */ __RPC__out EventRegistrationToken *token);

    HRESULT ( STDMETHODCALLTYPE *remove_VectorChanged )(__RPC__in __FIObservableVector_1_IInspectable * This, /* [in] */ EventRegistrationToken token);
    END_INTERFACE
} __FIObservableVector_1_IInspectableVtbl;

interface __FIObservableVector_1_IInspectable
{
    CONST_VTBL struct __FIObservableVector_1_IInspectableVtbl *lpVtbl;
};

#ifdef COBJMACROS
#define __FIObservableVector_1_IInspectable_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 
#define __FIObservableVector_1_IInspectable_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 
#define __FIObservableVector_1_IInspectable_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 

#define __FIObservableVector_1_IInspectable_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 
#define __FIObservableVector_1_IInspectable_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 
#define __FIObservableVector_1_IInspectable_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 

#define __FIObservableVector_1_IInspectable_add_VectorChanged(This,handler,token)	\
    ( (This)->lpVtbl -> add_VectorChanged(This,handler,token) ) 
#define __FIObservableVector_1_IInspectable_remove_VectorChanged(This,token)	\
    ( (This)->lpVtbl -> remove_VectorChanged(This,token) ) 

#endif /* COBJMACROS */


#endif // ____FIObservableVector_1_IInspectable_INTERFACE_DEFINED__





/*
 *
 * Interface NoiseBackendExample.IStoryItem
 *
 * Interface is a part of the implementation of type NoiseBackendExample.StoryItem
 *
 *
 * The IID for this interface was automatically generated by MIDLRT.
 *
 * Interface IID generation seed: NoiseBackendExample.IStoryItem:HRESULT get_Id(UInt64*);HRESULT get_Title(String*);HRESULT get_CommentCount(UInt64*);
 *
 *
 */
#if !defined(____x_NoiseBackendExample_CIStoryItem_INTERFACE_DEFINED__)
#define ____x_NoiseBackendExample_CIStoryItem_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_NoiseBackendExample_IStoryItem[] = L"NoiseBackendExample.IStoryItem";
/* [uuid("4cc4441f-bd5e-5bd2-87f8-7a7e686d4c9a"), version, object, exclusiveto] */
typedef struct __x_NoiseBackendExample_CIStoryItemVtbl
{
    BEGIN_INTERFACE
    HRESULT ( STDMETHODCALLTYPE *QueryInterface)(
    __RPC__in __x_NoiseBackendExample_CIStoryItem * This,
    /* [in] */ __RPC__in REFIID riid,
    /* [annotation][iid_is][out] */
    _COM_Outptr_  void **ppvObject
    );

ULONG ( STDMETHODCALLTYPE *AddRef )(
    __RPC__in __x_NoiseBackendExample_CIStoryItem * This
    );

ULONG ( STDMETHODCALLTYPE *Release )(
    __RPC__in __x_NoiseBackendExample_CIStoryItem * This
    );

HRESULT ( STDMETHODCALLTYPE *GetIids )(
    __RPC__in __x_NoiseBackendExample_CIStoryItem * This,
    /* [out] */ __RPC__out ULONG *iidCount,
    /* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*iidCount) IID **iids
    );

HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )(
    __RPC__in __x_NoiseBackendExample_CIStoryItem * This,
    /* [out] */ __RPC__deref_out_opt HSTRING *className
    );

HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )(
    __RPC__in __x_NoiseBackendExample_CIStoryItem * This,
    /* [OUT ] */ __RPC__out TrustLevel *trustLevel
    );
/* [propget] */HRESULT ( STDMETHODCALLTYPE *get_Id )(
        __x_NoiseBackendExample_CIStoryItem * This,
        /* [out, retval] */unsigned __int64 * value
        );
    /* [propget] */HRESULT ( STDMETHODCALLTYPE *get_Title )(
        __x_NoiseBackendExample_CIStoryItem * This,
        /* [out, retval] */HSTRING * value
        );
    /* [propget] */HRESULT ( STDMETHODCALLTYPE *get_CommentCount )(
        __x_NoiseBackendExample_CIStoryItem * This,
        /* [out, retval] */unsigned __int64 * value
        );
    END_INTERFACE
    
} __x_NoiseBackendExample_CIStoryItemVtbl;

interface __x_NoiseBackendExample_CIStoryItem
{
    CONST_VTBL struct __x_NoiseBackendExample_CIStoryItemVtbl *lpVtbl;
};

#ifdef COBJMACROS
#define __x_NoiseBackendExample_CIStoryItem_QueryInterface(This,riid,ppvObject) \
( (This)->lpVtbl->QueryInterface(This,riid,ppvObject) )

#define __x_NoiseBackendExample_CIStoryItem_AddRef(This) \
        ( (This)->lpVtbl->AddRef(This) )

#define __x_NoiseBackendExample_CIStoryItem_Release(This) \
        ( (This)->lpVtbl->Release(This) )

#define __x_NoiseBackendExample_CIStoryItem_GetIids(This,iidCount,iids) \
        ( (This)->lpVtbl->GetIids(This,iidCount,iids) )

#define __x_NoiseBackendExample_CIStoryItem_GetRuntimeClassName(This,className) \
        ( (This)->lpVtbl->GetRuntimeClassName(This,className) )

#define __x_NoiseBackendExample_CIStoryItem_GetTrustLevel(This,trustLevel) \
        ( (This)->lpVtbl->GetTrustLevel(This,trustLevel) )

#define __x_NoiseBackendExample_CIStoryItem_get_Id(This,value) \
    ( (This)->lpVtbl->get_Id(This,value) )

#define __x_NoiseBackendExample_CIStoryItem_get_Title(This,value) \
    ( (This)->lpVtbl->get_Title(This,value) )

#define __x_NoiseBackendExample_CIStoryItem_get_CommentCount(This,value) \
    ( (This)->lpVtbl->get_CommentCount(This,value) )


#endif /* COBJMACROS */


EXTERN_C const IID IID___x_NoiseBackendExample_CIStoryItem;
#endif /* !defined(____x_NoiseBackendExample_CIStoryItem_INTERFACE_DEFINED__) */


/*
 *
 * Interface NoiseBackendExample.IStoryItemFactory
 *
 * Interface is a part of the implementation of type NoiseBackendExample.StoryItem
 *
 *
 * The IID for this interface was automatically generated by MIDLRT.
 *
 * Interface IID generation seed: NoiseBackendExample.IStoryItemFactory:HRESULT CreateInstance(UInt64,String,UInt64,NoiseBackendExample.StoryItem**);
 *
 *
 */
#if !defined(____x_NoiseBackendExample_CIStoryItemFactory_INTERFACE_DEFINED__)
#define ____x_NoiseBackendExample_CIStoryItemFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_NoiseBackendExample_IStoryItemFactory[] = L"NoiseBackendExample.IStoryItemFactory";
/* [uuid("558f2bc6-d4be-5d65-aed3-32b851cf2bf7"), version, object, exclusiveto] */
typedef struct __x_NoiseBackendExample_CIStoryItemFactoryVtbl
{
    BEGIN_INTERFACE
    HRESULT ( STDMETHODCALLTYPE *QueryInterface)(
    __RPC__in __x_NoiseBackendExample_CIStoryItemFactory * This,
    /* [in] */ __RPC__in REFIID riid,
    /* [annotation][iid_is][out] */
    _COM_Outptr_  void **ppvObject
    );

ULONG ( STDMETHODCALLTYPE *AddRef )(
    __RPC__in __x_NoiseBackendExample_CIStoryItemFactory * This
    );

ULONG ( STDMETHODCALLTYPE *Release )(
    __RPC__in __x_NoiseBackendExample_CIStoryItemFactory * This
    );

HRESULT ( STDMETHODCALLTYPE *GetIids )(
    __RPC__in __x_NoiseBackendExample_CIStoryItemFactory * This,
    /* [out] */ __RPC__out ULONG *iidCount,
    /* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*iidCount) IID **iids
    );

HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )(
    __RPC__in __x_NoiseBackendExample_CIStoryItemFactory * This,
    /* [out] */ __RPC__deref_out_opt HSTRING *className
    );

HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )(
    __RPC__in __x_NoiseBackendExample_CIStoryItemFactory * This,
    /* [OUT ] */ __RPC__out TrustLevel *trustLevel
    );
HRESULT ( STDMETHODCALLTYPE *CreateInstance )(
        __x_NoiseBackendExample_CIStoryItemFactory * This,
        /* [in] */unsigned __int64 id,
        /* [in] */HSTRING title,
        /* [in] */unsigned __int64 commentCount,
        /* [retval, out] */__x_NoiseBackendExample_CIStoryItem * * value
        );
    END_INTERFACE
    
} __x_NoiseBackendExample_CIStoryItemFactoryVtbl;

interface __x_NoiseBackendExample_CIStoryItemFactory
{
    CONST_VTBL struct __x_NoiseBackendExample_CIStoryItemFactoryVtbl *lpVtbl;
};

#ifdef COBJMACROS
#define __x_NoiseBackendExample_CIStoryItemFactory_QueryInterface(This,riid,ppvObject) \
( (This)->lpVtbl->QueryInterface(This,riid,ppvObject) )

#define __x_NoiseBackendExample_CIStoryItemFactory_AddRef(This) \
        ( (This)->lpVtbl->AddRef(This) )

#define __x_NoiseBackendExample_CIStoryItemFactory_Release(This) \
        ( (This)->lpVtbl->Release(This) )

#define __x_NoiseBackendExample_CIStoryItemFactory_GetIids(This,iidCount,iids) \
        ( (This)->lpVtbl->GetIids(This,iidCount,iids) )

#define __x_NoiseBackendExample_CIStoryItemFactory_GetRuntimeClassName(This,className) \
        ( (This)->lpVtbl->GetRuntimeClassName(This,className) )

#define __x_NoiseBackendExample_CIStoryItemFactory_GetTrustLevel(This,trustLevel) \
        ( (This)->lpVtbl->GetTrustLevel(This,trustLevel) )

#define __x_NoiseBackendExample_CIStoryItemFactory_CreateInstance(This,id,title,commentCount,value) \
    ( (This)->lpVtbl->CreateInstance(This,id,title,commentCount,value) )


#endif /* COBJMACROS */


EXTERN_C const IID IID___x_NoiseBackendExample_CIStoryItemFactory;
#endif /* !defined(____x_NoiseBackendExample_CIStoryItemFactory_INTERFACE_DEFINED__) */


/*
 *
 * Class NoiseBackendExample.StoryItem
 *
 * RuntimeClass can be activated.
 *
 * Class implements the following interfaces:
 *    NoiseBackendExample.IStoryItem ** Default Interface **
 *    Windows.UI.Xaml.Data.INotifyPropertyChanged
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */

#ifndef RUNTIMECLASS_NoiseBackendExample_StoryItem_DEFINED
#define RUNTIMECLASS_NoiseBackendExample_StoryItem_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_NoiseBackendExample_StoryItem[] = L"NoiseBackendExample.StoryItem";
#endif



/*
 *
 * Interface NoiseBackendExample.IStoryListPage
 *
 * Interface is a part of the implementation of type NoiseBackendExample.StoryListPage
 *
 *
 * The IID for this interface was automatically generated by MIDLRT.
 *
 * Interface IID generation seed: NoiseBackendExample.IStoryListPage:HRESULT get_Stories(Windows.Foundation.Collections.IObservableVector`1<Object>**);
 *
 *
 */
#if !defined(____x_NoiseBackendExample_CIStoryListPage_INTERFACE_DEFINED__)
#define ____x_NoiseBackendExample_CIStoryListPage_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_NoiseBackendExample_IStoryListPage[] = L"NoiseBackendExample.IStoryListPage";
/* [uuid("60515a0f-a38d-52cd-9a25-f18aa659b881"), version, object, exclusiveto] */
typedef struct __x_NoiseBackendExample_CIStoryListPageVtbl
{
    BEGIN_INTERFACE
    HRESULT ( STDMETHODCALLTYPE *QueryInterface)(
    __RPC__in __x_NoiseBackendExample_CIStoryListPage * This,
    /* [in] */ __RPC__in REFIID riid,
    /* [annotation][iid_is][out] */
    _COM_Outptr_  void **ppvObject
    );

ULONG ( STDMETHODCALLTYPE *AddRef )(
    __RPC__in __x_NoiseBackendExample_CIStoryListPage * This
    );

ULONG ( STDMETHODCALLTYPE *Release )(
    __RPC__in __x_NoiseBackendExample_CIStoryListPage * This
    );

HRESULT ( STDMETHODCALLTYPE *GetIids )(
    __RPC__in __x_NoiseBackendExample_CIStoryListPage * This,
    /* [out] */ __RPC__out ULONG *iidCount,
    /* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*iidCount) IID **iids
    );

HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )(
    __RPC__in __x_NoiseBackendExample_CIStoryListPage * This,
    /* [out] */ __RPC__deref_out_opt HSTRING *className
    );

HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )(
    __RPC__in __x_NoiseBackendExample_CIStoryListPage * This,
    /* [OUT ] */ __RPC__out TrustLevel *trustLevel
    );
/* [propget] */HRESULT ( STDMETHODCALLTYPE *get_Stories )(
        __x_NoiseBackendExample_CIStoryListPage * This,
        /* [out, retval] */__FIObservableVector_1_IInspectable * * value
        );
    END_INTERFACE
    
} __x_NoiseBackendExample_CIStoryListPageVtbl;

interface __x_NoiseBackendExample_CIStoryListPage
{
    CONST_VTBL struct __x_NoiseBackendExample_CIStoryListPageVtbl *lpVtbl;
};

#ifdef COBJMACROS
#define __x_NoiseBackendExample_CIStoryListPage_QueryInterface(This,riid,ppvObject) \
( (This)->lpVtbl->QueryInterface(This,riid,ppvObject) )

#define __x_NoiseBackendExample_CIStoryListPage_AddRef(This) \
        ( (This)->lpVtbl->AddRef(This) )

#define __x_NoiseBackendExample_CIStoryListPage_Release(This) \
        ( (This)->lpVtbl->Release(This) )

#define __x_NoiseBackendExample_CIStoryListPage_GetIids(This,iidCount,iids) \
        ( (This)->lpVtbl->GetIids(This,iidCount,iids) )

#define __x_NoiseBackendExample_CIStoryListPage_GetRuntimeClassName(This,className) \
        ( (This)->lpVtbl->GetRuntimeClassName(This,className) )

#define __x_NoiseBackendExample_CIStoryListPage_GetTrustLevel(This,trustLevel) \
        ( (This)->lpVtbl->GetTrustLevel(This,trustLevel) )

#define __x_NoiseBackendExample_CIStoryListPage_get_Stories(This,value) \
    ( (This)->lpVtbl->get_Stories(This,value) )


#endif /* COBJMACROS */


EXTERN_C const IID IID___x_NoiseBackendExample_CIStoryListPage;
#endif /* !defined(____x_NoiseBackendExample_CIStoryListPage_INTERFACE_DEFINED__) */


/*
 *
 * Class NoiseBackendExample.StoryListPage
 *
 * RuntimeClass can be activated.
 *
 * Class implements the following interfaces:
 *    NoiseBackendExample.IStoryListPage ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */

#ifndef RUNTIMECLASS_NoiseBackendExample_StoryListPage_DEFINED
#define RUNTIMECLASS_NoiseBackendExample_StoryListPage_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_NoiseBackendExample_StoryListPage[] = L"NoiseBackendExample.StoryListPage";
#endif


#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __StoryListPage_h_p_h__

#endif // __StoryListPage_h_h__
