ln -s main.cpp main.c && gcc -std=c89 -Wall -Wextra -Werror -pedantic main.c -o xmlval && \

./xmlval name test2 <<EOF

<?xml version="1.0" encoding="UTF-8" standalone="no"?>
   <labels _FORMAT ="example" _QUANTITY="1" _PRINTERNAME="P1">

        <label>
	     <variable name= "test1">foobaz</variable>
	     <variable name= "test2">Hello blabla</variable>
	     <variable name= "test3">testme</variable>
	     <variable name= "test4">42</variable>
	     <variable name= "test5" />
        </label>

     </labels>
EOF