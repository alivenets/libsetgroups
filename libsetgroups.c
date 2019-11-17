/*
 * The library provides the way to add supplementary groups to process using setgroups
 */

// Required for: secure_getenv
#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <grp.h>

#define MAX_SUPPL_GROUPS 16

static gid_t supplGroupsList[MAX_SUPPL_GROUPS];

#define ARRAY_SIZEOF(arr) (sizeof(arr) / sizeof(arr[0]))

static size_t parseStringGroupList(const char *const str, char delim, gid_t *const arr, size_t len)
{
    // TODO: implement parsing
    arr[0] = strtol(str, NULL, 10);
    return 1;
}

static void setProcessSupplGroups(const char *const groupListStr)
{
    size_t groupCount = parseStringGroupList(groupListStr, ',', supplGroupsList, ARRAY_SIZEOF(supplGroupsList));
    
    printf("Setting supplementary group: %d\n", supplGroupsList[0]);
    
    int ret = setgroups(groupCount, (const gid_t*)(&supplGroupsList[0]));
    if (ret < 0) {
        printf("ERROR: failed to set supplementary groups: %d (%s)\n", ret, strerror(ret));
    }
}

/**
 * @brief Configure all buffers when library is being loaded
 */
__attribute__((constructor)) static void configureSupplementaryGroups(void)
{
    const char *supplGroups = secure_getenv("_SUPPL_GROUPS");

    printf("Setting groups\n");
    /* Configure stderr first to see errors if any */
    if (supplGroups != NULL)
        setProcessSupplGroups(supplGroups);
    else
        printf("WARN: suppl groups list is empty\n");
}
