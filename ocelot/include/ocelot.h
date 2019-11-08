//////////////////////////////////////////////////////////////////////
//
//            @@@
//            @@@
//   @@@@@@@  @@@@@@@@  @@   @@@ @@   @@@@@@@  @@@   @@  @@@@@@@
//  @@    @@@ @@@   @@@  @@  @@  @@  @@    @@@ @@@   @@  @@@@
//  @@    @@@ @@@   @@@  @@@@@   @@  @@    @@@ @@@   @@      @@@
//   @@@@@@@  @@@@@@@@    @@@    @@   @@@@@@@   @@@@@@@  @@@@@@@  @@
//
//       (//(#(                                       (#(//(#
//     &(/////(((/#(                                 (#/(((/////(
//    ######((((//(%      /,,,(///////(*,,/       #//(((((######
//    /(((####((##((//##%%%%/#######/(######/%%%#%#//((##((####((((
//    #(((#########((//#%%%##,,#%#  /  /%#,,##%%%#//((#########(((#
//     /###########((((/((//#   /*//(//./   #//((/((((###########(
//     /(((##########(///((//../#///((//##..//(((//(##########(((/
//      (((#######((((///(((.  ///////////  .(((///((((#######(((
//       (((########(//(((((../##**///**##/..((((((/(####%%##(((
//       (((((%#(####((((((*,(%%#*,(/(*,#%%(,*((((((####(#%(((((
//         //(((((###//((((..%%#..(((((..#%%..((((//###((((((/
//          ///*///////((((.*(%#**(((((,*#%(*./(((///////*///
//          /***//////((((,(/.###***/***###.,(,((((//////***/
//          **/((((/////((,*((.#%///////%#.((*.((/////((((/**(
//         ////(((((((%%%%*.###(#(/////(##(##..%%%%(((((((////
//         ///(......,   /(..*/*/((///((/*,*..(/   ,......(///
//          /......*....&*, .#&/*/(((((/**&%. ,,&....,......*
//          .*. /,,%%,........&&*//(((//*&&........,#%,,/..*.
//          ./((/,,,%/......,..&&//(/(//&&..,......*%,,,/((/,
//           ***,(,,,/%(.....  #&*/(/(/*  ...../%(,,,(,***
//            *,,/((,,,&&&&&..  *///////*  ..&&&&&,,,/((,,*
//             ******,*//*&,..  **//(//**  ..,&*//*,*****,
//               /**////,...... .(((#(((, ......,////***
//                  ////..,,*,. ***/((*** .,*,,..////
//                    ***,,**//.,/(#(#(/*./(**,,***#
//                    //**,*#&%/.*/////*./%&%*,**/*
//                     //**(%  &%,,///,,#&& &(**//
//                      //##/%#&&%%,..%%&&%%(##//
//                        /////*/###*###(*/////
//                           **///(/*/(///**
//                              /(((((/(/#
//                                 /(/
//
// Copyright © 2019,
// 4iiii Innovations Inc.,
// Cochrane, Alberta, Canada.
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are not permitted without express written approval of
// 4iiii Innovations Inc.
///////////////////////////////////////////////////////////////////////

#if !defined(OCELOT_H_)
#define OCELOT_H_

#include "ble.h"
#include "ocelot_feature.h"

#include <stdbool.h>
#include <stdint.h>


#if defined(__cplusplus)
   extern "C"
   {
#endif

#define OCELOT_VERSION_RELEASE         0
#define OCELOT_VERSION_MAJOR           1
#define OCELOT_VERSION_MINOR           10

#define OCELOT_CMAC_SIZE               16
#define OCELOT_KEY_SIZE                16

/// @defgroup OCELOT ocelot Library
/// @{
#define OCELOT_SUCCESS                 0                    ///< Operation completed successfully.
#define OCELOT_ERROR_INTERNAL          1                    ///< An internal error has occurred.  Please contact obvıous. support with details on how to replicate the error.
#define OCELOT_ERROR_NULL              2                    ///< A pointer parameter is set to NULL that should be set to a valid memory location.
#define OCELOT_ERROR_ALIGN             3                    ///< A pointer parameter is set to a location that violates the alignment specification of that parameter.
#define OCELOT_ERROR_RANGE             4                    ///< A pointer parameter is set to a value outside the appropriate range.
#define OCELOT_ERROR_WRITE             5                    ///< A flash write error has occurred.
#define OCELOT_ERROR_BLE               6                    ///< A BLE initialization error has occurred.  Please contact obvıous. support with details on how to replicate the error.
#define OCELOT_ERROR_BLE_MEM           7                    ///< Insufficient memory is available to store the current BLE configuration.  Increase the size and try again.
#define OCELOT_ERROR_BLE_VSUUID        8                    ///< Insufficient Vendor Specific UUID slots are available.  Increase the slot count by one and try again.
/// @}

enum OCELOT_EVT
{
   OCELOT_EVT_RESET_PREPARE,
   OCELOT_EVT_FLASH_ERASE_PAGE,
   OCELOT_EVT_FLASH_WRITE,
   OCELOT_EVT_REQUEST_FAST_CONN,
   OCELOT_EVT_SERVICE_DATA_UPDATE,
   OCELOT_EVTS
};

union OCELOT_EVT_ARGS
{
   struct
   {
      uint32_t address;
   } flash_erase_page_args;
   struct
   {
      const void* data;
      uint32_t address;
      uint32_t size;
   } flash_write_args;
};
struct OCELOT_VERSION
{
   uint16_t release;
   uint16_t major;
   uint16_t minor;
};
struct OCELOT_INIT                                          /// Initialization structure that must be set up for your application.
{
   struct OCELOT_VERSION application_version;               ///< Pointer to an application version structure.  The library will make a copy of the structure.  If set to NULL, or if any of the members are set to a value > 999, the version number is considered invalid, and will not be available for query and respond with an operation failure.
   uint32_t (*evt_handler)(enum OCELOT_EVT evt, union OCELOT_EVT_ARGS* args);
};


/// @addtogroup OCELOT ocelot Library
/// @{

/// Initialize the ocelot library.
/// @param [in] init Pointer to an initialization structure.  All
/// fields must be set to valid values.
/// @see OCELOT_INIT
/// @return An error code.  @see OCELOT_SUCCESS.
uint8_t ocelot_init(const struct OCELOT_INIT* init);

/// Initialize the ocelot Bluetooth service, and other platform
/// services.
/// @return An error code.  @see OCELOT_SUCCESS.
uint8_t ocelot_ble_init(void);

/// Get list of 16-bit UUIDs that should be advertised.
/// @param [out] size Pointer to variable to hold the size of the list.
/// @return A pointer to the list.
uint16_t* ocelot_ble_get_advertising_service_list(int* size);

/// Check if the ocelot library is ready to verify if features are
/// enabled.
/// @return true if ready.
/// @return false if not ready.
bool ocelot_is_ready(void);

/// Check if a feature is purchased.
/// @param [in] feature Integer representing the feature index in the
/// feature table. This number is the same number used across the
/// ocelot platform. The number is also used to identify the feature
/// in the ocelot Store, the ocelot App and the ocelot Developer
/// Portal.
/// @return true if purchased.
/// @return false if not purchased, if the library is not ready, or if
/// the feature number is out of range.
bool ocelot_is_feature_purchased(int feature);

/// Check if a feature is toggled on.
/// @param [in] feature Integer representing the feature index in the
/// feature table. This number is the same number used accross the
/// ocelot platform. The number is also used to identify the feature
/// in the ocelot Store, the ocelot App and the ocelot Developer
/// Portal.
/// @return true if toggled on.
/// @return false if not toggled on, if the library is not ready, or if
/// the feature number is out of range.
bool ocelot_is_feature_toggled(int feature);

/// Check if a feature is enabled (both purchased and toggled on).
/// @param [in] feature Integer representing the feature index in the
/// feature table.  This number is the same number used across the
/// ocelot platform.  The number is also used to identify the feature
/// in the ocelot Store, the ocelot App and the ocelot Developer
/// Portal.
/// @return true if enabled.
/// @return false if not enabled, if the library is not ready, or if
/// the feature number is out of range.
bool ocelot_is_feature_enabled(int feature);

/// Must be called by the application at 1 hz.
void ocelot_tick1hz(void);

/// Must be called by the application for every BLE event.
/// @param evt Pointer to a bluetooth event message.
void ocelot_on_ble_evt(ble_evt_t* evt);

/// Must be called by the application when an ocelot flash operation
/// is complete.
/// @param [in] success Set to true if successful.  Otherwise, set to
/// false.
void ocelot_flash_operation_complete(bool success);

/// @}

#if defined(__cplusplus)
   }
#endif

#endif // !defined(OCELOT_H_)

