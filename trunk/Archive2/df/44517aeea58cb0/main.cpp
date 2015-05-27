{-# LANGUAGE GADTs #-}

-- a sublanguage of integral and stringy operations,
-- with constants, addition, and concatenation

data Expr = Const Int | Lit String | Add Expr Expr | Concat Expr Expr
    deriving (Show, Read, Eq, Ord)

-- first problem: the constructors can be used to produce nonsensical values

-- 2 + "2"
nonsense = Add (Const 2) (Lit "2")

-- second problem: how to write an eval function?
-- we cannot reconciliate `eval (Const 2) :: Int` and `eval (Lit String) :: String`
-- we can have `eval :: Expr -> Either Int String` but that's somewhat unsatisfactory
eval = undefined


-- FIRST FIX

data Expr' a = Const' a | Add' (Expr' Int) (Expr' Int) | Concat' (Expr' String) (Expr' String)
    deriving (Show, Read, Eq, Ord)

-- now we can export smart constructors so that only sensible values can be made
const_ :: Int -> Expr' Int
const_ = Const'

lit :: String -> Expr' String
lit = Const'

-- error: Couldn't match expected type `Int' with actual type `String'
-- nonsense = Add' (const_ 2) (lit "2")

-- better...
eval' :: Expr' a -> a

eval' (Const' i) = i
eval' (Add' x y) = eval' x + eval' y
eval' (Concat' x y) = eval' x ++ eval' y
