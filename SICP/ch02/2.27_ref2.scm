(define (tree-reverse lst)
  (define (iter remained-items result)
	(if (null? remained-items)
	  result
	  (iter (cdr remained-items)
			(cons (if (pair? (car remained-items))
					(tree-reverse (car remained-items))
					(car remained-items))
				  result))))
  (iter lst '()))

(display (tree-reverse (cons (list 1 2) (list 3 4))))
(newline)
(display (tree-reverse (list (list 1 2) (list 3 4))))
