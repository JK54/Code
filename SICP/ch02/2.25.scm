(define x (list 1 3 (list 5 7) 9))
(define y (list (list 7)))
(define z (list 1 (list 2 (list 3 (list 4 (list 5 (list 6 7)))))))

(newline)
(display x)
(newline)
(display (car (cdr (car (cdr (cdr x))))))
(display (cadar (cddr x)))
; (display (cadaddr x)) the maximum deepth of reduction cr is 4.
(newline)
(display y)
(newline)
(display (car (car y)))
(display (caar y))
(newline)
(display z)
(newline)
(display (cadr (cadr (cadr (cadr (cadr (cadr z)))))));the car of (list 1) is 1,one extra car to pick the num from the pair.
(display (cadadr (cadadr (cadadr z))))