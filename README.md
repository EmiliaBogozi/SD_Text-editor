# SD_Text-editor

	Tema a constat in crearea unei liste dublu inlantuite in care este introdus textul si, prin intrarea in linia de comanda, in citirea comenzilor. La intalnirea textului "::i", se trece de la introducere de text la introducere de comenzi si invers. Textul este introdus de la tastatura pana la intalnirea comenzii "q", moment in care iese din citire. Am folosit switch pentru comenzi.
  
	Functia Save consta in deschiderea unui fisier si salvarea continutului listei in interiorul acestuia, reprezentand outputul programului. Functia save este apelata la intalnirea comenzii "s" sau la intalnirea a 5 comenzi diferite de "s"; am folosit un contor "salveaza" pentru a numara comenzile care sunt date, iar la final, daca acesta este egal cu 5, se apeleaza functia de save, iar contorul "salveaza" se initializeaza cu 0.
  
	Functia Backspace, in cazul in care lista nu este goala, elimina elementul aflat inaintea cursorului.
  
	Functia Delete_line, in cazul in care nu primeste niciun parametru, sterge linia curenta(la care se afla cursorul), iar daca primeste parametru, sterge linia trimisa prin acesta.
  
	Functia Delete, in cazul in care primeste un parametru, sterge numarul de caractere trimis ca parametru pozitionate dupa cursor; in cazul in care nu primeste parametru, functia sterge un singur caracter pozitionat imediat dupa cursor.
  
	Functia Goto_line consta in parcurgerea listei pana la linia trimisa ca parametru acesteia; cursorul este pozitionat la finalul acesteia.
  
	Functia Goto_char consta in parcurgerea listei pana la caracterul trimis ca parametru de aceasta, daca este trimisa si linia ca parametru, functia pozitioneaza cursorul la linia si caracterul indicate de aceasta; in cazul in care linia nu este trimisa ca parametru, functia pozitioneaza cursorul la caracterul trimis ca parametru de pe linia curenta.
  
	Functia Undo consta in crearea a 2 stive, una pentru comenzi, iar alta pentru text. In stiva pentru comenzi sunt stocate instructiunile si pozitia cursorului unde s-a realizat modificarea. In stiva pentru text este salvat caracter cu caracter tot textul care a fost editat.
