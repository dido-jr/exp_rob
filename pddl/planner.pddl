(define (domain simple)
(:requirements :strips :typing :adl :fluents :durative-actions)

;; Types ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(:types
    robot
    waypoint
);; end Types ;;;;;;;;;;;;;;;;;;;;;;;;;

;; Predicates ;;;;;;;;;;;;;;;;;;;;;;;;;
(:predicates
    (robot_at ?r - robot ?p - waypoint) ; posizione attuale del robot
    (visited ?r - robot ?wp - waypoint) ; waypoint visitato dal robot
    (inspected ?r - robot ?wp - waypoint) ; waypoint ispezionato dal robot
    (is_lower ?wp - waypoint) ; il waypoint è più basso
    (reach_lower ?r - robot) ; il robot ha raggiunto il waypoint più basso
);; end Predicates ;;;;;;;;;;;;;;;;;;;;

;; Actions ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(:durative-action go_to_waypoint
    :parameters (?r - robot ?wp1 ?wp2 - waypoint)
    :duration (= ?duration 60)
    :condition (and
        (at start (robot_at ?r ?wp1))
        (at start (not (robot_at ?r ?wp2)))
        (at start (not (visited ?r ?wp2)))
    )
    :effect (and
        (at start (not (robot_at ?r ?wp1)))
        (at end (robot_at ?r ?wp2))
        (at end (visited ?r ?wp2))
    )
)

(:durative-action inspect
    :parameters (?r - robot ?wp - waypoint)
    :duration (= ?duration 1)
    :condition (and
        (at start (visited ?r ?wp))
        (over all (robot_at ?r ?wp))
        (at start (not (inspected ?r ?wp)))
    )
    :effect (and
        (at end (inspected ?r ?wp))
    )
)

(:durative-action find_lower
    :parameters (?r - robot ?wp - waypoint)
    :duration (= ?duration 60)
    :condition (and
        (at start (forall (?wp2 - waypoint) 
                        (or (not (inspected ?r ?wp2)) (is_lower ?wp2))))
    )
    :effect (and
        (at end (reach_lower ?r))
    )
)
)
