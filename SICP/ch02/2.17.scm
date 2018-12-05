(define (last-pair lt)
 	(list-ref lt (- (length lt) 1)))

(last-pair (list 1 2 3 4 5 6 1))
