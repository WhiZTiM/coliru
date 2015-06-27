int main()
{
        int i = 7 ;

        switch(i)
        {
            case 3 :
                // ...

            case 1 :
            {
                int j = 25 ;
                ++j ;
                // ...
            }
                break ;

            case 7 : // *** error: cannot jump from switch statement to this case label
                     // *** error: jump bypasses initialisation of 'int j'
                ;
                // ...
        }
        
        int k = 6 ;
        if( i < 10 ) goto label ; // *** cannot jump from this goto statement to its label

        // int k = 6 ;
        ++k ;

    label:  ; // // *** error: jump bypasses initialisation of 'int k'
}
