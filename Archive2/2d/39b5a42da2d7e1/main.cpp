insertionSort :: Ord a => [a] -> [a]
insertionSort = scanr insert []
  where insert x (y:ys) | x > y = y : insert x ys
        insert x ys = x : ys
        
main :: IO ()
main = return ()