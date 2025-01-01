-- Script to populate the conference management system
-- Dev Purandare for CSE 180 Fall '21

COPY Persons FROM stdin USING DELIMITERS ',';
991,Woods,Elle,ewoods@cula.edu,California University of Los Angeles,TRUE
993,Forrest,Emmett,eforre@cula.edu,California University of Los Angeles,TRUE
3396,Buonofuonte,Paulette,pbuono@ccsc.edu,City College of Santa Cruz,FALSE
2013,Huntington,Warner,hwarner@orange.com,Orange Law Corp.,FALSE
987,O\'Boyle,Kyle,kobo@ups.com,United Parcel Service,FALSE
1,Kensington,Vivienne,vkensi@harvard.edu,Harvard University,TRUE
\.

Copy Conferences FROM stdin USING DELIMITERS ',';
Harvard Law Review,2020,2020-07-21,220.99,110.00,2019-12-10,2020-03-21,H
Harvard Law Review,2021,2021-07-21,320.99,160.00,2020-12-10,2021-03-21,H
American Conference of Law,2020,2020-04-11,1100.50,110.00,2020-01-10,2020-02-21,H
Santa Cruz Law Review,2021,2021-08-15,150.00,00.00,2021-01-21,2021-06-30,L
\.

Copy Submissions FROM stdin USING DELIMITERS ',';
Harvard Law Review,2020,10,10,2019-12-09,TRUE,'Jury Bias Analysis: Modern approaches',2020-01-31,2020-03-21
Harvard Law Review,2020,11,10,2019-12-09,FALSE,'New directions in regulatory law',\N,\N
Harvard Law Review,2020,12,10,2019-12-10,FALSE,'Policy implications of Wall St. regulation',\N,\N
American Conference of Law,2020,55,16,2020-01-10,FALSE,'DNA reliability in crimnal law',\N,\N
American Conference of Law,2020,196,16,2020-01-10,TRUE,'Abrogation of Death Penalty and Redecivism',2020-01-28,2020-02-21
American Conference of Law,2020,51,16,2020-01-10,FALSE,'Class Action Lawsuit response analysis',\N,\N
Santa Cruz Law Review,2021,1,8,2021-01-20,TRUE,'Tailgating Decriminalization: 5 years later',2021-03-28,2021-06-30
Santa Cruz Law Review,2021,2,8,2021-01-20,TRUE,'A primer on local freight laws of the west coast',2021-03-28,2021-06-30
Santa Cruz Law Review,2021,3,7,2021-01-20,TRUE,'Ham radio rebellion: why well-intentioned laws fail',2021-03-28,2021-06-30
\.

Copy Authors FROM stdin USING DELIMITERS ',';
1,Harvard Law Review,2020,10,1
2013,Harvard Law Review,2020,10,2
991,American Conference of Law,2020,196,1
993,American Conference of Law,2020,196,2
1,American Conference of Law,2020,51,1
2013,American Conference of Law,2020,51,2
3396,Santa Cruz Law Review,2021,2,1
987,Santa Cruz Law Review,2021,2,2
1,Santa Cruz Law Review,2021,2,3
\.

Copy Reviewers FROM stdin USING DELIMITERS ',';
2013,Santa Cruz Law Review,2021,H
2013,Harvard Law Review,2020,H
987,American Conference of Law,2020,L
3396,American Conference of Law,2020,H
\.

Copy Reviews FROM stdin USING DELIMITERS ',';
2013,Santa Cruz Law Review,2021,2,2021-06-30,5
2013,Santa Cruz Law Review,2021,1,2021-06-30,2
2013,Santa Cruz Law Review,2021,3,2021-06-30,0
987,American Conference of Law,2020,55,2020-02-20,0
987,American Conference of Law,2020,51,2020-02-20,1
987,American Conference of Law,2020,196,2020-02-20,2
2013,Harvard Law Review,2020,10,2020-03-17,3
2013,Harvard Law Review,2020,11,2020-03-17,3
2013,Harvard Law Review,2020,12,2020-03-17,0
3396,American Conference of Law,2020,55,2020-02-19,2
3396,American Conference of Law,2020,51,2020-02-19,2
3396,American Conference of Law,2020,196,2020-02-19,3
\.

Copy Attendees FROM stdin USING DELIMITERS ',';
991,Harvard Law Review,2020
991,Harvard Law Review,2021
2013,Harvard Law Review,2020
2013,Harvard Law Review,2021
993,Harvard Law Review,2020
3396,Harvard Law Review,2020
3396,Harvard Law Review,2021
1,Harvard Law Review,2020
1,Harvard Law Review,2021
991,American Conference of Law,2020
993,American Conference of Law,2020
1,American Conference of Law,2020
987,American Conference of Law,2020
3396,American Conference of Law,2020
2013,American Conference of Law,2020
3396,Santa Cruz Law Review,2021
987,Santa Cruz Law Review,2021
1,Santa Cruz Law Review,2021
2013,Santa Cruz Law Review,2021
\.
