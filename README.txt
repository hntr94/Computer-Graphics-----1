Vinatoru Andrei-Ioan - 335CB

=========================================================

Utilizare Aplicatie:
	Mouse: in functie de mouse, jucatorul se roteste
		apasand MOUSE1 (click) acesta va genera proiectile in directia orientarii
	Tastatura: tastele W, A, S, D pentru miscarea jucatorului
	Scopul este de a elimina cat mai multi inamici cu proiectilele generate.


In principiu, pentru fiecare obiect care apare pe ecran am devoltat cate o clasa: pentru Player, Inamici,
Vieti, Gloante, Gifts. Cele mai multe actiuni se pentrc in Update, unde se realizeaza operatiile geometrice.

In OnMousePress generez gloantele si le pun in vector. Am adaugat aici si posibilitatea de a genera 5 gloante
o data, cand se ridica un anumit cadou.
In MouseMove iau unghiul pentru player.
In Update randez toate obiectele generate si efectuez toate calculele si animatiile necesare. Acestea includ:
 - calculul coliziunilor
 - stergerea obiectelor inutile (gloante iesite in afara, inamici distrusi)
 - comportament al diversilor inamici
 - miscarea obiectelor (gloante, inamici)
 - implementare vieti (vietile scad cand este atins jucatorul de inamici; la 0 se termina jocul)
Vietile au fost facute dreptunghiuri, ca in cerinte, doar ca le-am dat si o anumita rotatie.


Implementare: am implementat tot ce era in baseline + urmatoarele bonusuri:
	obiecte cadou care apar random pe harta
	inamici care se divizeaza

Inamici: Obiecte care trebuie distruse
	- inamicul albastru - inamic simplu, cu o viata
	- inamicul galben - inamic mare care cand e impuscat devine mai mic, isi schimba culoare in rosu
		si devine mai rapid
	- inamicul gri - inamic care atunci cand e impuscat se separa in doi mai mici (turcoaz) care 
			au viteza ceva mai mica

	Acestia apar la inceput la un interval de 2 secunde care se micsoreaza treptat pana la 0.5 secunde

Cadouri: obiecte aditionale ce apar o data la 10 secunde
	- obiectele albe te fac invulnerabil timp de 5 secunde, poti distruge inamicii doar atingandu-te de ei
		i se schimba si culoarea playerului in alb
	- obiectele albastre iti dau posibilitatea sa tragi cu gloante in 5 directii 
	- obiectele roz iti dau o viata in plus

