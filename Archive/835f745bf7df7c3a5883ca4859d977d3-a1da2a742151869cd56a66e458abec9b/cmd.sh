find /usr/include > a ; find /usr/bin > b ; find /usr/local/include > c ; find /usr/local/bin > d ; paste -d ' ' a b c d | mawk '{ printf "%-80s %-80s %-80s %-80s\n", $1, $2, $3, $4 }'