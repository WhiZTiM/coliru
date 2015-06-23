import Data.List
f '[' = '{';f ']' = '}';f c = c;main = (readLn :: IO [Integer]) >>= putStrLn . map f . show . subsequences