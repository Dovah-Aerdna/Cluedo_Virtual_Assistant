#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <algorithm>

void add(int pl, int k);
int select_player();

const std::string name_sospetti[6] =
{"Draco Malfoy",
"Tiger e Goyle",
"Lucius Malfoy",
"Dolores Umbridge",
"Peter Minus",
"Bellatrix Lestrange"};

const std::string name_armi[6] =
{"Distillato Soporifero",
"Armadietto che scompare",
"Passaporta",
"Impedimenta",
"Petrificus Totalus",
"Mandragola"};

const std::string name_stanze[9] =
{"Sala Grande",
"Ala dell'Ospedale",
"Stanza delle Necessita'",
"Aula di Pozioni",
"Sala dei trofei",
"Aula di Divinazione",
"Gufaia",
"Biblioteca",
"Difesa contro le Arti Oscure"};



std::vector<std::string> players;
std::vector<int> N_carte_mano;
std::vector<std::vector<std::array<int, 3>>> passate;
std::vector<std::vector<char>> sospetti;
std::vector<std::vector<char>> armi;
std::vector<std::vector<char>> stanze;
std::string soluzione_sospetto;
std::string soluzione_arma;
std::string soluzione_stanza;

void print()
{
    int N=players.size();

    std::cout << std::setw(33);

    for(std::string pl: players)
      std::cout << '\t' << pl;

    std::cout << '\n';

    for(int i=0; i<6; i++)
    {
      std::cout << std::setw(30) << name_sospetti[i] << ": ";

      for(int n=0; n<N; n++)
        std::cout << '\t' << sospetti[n][i];

      std::cout << '\n';
    }

std::cout << "\n" << '\n';

    for(int i=0; i<6; i++)
    {
      std::cout << std::setw(30) << name_armi[i] << ": ";

      for(int n=0; n<N; n++)
        std::cout << '\t' << armi[n][i];

      std::cout << '\n';
    }

std::cout << "\n" << '\n';

    for(int i=0; i<9; i++)
    {
      std::cout << std::setw(30) << name_stanze[i] << ": ";

      for(int n=0; n<N; n++)
        std::cout << '\t' << stanze[n][i];

      std::cout << '\n';
    }

}

void set_players()
{
  int N_players;
  std::cout << "Inserire numero giocatori: " << '\n';
  std::cin>>N_players;
  if(N_players < 3)
  {
    std::cout << "Troppo pochi, non ancora supportato" << '\n';
    exit(0);
  }
  if(N_players > 7)
  {
    std::cout << "Pirletta! Troppi..." << '\n';
    exit(0);
  }

  std::string pl;
  std::vector<std::vector<std::array<int, 3>>> init_passate;
  std::vector<std::array<int, 3>> vec_pass = {{}};
  std::vector<char> vec6(6, '_');
  std::vector<char> vec9(9, '_');

  for(int i=1; i<N_players+1;i++)
  {

      std::cout << "Inserisci il nome del giocatore " << i << ":\n";
      std::cin >> pl;
      players.push_back(pl);

      sospetti.push_back(vec6);
      armi.push_back(vec6);
      stanze.push_back(vec9);

      // initialize passate

      init_passate.push_back(vec_pass);
  }

  passate=init_passate;
/*
  std::cout << "dimension passate " << passate.size()<< '\n';
  std::cout << "size passate[0] "<< passate[0].size() << '\n';
  std::cout << "size passate[0][0] "<< passate[0][0].size() << '\n';
  std::cout << "elemento passate[0][0][0] " << passate[0][0][1]<< '\n';
*/
}

int menu()
{
  int k;
  std::cout << "\n\n";
  std::cout << "1. Guarda griglia" << '\n';
  std::cout << "2. Passaggio carte" << '\n';
  std::cout << "3. Aggiungi carta" << '\n';
  std::cout << "4. Non ha" << '\n';
  std::cout << "5. Modifica carte in mano giocatore" << '\n';
  std::cout << "999. Esci" << '\n';

  std::cout << "Seleziona: ";
  std::cin >> k;

  return k;
}

int select_cards()
{
  int k;
  for(int i=0; i<21; i++)
  {
    if(i<6) std::cout << i+1 << ". " << name_sospetti[i] << '\n';
    else if(i<12) std::cout << i+1 << ". " << name_armi[i-6] << '\n';
    else std::cout << i+1 << ". " << name_stanze[i-12] << '\n';
  }
  std::cout << "seleziona: ";
  std::cin >> k;

  return k;
}

void init()
{
  int N=players.size();
  int k, count;
  char control = '_';
  std::cout<<"\n\nPreparazione strategia... \n\n";
  std::cout << "\nQuali carte hai in mano?" << '\n';
  while(control!='n')
  {
  k=select_cards();
  add(0,k);
  std::cout << "Hai altre carte? (s/n)" << '\n';
  std::cin >> control;
  count++;
  }

  N_carte_mano.push_back(count);

  if(18%N==0 && 18/N==count)//carte disponibili: 21-3=18
  {
    for(int pl=1; pl<N; pl++)
    {
      N_carte_mano.push_back(count);
    }
  }else{
    for(int i=1; i<N; i++)
    {
      std::cout << "Inserire il numero carte in mano a "<< players[i] << ": ";
      std::cin >> count;
      N_carte_mano.push_back(count);
    }
  }

  //for(int i = 0; i<N_carte_mano.size(); i++)std::cout << N_carte_mano[i] << '\n';
  for(int i=0; i<6; i++)
  {
    if(sospetti[0][i]!='x') sospetti[0][i]='o';

    if(armi[0][i]!='x') armi[0][i]='o';

    if(stanze[0][i]!='x') stanze[0][i]='o';
  }
  for(int i=6; i<9; i++)
  {
    if(stanze[0][i]!='x') stanze[0][i]='o';
  }

}

void pass()
{
  std::array<int, 3> richiesta;


  std::cout << "Selezionare la richiesta effettuata:" << '\n';
  for(int i=0; i<3; i++)
  {
    std::cout << "Richiesta " << i+1 << '\n';
    richiesta[i]=select_cards()-1;
  }

while(1)
{
    char c, b;
    int k;
    int pl = select_player();
    std::cout << players[pl] << " ha passato una carta? (s/n) ";
    std::cin >> c;
    if(c=='n')
    {
      for(int i=0; i<3; i++)
      {
        if(richiesta[i]<6)
        {
          if(sospetti[pl][richiesta[i]]!='x') sospetti[pl][richiesta[i]]='o';
        }
        else if(richiesta[i]<12)
        {
          if(sospetti[pl][richiesta[i]]!='x') armi[pl][richiesta[i]-6]='o';
        }
        else
        {
          if(sospetti[pl][richiesta[i]]!='x') stanze[pl][richiesta[i]-12]='o';
        }
      }
    }
    if(c=='s')
    {
      // tag punto interrogativo sulla griglia e aggiungi tripletta

      std::cout << "Conosci la carta passata? (s/n)" << '\n';
      std::cin >> b;
      if(b=='s')
      {
      k=select_cards();
      add(pl, k);
      return;
      }
      //Else, aggiungo i punti interrogativi e le triplette

      int n=passate[pl].size();
      //std::cout << "n: "<< n << '\n';

      passate[pl].push_back(richiesta);
      /*  std::cout << "n dopo: "<< passate[pl].size() << '\n';
      for(int i=0; i<3; i++)
      {
        std::cout << passate[pl][n][i] << '\n';
      }
      */

      for(int i=0; i<3; i++)
      {
        if(richiesta[i]<6)
        {
          if(sospetti[pl][richiesta[i]]!='x' && sospetti[pl][richiesta[i]]!='o') sospetti[pl][richiesta[i]]='?';
        }
        else if(richiesta[i]<12)
        {
          if(sospetti[pl][richiesta[i]]!='x' && sospetti[pl][richiesta[i]]!='o') armi[pl][richiesta[i]-6]='?';
        }
        else
        {
          if(sospetti[pl][richiesta[i]]!='x' && sospetti[pl][richiesta[i]]!='o') stanze[pl][richiesta[i]-12]='?';
        }
      }
    }
    std::cout << "Continuare con il giro? (s/n)" << '\n';
    std::cin >> b;
    if(b=='n') break;
 }
}

void add(int pl, int k)
{
  if(pl>players.size())
  {
      return;
  }
  k=k-1;
  if(k<6)
  {
    sospetti[pl][k]='x';
    for(int i=0; i<players.size(); i++)
    {
      if(i!=pl) {sospetti[i][k]='o';}
    }

  }
  else if(k<12)
  {
    armi[pl][k-6]='x';
    for(int i=0; i<players.size(); i++)
    {
      if(i!=pl) {armi[i][k-6]='o';}
    }
  }
  else
  {
    stanze[pl][k-12]='x';
    for(int i=0; i<players.size(); i++)
    {
      if(i!=pl) {stanze[i][k-12]='o';}
    }
  }

}

int select_player()
{
  int pl;
  std::cout << "seleziona giocatore" << '\n';
  for(int i=1; i<players.size(); i++)
    std::cout << i << ". " << players[i] << '\n';
  std::cin >> pl;
  return pl;
}

void add_card()
{

  int pl;

  pl = select_player();



  std::cout << "Seleziona la carta" << '\n';
  int k=select_cards();

  add(pl, k);
}

void mod_cards()
{
  //modifica le carte in mano dei giocatori
  int count;
  for(int pl=0; pl<players.size(); pl++)
  {
    std::cout << "\nInserire il numero carte in mano a "<< players[pl] << ": ";
    std::cin >> count;

    // se un player pesca una carta, si perde l'informazione su cosa non ha! (cancella anche i ?)
    if(N_carte_mano[pl]!=count && pl!=0)
    {
      N_carte_mano[pl]=count;

      for(int i=0; i<6; i++)
      {
        if(sospetti[pl][i]!='x') sospetti[pl][i]='_';

        if(armi[pl][i]!='x') armi[pl][i]='_';

        if(stanze[pl][i]!='x') stanze[pl][i]='_';
      }
      for(int i=6; i<9; i++)
      {
        if(stanze[pl][i]!='x') stanze[pl][i]='_';
      }

    }
  }

//for(int i = 0; i<N_carte_mano.size(); i++)std::cout << N_carte_mano[i] << '\n';

}

void togli()
{
  int pl = select_player();
  int k = select_cards();

  k=k-1;

  if(k<6)
  {
    sospetti[pl][k]='o';
  }
  else if(k<12)
  {
    armi[pl][k-6]='o';
  }
  else
  {
    stanze[pl][k-12]='o';
  }

}

void handle(int choice)
{
  switch (choice)
  {
    case 1:
      print();
      break;
    case 2:
      pass();
      break;
    case 3:
      add_card();
      break;
    case 4:
      togli();
      break;
    case 5:
      mod_cards();
      break;
    case 999:
      char c;
      std::cout << "Sicuro di voler uscire? Tutti i progressi saranno persi (s/n)" << '\n';
      std::cin >> c;
      if(c=='S' || c=='s') exit(0);
      else break;
    default:
      std::cout << "Scelta non valida!" << '\n';
  }
}

void check_row()
{
  int N = players.size();
  int c_sos, c_arm, c_sta;

  for(int i=0; i<6; i++)
  {
    c_sos=0;
    c_arm=0;
    c_sta=0;
    for(int pl=0; pl<N; pl++)
    {
      if(sospetti[pl][i]=='o') c_sos++;
      if(armi[pl][i]=='o') c_arm++;
      if(stanze[pl][i]=='o') c_sta++;
    }
    if(c_sos==N) soluzione_sospetto=name_sospetti[i];
    if(c_arm==N) soluzione_arma=name_armi[i];
    if(c_sta==N) soluzione_stanza=name_stanze[i];
  }
  for(int i=6; i<9; i++)
  {
    c_sta=0;
    for(int pl=0; pl<N; pl++)
    {
      if(stanze[pl][i]=='o') c_sta++;
    }
    if(c_sta==N) soluzione_stanza=name_stanze[i];
  }

}

void check_x()
{
  int N = players.size();
  int c_sos=0, c_arm=0, c_sta=0;

  for(int i=0; i<6; i++)
  {
    for(int pl=0; pl<N; pl++)
    {
      if(sospetti[pl][i]=='x') c_sos++;
      if(armi[pl][i]=='x') c_arm++;
      if(stanze[pl][i]=='x') c_sta++;
    }
  }
  for(int i=6; i<9; i++)
  {
    for(int pl=0; pl<N; pl++)
    {
      if(stanze[pl][i]=='x') c_sta++;
    }
  }

if(c_sos==5) //5=6-1
{
  for(int i=0; i<6; i++)
  {
    for(int pl=0; pl<N; pl++)
    {
      if(sospetti[pl][i]=='x') break;
      if(pl==N-1) soluzione_sospetto=name_sospetti[i];
    }
  }
}

if(c_arm==5) //5=6-1
{
  for(int i=0; i<6; i++)
  {
    for(int pl=0; pl<N; pl++)
    {
      if(armi[pl][i]=='x') break;
      if(pl==N-1) soluzione_arma=name_armi[i];
    }
  }
}

if(c_sta==8) //5=6-1
{
  for(int i=0; i<6; i++)
  {
    for(int pl=0; pl<N; pl++)
    {
      if(stanze[pl][i]=='x') break;
      if(pl==N-1) soluzione_stanza=name_stanze[i];
    }
  }
}

}

void check_col()
{
  int mod = 0;
  int count;

  for(int pl=1; pl<players.size(); pl++)
  {
    count=0;

    for(int i=0; i<6; i++)
    {
      if(sospetti[pl][i]=='x') count++;

      if(armi[pl][i]=='x') count++;

      if(stanze[pl][i]=='x') count++;
    }
    for(int i=6; i<9; i++)
    {
      if(stanze[pl][i]=='x') count++;
    }

    if(count==N_carte_mano[pl])
    {
      mod=1;
      for(int i=0; i<6; i++)
      {
        if(sospetti[pl][i]!='x') sospetti[pl][i]='o';

        if(armi[pl][i]!='x') armi[pl][i]='o';

        if(stanze[pl][i]!='x') stanze[pl][i]='o';
      }
      for(int i=6; i<9; i++)
      {
        if(stanze[pl][i]!='x') stanze[pl][i]='o';
      }
    }
  }

  if(mod!=0) check_row();
}

void check_unk()
{
  int mod_x = 0;

  // loop sulle triplette
  // RICORDA CHE passate[pl][n][i], n PARTE DA 1, L'INDICE 0 E' SPORCIZIA DOCUTA ALL'INIZIALIZZAZIONE
  // se resta 1 ? e gli altri 2 sono 'o', ?=x
  // se resta 1 ? e tra gli altri 2 c'è almeno una x, ?=_
  std::array<char, 3> tripletta;
  for(int pl=1; pl<players.size(); pl++)
  {
    for(int n=1; n<passate[pl].size(); n++)
    {
      for(int i=0; i<3; i++)
      {
        int k=passate[pl][n][i];
        if(k<6)
        {
          tripletta[i]=sospetti[pl][k];
          continue;
        }
        if(k<12)
        {
          tripletta[i]=armi[pl][k-6];
          continue;
        }

        tripletta[i]=stanze[pl][k-12];
      }

      //for(int i=0; i<3; i++) std::cerr << tripletta[i] << '\n';

      if(std::count(tripletta.begin(), tripletta.end(), 'x')==1)
      {
        std::cout << "\nTrovata una corrispondenza tra le precedenti giocate! (1 x)" << '\n';
        for(int i=0; i<3; i++)
        {
          int j=passate[pl][n][i];
          if(tripletta[i]=='?')
          {
            if(j<6){sospetti[pl][j]='_'; continue;}
            if(j<12){armi[pl][j-6]='_'; continue;}
            stanze[pl][j-12];
          }
        }

        //std::cout << "cancello tripletta, pl="<<pl<<" n="<<n<< '\n';
        passate[pl].erase(passate[pl].begin()+n);
      }

      if(std::count(tripletta.begin(), tripletta.end(), '?')==1)
      {
        std::cout << "\nTrovata una corrispondenza tra le precedenti giocate! (1 ?)" << '\n';

        // se resta 1 ? e gli altri 2 sono 'o', ?=x, add (così le altre vanno a 'o')
        if(std::count(tripletta.begin(), tripletta.end(), 'o')==2)
        {
          for(int i=0; i<3; i++)
          {
            if(tripletta[i]=='?')
            {
              add(pl, passate[pl][n][i]+1);
              mod_x=1;
              // cancella tripletta, ormai è stata usata
              //std::cout << "cancello tripletta, pl="<<pl<<" n="<<n<< '\n';
              passate[pl].erase(passate[pl].begin()+n);
              break;
            }
          }
        }
      }
    }
  }

  if(mod_x!=0)
  {
    std::cout << "\nAggiunta una x!" << '\n';
    check_x();
    check_col();
    //non ottimizzato, ma per buona misura lo metto qui in caso le due chiamate precedenti abbiano modificato un '?'
    check_unk();
  }

}

void check()
{
  check_row();
  check_x();

  check_col();
  check_unk();
  // dividere check in più funzioni!!!
  // check_col
  // check_row
  // check_unk  (unknown, sui '?')
  // check_x


  //controlla griglia per vedere se so qualcosa...
  //controlla 'passate', i punti interrogativi, per sapere qualcosa o eliminarlo
  // se resta 1 ? e gli altri 2 sono 'o', ?=x
  // se resta 1 ? e tra gli altri 2 c'è almeno una x, ?=_
  //controlla se il numero di X in una colonna è uguale al numero di carte di quel giocatore,
  // in quel caso riempie con o
 // controlla una riga, se tutti sono 'o', seleziona la cosa.
 // per ogni controllo che porta ad un cambio, tutti gli altri relativi a quel cambio vanno rifatti
 // in check_col e check_unk, le uniche funzioni che modificano la griglia, se si ha una modifica,
 // lancio la coppia check row, check_x (in base a cosa ho modificato).


 if(!soluzione_sospetto.empty())
  std::cout << "\n\n*******************************\nTrovato il colpevole: "<< soluzione_sospetto << "!\n";

 if(!soluzione_arma.empty())
  std::cout << "\n\n*******************************\nTrovata l'arma: "<< soluzione_arma << "!\n";

 if(!soluzione_stanza.empty())
  std::cout << "\n\n*******************************\nTrovato il colpevole: "<< soluzione_stanza << "!\n";

}

int main()
{

    set_players();
    init();

    //game loop
    while(1)
    {
      int choice = menu();
      handle(choice);
      check();

      /*std::cout << "dimension passate " << passate.size()<< '\n';
      std::cout << "size passate[0] "<< passate[0].size() << '\n';
      std::cout << "size passate[0][0] "<< passate[0][0].size() << '\n';
      std::cout << "elemento passate[0][0][1] " << passate[0][0][1]<< '\n';
      for(int i=0; i<3; i++)
      {
        std::cout<<passate[1][1][i]<<'\n';
      }*/

    }


    return 0;
}
