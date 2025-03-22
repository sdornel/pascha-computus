#include <iostream>
#include <string>
using namespace std;


void computus(int);
void defineEvangelismosArray();
void defineSaintDyonisiusArray();
void definePaschalMoonsArray();
void printPaschalMoon();
void printEvangelismos();
void printPascha();

// alpha = year mod 28
// beta = year mod 19
int alpha, beta, gamma;

int case_KyrioPascha = 0;
int case_Holyweek = 0;
int case_Brightweek = 0;

int year;
int PaschaMonth;
int PaschaDay;
int delta;
int Eva = 0;

string daysOfWeek[7] = {"Kyriaki (Sunday)", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


// The Paschal Moon always takes place on Palm Sunday or Holy Week (7 day range), Holy Week is Holy Monday thru Holy Saturday
// We will use the daysOfHolyWeek array to hold the names of Palm Sunday together with Holy Week
// we will use this array to print the day of the week of the Paschal Moon
// additionally if Evangelismos falls within this range, i.e. Pascha is in March, we will use this array instead of the daysOfWeek array
string daysOfHolyWeek[7] = {"Palm Sunday", "Holy Monday", "Holy Tuesday", "Holy Wednesday", "Holy Thursday", "Holy Friday", "Holy Saturday"};
string daysOfBrightWeek[7] = {"Pascha Sunday", "Bright Monday", "Bright Tuesday", "Bright Wednesday", "Bright Thursday", "Bright Friday", "Bright Saturday"};


// defines the day of the week for Evangelismos (Annunciation) within the 28 year Menaion Cycle
// EvangelismosArray[alpha] gives the day of the week for Evangelismos
// the array will be algorithmically generated and will contain the following values
// 4, 5, 6, 0, 2, 3, 4, 5, 0, 1, 2, 3, 5, 6, 0, 1, 3, 4, 5, 6, 1, 2, 3, 4, 6, 0, 1, 2
int EvangelismosArray[28];


// these are the 19 Paschal Moons. Paschal Moons repeat every 19 years, Pascha repeats every 532 years.
// PaschalMoonsArray[beta] gives the date of the Paschal moon
// the array will be algorithmically generated and will contain the following values
// APR 5, MAR 25, APR 13, APR 2, MAR 22, APR 10, MAR 30, APR 18, APR 7,
// MAR 27, APR 15, APR 4, MAR 24, APR 12, APR 1, MAR 21, APR 9, MAR 29, APR 17
int PaschalMoonsArray[19][2];

// Saint Dyonisius' writing is the earliest algorithm we have for calculating Pascha
// this array just holds 30 consecutive dates from March 21 (the earliest Paschal Moon) to April 19
// April 18 is the latest Paschal Moon but we need April 19 as a place holder
// for the for loop which creates the PaschalMoons array to work correctly
int SaintDyonisiusArray[30][2];




int main() {

  cout << "Pascha Computus 25.3.1.a" << endl;
  cout << "file generated: " << "Feb, 03, 2025 4:47 AM" << endl;
  cout << "this file is only for testing purposes. it needs verification and may contain errors" << endl;

  defineEvangelismosArray();
  defineSaintDyonisiusArray();
  definePaschalMoonsArray();

  for (int i=1596; i<=2127; i++) {
    year = i;
    computus(i);
  }

  cout << endl << endl;

  cout << "BW: " << case_Brightweek << ", HW: " << case_Holyweek << ", KP: " << case_KyrioPascha << endl;
  return 0;
}


void computus(int year) {
  alpha = year % 28;
  beta = year % 19;
  gamma = year % 532;



  cout << "(" << gamma << ") " << "Year " << year;

  cout << "; alpha = " << alpha << ", beta = " << beta << endl;

  int index; // locate value of index of current Paschal Moon within Saint Dyonisius array

  for (index=0; index<=29; index++) {
    if (SaintDyonisiusArray[index][1] ==  PaschalMoonsArray[beta][1]) {
      break;
    }
  }


  delta = (index + 3) % 7;

  int indexPaschalMoon;
  indexPaschalMoon = (EvangelismosArray[alpha] + delta) % 7;
  int daysToPascha = 7 - indexPaschalMoon;

  int PaschalMoonMonth;
  int PaschalMoonDate;
  PaschalMoonMonth = PaschalMoonsArray[beta][0];
  PaschalMoonDate = PaschalMoonsArray[beta][1];


  if (PaschalMoonMonth == 3) {
    PaschaMonth = SaintDyonisiusArray[index + daysToPascha][0];
    PaschaDay = SaintDyonisiusArray[index + daysToPascha][1];
  }

  if (PaschalMoonMonth == 4) {
    PaschaMonth = 4;
    PaschaDay = SaintDyonisiusArray[index][1] + daysToPascha;
  }



  // print the Paschal Moon, Evangelismos, Pascha in their order of occurence
  if ((PaschalMoonsArray[beta][1] >= 21) && (PaschalMoonsArray[beta][1] <= 24)) {
    printPaschalMoon();

    // paschal moon, pascha, evangelismos
    if (PaschaDay < 25) {
      printPascha();
      printEvangelismos();
    }

    // paschal moon, evangelismos, pascha
    else {
      printEvangelismos();
      printPascha();
    }

    // evangelismos, paschal moon, pascha
  } else {
      printEvangelismos();
      printPaschalMoon();
      printPascha();
  }



  cout << endl;

}


void printPaschalMoon() {
  cout << "Paschal Moon: ";
  if (PaschalMoonsArray[beta][0] == 3)
  cout << "March";
  if (PaschalMoonsArray[beta][0] == 4)
  cout << "April";
  cout << " " << PaschalMoonsArray[beta][1];
  // print the day of the week of the Paschal Moon
  cout << ", " << daysOfHolyWeek[(EvangelismosArray[alpha] + delta) % 7] << endl;
}

void printPascha() {
  cout << "Pascha: ";
  if (PaschaMonth == 3)
    cout << "March";
  if (PaschaMonth == 4)
    cout << "April";
  cout << " " << PaschaDay;
  cout << " ";


  if ((!daysOfWeek[EvangelismosArray[alpha]].compare("Kyriaki (Sunday)")) && ((beta == 4) || (beta == 12) || (beta == 15)) ) {
    cout << ", KyrioPascha+";
  }

  cout << endl;
}


void printEvangelismos()
{

    if (PaschaMonth == 3) {
      Eva++;
      //cout << "+Evangelismos(" << Eva << "): March 25, ";
      cout << "+Evangelismos: March 25, ";

      // Evangelismos is in Bright Week
      if (PaschaDay < 25) {
        cout << daysOfBrightWeek[EvangelismosArray[alpha]];
        case_Brightweek++;
      }

      // Evangelismos is in Holy Week
      if (PaschaDay > 25) {
        cout << daysOfHolyWeek[EvangelismosArray[alpha]];
        case_Holyweek++;
      }

      // if Pascha = March 25 it is KyrioPascha
      if (PaschaDay == 25) {
        cout << daysOfBrightWeek[EvangelismosArray[alpha]];
        case_KyrioPascha++;
      }
      cout << " year: \t" << year << "\t*";
      cout << endl;
    }

    // Pascha is in April
    if (PaschaMonth == 4) {

      if (PaschaDay <= 2) {
        Eva++;
        //cout << "+Evangelismos(" << Eva << "): March 25, ";
        cout << "+Evangelismos: March 25, ";
      }

      // Evangelismos is Palm Sunday
      if (PaschaDay == 1) {
        cout << daysOfHolyWeek[EvangelismosArray[alpha]];
        case_Holyweek++;
      }

      // Evangelismos is Lazarus Saturday
      if (PaschaDay == 2) {
        cout << "Lazarus Saturday";
      }

      // Evangelismos is in regular week
      if (PaschaDay >= 3) {
        cout << "Evangelismos: March 25, " << daysOfWeek[EvangelismosArray[alpha]];
      } else {
        cout << " year: \t" << year << "\t*";
      }

      cout << endl;
    }



}



void defineEvangelismosArray() {
  for (int i=0; i<=27; i++) {
    EvangelismosArray[i] = (4 + i + int (i / 4)) % 7;
  }
}

void defineSaintDyonisiusArray() {

  // Saint Dyonisius array holds 30 consecutive dates
  // from 3, 21 (March 21) to 4, 19 (April 19)


  // march dates
  for (int i=0; i<=10; i++) {
    SaintDyonisiusArray[i][0] = 3;
    SaintDyonisiusArray[i][1] = i + 21;
  }

  // april dates
  for (int i=11; i<=29; i++) {
    SaintDyonisiusArray[i][0] = 4;
    SaintDyonisiusArray[i][1] = i - 10;
  }

}

void definePaschalMoonsArray() {
  // beta 0 needs to be initialized to April 5 (index 15 of Saint Dyonisius array)
  int j = 15;

  // generate the 19 Year Paschal Cycle using SaintDyonisiusArray
  for (int i=0; i<=18; i++) {

    PaschalMoonsArray[i][0] = SaintDyonisiusArray[j][0];
    PaschalMoonsArray[i][1] = SaintDyonisiusArray[j][1];

    j = j + 19;
    j = j % 30;
  }
}
