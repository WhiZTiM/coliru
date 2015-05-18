insertionSort :: Ord a => [a] -> [a]
insertionSort = foldr insert []
  where insert x (y:ys) 
            | x > y     = y : insert x ys
            | otherwise = x : y : ys
        
main :: IO ()
main = print $ insertionSort ([0, 0, 2, 91, 2, 376, 37, -283, -3, 86, -23] :: [Int])