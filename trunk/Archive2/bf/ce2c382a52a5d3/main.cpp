        do
        {
            const char *s1c = S1.c_str();
            for (POSS1 = 0; s1c[POSS1] != '\0'; POSS1++)
            {
                LENS1++;
            }
            const char *s2c = S2.c_str();
            for (POSS2 = 0; s2c[POSS2] != '\0'; POSS2++)
            {
                LENS2++;
            }

        } while (LENS2 >= LENS1);
