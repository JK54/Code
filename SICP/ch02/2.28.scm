(define (fringe x)
 	(cond ((null? x) '() )
	 	  ((not (pair? x)) (list x))
		  (else (append (fringe (car x)) (fringe (cdr x))))))

(define x (list (list 1 2) (list 3 4)))
(display (fringe x))
(newline)
(display (fringe (list(list x x))))
(newline)
(display (fringe (list 1 2 3 4)))
