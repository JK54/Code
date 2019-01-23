(define (repeated f n)
  (if (= n 1)
	f
	(lambda (x)
	  (let ((fs (repeated f (- n 1))))
		(f (fs x))))))
