;Calcular e imprimir el factorial del numero X
(defun factorial (x)
    (cond               ;funciona como el switch de C
        ((= x 0) 1)     ; ((condicion) accion)
        ((= x 1) 1)
        ((> x 1)
            (* x (factorial (- x 1))))   ; x * factorial(x-1)
    ))

(print(factorial 3))