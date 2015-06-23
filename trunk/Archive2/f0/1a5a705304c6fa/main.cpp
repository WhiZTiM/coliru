import Data.List

main :: IO ()
main = 
    let fn '[' = '{'
        fn ']' = '}'
        fn c   = c
    in (return [1, 2, 3] :: IO [Integer]) >>= putStrLn . map fn . show . subsequences