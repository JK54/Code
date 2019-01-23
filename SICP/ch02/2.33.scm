(load "accumulate.scm")

(define (map0 p sequence)
 	(accumulate (lambda (x y) 
				 	(cons (p x) y))
	 			'() 
				sequence))

(define (append0 seq1 seq2)
 	(accumulate cons seq2 seq1))

(define (length0 sequence)
 	(accumulate (lambda (x y) (+ 1 y))
	 0 sequence))
(display (map0 square (list 1 2 3 4)))
(newline)
(display (append0 (list 1 2) (list 3 4)))
(newline)
(display (length0 (list 1 2 3 4)))
