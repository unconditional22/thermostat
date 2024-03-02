// Database Paths
var dataFloatPath = 'test/float'; //'test/float'
var dataIntPath = 'test/int'; //'test/int'

var databasePath = 'thermolit/date'; //'thermolit/date'
var dataHourPath = 'thermolit/horaire'; //'thermolit/horaire'

var dataC1Path = 'thermolit/consigne1'; //'thermolit/consigne1'
var dataC2Path = 'thermolit/consigne2'; //'thermolit/consigne2'
var dataC3Path = 'thermolit/consigne3'; //'thermolit/consigne3'
var dataC4Path = 'thermolit/consigne4'; //'thermolit/consigne4'
var dataC5Path = 'thermolit/consigne5'; //'thermolit/consigne5'


// Get a database reference 
const databaseFloat = database.ref(dataFloatPath);
const databaseInt = database.ref(dataIntPath);

// reference pour date et horaire
const databaseDate = database.ref(databasePath);
const databaseHour = database.ref(dataHourPath);

// reference pour les consignes
const databaseC1 = database.ref(dataC1Path);
const databaseC2 = database.ref(dataC2Path);
const databaseC3 = database.ref(dataC3Path);
const databaseC4 = database.ref(dataC4Path);
const databaseC5 = database.ref(dataC5Path);


// Variables to save database current values
var floatReading;
var intReading;

// LIRE DATE ET HORAIRES
var dateReading;
var hourReading;

// LIRE LES CONSIGNES
var c1Reading;
var c2Reading;
var c3Reading;
var c4Reading;
var c5Reading;


// Attach an asynchronous callback to read the data
databaseFloat.on('value', (snapshot) => {
  floatReading = snapshot.val();
  console.log(floatReading);
  document.getElementById("reading-float").innerHTML = floatReading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

databaseInt.on('value', (snapshot) => {
  intReading = snapshot.val();
  console.log(intReading);
  document.getElementById("reading-int").innerHTML = intReading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});



// AFFICHER DATE
databaseDate.on('value', (snapshot) => {
  dateReading = snapshot.val();
  console.log(dateReading);
  document.getElementById("lire-date").innerHTML = dateReading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

// AFFICHER HORAIRE
databaseHour.on('value', (snapshot) => {
  hourReading = snapshot.val();
  console.log(hourReading);
  document.getElementById("lire-horaire").innerHTML = hourReading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

/*************** LES CONSIGNES *****************/

// AFFICHER CONSIGNE 1
databaseC1.on('value', (snapshot) => {
  c1Reading = snapshot.val();
  console.log(c1Reading);
  document.getElementById("lire-c1").innerHTML = c1Reading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

// AFFICHER CONSIGNE 2
databaseC2.on('value', (snapshot) => {
  c2Reading = snapshot.val();
  console.log(c2Reading);
  document.getElementById("lire-c2").innerHTML = c2Reading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

// AFFICHER CONSIGNE 3
databaseC3.on('value', (snapshot) => {
  c3Reading = snapshot.val();
  console.log(c3Reading);
  document.getElementById("lire-c3").innerHTML = c3Reading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

// AFFICHER CONSIGNE 4
databaseC4.on('value', (snapshot) => {
  c4Reading = snapshot.val();
  console.log(c4Reading);
  document.getElementById("lire-c4").innerHTML = c4Reading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

// AFFICHER CONSIGNE 5
databaseC5.on('value', (snapshot) => {
  c5Reading = snapshot.val();
  console.log(c5Reading);
  document.getElementById("lire-c5").innerHTML = c5Reading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

