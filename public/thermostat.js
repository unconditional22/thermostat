// Initialize Firebase
const firebaseConfig = {
    apiKey: "",
    authDomain: "thermostat-c1685.firebaseapp.com",
    databaseURL: "thermostat-c1685-default-rtdb.firebaseio.com",
    projectId: "thermostat-c1685",
    storageBucket: "thermostat-c1685.appspot.com",
    messagingSenderId: "881952907613",
    appId: "1:881952907613:web:12ec9e44f6406c29cc48b4"
  };
  const app = initializeApp(firebaseConfig);

$(document).ready(function(){
  var database = firebase.database();
  var btnEtat;

  database.ref().on("value", function(snap){
    btnEtat = snap.val().btnEtat;
    if(btnEtat == 1){
      $(".btnEtat").text("ON");
      document.getElementById("active").style.backgroundColor = 'green';
    } else {
      $(".btnEtat").text("OFF");
      document.getElementById("active").style.backgroundColor = 'white';
    }
  });

  $(".allumerBtn").click(function(){
    var firebaseRef = firebase.database().ref().child("btnEtat");

    if(btnEtat == 1){
      firebaseRef.set(0);
      btnEtat = 0;
    } else {
      firebaseRef.set(1);
      btnEtat = 1;
    }
  });
});
