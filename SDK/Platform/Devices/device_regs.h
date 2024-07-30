/**************************************************************************************************/
/**
 * @file     device_regs.h
 * @brief    Z20K11xM device reg resource file.
 * @version  V1.7.0
 * @date     May-2020
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#ifndef DEVICE_REGS_H
#define DEVICE_REGS_H

#if (defined(DEV_Z20K118M))
    #include "Z20K118M.h"
#elif (defined(DEV_Z20K116M))
    #include "Z20K116M.h"
#else
    #error "No valid device defined!"
#endif

#endif /* DEVICE_REGS_H */
