hasEnoughExperience(X) :- workExperience(X, WorkExp), WorkExp >= 2.

hasMinimumCGPA(Person) :- studentCGPA(Person, CGPA), CGPA >= 8.5.

isPlaced(X) :- (passCodingTest(X), hasMinimumCGPA(X), passInterview(X));(appliedExternally(X), passInterview(X), hasEnoughExperience(X)).

passCodingTest(prathamesh).
studentCGPA(prathamesh,9.7).
passInterview(prathamesh).

passCodingTest(jay).
studentCGPA(jay,8.4).
passInterview(jay).

appliedExternally(satish).
passInterview(satish).
workExperience(satish,2).

appliedExternally(pranav).
passInterview(pranav).
workExperience(pranav,1).

printResult(X) :-
    isPlaced(X),
    write(X),
