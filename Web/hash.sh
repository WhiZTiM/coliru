#!/bin/bash
[ "$INPUT_FILES_DIR" == "" ] && { echo "INPUT_FILES_DIR is not set." 1>&2 ; exit 1 ; }
[ "$INPUT_FILES_DIR" == "." ] && { echo "INPUT_FILES_DIR is jsut a dot." 1>&2 ; exit 1 ; }
sum="$(shasum ${INPUT_FILES_DIR}/cmd.sh | cut -d ' ' -f1)"
[ -f main.cpp ] && {
    sum="$(shasum ${INPUT_FILES_DIR}/main.cpp | cut -d ' ' -f1)${sum}"
    sum="$(echo ${sum} | shasum | cut -d ' ' -f1)"
}
HASH=$(echo $sum | cut -c -16)
echo $(echo "${HASH}" | cut -c -2)/$(echo "${HASH:2}")
