-- A.hs

module A (Type, whatever, printType) where

data Type = Whatever

whatever :: Type
whatever = Whatever

printType :: Type -> String
printType _ = "Whatever"

-- Main.hs

module Main where

import A

instance Show Type where
    show = printType

main :: IO ()
main = print whatever