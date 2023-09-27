;; this is how to load external modules in scheme
(load-from-path "/escnfs/home/wbagley/esc-courses/fa23-cse-30332.01/public/scheme/d1/paradigms_d1.scm")
(use-modules (ice-9 paradigms_d1))

;; Walker Bagley

;; the list q
;; notice it has a ' in front of the list; that tells the interpreter to read
;; the list literally (e.g., as atoms, instead of functions)
(define q '(turkey (gravy) (stuffing potatoes ham) peas))

;; question 1
(display "question 1: ")
(display (atom? (car (cdr (cdr q)))))
(display "\n")
;; output:
;; (copy the output you saw here)
;; question 1: #f
;;
;; explanation:
;; (use as many lines as necessary, just add more comments)
;; (atom? (car (cdr (cdr (turkey (gravy) (stuffing potatoes ham) peas)))))
;; (atom? (car (cdr ((gravy) (stuffing potatoes ham) peas))))
;; (atom? (car ((stuffing potatoes ham) peas)))
;; (atom? (stuffing potatoes ham))
;; the list (stuffing potatoes ham) is not in fact atomic so this evaluates to false
;; #f


;; question 2
(display "question 2: ")
(display (lat? (car (cdr (cdr q)))))
(display "\n")
;; output:
;; question 2: #t
;;
;; explanation:
;; (lat? (car (cdr (cdr (turkey (gravy) (stuffing potatoes ham) peas)))))
;; (lat? (car (cdr ((gravy) (stuffing potatoes ham) peas))))
;; (lat? (car ((stuffing potatoes ham) peas)))
;; (lat? (stuffing potatoes ham))
;; all elements of the list (stuffing potatoes ham) are atomic, so this evaluates to true
;; #t

;; question 3
(display "question 3: ")
(display (cond ((atom? (car q)) (car q)) (else '())))
(display "\n")
;; output:
;; question 3: turkey
;;
;; explanation:
;; (cond ((atom? (car q)) (car q)) (else '()))
;; (cond ((atom? turkey) turkey) (else '()))
;; turkey is in fact atomic so we meet the conditional and follow the appropriate output
;; (cond (#t turkey) (else '()))
;; turkey
