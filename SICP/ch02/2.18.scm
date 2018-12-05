(define (reverse lt)
 	(define (iter lt count result)
	 	(if (< count 0)
		 	result
			(iter lt (- count 1) (append result (list (list-ref lt count))))))
	(iter lt (- (length lt) 1) (list)))
