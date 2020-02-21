///////////////////////////////////////////////////////////////////////
// Copyright © 2019,
// 4iiii Innovations Inc.,
// Cochrane, Alberta, Canada.
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are not permitted without express written approval of
// 4iiii Innovations Inc.
///////////////////////////////////////////////////////////////////////

#if !defined(M_OCELOT_INIT_)
#define M_OCELOT_INIT_

#include <stdbool.h>
#include <stdint.h>


#if defined(__cplusplus)
   extern "C"
   {
#endif

bool m_ocelot_init(void);
bool m_ocelot_ble_init(void);

#if defined(__cplusplus)
   }
#endif
#endif // !defined(M_OCELOT_INIT_)

