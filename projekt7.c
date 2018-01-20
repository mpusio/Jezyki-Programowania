#include <stdio.h>
#include <stdlib.h> //abs()
#include <string.h> // strcmp()
#include <stdbool.h> // true, false
#include <ctype.h> // isspace()

/*zmienne globalne*/
char str[100]; //przechowuje słowa
char splitStrings[10][100]; //przechowuje max 10 wyrazów po max. długości 100 znaków
int nswe = 0; //tym będziesz chadzał po tablicy i zmieniał kierunek

/*struktury i funkcje*/
enum Kierunki {GORA = 'N', DOL = 'S', LEWO = 'W', PRAWO = 'E'}ruch;
struct Point{
  int x;
  int y;
} island_1 = {2,3};
struct Ship{
  char compas[4];
  struct Point point_1;
} ship = {{'N','E','S','W'},{0,0}}; //mam statek z kompasem i wyjściowymi współrzędnymi (x,y)=(0,0)

void f_nswe(); //kontroluje zmienną globalną
void welcome(); //przywitaj w programie
void acctual_situation(); //podaje kierunek, współrzędne
void commands(); //tutaj przechowuje komendy poruszania się
void swim(); //płyń :)
void split_and_save(); //dziel i zapisz w tablicy
void free_tab(); //czyść tablicę po każdej pętli

int main() {
  welcome(); //przywitanie
  while (true) {
    acctual_situation();
    printf("Co chcesz zrobić ?\n");
    fgets (str, 100, stdin); //pobiera ciąg ze spacją do 100 znaków max., pozwala zachować spacje
    split_and_save();
    if (strcmp("EXIT", splitStrings[0])==0)
      break;
    commands();
    f_nswe(); //zakres od 0 do 3, obraca statkiem
    free_tab();
  }
  exit(1);
}

void f_nswe(){
  if (nswe<0)
    nswe = 3;
  else if (nswe>3)
    nswe = 0;
}
void welcome(){
  printf("Witaj! Przetrzyj pokład i możemy płynąć!\n");
  printf("• Jeżeli chcesz popłynąć na przód, wpisz 'n'\n");
  printf("• Aby popłynąć wstecz, wpisz 'w'\n");
  printf("• Aby obrócić statek w lewo, wpisz 'l', w prawo 'p'\n");
  printf("Wpisz EXIT, jeżeli chcesz zakończyć rejs!\n" );
}
void acctual_situation(){ //wypisz kierunek, współrzędne
  printf("Aktualne współrzędne(x,y) = (%d,%d)\n", ship.point_1.x, ship.point_1.y);
  printf("Aktualny kierunek: %c\n", ship.compas[nswe]);
  if (abs(island_1.x - ship.point_1.x)<=1 && abs(island_1.y - ship.point_1.y)<=1)
    printf("Wykryta wyspa w promieniu 1 kratki o współrzędnych(x,y) = (%d,%d) \n", island_1.x, island_1.y);
}
void commands(){ //komendy
  for (int i = 0; i < 10; i++) {
    if (strcmp("n", splitStrings[i])==0) {
      printf("Lecim do przodu!\n");
      swim();
    }
    else if (strcmp("w", splitStrings[i])==0) {
      printf("Cofamy do tyłu\n");
      if (nswe == 0)
        nswe = 2;
      else
        nswe -=2;
      swim();
    }
    else if (strcmp("l", splitStrings[i])==0) {
      printf("Obrót statku w lewo\n");
      nswe--;
    }
    else if (strcmp("p", splitStrings[i])==0) {
      printf("Obrót statku w prawo\n");
      nswe++;
    }
    else {
      if (*splitStrings[i]=='\0') {
        continue;
      }
      printf("Nie ruszyłeś statku\n");
    }
  }
}
void swim(){ //płyń :)
  if (ship.compas[nswe]=='N')
    ship.point_1.x++;
  else if (ship.compas[nswe]=='S')
    ship.point_1.x--;
  else if (ship.compas[nswe]=='W')
    ship.point_1.y--;
  else if (ship.compas[nswe]=='E')
    ship.point_1.y++;

  if (island_1.x == ship.point_1.x && island_1.y == ship.point_1.y) {
    printf("Wpadłeś na wyspę!\n");
  }
}
void split_and_save(){
  int kol = 0;
  int b = 0;

  for (int a = 0; str[a] != '\0'; a++){
    if (isspace(str[a]) || str[a] == ',') {
      if (isspace(str[a+1]) || str[a+1] == ',') {
        a ++;
      }
      kol++;
      b = 0;
    }
    else {
    splitStrings[kol][b] = str[a];
    b++;
    }
  }
}
void free_tab(){ //czyści tablice z wartości (nie pamięci)
  memset(str, 0, 100);
  for (int i = 0; i < 10; i++) {
    memset(splitStrings[i], 0, 100); //dwuwymiarowa czyszczenie
  }
}