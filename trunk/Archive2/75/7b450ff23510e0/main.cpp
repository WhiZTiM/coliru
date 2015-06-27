factorial :: Integer -> Integer
factorial = go 1
    where
        go c 0 = c
        go c 1 = c
        go c n = go (c * n) (n - 1)

trailingZeroes :: Integer -> Integer
trailingZeroes = go 0
    where go c i = if i `mod` 10 == 0 then go (c + 1) (i `div` 10) else c

main :: IO ()
main = mapM_ print . map (trailingZeroes . factorial) $ [0..250]