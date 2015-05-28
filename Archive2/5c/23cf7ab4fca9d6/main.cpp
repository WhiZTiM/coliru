{-# LANGUAGE RankNTypes #-}
{-# LANGUAGE ExistentialQuantification #-}

data Exceptional a = Result a | forall b. Show b => YouFuckedUp b

instance Show a => Show (Exceptional a) where
    show (Result a) = show a
    show (YouFuckedUp a) = show a

main = print $ show (YouFuckedUp "up" :: Exceptional ())