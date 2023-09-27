(define-module (ice-9 paradigms_ttt))

(define-public pick
  (lambda (n lat)
    (cond
      ((zero? (- n 1)) (car lat))
      (else (pick (- n 1) (cdr lat))))))

;; does player 'p' win this game state?
;; p = x or o
;; e.g., (x x x o o e e e e) is a win for x
(define-public win?
  (lambda (p gs)
    (cond
      ((or (eq? (pick 1 gs) (pick 4 gs) (pick 7 gs) p)
           (eq? (pick 2 gs) (pick 5 gs) (pick 8 gs) p)
           (eq? (pick 3 gs) (pick 6 gs) (pick 9 gs) p)
           (eq? (pick 1 gs) (pick 2 gs) (pick 3 gs) p)
           (eq? (pick 4 gs) (pick 5 gs) (pick 6 gs) p)
           (eq? (pick 7 gs) (pick 8 gs) (pick 9 gs) p)
           (eq? (pick 1 gs) (pick 5 gs) (pick 9 gs) p)
           (eq? (pick 3 gs) (pick 5 gs) (pick 7 gs) p) ) #t)
       (else #f) )))

;; return the other player (e.g., given 'x', return 'o')
(define-public other
  (lambda (p)
    (cond
      ((eq? p 'o) 'x)
      (else 'o))))

(define-public firsts
  (lambda (l)
    (cond
      ((null? l) (list))
      (else (cons (car (car l)) (firsts (cdr l)))))))

;; entire game tree for setup we discussed in class... :-)
;; be glad I didn't make you write this
(define-public onegametree (lambda () (list (list 'x 'o 'x 'o 'o 'e 'e 'x 'e)
			  ;; node 1, child of root
			  (list (list 'x 'o 'x 'o 'o 'x 'e 'x 'e)
				    ;; node 4, child of node 1
				    (list (list 'x 'o 'x 'o 'o 'x 'o 'x 'e)
					      ;; node 10, child of node 4
					      (list (list 'x 'o 'x 'o 'o 'x 'o 'x 'x)
					      ) ;; end of node 10
				    ) ;; end of node 4
                                    (list (list 'x 'o 'x 'o 'o 'x 'e 'x 'o)
                                              (list (list 'x 'o 'x 'o 'o 'x 'x 'x 'o)
					      ) ;; end of node 11
				    ) ;; end of node 5
			  ) ;; end of node 1

			  ;; node 2, child of root
			  (list (list 'x 'o 'x 'o 'o 'e 'x 'x 'e)
                                    ;; node 6, child of node 2
                                    (list (list 'x 'o 'x 'o 'o 'o 'x 'x 'e)
				    ) ;; end of node 6
                                    ;; node 7, child of node 2
                                    (list (list 'x 'o 'x 'o 'o 'e 'x 'x 'o)
                                              ;; node 12, child of node 7
                                              (list (list 'x 'o 'x 'o 'o 'x 'x 'x 'o)
					      ) ;; end of node 12
				    ) ;; end of node 7
			  ) ;; end of node 2

			  ;; node 3, child of root
			  (list (list 'x 'o 'x 'o 'o 'e 'e 'x 'x)
                                    ;; node 8, child of node 3
                                    (list (list 'x 'o 'x 'o 'o 'o 'e 'x 'x)
				    ) ;; end of node 8
                                    ;; node 9, child of node 3
                                    (list (list 'x 'o 'x 'o 'o 'e 'o 'x 'x)
                                              ;; node 10, child of node 4
                                              (list (list 'x 'o 'x 'o 'o 'x 'o 'x 'x)
					      ) ;; end of node 10
                                    ) ;; end of node 9
			  ) ;; end of node 3
		    ) ;; end list of children of root
		)
)

