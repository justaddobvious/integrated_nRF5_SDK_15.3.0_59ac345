///////////////////////////////////////////////////////////////////////
// Copyright © 2019,
// 4iiii Innovations Inc.,
// Cochrane, Alberta, Canada.
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are not permitted without express written approval of
// 4iiii Innovations Inc.
///////////////////////////////////////////////////////////////////////

#include "app_timer.h"
#include "ble.h"
#include "nrf_fstorage.h"
#include "nrf_fstorage_sd.h"
#include "nrf.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "ocelot.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h> 

#include "nrf_log.h"

#define OCELOT_FLASH_START 0xFB000

static uint32_t m_ocelot_evt_handler(enum OCELOT_EVT evt, union OCELOT_EVT_ARGS* args);
static bool m_ocelot_flash_erase_page(uint32_t address);
static uint32_t m_ocelot_flash_write(const void* data, uint32_t address, uint32_t size);
static void m_ocelot_flash_instance_evt_handler(nrf_fstorage_evt_t* p_evt);
static void m_ocelot_timer_handler(void* context);
static void m_ocelot_ble_evt_handler(const ble_evt_t* p_ble_evt, void* p_context);


APP_TIMER_DEF(m_ocelot_timer_id);
NRF_FSTORAGE_DEF(static nrf_fstorage_t main_ocelot_flash_instance) =
{
    .evt_handler = m_ocelot_flash_instance_evt_handler,
    .start_addr = OCELOT_FLASH_START,
    .end_addr = (OCELOT_FLASH_START + 4096 * 3 - 1)
};
static const struct OCELOT_INIT m_ocelot_init_info =
{
   .application_version =
   {
      .release = 0,
      .major = 1,
      .minor = 1
   },
   .evt_handler = m_ocelot_evt_handler
};


bool m_ocelot_init(void)
{
   uint32_t err_code;

   if (nrf_fstorage_init(&main_ocelot_flash_instance, &nrf_fstorage_sd, NULL) != NRF_SUCCESS)
      return false;

   if (ocelot_init(&m_ocelot_init_info) != OCELOT_SUCCESS)
       return false;

   err_code = app_timer_create(&m_ocelot_timer_id, APP_TIMER_MODE_REPEATED, m_ocelot_timer_handler);

   if (err_code != NRF_SUCCESS)
      return false;

   err_code = app_timer_start(m_ocelot_timer_id, APP_TIMER_TICKS(1000), NULL);

   if (err_code != NRF_SUCCESS)
      return false;

   return true;
}

bool m_ocelot_ble_init(void)
{
   if (ocelot_ble_init() != OCELOT_SUCCESS)
      return false;

   NRF_SDH_BLE_OBSERVER(m_ocelot_ble_observer, 2, m_ocelot_ble_evt_handler, NULL);
   return true;
}


static uint32_t m_ocelot_evt_handler(enum OCELOT_EVT evt, union OCELOT_EVT_ARGS* args)
{
   uint32_t retval = 0;

   switch (evt)
   {
      case OCELOT_EVT_RESET_PREPARE:
         break;

      case OCELOT_EVT_FLASH_ERASE_PAGE:
         retval = (uint32_t) m_ocelot_flash_erase_page(args->flash_erase_page_args.address);
         break;

      case OCELOT_EVT_FLASH_WRITE:
         retval = m_ocelot_flash_write(args->flash_write_args.data, args->flash_write_args.address, args->flash_write_args.size);
         break;

      case OCELOT_EVT_REQUEST_FAST_CONN:
         break;

      case OCELOT_EVT_SERVICE_DATA_UPDATE:
         break;

      default:
         break;
   }

   return retval;
}

static bool m_ocelot_flash_erase_page(uint32_t address)
{
   return nrf_fstorage_erase(&main_ocelot_flash_instance, address, 1, NULL) == NRF_SUCCESS;
}

static uint32_t m_ocelot_flash_write(const void* data, uint32_t address, uint32_t size)
{
   return nrf_fstorage_write(&main_ocelot_flash_instance, address, data, size, NULL) == NRF_SUCCESS ? size : 0;
}

static void m_ocelot_flash_instance_evt_handler(nrf_fstorage_evt_t* p_evt)
{
    switch (p_evt->id)
    {
        case NRF_FSTORAGE_EVT_WRITE_RESULT:
        case NRF_FSTORAGE_EVT_ERASE_RESULT:
            ocelot_flash_operation_complete(p_evt->result == NRF_SUCCESS);
            break;

        default:
            break;
    }
}

static void m_ocelot_timer_handler(void* context)
{
   (void) context;
   ocelot_tick1hz();
}

static void m_ocelot_ble_evt_handler(const ble_evt_t* p_ble_evt, void* p_context)
{
   (void) p_context;
   ocelot_on_ble_evt((ble_evt_t*) p_ble_evt);
}

