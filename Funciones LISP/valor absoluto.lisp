;Calcular e imprimir el valor absoluto del numero X
(defun valor_absoluto (x)
    (cond
        ((>= x 0) x)           ; si x>=0 se mantiene
        ((< x 0) (- x))        ; si x<0 se multiplica por -1
    ))

(print(valor_absoluto -13))