import Data.String

type Nr = Double
data Algo
  = Nom Nr
  | Lit String
  | String
  | Und 
  deriving (Show)

instance Num Algo where
  (+) (Nom a) (Nom b)=Nom(a+b)
  (+) _ _=Und
  (*) (Nom a) (Nom b)=Nom(a*b)
  (*) _ _=Und
  abs (Nom a)=Nom(abs a)
  abs _=Und
  signum (Nom a)=Nom(signum a)
  signum _=Und
  fromInteger a=Nom(fromInteger a)
  
instance IsString Algo where
  fromString = Lit

main=do
  print (["test", 1,2,3,Und,Nom 5,Lit "x"]::[Algo])