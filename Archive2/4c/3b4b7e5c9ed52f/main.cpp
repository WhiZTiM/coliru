import Data.List

main :: IO ()
main = 
    let fn '[' = '{'
        fn ']' = '}'
        fn c   = c
    in (readLn :: IO [Integer]) >>= putStrLn . map fn . show . subsequences