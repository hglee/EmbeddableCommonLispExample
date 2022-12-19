;; graph related
(defun g-name (exp)
  ;; replace non alpha-numeric characters
  (substitute-if #\_ (complement #'alphanumericp) (prin1-to-string exp)))

(defparameter *max-label-length* 30)

(defun g-label (exp)
  (if exp
      (let ((s (write-to-string exp :pretty nil)))
        ;; limit string length
        (if (> (length s) *max-label-length*)
            (concatenate 'string (subseq s 0 (- *max-label-length* 3)) "...")
            s))))

(defun draw-nodes (fn nodes)
  (mapc (lambda (node)
          (funcall fn (g-name (car node)) (g-label node)))
        nodes))

(defun draw-edges (fn edges)
  (maplist (lambda (lst)
             (mapc (lambda (edge)
                     (unless (assoc (car edge) (cdr lst))
                       (funcall fn (g-name (caar lst)) (g-name (car edge)) (g-label (cdr edge)))
                       ))
                   (cdar lst)))
           edges))

(defparameter *congestion-city-nodes* nil)
(defparameter *congestion-city-edges* nil)
(defparameter *visited-nodes* nil)
(defparameter *node-num* 30)
(defparameter *edge-num* 45)
(defparameter *worm-num* 3)
(defparameter *cop-odds* 15)

(defun random-node ()
  (1+ (random *node-num*)))

(defun edge-pair (a b)
  (unless (eql a b)
    (list (cons a b) (cons b a))))

(defun make-edge-list ()
  "make selected edge-pair by repeating *edge-num*"
  (apply #'append (loop repeat *edge-num*
                     collect (edge-pair (random-node) (random-node)))))

(loop repeat 10 collect 1)
(loop for n from 1 to 10 collect n)

(defun direct-edges (node edge-list)
  "remove item that start with node from edge-list"
  (remove-if-not (lambda (x)
                   (eql (car x) node))
                 edge-list))


(defun get-connected (node edge-list)
  "find connected nodes start from node"
  (let ((visited nil))
    (labels ((traverse (node)
               (unless (member node visited)
                 (push node visited)
                 (mapc (lambda (edge)
                         (traverse (cdr edge)))
                       (direct-edges node edge-list)))))
      (traverse node))
    visited))

;; 1. 첫번째 노드와 연결된 노드를 모두 구함
;; 2. 입력 노드에서 1의 연결된 노드를 제거 : 고립된 섬
;; 3. 2가 있다면 2를 기준으로 다시 고립된 섬 구함
(defun find-islands (nodes edge-list)
  (let ((islands nil))
    (labels ((find-island (nodes)
               (let* ((connected (get-connected (car nodes) edge-list))
                      ;; nodes - connected
                      (unconnected (set-difference nodes connected)))
                 (push connected islands)
                 (when unconnected
                   (find-island unconnected)))))
      (find-island nodes))
    islands))

(defun connect-with-bridges (islands)
  "connects additional nodes from islands"
  (when (cdr islands)
    (append (edge-pair (caar islands) (caadr islands))
            (connect-with-bridges (cdr islands)))))

(defun connect-all-islands (nodes edge-list)
  "connects all isolated nodes"
  (append (connect-with-bridges (find-islands nodes edge-list)) edge-list))

(defun make-city-edges ()
  "make whole city edge"
  ;; 1. make edge
  ;; 2. connect isolated edge
  ;; 3. generate random cop positions
  ;; 4. place cop on edge
  (let* ((nodes (loop for i from 1 to *node-num*
                      collect i))
         (edge-list (connect-all-islands nodes (make-edge-list)))
         (cops (remove-if-not (lambda (x)
                                (zerop (random *cop-odds*)))
                              edge-list)))
    (add-cops (edges-to-alist edge-list) cops)))

(defun edges-to-alist (edge-list)
  "convert edge list to alist"
  ;; e.g. ((1 . 2) (2 . 1) (2 . 3) (3 . 2)) => ((1 (2)) (2 (1) (3)) (3 (2)))
  (mapcar (lambda (node1)
            (cons node1
                  (mapcar (lambda (edge)
                            (list (cdr edge)))
                          (remove-duplicates (direct-edges node1 edge-list)
                                             :test #'equal))))
          ;; get first node to remote duplicate
          (remove-duplicates (mapcar #'car edge-list))))

(defun add-cops (edge-alist edges-with-cops)
  "add cop symbol by nested alist"
  ;; e.g. ((1 (2)) (2 (1) (3)) (3 (2)))  =>  ((1 (2)) (2 (1) (3 COPS)) (3 (2 COPS)))
  (mapcar (lambda (x)
            (let ((node1 (car x))
                  (node1-edges (cdr x)))
              (cons node1
                    (mapcar (lambda (edge)
                              (let ((node2 (car edge)))
                                ;; add cops symbol to for intersection with edges-with-cops
                                (if (intersection (edge-pair node1 node2)
                                                  edges-with-cops
                                                  :test #'equal)
                                    (list node2 'cops)
                                  edge)))
                            node1-edges))))
          edge-alist))

(defun neighbors (node edge-alist)
  "find node that connected to node directly"
  (mapcar #'car (cdr (assoc node edge-alist))))

(defun within-one (a b edge-alist)
  "check node is in distance 1"
  (member b (neighbors a edge-alist)))

(defun within-two (a b edge-alist)
  "check node is in distance 2"
  ;; 1. node in distance 1
  ;; 2. neighbor nodes in distance 1
  (or (within-one a b edge-alist)
      (some (lambda (x)
              (within-one x b edge-alist))
            (neighbors a edge-alist))))

(defun make-city-nodes (edge-alist)
  "make final city map"
  ;; generate wumpus by random and glow-worm by random to worm count
  (let ((wumpus (random-node))
        (glow-worms (loop for i below *worm-num*
                          collect (random-node))))
    ;; place hint around wumpus, glow-worms
    (loop for n from 1 to *node-num*
          collect (append (list n)
                          (cond ((eql n wumpus) '(wumpus))
                                ((within-two n wumpus edge-alist) '(blood!)))
                          (cond ((member n glow-worms)
                                 '(glow-worm))
                                ((some (lambda (worm)
                                         (within-one n worm edge-alist))
                                       glow-worms)
                                 '(lights!)))
                          ;; value on cdr means cop
                          (when (some #'cdr (cdr (assoc n edge-alist)))
                            '(sirens!))))))

(defun new-game()
  (setf *congestion-city-edges* (make-city-edges))
  (setf *congestion-city-nodes* (make-city-nodes *congestion-city-edges*))
  (setf *player-pos* (find-empty-node))
  (setf *visited-nodes* (list *player-pos*))
  (draw-city)
  (draw-known-city)
  (SetStatus "Started"))

(defun find-empty-node ()
  "find empty node by choosing random node"
  (let ((x (random-node)))
    (if (cdr (assoc x *congestion-city-nodes*))
        (find-empty-node)
      x)))

(defun draw-city ()
  (draw-nodes #'AddNodeToAllCity *congestion-city-nodes*)
  (draw-edges #'AddEdgeToAllCity *congestion-city-edges*))

(defun known-city-nodes ()
  (mapcar (lambda (node)
            ;; marks visited. current: *, not visited: ?
            (if (member node *visited-nodes*)
                (let ((n (assoc node *congestion-city-edges*)))
                  (if (eql node *player-pos*)
                      (append n '(*))
                    n))
              (list node '?)))
          ;; remove visited and neighbors of visited
          (remove-duplicates
           (append *visited-nodes*
                   (mapcan (lambda (node)
                             (mapcar #'car
                                     (cdr (assoc node *congestion-city-edges*))))
                           *visited-nodes*)))))

(defun known-city-edges ()
  (mapcar (lambda (node)
            (cons node (mapcar (lambda (x)
                                 (if (member (car x) *visited-nodes*)
                                             x
                                   (list (car x))))
                               (cdr (assoc node *congestion-city-edges*)))))
          *visited-nodes*))

(defun draw-known-city ()
  (draw-nodes #'AddNodeToKnownCity (known-city-nodes))
  (draw-edges #'AddEdgeToKnownCity (known-city-edges)))

(defun walk (pos)
  (handle-direction pos nil))

(defun charge (pos)
  (handle-direction pos t))

(defun handle-direction (pos charging)
  (let ((edge (assoc pos
                     (cdr (assoc *player-pos* *congestion-city-edges*)))))
    (if edge
        (handle-new-place edge pos charging)
        (progn (SetStatus "That location does not exist!")
               (draw-known-city)))))

(defun handle-new-place (edge pos charging)
  (let* ((node (assoc pos *congestion-city-edges*))
         (has-worm (and (member 'glow-worm node)
                        (not (member pos *visited-nodes*)))))
    (pushnew pos *visited-nodes*)
    (setf *player-pos* pos)
    (draw-known-city)
    (cond ((member 'cops edge) (SetStatus "You ran into the cops. Game Over."))
          ((member 'wumpus node) (if charging
                                     (SetStatus "You found the Wumpus!")
                                   (SetStatus "You ran into the Wumpus")))
          (charging (SetStatus "You wasted your last bullet. Game Over."))
          (has-worm (let ((new-pos (random-node)))
                      (SetStatus (format nil "You ran into Glow Worm Gang! You're now at ~a" new-pos))
                      (handle-new-place nil new-pos nil))))))

(SetStatus "Loaded")
