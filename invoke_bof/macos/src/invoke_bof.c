/*++

 Copyright (c) SCYTHE, Inc. Use is subject to agreement.

 --*/
#define _GNU_SOURCE
#include "common.h"

PSCYTHE_CLIENT g_pClient = NULL;

// {495c51c0-c026-11ec-810c-33e4a10903dc}
static const GUID invoke_bofModuleId =
{ 0x495c51c0, 0xc026, 0x11ec, { 0x81, 0x0c, 0x33, 0xe4, 0xa1, 0x09, 0x03, 0xdc}};

static const SCYTHE_MODULE_TYPE invoke_bofModuleType = CATEGORY_WORKER;

INT init(PSCYTHE_CLIENT pClient, PVOID pvReserved)
{
    g_pClient = pClient;
        
    return SCYTHE_NOERROR;
}

ERROR_T run(PSCYTHE_MESSAGE pMessage, PVOID pvReserved)
{
    ERROR_T status = SCYTHE_NOERROR;

    const CHAR szDefaultMessage[] = "Nothing to echo.";
    
    if (pMessage->MessageSize > 0)
    {
        status = g_pClient->PostToMessagingSubsystem(pMessage->MessageId, 0, 0,
                                                    CATEGORY_OUTPUT_COMMUNICATION,
                                                    &invoke_bofModuleId,
                                                    NULL,
                                                    pMessage->MessageSize,
                                                    pMessage->Message);
    }
    else
    {
        status = g_pClient->PostToMessagingSubsystem(pMessage->MessageId, 0, 0,
                                                     CATEGORY_OUTPUT_COMMUNICATION,
                                                     &invoke_bofModuleId,
                                                     NULL,
                                                     strlen(szDefaultMessage), (PBYTE)szDefaultMessage);
    }

    return status;
}

ERROR_T getinfo(PSCYTHE_MODULE_INFORMATION pInformation)
{
    ERROR_T status = SCYTHE_ERROR_INVALID_PARAMETER;

    if (NULL != pInformation)
    {
        if (pInformation->cbSize >= sizeof(SCYTHE_MODULE_INFORMATION))
        {
            pInformation->ModuleVersion.wMajor = 1;
            pInformation->ModuleVersion.wMinor = 0;
            pInformation->ModuleType = invoke_bofModuleType;
            memcpy(&(pInformation->ModuleId), &invoke_bofModuleId, sizeof(GUID));
            status = SCYTHE_NOERROR;
        }
    }

    return status;
}

// Required function: deinit
ERROR_T deinit(PVOID pvReserved)
{
    return SCYTHE_NOERROR;
}