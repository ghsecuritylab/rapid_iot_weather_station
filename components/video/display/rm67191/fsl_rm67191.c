/*
 * The Clear BSD License
 * Copyright (c) 2017, NXP Semiconductors, Inc.
 * All rights reserved.
 *
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_display.h"
#include "fsl_rm67191.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define RM67191_DelayMs VIDEO_DelayMs

/*******************************************************************************
 * Variables
 ******************************************************************************/
static const uint8_t lcmInitSetting[][2] = {
    {0xFE, 0x0B}, {0x28, 0x40}, {0x29, 0x4F}, {0xFE, 0x0E}, {0x4B, 0x00}, {0x4C, 0x0F}, {0x4D, 0x20}, {0x4E, 0x40},
    {0x4F, 0x60}, {0x50, 0xA0}, {0x51, 0xC0}, {0x52, 0xE0}, {0x53, 0xFF}, {0xFE, 0x0D}, {0x18, 0x08}, {0x42, 0x00},
    {0x08, 0x41}, {0x46, 0x02}, {0x72, 0x09}, {0xFE, 0x0A}, {0x24, 0x17}, {0x04, 0x07}, {0x1A, 0x0C}, {0x0F, 0x44},
    {0xFE, 0x04}, {0x00, 0x0C}, {0x05, 0x08}, {0x06, 0x08}, {0x08, 0x08}, {0x09, 0x08}, {0x0A, 0xE6}, {0x0B, 0x8C},
    {0x1A, 0x12}, {0x1E, 0xE0}, {0x29, 0x93}, {0x2A, 0x93}, {0x2F, 0x02}, {0x31, 0x02}, {0x33, 0x05}, {0x37, 0x2D},
    {0x38, 0x2D}, {0x3A, 0x1E}, {0x3B, 0x1E}, {0x3D, 0x27}, {0x3F, 0x80}, {0x40, 0x40}, {0x41, 0xE0}, {0x4F, 0x2F},
    {0x50, 0x1E}, {0xFE, 0x06}, {0x00, 0xCC}, {0x05, 0x05}, {0x07, 0xA2}, {0x08, 0xCC}, {0x0D, 0x03}, {0x0F, 0xA2},
    {0x32, 0xCC}, {0x37, 0x05}, {0x39, 0x83}, {0x3A, 0xCC}, {0x41, 0x04}, {0x43, 0x83}, {0x44, 0xCC}, {0x49, 0x05},
    {0x4B, 0xA2}, {0x4C, 0xCC}, {0x51, 0x03}, {0x53, 0xA2}, {0x75, 0xCC}, {0x7A, 0x03}, {0x7C, 0x83}, {0x7D, 0xCC},
    {0x82, 0x02}, {0x84, 0x83}, {0x85, 0xEC}, {0x86, 0x0F}, {0x87, 0xFF}, {0x88, 0x00}, {0x8A, 0x02}, {0x8C, 0xA2},
    {0x8D, 0xEA}, {0x8E, 0x01}, {0x8F, 0xE8}, {0xFE, 0x06}, {0x90, 0x0A}, {0x92, 0x06}, {0x93, 0xA0}, {0x94, 0xA8},
    {0x95, 0xEC}, {0x96, 0x0F}, {0x97, 0xFF}, {0x98, 0x00}, {0x9A, 0x02}, {0x9C, 0xA2}, {0xAC, 0x04}, {0xFE, 0x06},
    {0xB1, 0x12}, {0xB2, 0x17}, {0xB3, 0x17}, {0xB4, 0x17}, {0xB5, 0x17}, {0xB6, 0x11}, {0xB7, 0x08}, {0xB8, 0x09},
    {0xB9, 0x06}, {0xBA, 0x07}, {0xBB, 0x17}, {0xBC, 0x17}, {0xBD, 0x17}, {0xBE, 0x17}, {0xBF, 0x17}, {0xC0, 0x17},
    {0xC1, 0x17}, {0xC2, 0x17}, {0xC3, 0x17}, {0xC4, 0x0F}, {0xC5, 0x0E}, {0xC6, 0x00}, {0xC7, 0x01}, {0xC8, 0x10},
    {0xFE, 0x0D}, {0x95, 0xEC}, {0x8D, 0xEE}, {0x44, 0xEC}, {0x4C, 0xEC}, {0x32, 0xEC}, {0x3A, 0xEC}, {0x7D, 0xEC},
    {0x75, 0xEC}, {0x00, 0xEC}, {0x08, 0xEC}, {0x85, 0xEC}, {0xA6, 0x21}, {0xA7, 0x05}, {0xA9, 0x06}, {0x82, 0x06},
    {0x41, 0x06}, {0x7A, 0x07}, {0x37, 0x07}, {0x05, 0x06}, {0x49, 0x06}, {0x0D, 0x04}, {0x51, 0x04},
};

const display_operations_t rm67191_ops = {
    .init = RM67191_Init, .deinit = RM67191_Deinit, .start = RM67191_Start, .stop = RM67191_Stop,
};

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t RM67191_Init(display_handle_t *handle, const display_config_t *config)
{
    uint32_t i;
    status_t status = kStatus_Success;
    rm67191_resource_t *resource = (rm67191_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice = &(resource->dsiDevice);

    /* Perform reset. */
    resource->pullResetPin(true);

    RM67191_DelayMs(10);

    resource->pullResetPin(false);

    RM67191_DelayMs(5);

    resource->pullResetPin(true);
    RM67191_DelayMs(20);

    /* Set the LCM init settings. */
    for (i = 0; i < ARRAY_SIZE(lcmInitSetting); i++)
    {
        status = MIPI_DSI_GenericWrite(dsiDevice, lcmInitSetting[i], 2);

        if (kStatus_Success != status)
        {
            return status;
        }
    }

    /* Change to send user command. */
    const uint8_t rm67191UserCmdEntry[] = {RM67191_WRMAUCCTR, 0x00};
    MIPI_DSI_GenericWrite(dsiDevice, rm67191UserCmdEntry, ARRAY_SIZE(rm67191UserCmdEntry));

    /* Software reset */
    MIPI_DSI_DCS_SoftReset(dsiDevice);

    RM67191_DelayMs(100);

    /* Set DSI mode */
    const uint8_t rm67191DsiMode[] = {RM67191_SETDSIMODE, 0x03};
    MIPI_DSI_GenericWrite(dsiDevice, rm67191DsiMode, ARRAY_SIZE(rm67191DsiMode));

    /* Brightness. */
    const uint8_t rm67191Brightness[] = {RM67191_WRDISBV, 0xff};
    MIPI_DSI_GenericWrite(dsiDevice, rm67191Brightness, ARRAY_SIZE(rm67191Brightness));

    /* Exit sleep mode */
    MIPI_DSI_DCS_EnterSleepMode(dsiDevice, false);

    RM67191_DelayMs(120);

    /* Set display on. */
    MIPI_DSI_DCS_SetDisplayOn(dsiDevice, true);

    RM67191_DelayMs(100);

    return kStatus_Success;
}

status_t RM67191_Deinit(display_handle_t *handle)
{
    rm67191_resource_t *resource = (rm67191_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice = &(resource->dsiDevice);

    MIPI_DSI_DCS_EnterSleepMode(dsiDevice, true);

    resource->pullResetPin(false);

    return kStatus_Success;
}

status_t RM67191_Start(display_handle_t *handle)
{
    rm67191_resource_t *resource = (rm67191_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice = &(resource->dsiDevice);

    return MIPI_DSI_DCS_SetDisplayOn(dsiDevice, true);
}

status_t RM67191_Stop(display_handle_t *handle)
{
    rm67191_resource_t *resource = (rm67191_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice = &(resource->dsiDevice);

    return MIPI_DSI_DCS_SetDisplayOn(dsiDevice, false);
}
