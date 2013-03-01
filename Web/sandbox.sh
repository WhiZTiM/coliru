#!/bin/bash
if [ "$(uname)" == "Darwin" ] ; then 
    ID="$(md5 main.cpp | cut -d '=' -f 2 | sed -e 's/ //g')-$(md5 cmd.sh | cut -d '=' -f 2 | sed -e 's/ //g')"
else
    ID="$(md5sum main.cpp | cut -d ' ' -f 1)-$(md5sum cmd.sh | cut -d ' ' -f 1)"
fi

if [ -f "${COLIRU_ARCHIVE}/${ID}/output" ] ; then
    cat "${COLIRU_ARCHIVE}/${ID}/output"
    exit
fi

pkill -9 -u sandbox
./repair-permissions.sh >/dev/null 2>&1
./build_and_run.sh
