(define (fringe x result)
 	(cond ((null? x) result)
	 	  ((not (pair? x)) (cons result x))
		  (else
			 	(let ((y (fringe (car x) result)))
				 (fringe (cdr x) y)))))

(define x (list (list 1 2) (list 3 4)))
(fringe x '())
(newline)
(fringe (list x x) '())
