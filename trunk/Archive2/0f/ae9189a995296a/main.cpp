
zip' :: [a]->[b]->[(a,b)]
zip' _ [] = []
zip' [] _ = []
zip' (x:xs) (y:ys)=(x,y):(zip' xs ys)

main = print $ show (zip' [1..10] [10..20])
