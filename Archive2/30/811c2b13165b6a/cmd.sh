md5sum main.cpp | (echo "const unsigned char binary_data[] = {"; od -txC - | sed -e "s/^[0-9]*//" -e s"/ \([0-9a-f][0-9a-f]\)/0x\1,/g" -e"\$d" | sed -e"\$s/,$/};/")