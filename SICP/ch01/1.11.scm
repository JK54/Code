(define (f_recursive n)
 	(cond ((< n 3) n)
	(else (+ (f_recursive (- n 1)) (* 2 (f_recursive (- n 2))) (* 3 (f_recursive (- n 3)))))))

(define (f_iterative i0 i1 i2 count n)
 	(cond ((= n 0) i0)
	 	  ((= n 1) i1)
		  ((= n 2) i2)
		  ((= count n) (+ i2 (* 2 i1) (* 3 i0)))
		  ((< count n) (f_iterative i1 i2 (+ i2 (* 2 i1) (* 3 i0)) (+ count 1) n))))

(define (f0 n) (f_recursive n))
(define (f1 n) (f_iterative 0 1 2 3 n))
