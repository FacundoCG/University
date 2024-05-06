data AB a = Nil | Bin (AB a) a (AB a)

maximaDistancia :: AB a -> Int
maximaDistancia Nil = 0
maximaDistancia (Bin l _ r) = 1 + maximaDistancia l + maximaDistancia r