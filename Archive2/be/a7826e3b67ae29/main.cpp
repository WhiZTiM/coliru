rep :: Int -> Int -> [Int]
rep a = reverse . rep' a
    where rep' 0 _ = [0]
          rep' z k = (z `mod` k) : rep' (z `div` k) k

main :: IO ()
main = do
    print $ rep 8 2