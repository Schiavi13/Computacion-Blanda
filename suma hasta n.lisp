;Calcular la sumatoria de los numeros hasta el valor N
(defun suma_hasta_n (n)
    (/ (* n (+ n 1)) 2))    ;n(n+1)/2

(print(suma_hasta_n 13))