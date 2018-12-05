(define (square-list1 items)
 	(if (null? items)
	 ()
	 (cons (square (car items)) 
	  	   (square-list1 (cdr items)))))

(define (square-list2 items)
 	(map (lambda(x) (square x)) items))

(square-list1 (list 1 2 3 4))
(newline)
(square-list2 (list 5 6 7 8))
