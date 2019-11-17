# libsetgroups

Library to set supplementary groups for running processes

# Motivation

When running unprivileged containers, there are mappings of groups from host to user namespace,
but for user there is no direct possibility to use these mappings inside.
There may be such with using `shadow-utils`, but it requires creation of all related files like `/etc/group` etc., 
and it may not work in such case (WAS NOT TESTED YET).

The current approach is to set per-process supplementary groups by applying `LD_PRELOAD` trick without creating other

# How to run

To inject supplementary groups in process, run:
```
_SUPPL_GROUPS=<group_list> LD_PRELOAD=<path_to_lib>/libsetgroups.so <executable_file>

# <group_list> - list of GIDs delimited with ','
# <path_to_lib> - path to library
# <executable_file> - executable file
```
