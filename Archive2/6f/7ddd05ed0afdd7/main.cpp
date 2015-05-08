import Control.Monad (replicateM)

ints :: [String]
ints = map (\i -> [i]) ['1'..'9']

inbetweens :: [[String]]
inbetweens = replicateM 8 
    [ " + "
    , " - "
    , ""
    ]

alternate :: [a] -> [a] -> [a]
alternate [] r = r
alternate (x:xs) r = x : alternate r xs

allStrings :: [String]
allStrings = map (concat . alternate ints) inbetweens

splitBy :: (a -> Bool) -> [a] -> [[a]]
splitBy _ [] = []
splitBy c ls = 
    let (l, r) = span (not . c) ls
    in l : (splitBy c . drop 1 $ r)
    
opOf :: String -> (Int -> Int -> Int)
opOf "+" = (+)
opOf "-" = (-)
opOf _ = error "Unrecognized OP code"
    
-- Evaluates tokens
eval :: Int -> [String] -> Int
eval acc [] = acc
eval _ [_] = error "Invalid tokens"
eval acc (op:b:r) = eval ((opOf op) acc (read b)) r
        
-- Evaluates a string
evalString :: String -> Int
evalString str = 
    let (h:tokens) = (splitBy (==' ') str) in
    eval (read h) tokens 
    
solution :: [String]
solution = map fst 
         . filter ((==100) . snd)
         . map (\s -> (s, evalString s))
         $ allStrings

main :: IO ()
main = mapM_ putStrLn solution