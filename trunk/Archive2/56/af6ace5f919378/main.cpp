xs = [1,2,3,1,1]
f = minimum xs
findPos = map fst . filter (\e -> snd e == f) . zip [1..]

main = print $ findPos xs