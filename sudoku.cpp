#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <cmath>

using namespace std;

char niveauJeu();
int level=0;
int correct=0;
int sudokuPointer=0;
int sudokuTaille;
int sudokuNumero;
double progres_final=0;
string etatSudoku;
string sudokuPuzzle[81];
string sudokuHighlights[81];
string sudokuSolution[81];

void jouerSudoku();
void quitterMenu();
void verifierJeu();
void flecheUp();
void flecheDown();
void flecheGauche();
void flecheDroite();
void pauseJeu();
void helpSudoku(string located);
void setPuzzle(int level);
void creerPuzzle(string target, string puzzle);
void setNumeroCle(string value);
void afficherProgresModeDiff(double progres_final);
void cacherCurseur(bool condition);
void allerMenu(char choix);
void colorSet(int tint);
void gamePart(string part);
void jeuMain();

int main()
{
	cacherCurseur(true);
	
	SetConsoleTitle(("Sudoku"));
	
	int choix;
	
	while(true){
		
		system("cls");
		colorSet(14);
		gamePart("ligne_gauche");
		colorSet(8);
		cout<<"SUDOKU";
		colorSet(14);
		gamePart("ligne_droite");
		colorSet(15);
		cout<<"[1] ";
		colorSet(15);
		cout<<"DEBUT"<<endl;
		colorSet(15);
		cout<<"[2] ";
		colorSet(15);
		cout<<"INSTRUCTIONS"<<endl;
		colorSet(15);
		cout<<"[3] ";
		colorSet(15);
		cout<<"QUITTER"<<endl;
		colorSet(14);
		gamePart("separateur");
		colorSet(7);
	  	cout<<"(Choisir un numero!)";
	  	colorSet(8);
	  	
	  	char select = getch();
	  	if(!(select<'1'||select>'3')){
	  		choix=select;
	  		break;
		  }

	}
	allerMenu(choix);
}

void allerMenu(char choix){
	if(choix == '1'){
		jouerSudoku();
	}
	else if(choix == '2'){
		helpSudoku("main");
	}
	else if(choix=='3'){
		quitterMenu();
	}
}

void jouerSudoku(){
	
	char setLevel=niveauJeu();
	
	if(setLevel=='4'){
		main();
	}
	else{
		level = (int)setLevel-48;
		setPuzzle(level);
		etatSudoku="playing";
		sudokuPointer=0;
		verifierJeu();
		jeuMain();
	}
	
	getch();
	
	main();
}

char niveauJeu(){
	
	char choix;
	
	do{
		system("cls");
		colorSet(4);
		gamePart("ligne_gauche");
		colorSet(8);
		cout<<"SUDOKU";
		colorSet(4);
		gamePart("ligne_droite");
		colorSet(8);
		cout<<setw(29)<<right<<"CHOISIR UNE DIFFICULTE"<<endl;
		colorSet(4);
		gamePart("separateur");
		colorSet(15);
		cout<<"[1] ";
		colorSet(10);
		cout<<"FACILE"<<endl;
		colorSet(15);
		cout<<"[2] ";
		colorSet(14);
		cout<<"MOYEN"<<endl;
		colorSet(15);
		cout<<"[3] ";
		colorSet(12);
		cout<<"DIFFICILE"<<endl;
		colorSet(4);
		gamePart("separateur");
		colorSet(15);
		cout<<"[4] ";
		colorSet(15);
		cout<<"RETOUR"<<endl;
		colorSet(4);
		gamePart("separateur");
		colorSet(7);
		cout<<"(Choisir un numero!)";
		colorSet(15);
		
		char select = getch();
	  	if(!(select<'1'||select>'4')){
	  		choix=select;
	  		break;
		  }
	} while(true);
	
	return choix;
}

void afficherProgresModeDiff(double progres_final){
	if(progres_final >= 69){
		if(progres_final >= 84){
			if(progres_final >=94){
				cout<<"Encore un peu!";
			}
			else {
				cout<<"presque la!";
			}
		}
		else {
			cout<<"a moitie fini!";
		}
	} 
	else {
		cout<<"Incomplet";
	}
}

void setPuzzle(int level){
	
	string dot = ".";
	string puzzle,highlight,solution;
	
	if(level==1){
		puzzle = (" .7.8|3.1. | . . " + dot
				+ " .4. | .2.6|5. . " + dot
				+ "6. . |9.4.7|8. .1" + dot
				
				+ "2. . | . . | .4. " + dot
				+ "5. . |7. .1| . .2" + dot
				+ " .1. | . . | . .3" + dot
				
				+ "4. .5| . . | . .9" + dot
				+ " . .1|4.5. | .2. " + dot
				+ " . . | .9.2|4.7. " );
		
		highlight = ("0.F.F|F.F.0|0.0.0" + dot
				+ "0.F.0|0.F.F|F.0.0" + dot
				+ "F.0.0|F.F.F|F.0.F" + dot
				
				+ "F.0.0|0.0.0|0.F.0" + dot
				+ "F.0.0|F.0.F|0.0.F" + dot
				+ "0.F.0|0.0.0|0.0.F" + dot
				
				+ "F.0.F|0.0.0|0.0.F" + dot
				+ "0.0.F|F.F.0|0.F.0" + dot
				+ "0.0.0|0.F.F|F.F.0" );
				
		solution = ("9.7.8|3.1.5|2.6.4" + dot
				+ "1.4.3|8.2.6|5.9.7" + dot
				+ "6.5.2|9.4.7|8.3.1" + dot
				
				+ "2.3.7|5.8.9|1.4.6" + dot
				+ "5.6.4|7.3.1|9.8.2" + dot
				+ "8.1.9|2.6.4|7.5.3" + dot
				
				+ "4.2.5|6.7.8|3.1.9" + dot
				+ "7.9.1|4.5.3|6.2.8" + dot
				+ "3.8.6|1.9.2|4.7.5" );
	}
	
	else if(level==2){
		puzzle = (" .8.4|2. . | . .9" + dot
				+ "1. .2|8. . |5. . " + dot
				+ "9. . | .6. | . .3" + dot
				
				+ " .9. | . . |2.7. " + dot
				+ "5. . | . . | . .8" + dot
				+ " .4.8| . . | .3. " + dot
				
				+ "7. . | .2. | . .1" + dot
				+ " . .3| . .6|7. .4" + dot
				+ "4. . | . .5|3.9. " );
		
		highlight = ("0.F.F|F.0.0|0.0.F" + dot
				+ "F.0.F|F.0.0|F.0.0" + dot
				+ "F.0.0|0.F.0|0.0.F" + dot
				
				+ "0.F.0|0.0.0|F.F.0" + dot
				+ "F.0.0|0.0.0|0.0.F" + dot
				+ "0.F.F|0.0.0|0.F.0" + dot
				
				+ "F.0.0|0.F.0|0.0.F" + dot
				+ "0.0.F|0.0.F|F.0.F" + dot
				+ "F.0.0|0.0.F|F.F.0" );
				
		solution = ("3.8.4|2.5.7|1.6.9" + dot
				+ "1.6.2|8.3.9|5.4.7" + dot
				+ "9.7.5|1.6.4|8.2.3" + dot
				
				+ "6.9.1|3.4.8|2.7.5" + dot
				+ "5.3.7|6.9.2|4.1.8" + dot
				+ "2.4.8|5.7.1|9.3.6" + dot
				
				+ "7.5.9|4.2.3|6.8.1" + dot
				+ "8.2.3|9.1.6|7.5.4" + dot
				+ "4.1.6|7.8.5|3.9.2" );
	}
	
	else{
		puzzle = (" .8. |5.2. |6.4. " + dot
				+ "7. .6| . . | . .2" + dot
				+ "4.2. | . . | .3. " + dot
				
				+ " .5. | . .1| . . " + dot
				+ "6. . |7.8.3| . .9" + dot
				+ " . . |9. . | .6. " + dot
				
				+ " .3. | . . | .2.6" + dot
				+ "1. . | . . |3. .5" + dot
				+ " .9.2| .3.5| . . " );
		
		highlight = ("0.F.0|F.F.0|F.F.0" + dot
				+ "F.0.F|0.0.0|0.0.F" + dot
				+ "F.F.0|0.0.0|0.F.0" + dot
				
				+ "0.F.0|0.0.F|0.0.0" + dot
				+ "F.0.0|F.F.F|0.0.F" + dot
				+ "0.0.0|F.0.0|0.F.0" + dot
				
				+ "0.F.0|0.0.0|0.F.F" + dot
				+ "F.0.0|0.0.0|F.0.F" + dot
				+ "0.F.F|0.F.F|0.0.0" );
				
		solution = ("9.8.3|5.2.7|6.4.1" + dot
				+ "7.1.6|3.4.8|5.9.2" + dot
				+ "4.2.5|1.9.6|7.3.8" + dot
				
				+ "2.5.9|4.6.1|8.7.3" + dot
				+ "6.4.1|7.8.3|2.5.9" + dot
				+ "3.7.8|9.5.2|1.6.4" + dot
				
				+ "5.3.7|8.1.4|9.2.6" + dot
				+ "1.6.4|2.7.9|3.8.5" + dot
				+ "8.9.2|6.3.5|4.1.7" );
	}
	
	creerPuzzle("puzzle_layout",puzzle);
	creerPuzzle("highlight_layout",highlight);
	creerPuzzle("solution_layout",solution);
	
}

void creerPuzzle(string target, string puzzle){
    
    char cpuzzle[puzzle.length()];
    int i;
    int pointer = 0;
    for (i = 0; i < sizeof(cpuzzle); i++) {
        cpuzzle[i] = puzzle[i];
        if(!(cpuzzle[i] == '.'||cpuzzle[i] == '|')){
        	
        	string sudokuNumber(1, cpuzzle[i]);
        	if(target == "puzzle_layout"){
        		sudokuPuzzle[pointer] = sudokuNumber;	
			}
			else if(target == "highlight_layout"){
				sudokuHighlights[pointer] = sudokuNumber;
			}
			else if(target == "solution_layout"){
				sudokuSolution[pointer] = sudokuNumber;
			}
        	pointer++;
		}
		
    }
    cout<<endl<<endl;
    
}

void jeuMain(){
	
	system("cls");
	colorSet(4);
	gamePart("ligne_gauche");
	colorSet(15);
	cout<<"SUDOKU";
	colorSet(4);
	gamePart("ligne_droite");
	
	switch(level){
		case 1:
			colorSet(10);
			cout<<setw(24)<<right<<"NIVEAU FACILE"<<endl;
			break;
		case 2:
			colorSet(14);
			cout<<setw(25)<<right<<"NIVEAU MOYEN"<<endl;
			break;
		default:
			colorSet(12);
			cout<<setw(24)<<right<<"NIVEAU DIFFICILE"<<endl;
	}
	
	colorSet(4);
	gamePart("separateur");
	cout<<endl;
	
	
	int colorTable=8;
	
	
	sudokuTaille = (sizeof(sudokuPuzzle)/sizeof(sudokuPuzzle[0]));
	if(etatSudoku == "quitted"){
		for(int checker = 0; checker < sudokuTaille; checker++){
			sudokuPuzzle[checker] = sudokuSolution[checker];
		}
	}
		sudokuNumero = 0;
		for(int tpart = 1;tpart <= 182;tpart++){
			
			if(tpart == 1 || tpart == 62 || tpart == 122 || tpart == 182){
				colorSet(colorTable);
				gamePart("sudoku_outer_border");
			}
			else if(tpart ==   2 || tpart ==   8 || tpart ==  14 || tpart ==  22 || tpart ==  28 || tpart ==  34 ||
					tpart ==  42 || tpart ==  49 || tpart ==  55 || tpart ==  63 || tpart ==  69 || tpart ==  75 ||
					tpart ==  83 || tpart ==  89 || tpart ==  95 || tpart == 103 || tpart == 109 || tpart == 115 ||
					tpart == 123 || tpart == 129 || tpart == 135 || tpart == 143 || tpart == 149 || tpart == 155 ||
					tpart == 163 || tpart == 169 || tpart == 175){
				colorSet(colorTable);
				gamePart("sudoku_outer_vertical_border_small");
			}
			else if(tpart ==  20 || tpart ==  40 || tpart ==  61 || tpart == 81 || tpart == 101 || tpart == 121 ||
					tpart == 141 || tpart == 161 || tpart == 181){
				colorSet(colorTable);
				gamePart("sudoku_outer_vertical_border_next_line");
			}
			else if(tpart ==   3 || tpart ==   5 || tpart ==   7 || tpart ==   9 || tpart ==  11 || tpart ==  13 ||
					tpart ==  15 || tpart ==  17 || tpart ==  19 || tpart ==  23 || tpart ==  25 || tpart ==  27 ||
					tpart ==  29 || tpart ==  31 || tpart ==  33 || tpart ==  35 || tpart ==  37 || tpart ==  39 ||
					tpart ==  43 || tpart ==  45 || tpart ==  47 || tpart ==  50 || tpart ==  52 || tpart ==  54 ||
					tpart ==  56 || tpart ==  58 || tpart ==  60 || tpart ==  64 || tpart ==  66 || tpart ==  68 ||
					tpart ==  70 || tpart ==  72 || tpart ==  74 || tpart ==  76 || tpart ==  78 || tpart ==  80 ||
					tpart ==  84 || tpart ==  86 || tpart ==  88 || tpart ==  90 || tpart ==  92 || tpart ==  94 ||
					tpart ==  96 || tpart ==  98 || tpart == 100 || tpart == 104 || tpart == 106 || tpart == 108 ||
					tpart == 110 || tpart == 112 || tpart == 114 || tpart == 116 || tpart == 118 || tpart == 120 ||
					tpart == 124 || tpart == 126 || tpart == 128 || tpart == 130 || tpart == 132 || tpart == 134 ||
					tpart == 136 || tpart == 138 || tpart == 140 || tpart == 144 || tpart == 146 || tpart == 148 ||
					tpart == 150 || tpart == 152 || tpart == 154 || tpart == 156 || tpart == 158 || tpart == 160 ||
					tpart == 164 || tpart == 166 || tpart == 168 || tpart == 170 || tpart == 172 || tpart == 174 ||
					tpart == 176 || tpart == 178 || tpart == 180){
				
				colorSet(15);
				
				if(sudokuHighlights[sudokuNumero]=="0"){
					colorSet(15);
				}
				else if(sudokuHighlights[sudokuNumero]=="F"){
					colorSet(14);
				}
				 	
				if(etatSudoku == "quitted" || etatSudoku == "finished"){
					cout<<sudokuPuzzle[sudokuNumero];
				}
				else{
					
					if(sudokuNumero == sudokuPointer){
						colorSet(10);
						if(sudokuHighlights[sudokuPointer]=="F")
						 {
						 	colorSet(11);
							cout<<sudokuPuzzle[sudokuNumero];
						 }
						 else{
						 	
						 	if(sudokuPuzzle[sudokuNumero] ==  "1" || sudokuPuzzle[sudokuNumero] ==  "2" ||
							   sudokuPuzzle[sudokuNumero] ==  "2" || sudokuPuzzle[sudokuNumero] ==  "3" ||
							   sudokuPuzzle[sudokuNumero] ==  "4" || sudokuPuzzle[sudokuNumero] ==  "5" ||
							   sudokuPuzzle[sudokuNumero] ==  "6" || sudokuPuzzle[sudokuNumero] ==  "7" ||
							   sudokuPuzzle[sudokuNumero] ==  "8" || sudokuPuzzle[sudokuNumero] ==  "9"){
									cout<<sudokuPuzzle[sudokuNumero];
							}
							else{
									cout<<"x";	
							}
						 	
						 }
		
					}
					else{
						cout<<sudokuPuzzle[sudokuNumero];
					}
					
				}	
				sudokuNumero++;
				
			}
			else if(tpart ==   4 || tpart ==   6 || tpart ==  10 || tpart ==  12 || tpart ==  16 || tpart ==  18 ||
					tpart ==  24 || tpart ==  26 || tpart ==  30 || tpart ==  32 || tpart ==  36 || tpart ==  38 ||
					tpart ==  44 || tpart ==  46 || tpart ==  51 || tpart ==  53 || tpart ==  57 || tpart ==  59 ||
					tpart ==  65 || tpart ==  67 || tpart ==  71 || tpart ==  73 || tpart ==  77 || tpart ==  79 ||
					tpart ==  85 || tpart ==  87 || tpart ==  91 || tpart ==  93 || tpart ==  97 || tpart ==  99 ||
					tpart == 105 || tpart == 107 || tpart == 111 || tpart == 113 || tpart == 117 || tpart == 119 ||
					tpart == 125 || tpart == 127 || tpart == 131 || tpart == 133 || tpart == 137 || tpart == 139 ||
					tpart == 145 || tpart == 147 || tpart == 151 || tpart == 153 || tpart == 157 || tpart == 159 ||
					tpart == 165 || tpart == 167 || tpart == 171 || tpart == 173 || tpart == 177 || tpart == 179){
				colorSet(colorTable);
				gamePart("sudoku_inner_vertical_border_small");
			}
			else if(tpart == 21 || tpart == 41 || tpart == 82 || tpart == 102 || tpart == 142 || tpart == 162){
				colorSet(colorTable);
				gamePart("sudoku_inner_border");
			}
		}
		cout<<endl;
		
		progres_final = round(((double(correct)/81.0)*100.0));
		
		if(etatSudoku == "playing"){
			colorSet(11);
			cout<<" Progres: ";
			colorSet(15);
			
			switch(level){
				case 1:
					cout<<correct<<"/81";
					break;
				case 2:
					cout<<progres_final<<"%";
					break;
				default:
				 	afficherProgresModeDiff(progres_final);
					 	
			}
			
			cout<<endl;
			colorSet(14);
			cout<<" Appuyer";
			colorSet(12);
			cout<<" [Esc]";
			colorSet(15);
			cout<<" ou ";
			colorSet(12);
			cout<<"[P] ";
			colorSet(14);
			cout<<"pour mettre le jeu en pause. ";
		}
		else if(etatSudoku == "quitted"){
			colorSet(14);
			cout<<" Desole vous n'avez pas"<<endl
			 <<" fini le puzzle."<<endl;
			 colorSet(13);
			 cout<<"Plus de chance la prochaine fois!"<<endl;
			 colorSet(15);
			 cout<<"D'ailleurs, voici la solution"<<endl<<endl;
			 colorSet(7);
			 cout<<"[Appuyez sur n'importe quelle touche pour quitter]";
			 getch();
			 main();
		}
		else if(etatSudoku == "finished"){
			colorSet(10);
			 cout<<"Felicitations, vous avez"<<endl
			 << " fini le puzzle."<<endl;
			 colorSet(13);
			 cout<<"Vos competences en SUDOKU"<<endl
			 <<" sont impressionnates"<<endl<<endl;
			 colorSet(7);
			 cout<<"[Appuyez sur n'importe quelle touche pour quitter]";
			 getch();
			 main();
		}
		else {
			cout<<" Pointer: "<<sudokuPointer<<endl;
			cout<<" Highlight: "<<sudokuHighlights[sudokuPointer]<<endl;
		}
		
		while(true){
			int keyPress;
			colorSet(15);
			keyPress=0;
			keyPress=getch();
			
			if(keyPress == 0 || keyPress == 224){
				keyPress = 256 + getch();
				if(keyPress == 328){
					flecheUp();
					break;
				}
				else if(keyPress == 336){
					flecheDown();
					break;
				}
				else if(keyPress == 331){
					flecheGauche();
					break;
				}
				else if(keyPress == 333){
					flecheDroite();
					break;
				}
				else if(keyPress == 339){
					setNumeroCle("clear");
					break;
				}
			}
			else{
				
				if(keyPress == 122|| keyPress == 90){ 
					flecheUp();
					break;
				}
				else if(keyPress == 115 || keyPress == 83){ 
					flecheDown();
					break;
				}
				else if(keyPress == 113|| keyPress == 81){ 
					flecheGauche();
					break;
				}
				else if(keyPress == 100 || keyPress == 68){ 
					flecheDroite();
					break;
				}
				
				if(keyPress == 49){
					setNumeroCle("1");
					break;
				}
				else if(keyPress == 50){
					setNumeroCle("2");
					break;
				}
				else if(keyPress == 51){
					setNumeroCle("3");
					break;
				}
				else if(keyPress == 52){
					setNumeroCle("4");
					break;
				}
				else if(keyPress == 53){
					setNumeroCle("5");
					break;
				}
				else if(keyPress == 54){
					setNumeroCle("6");
					break;
				}
				else if(keyPress == 55){
					setNumeroCle("7");
					break;
				}
				else if(keyPress == 56){
					setNumeroCle("8");
					break;
				}
				else if(keyPress == 57){
					setNumeroCle("9");
					break;
				}
				else if(keyPress == 8){
					setNumeroCle("clear");
					break;
				}
				else if(keyPress == 27 || keyPress == 112 || keyPress == 80){
					pauseJeu();
					break;
				}
				else {
					continue;
				}
			}
		}
		
		verifierJeu();
}

void verifierJeu(){
	
	sudokuTaille = (sizeof(sudokuPuzzle) / sizeof(sudokuPuzzle[0]));
	
	correct = 0;
	for(int sudokuPointing = 0; sudokuPointing < sudokuTaille; sudokuPointing++){
		if(sudokuPuzzle[sudokuPointing] == sudokuSolution[sudokuPointing]){
			correct++;
		}
	}
	
	if(correct == sudokuTaille){
		etatSudoku = "finished";
	}
	
	jeuMain();
}

void flecheUp(){
	sudokuPointer = sudokuPointer - 9;
	
	if(sudokuPointer == -9){
		sudokuPointer = 72;
	}
	else if(sudokuPointer == -8){
		sudokuPointer = 73;
	}
	else if(sudokuPointer == -7){
		sudokuPointer = 74;
	}
	else if(sudokuPointer == -6){
		sudokuPointer = 75;
	}
	else if(sudokuPointer == -5){
		sudokuPointer = 76;
	}
	else if(sudokuPointer == -4){
		sudokuPointer = 77;
	}
	else if(sudokuPointer == -3){
		sudokuPointer = 78;
	}
	else if(sudokuPointer == -2){
		sudokuPointer = 79;
	}
	else if(sudokuPointer <= -1){
		sudokuPointer = 80;
	}
}

void flecheDown(){
	sudokuPointer = sudokuPointer + 9;
		if(sudokuPointer==81)
		 {
			sudokuPointer=0;
		 }
		else if(sudokuPointer==82)
		 {
			sudokuPointer=1;
		}
		else if(sudokuPointer==83)
		 {
			sudokuPointer=2;
		 }
		else if(sudokuPointer==84)
		 {
			sudokuPointer=3;
		 }
		else if(sudokuPointer==85)
		 {
			sudokuPointer=4;
		 }
		else if(sudokuPointer==86)
		 {
			sudokuPointer=5;
		 }
		else if(sudokuPointer==87)
		 {
			sudokuPointer=6;
		 }
		else if(sudokuPointer==88)
		 {
			sudokuPointer=7;
		 }
		else if(sudokuPointer==89)
		 {
			sudokuPointer=8;
		 }
}
void flecheGauche(){
	sudokuPointer = sudokuPointer - 1;
		if(sudokuPointer==62)
		 {
			sudokuPointer=71;
		 }
		else if(sudokuPointer==71)
		 {
			sudokuPointer=80;
		}
		else if(sudokuPointer==53)
		 {
			sudokuPointer=62;
		 }
		else if(sudokuPointer==44)
		 {
			sudokuPointer=53;
		 }
		else if(sudokuPointer==35)
		 {
			sudokuPointer=44;
		 }
		else if(sudokuPointer==26)
		 {
			sudokuPointer=35;
		 }
		else if(sudokuPointer==17)
		 {
			sudokuPointer=26;
		 }
		else if(sudokuPointer==8)
		 {
			sudokuPointer=17;
		 }
		else if(sudokuPointer==-1)
		 {
			sudokuPointer=8;
		 }
}
void flecheDroite(){
	sudokuPointer = sudokuPointer + 1;
		if(sudokuPointer==81)
		 {
			sudokuPointer=72;
		 }
		else if(sudokuPointer==72)
		 {
			sudokuPointer=63;
		 }
		else if(sudokuPointer==63)
		 {
			sudokuPointer=54;
		 }
		else if(sudokuPointer==54)
		 {
			sudokuPointer=45;
		 }
		else if(sudokuPointer==45)
		 {
			sudokuPointer=36;
		 }
		else if(sudokuPointer==36)
		 {
			sudokuPointer=27;
		 }
		else if(sudokuPointer==27)
		 {
			sudokuPointer=18;
		 }
		else if(sudokuPointer==18)
		 {
			sudokuPointer=9;
		 }
		else if(sudokuPointer==9)
		 {
			sudokuPointer=0;
		 }
}

void setNumeroCle(string value){

	if(!(value == "clear")){
		if(sudokuHighlights[sudokuPointer] == "0"){
		sudokuPuzzle[sudokuPointer] = value;
		}
	}
	else{
		if(sudokuHighlights[sudokuPointer] == "0"){
		sudokuPuzzle[sudokuPointer] = " ";
		}	
	}
}

void pauseJeu(){
	do{
		
		system("cls");
		colorSet(4);
		 gamePart("ligne_gauche");
		colorSet(8);
		cout<<"SUDOKU";
		colorSet(4);
		 gamePart("ligne_droite");
		colorSet(12);
		 cout<<setw(24)<<right<<"JEU EN PAUSE"<<endl;
		colorSet(4);
		 gamePart("separateur");
		colorSet(15);
		 cout<<"[1] ";
		colorSet(15);
		 cout<<"RESUME"<<endl;
		colorSet(15);
		 cout<<"[2] ";
		colorSet(15);
		 cout<<"INSTRUCTIONS"<<endl;
		colorSet(15);
		 cout<<"[3] ";
		colorSet(15);
		 cout<<"QUITTER"<<endl;
		colorSet(4);
		 gamePart("separateur");
		colorSet(7);
		 cout<<"(Choisir un numero!) ";
		colorSet(15);
		
		char select = getch();
		if(!(select<'1'||select>'3')){
			cout<<endl;
			if(select == '2'){
				helpSudoku("in-game");
			}
			else if(select == '3'){
				etatSudoku = "quitted";
				break;
			}
			else{
				break;
			}
		}
		 
		}while(true);
}

void helpSudoku(string located){
	system("cls");
		colorSet(4);
		 gamePart("ligne_gauche");
		colorSet(15);
		 cout<<"SUDOKU";
		colorSet(4);
		 gamePart("ligne_droite");
		colorSet(13);
		 cout<<setw(25)<<right<<"INSTRUCTIONS"<<endl;
		colorSet(4);
		 gamePart("separateur");
		colorSet(10);
		 cout<<"Comment jouer: "<<endl;
		colorSet(15);
		 cout<<" * Le puzzle SUDOKU consiste d'une"<<endl
		     <<"   grille 9x9. Vous devez remplir"<<endl
		     <<"   les carreaux vides avec"<<endl	
		     <<"   les numeros de 1 a 9."<<endl
		     <<" * Utiliser les touches 1-9 sur"<<endl
		     <<"   votre clavier pour remplir"<<endl
		     <<"   le puzzle."<<endl
		     <<" * Pour naviguer le puzzle"<<endl
		     <<"   utiliser les touches ZQSD ou"<<endl
		     <<"   les touches flechees."<<endl
		     <<" * Utiliser la touche retour arriere"<<endl
		     <<"   ou bien [suppr] pour effacer le numero"<<endl
		     <<"   choisi en cas de faute."<<endl
		     <<" * Une fois fini, le jeu vous"<<endl
		     <<"   confirmera que vous l'avez"<<endl
		     <<"   fini. Sinon, vous pouvez"<<endl
		     <<"   appuyez sur [P] puis choisir\"Quitter\" "<<endl
		     <<"   dans le menu de pause si vous"<<endl
		     <<"   trouvez le jeu un peu difficile ."<<endl;
		colorSet(4);
		 gamePart("separateur");
		colorSet(7);
		 cout<<"(Appuyez sur n'importe quelle touche pour retourner!) ";
		colorSet(15);
		
		getch();
		if(located == "main"){
			main();
		}
}	

void quitterMenu(){

	do{
		system("cls");
		colorSet(4);
		 gamePart("ligne_gauche");
		colorSet(15);
		cout<<"SUDOKU";
		colorSet(4);
		 gamePart("ligne_droite");
		colorSet(13);
		 cout<<setw(28)<<right<<"VOULEZ VOUS QUITTER ?"<<endl;
		colorSet(4);
		 gamePart("sperateur");
		colorSet(15);
		 cout<<"[1] ";
		colorSet(12);
		 cout<<"OUI"<<endl;
		colorSet(15);
		 cout<<"[2] ";
		colorSet(10);
		 cout<<"NON"<<endl;
		colorSet(4);
		 gamePart("separateur");
		colorSet(7);
		 cout<<"(Choisir un numero!) ";
		colorSet(15);

		char select = getch();
		if(!(select<'1'||select>'2')){
			cout<<endl;
			if(select == '1'){
				exit(0);
			}
			else{
				main();
			}
		}
	
		}while(true);
}

void colorSet(int tint){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), tint);
}

void gamePart(string part){
	
	if(part == "ligne_gauche"){
		cout<<"************* ";
	}
	else if(part == "ligne_droite"){
		cout<<" **************"<<endl;
	}
	else if(part == "separateur"){
		cout<<"========================================"<<endl;
	}
	else if(part == "sudoku_outer_border"){
		cout<<" $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
	}
	else if(part == "sudoku_outer_vertical_border_small"){
		cout<<" $ ";
	}
	else if(part == "sudoku_outer_vertical_border_next_line"){
		cout<<" $"<<endl;
	}
	else if(part == "sudoku_inner_vertical_border_small"){
		cout<<" | ";
	}
	else if(part == "sudoku_inner_border"){
		cout<<" $---*---*---$---*---*---$---*---*---$"<<endl;
	}
	else{
		cout<<"";
	}
}

void cacherCurseur(bool condition){
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = (!(condition));
	SetConsoleCursorInfo(out, &cursorInfo);
}

















