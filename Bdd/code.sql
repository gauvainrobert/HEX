drop table Partie;
drop table Joueur;

create table Joueur
	(	
		idJoueur number;
		pseudo varchar2(100),
	  	email varchar2(100),
	  	dateDeNaissance date,

	  	constraint pk_idJoueur primary key (idJoueur),
	  	constraint ck_pseudo check (pseudo is not null),
	  	constraint ck_email check (email is not null),
	  	constraint ck_dateDeNaissance check (deDeNaissance is not null)
);

create table Partie
	(	idPartie number,
		dateP date,
		idJoueur1 varchar(100),
		idJoueur2 varchar(100),
		gagnant varchar2(3),
		premierCoup varchar2(5),
		

		constraint pk_idPartie primary key (noP),
		constraint fk_idJoueur1 foreign key (idJoueur1) references Joueur(idJoueur) on delete cascade,
		constraint fk_idJoueur2 foreign key (idJoueur2) references Joueur(idJoueur) on delete cascade,
		constraint ck_dateP check (dateP is not null),
		constraint ck_premierCoup_non_null check (premierCoup is not null),
		constraint ck_gagnant check (gagnant="oui" or gagnant="non"),
		constraint ck_premierCoup check (premierCoup='*' or premierCoup='o')
);


insert into Joueur values (0,'Antoine','antoine@hotmail.fr','05-01-1990');
insert into Joueur values (1,'Gauvain','gauvain@gmail.com','25-12-1998');
insert into Joueur values (2,'Fabien','fabien@noob.fr','11/11/2011');

insert into Partie values (0,'01/05/2017',0,1,'oui','blanc');
insert into Partie values (1,'02/05/2017',0,2,'non','noir');
insert into Partie values (2,'01/05/2017',1,2,'oui','blanc');
insert into Partie values (3,'04/05/2017',1,0,'oui','noir');


select *
from Joueur J, Partie P
where (P.idJoueur = J.idJoueur1 or P.idJoueur = J.idJoueur2)


select *
from Joueur J, Partie P
where (P.idJoueur = J.idJoueur1 or P.idJoueur = J.idJoueur2) and P.dateP='01/05/2017'

select *
from Joueur J, Partie P
where (P.idJoueur = J.idJoueur1 or P.idJoueur = J.idJoueur2) and P.gagnant='oui'


select *
from Joueur J, Partie P
where (P.idJoueur = J.idJoueur1 or P.idJoueur = J.idJoueur2) and P.gagnant='non'


select * from Partie P
where P.premierCoup='noir';

