areBothFive:: Int -> Int -> Bool
5 `areBothFive` 5 = True 
x `areBothFive` y = False -- the x and y are variables in the pattern match here

main = print $ (show $ areBothFive 5 5) ++ " " ++  (show $ areBothFive 5 4)
