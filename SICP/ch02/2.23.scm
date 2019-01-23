(define (for-each f list1)
	(define (iter lt)
	 	(if (not (null? lt))
		 	(begin
			 	(f (car lt))
				(iter (cdr lt)))))
	(iter list1))

(for-each (lambda (x)
		   (newline)
		   (display x))
 		(list 57 321 88))
