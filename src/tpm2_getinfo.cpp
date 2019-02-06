//**********************************************************************;
// Copyright (c) 2015, Intel Corporation
// All rights reserved.
//
// Modified by Seunghun Han (@kkamagui1)
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of Intel Corporation nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
// THE POSSIBILITY OF SUCH DAMAGE.
//**********************************************************************;

#include <stdarg.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <getopt.h>

#include <sapi/tpm20.h>
#include <tcti/tcti_socket.h>
#include "common.h"

int debugLevel = 0;
char outFilePath[PATH_MAX];

UINT32 changeEndianDword( UINT32 p )
{
    return( ((const UINT32)(((p)& 0xFF) << 24))    | \
          ((const UINT32)(((p)& 0xFF00) << 8))   | \
          ((const UINT32)(((p)& 0xFF0000) >> 8)) | \
          ((const UINT32)(((p)& 0xFF000000) >> 24)));
}

int getInfo()
{
    TPMI_YES_NO moreData;
    TPMS_CAPABILITY_DATA capabilityData;
    char manuID[5] = "    ";
    char *manuIDPtr = &manuID[0];
    UINT32 rval;

    // Get a manufacturer string.
    rval = Tss2_Sys_GetCapability( sysContext, 0, TPM_CAP_TPM_PROPERTIES, TPM_PT_MANUFACTURER, 1, &moreData, &capabilityData, 0 );
    *( (UINT32 *)manuIDPtr ) = changeEndianDword( capabilityData.data.tpmProperties.tpmProperty[0].value );
    if(rval != TPM_RC_SUCCESS)
    {
        goto ERROR;
    }
    *( (UINT32 *)manuIDPtr ) = changeEndianDword( capabilityData.data.tpmProperties.tpmProperty[0].value );
    printf( "Manufacturer: %s\n", manuID );

    // Get vendor strings.
    rval = Tss2_Sys_GetCapability( sysContext, 0, TPM_CAP_TPM_PROPERTIES, TPM_PT_VENDOR_STRING_1, 1, &moreData, &capabilityData, 0 );
    *( (UINT32 *)manuIDPtr ) = changeEndianDword( capabilityData.data.tpmProperties.tpmProperty[0].value );
    if(rval != TPM_RC_SUCCESS)
    {
        goto ERROR;
    }
    *( (UINT32 *)manuIDPtr ) = changeEndianDword( capabilityData.data.tpmProperties.tpmProperty[0].value );
    printf( "Vendor strings: %s ", manuID );

    rval = Tss2_Sys_GetCapability( sysContext, 0, TPM_CAP_TPM_PROPERTIES, TPM_PT_VENDOR_STRING_2, 1, &moreData, &capabilityData, 0 );
    *( (UINT32 *)manuIDPtr ) = changeEndianDword( capabilityData.data.tpmProperties.tpmProperty[0].value );
    if(rval != TPM_RC_SUCCESS)
    {
        goto ERROR;
    }
    *( (UINT32 *)manuIDPtr ) = changeEndianDword( capabilityData.data.tpmProperties.tpmProperty[0].value );
    printf( " %s", manuID );

    rval = Tss2_Sys_GetCapability( sysContext, 0, TPM_CAP_TPM_PROPERTIES, TPM_PT_VENDOR_STRING_3, 1, &moreData, &capabilityData, 0 );
    *( (UINT32 *)manuIDPtr ) = changeEndianDword( capabilityData.data.tpmProperties.tpmProperty[0].value );
    if(rval != TPM_RC_SUCCESS)
    {
        goto ERROR;
    }
    *( (UINT32 *)manuIDPtr ) = changeEndianDword( capabilityData.data.tpmProperties.tpmProperty[0].value );
    printf( " %s", manuID );

    rval = Tss2_Sys_GetCapability( sysContext, 0, TPM_CAP_TPM_PROPERTIES, TPM_PT_VENDOR_STRING_4, 1, &moreData, &capabilityData, 0 );
    *( (UINT32 *)manuIDPtr ) = changeEndianDword( capabilityData.data.tpmProperties.tpmProperty[0].value );
    if(rval != TPM_RC_SUCCESS)
    {
        goto ERROR;
    }
    *( (UINT32 *)manuIDPtr ) = changeEndianDword( capabilityData.data.tpmProperties.tpmProperty[0].value );
    printf( " %s \n", manuID );

    // Get firmware version strings.
    rval = Tss2_Sys_GetCapability( sysContext, 0, TPM_CAP_TPM_PROPERTIES, TPM_PT_FIRMWARE_VERSION_1, 1, &moreData, &capabilityData, 0 );
    if(rval != TPM_RC_SUCCESS)
    {
        goto ERROR;
    }
    printf( "Firmware Version: %08X ",  capabilityData.data.tpmProperties.tpmProperty[0].value );

    rval = Tss2_Sys_GetCapability( sysContext, 0, TPM_CAP_TPM_PROPERTIES, TPM_PT_FIRMWARE_VERSION_2, 1, &moreData, &capabilityData, 0 );
    if(rval != TPM_RC_SUCCESS)
    {
        goto ERROR;
    }
    printf( "%08X \n",  capabilityData.data.tpmProperties.tpmProperty[0].value );

    // Get a revision version value.
    rval = Tss2_Sys_GetCapability( sysContext, 0, TPM_CAP_TPM_PROPERTIES, TPM_PT_REVISION, 1, &moreData, &capabilityData, 0 );
    if(rval != TPM_RC_SUCCESS)
    {
        goto ERROR;
    }
    printf( "Revision: %d\n",  capabilityData.data.tpmProperties.tpmProperty[0].value );

    // Get a year value.
    rval = Tss2_Sys_GetCapability( sysContext, 0, TPM_CAP_TPM_PROPERTIES, TPM_PT_YEAR, 1, &moreData, &capabilityData, 0 );
    if(rval != TPM_RC_SUCCESS)
    {
        goto ERROR;
    }
    printf( "Year: %d\n",  capabilityData.data.tpmProperties.tpmProperty[0].value );

    // Get a day of year value.
    rval = Tss2_Sys_GetCapability( sysContext, 0, TPM_CAP_TPM_PROPERTIES, TPM_PT_DAY_OF_YEAR, 1, &moreData, &capabilityData, 0 );
    if(rval != TPM_RC_SUCCESS)
    {
        goto ERROR;
    }
    printf( "Day of year: %d\n",  capabilityData.data.tpmProperties.tpmProperty[0].value );

    return 0;

ERROR:
    printf("TPM Error:0x%x......\n", rval);
    return -1;
}

void showHelp(const char *name)
{
    printf("\n%s  [options]\n"
            "-h, --help                Display command tool usage info;\n"
            "-v, --version             Display command tool version info;\n"
            "-p, --port    <port number>   The Port number, default is %d, optional\n"
            "-d, --debugLevel <0|1|2|3>    The level of debug message, default is 0, optional\n"
                "\t0 (high level test results)\n"
                "\t1 (test app send/receive byte streams)\n"
                "\t2 (resource manager send/receive byte streams)\n"
                "\t3 (resource manager tables)\n"
            "\n\tExample:\n"
            "display usage:\n"
            "    %s -h\n"
            "display version:\n"
            "    %s -v\n"
            , name, DEFAULT_RESMGR_TPM_PORT, name, name  );
}

int main(int argc, char *argv[])
{
    char hostName[200] = DEFAULT_HOSTNAME;
    int port = DEFAULT_RESMGR_TPM_PORT;

    setbuf(stdout, NULL);
    setvbuf (stdout, NULL, _IONBF, BUFSIZ);

    int opt = -1;
    const char *optstring = "hvg:p:d:o:L:s";
    static struct option long_options[] = {
        {"help",0,NULL,'h'},
        {"version",0,NULL,'v'},
        {"port",1,NULL,'p'},
        {"debugLevel",1,NULL,'d'},
        {0,0,0,0}
    };

    TPMI_ALG_HASH algorithmId;

    int returnVal = 0;
    int flagCnt = 0;
    int h_flag = 0,
        v_flag = 0;

    while((opt = getopt_long(argc,argv,optstring,long_options,NULL)) != -1)
    {
        switch(opt)
        {
        case 'h':
            h_flag = 1;
            break;
        case 'v':
            v_flag = 1;
            break;
        case 'p':
            if( getPort(optarg, &port) )
            {
                printf("Incorrect port number.\n");
                returnVal = -3;
            }
            break;
        case 'd':
            if( getDebugLevel(optarg, &debugLevel) )
            {
                printf("Incorrect debug level.\n");
                returnVal = -4;
            }
            break;
            //          case 0:
            //              break;
        case ':':
            //              printf("Argument %c needs a value!\n",optopt);
            returnVal = -5;
            break;
        case '?':
            //              printf("Unknown Argument: %c\n",optopt);
            returnVal = -6;
            break;
            //default:
            //  break;
        }
        if(returnVal)
            break;
    };

    if(returnVal != 0)
        return returnVal;
    flagCnt = h_flag + v_flag;

    if(flagCnt > 1)
    {
        showArgMismatch(argv[0]);
        return -7;
    }

    if(h_flag)
    {
        showHelp(argv[0]);
        return 0;
    }
    else if(v_flag == 1)
    {
        showVersion(argv[0]);
        return 0;
    }

    prepareTest(hostName, port, debugLevel);

    returnVal = getInfo();

    finishTest();

    if(returnVal)
        return -9;

    return 0;
}
