#!/bin/bash
export CHROOT="/var/chroot"
export COLIRU_TIMEOUT="$(cat timeout.txt || echo 20)"
echo "COLIRU_TIMEOUT: ${COLIRU_TIMEOUT}"


rm -rf "${CHROOT}/tmp/*"
set -e
ulimit -f 10000
[ -f main.cpp ] || { echo "Webserver could not find main.cpp. Exiting." 1>&2 ; exit 1; }

cp cmd.sh main.cpp "${CHROOT}/tmp/"
cat compile.sh | sed -e "s/TIMEOUT/${COLIRU_TIMEOUT}/" > "${CHROOT}/tmp/compile.sh"

chmod 755 "${CHROOT}/tmp/cmd.sh"
chmod 755 "${CHROOT}/tmp/compile.sh"

./chroot.sh
