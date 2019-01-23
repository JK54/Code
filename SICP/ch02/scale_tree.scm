(define (scale-tree1 tree factor)
 	(define nil '())
 	(cond ((null? tree) nil)
	 	  ((not (pair? tree)) (* tree factor))
		  (else
		   	(cons (scale-tree (car tree) factor) (scale-tree (cdr tree) factor)))))

(define (scale-tree2 tree factor)
 	(map (lambda (sub-tree)
		  	(if (pair? sub-tree)
			 	(scale-tree2 sub-tree factor)
				(* sub-tree factor)))
	 tree))

(define tree (list 1 (list 2 (list 3 4) 5) (list 6 7)))
(define factor 10)
(scale-tree2 tree factor)

(define t (list 1 (list 2 (list 3 (list 4 5)))))
(scale-tree2 t factor)
