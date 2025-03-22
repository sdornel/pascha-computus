let alpha;
let beta;
let gamma;

let case_KyrioPascha = 0;
let case_Holyweek = 0;
let case_Brightweek = 0;

let year;
let PaschaMonth;
let PaschaDay;
let delta;

const daysOfWeek = ["Kyriaki (Sunday)", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];

// The Paschal Moon always takes place on Palm Sunday or Holy Week (7 day range), Holy Week is Holy Monday thru Holy Saturday
// We will use the daysOfHolyWeek array to hold the names of Palm Sunday together with Holy Week
// we will use this array to print the day of the week of the Paschal Moon
// additionally if Evangelismos falls within this range, i.e. Pascha is in March, we will use this array instead of the daysOfWeek array
const daysOfHolyWeek = ["Palm Sunday", "Holy Monday", "Holy Tuesday", "Holy Wednesday", "Holy Thursday", "Holy Friday", "Holy Saturday"];
const daysOfBrightWeek = ["Pascha Sunday", "Bright Monday", "Bright Tuesday", "Bright Wednesday", "Bright Thursday", "Bright Friday", "Bright Saturday"];

// defines the day of the week for Evangelismos (Annunciation) within the 28 year Menaion Cycle
// EvangelismosArray[alpha] gives the day of the week for Evangelismos
// the array will be algorithmically generated and will contain the following values
// 4, 5, 6, 0, 2, 3, 4, 5, 0, 1, 2, 3, 5, 6, 0, 1, 3, 4, 5, 6, 1, 2, 3, 4, 6, 0, 1, 2
const EvangelismosArray = [];

// these are the 19 Paschal Moons. Paschal Moons repeat every 19 years, Pascha repeats every 532 years.
// PaschalMoonsArray[beta] gives the date of the Paschal moon
// the array will be algorithmically generated and will contain the following values
// APR 5, MAR 25, APR 13, APR 2, MAR 22, APR 10, MAR 30, APR 18, APR 7,
// MAR 27, APR 15, APR 4, MAR 24, APR 12, APR 1, MAR 21, APR 9, MAR 29, APR 17
const PaschalMoonsArray = [[], []];

// Saint Dyonisius' writing is the earliest algorithm we have for calculating Pascha
// this array just holds 30 consecutive dates from March 21 (the earliest Paschal Moon) to April 19
// April 18 is the latest Paschal Moon but we need April 19 as a place holder
// for the for loop which creates the PaschalMoons array to work correctly
const SaintDyonisiusArray = [[], []];


function main() {
    console.log("Pascha Computus 25.3.1.a");
    console.log("this file is only for testing purposes. it needs verification and may contain errors");

    defineEvangelismosArray();
    defineSaintDionysiusArray();
    definePaschalMoonsArray();
    for (let i = 1596; i <= 2127; i++) {
        year = i;
        computus(i);
    }

    return;
}

function computus(year) {
    alpha = year % 28;
    beta = year % 19;
    gamma = year % 532;

    console.log('(' + gamma + ') Year ' + year);
    console.log('; alpha = ' + alpha, ', beta = ' + beta);

    let index; // locate value of index of current Paschal Moon within Saint Dyonisius array
    for (index = 0; index <= 29; index++) {
        if (SaintDyonisiusArray[index][1] === PaschalMoonsArray[beta][1]) {
            break;
        }
    }

    delta = (index + 3) % 7;

    const indexPaschalMoon = (EvangelismosArray[alpha] + delta) % 7;
    const daysToPascha = 7 - indexPaschalMoon;
    
    const PaschalMoonMonth = PaschalMoonsArray[beta][0];
    const PaschalMoonDate = PaschalMoonsArray[beta][1];

    // if (PaschaDay === 7) debugger;
    if (PaschalMoonMonth === 3) {
        PaschaMonth = SaintDyonisiusArray[index + daysToPascha][0];
        PaschaDay = SaintDyonisiusArray[index + daysToPascha][1];
    }
    
    if (PaschalMoonMonth === 4) {
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
}

function printPaschalMoon() {
    let paschalMoonOutput = "Paschal Moon: ";
    if (PaschalMoonsArray[beta][0] === 3) {
        paschalMoonOutput += "March " + PaschalMoonsArray[beta][1] + ", " + daysOfHolyWeek[(EvangelismosArray[alpha] + delta) % 7];
    }
    if (PaschalMoonsArray[beta][0] === 4) {
        // print the day of the week of the Paschal Moon
        paschalMoonOutput += "April " + PaschalMoonsArray[beta][1] + ", " + daysOfHolyWeek[(EvangelismosArray[alpha] + delta) % 7];
    }
    console.log(paschalMoonOutput);
}

function printPascha() {
    let paschaInfo = 'Pascha: ';
    if (PaschaMonth === 3) {
        paschaInfo += "March";
    } else {
        paschaInfo += "April";
    }

    if ((daysOfWeek[EvangelismosArray[alpha]] === "Kyriaki (Sunday)") && ((beta == 4) || (beta == 12) || (beta == 15)) ) {
        console.log(paschaInfo + ` ${PaschaDay}` + ", KyrioPascha");
    } else {
        console.log(paschaInfo + ` ${PaschaDay}`);
    }
}

function printEvangelismos() {
    let Eva = 0;
    let evangelismosDay = '';
    if (PaschaMonth === 3) {
        Eva++;
        evangelismosDay += "+Evangelismos: March 25, ";

        // Evangelismos is in Bright Week
        if (PaschaDay < 25) {
            evangelismosDay += daysOfBrightWeek[EvangelismosArray[alpha]];
            case_Brightweek++;
        }

        // Evangelismos is in Holy Week
        if (PaschaDay > 25) {
            evangelismosDay += daysOfHolyWeek[EvangelismosArray[alpha]];
            case_Holyweek++;
        }

        // if Pascha = March 25 it is KyrioPascha
        if (PaschaDay === 25) {
            evangelismosDay += daysOfBrightWeek[EvangelismosArray[alpha]];
            case_KyrioPascha++;
        }
        evangelismosDay += " year: \t" + year + "\t*";
    } else {
        // Pascha is in April
        if (PaschaDay <= 2) {
            Eva++;
            evangelismosDay += "+Evangelismos: March 25, ";
        }

        // Evangelismos is Palm Sunday
        if (PaschaDay === 1) {
            console.log(daysOfHolyWeek[EvangelismosArray[alpha]]);
            case_Holyweek++;
        }
        // Evangelismos is Lazarus Saturday
        if (PaschaDay === 2) {
            evangelismosDay += "Lazarus Saturday";
        }
        // Evangelismos is in regular week
        if (PaschaDay >= 3) {
            evangelismosDay += "Evangelismos: March 25, " + daysOfWeek[EvangelismosArray[alpha]];
        } else {
            evangelismosDay += " year: \t" + year + "\t*";
        }
        console.log(evangelismosDay);
    }
}

function defineEvangelismosArray() {
    for (let i = 0; i <= 27; i++) {
        //  we need parseInt to remove decimals
        EvangelismosArray[i] = (4 + i + parseInt((i / 4))) % 7;
    }
}

function defineSaintDionysiusArray() {
    // Saint Dyonisius array holds 30 consecutive dates
    // from 3, 21 (March 21) to 4, 19 (April 19)

    // march dates
    for (let i = 0; i <= 10; i++) {
        SaintDyonisiusArray[i] = [3, 21 + i];
    }

    // april dates
    for (let i = 11; i <= 29; i++) {
        SaintDyonisiusArray[i] = [4, i - 10];
    }
}

function definePaschalMoonsArray() {
    // beta 0 needs to be initialized to April 5 (index 15 of Saint Dyonisius array)
    let j = 15;

    // generate the 19 Year Paschal Cycle using SaintDyonisiusArray
    for (let i = 0; i <= 18; i++) {
        PaschalMoonsArray[i] = [null, null];
        PaschalMoonsArray[i][0] = SaintDyonisiusArray[j][0];
        PaschalMoonsArray[i][1] = SaintDyonisiusArray[j][1];

        j = j + 19;
        j = j % 30;    
    }
}

main();