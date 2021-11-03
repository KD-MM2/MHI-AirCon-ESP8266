const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, shrink-to-fit=no">
    <title>A/C Controller</title>
    <link rel="stylesheet" href="bootstrap.min.css">
    <link rel="stylesheet" href="styles.css">
</head>
<body class="text-center d-grid">
    <div class="container d-grid flex-grow-0 flex-shrink-0 justify-content-center align-content-center flex-wrap">
        <div class="flex-wrap" id="panel" style="background: url(&quot;frame.png&quot;) center / contain no-repeat;no-repeat center center fixed;-webkit-background-size: cover;-moz-background-size: cover;/*-o-background-size: cover;*/height: 500px;width: 500px;">
            <div style="width: 365px;height: 345px;margin-top: 77px;margin-left: 67px;">
                <div style="height: 118px;width: 365px;background: var(--bs-gray-900);padding-top: 35px;text-align: left;padding-left: 50px;">
                    <div class="d-inline-flex" style="width: 153px;height: 117px;margin-top: -35px;margin-left: -40px;"><i class="fa fa-thermometer-2" style="font-size: 40px;letter-spacing: 0px;line-height: 115px;width: 76px;height: 117px;color: rgb(255,255,255);text-align: center;"></i>
                        <p id="temperature" style="font-size: 40px;letter-spacing: 3px;font-family: DSEG7-Classic;line-height: 115px;height: 117px;width: 86px;color: rgb(255,255,255);">88</p>
                        <div><svg xmlns="http://www.w3.org/2000/svg" width="1em" height="1em" viewBox="0 0 24 24" stroke-width="2" stroke="currentColor" fill="none" stroke-linecap="round" stroke-linejoin="round" class="icon icon-tabler icon-tabler-temperature-celsius" style="font-size: 30px;line-height: 0px;letter-spacing: 0px;width: 38px;height: 60px;padding-top: 30px;color: rgb(255,255,255);">
                                <path stroke="none" d="M0 0h24v24H0z" fill="none"></path>
                                <circle cx="6" cy="8" r="2"></circle>
                                <path d="M20 9a3 3 0 0 0 -3 -3h-1a3 3 0 0 0 -3 3v6a3 3 0 0 0 3 3h1a3 3 0 0 0 3 -3"></path>
                            </svg></div>
                    </div>
                    <div style="width: 106px;height: 117px;margin-top: -117px;margin-left: 112px;"><img class="img-fluid" src="horizon.png" style="margin-top: 40px;margin-left: 25px;" width="49" height="69"></div>
                    <div style="width: 100px;height: 117px;margin-top: -117px;margin-left: 217px;"><img src="vert.png" width="37" height="49" style="margin-top: 40px;margin-left: 28px;width: 37px;"></div>
                </div>
                <div class="d-inline-flex" style="height: 70px;width: 365px;background: var(--bs-gray-900);border-top-width: 1px;border-top-style: solid;border-bottom-width: 1px;border-bottom-style: solid;color: rgb(255,255,255);">
                    <div class="d-inline-flex align-items-xl-end" style="height: 71px;width: 122.5px;min-height: 71px;max-height: 71px;"><i class="fas fa-fan" style="width: 35px;height: 71px;font-size: 30px;line-height: 100px;margin-left: 1px;"></i>
                      <svg xmlns="http://www.w3.org/2000/svg" width="1em" height="1em" fill="currentColor" viewBox="0 0 16 16" class="bi bi-reception-0" id="fan_0" style="display: inline;width: 87px;height: 69px;border-right-width: 1px;border-right-style: solid;">
                            <path d="M0 13.5a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 0 1h-2a.5.5 0 0 1-.5-.5zm4 0a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 0 1h-2a.5.5 0 0 1-.5-.5zm4 0a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 0 1h-2a.5.5 0 0 1-.5-.5zm4 0a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 0 1h-2a.5.5 0 0 1-.5-.5z"></path>
                      </svg>
                      <svg xmlns="http://www.w3.org/2000/svg" width="1em" height="1em" fill="currentColor" viewBox="0 0 16 16" class="bi bi-reception-1" id="fan_1" style="display: none;width: 87px;height: 69px;border-right-width: 1px;border-right-style: solid;">
                            <path d="M0 11.5a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 .5.5v2a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1-.5-.5v-2zm4 2a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 0 1h-2a.5.5 0 0 1-.5-.5zm4 0a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 0 1h-2a.5.5 0 0 1-.5-.5zm4 0a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 0 1h-2a.5.5 0 0 1-.5-.5z"></path>
                      </svg>
                      <svg xmlns="http://www.w3.org/2000/svg" width="1em" height="1em" fill="currentColor" viewBox="0 0 16 16" class="bi bi-reception-2" id="fan_2" style="display: none;width: 87px;height: 69px;border-right-width: 1px;border-right-style: solid;">
                            <path d="M0 11.5a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 .5.5v2a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1-.5-.5v-2zm4-3a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 .5.5v5a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1-.5-.5v-5zm4 5a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 0 1h-2a.5.5 0 0 1-.5-.5zm4 0a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 0 1h-2a.5.5 0 0 1-.5-.5z"></path>
                      </svg>
                      <svg xmlns="http://www.w3.org/2000/svg" width="1em" height="1em" fill="currentColor" viewBox="0 0 16 16" class="bi bi-reception-3" id="fan_3" style="display: none;width: 87px;height: 69px;border-right-width: 1px;border-right-style: solid;">
                            <path d="M0 11.5a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 .5.5v2a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1-.5-.5v-2zm4-3a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 .5.5v5a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1-.5-.5v-5zm4-3a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 .5.5v8a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1-.5-.5v-8zm4 8a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 0 1h-2a.5.5 0 0 1-.5-.5z"></path>
                      </svg>
                      <svg xmlns="http://www.w3.org/2000/svg" width="1em" height="1em" fill="currentColor" viewBox="0 0 16 16" class="bi bi-reception-4" id="fan_4" style="display: none;width: 87px;height: 69px;border-right-width: 1px;border-right-style: solid;">
                            <path d="M0 11.5a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 .5.5v2a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1-.5-.5v-2zm4-3a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 .5.5v5a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1-.5-.5v-5zm4-3a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 .5.5v8a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1-.5-.5v-8zm4-3a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 .5.5v11a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1-.5-.5v-11z"></path>
                      </svg>
                    </div>
                    <div class="justify-content-xl-start" style="height: 71px;width: 80px;min-height: 71px;max-height: 71px;border-right-color: rgb(84,96,117);">
                        <p id="fan_max" class="text-center" style="background: #ffffff00;color: #ffffff;border-width: 1px;border-style: solid;border-radius: 10px;width: 68px;height: 25px;font-size: 12px;letter-spacing: 4px;margin-left: 5px;margin-top: 7px;line-height: 22px;">MAX</p>
                        <p id="fan_auto" class="text-center" style="background: #ffffff00;color: #ffffff;border-width: 1px;border-style: solid;border-radius: 10px;width: 68px;height: 25px;font-size: 12px;letter-spacing: 4px;margin-left: 5px;margin-top: -10px;line-height: 22px;">AUTO</p>
                    </div>
                    <div class="justify-content-xl-start" style="height: 71px;width: 80px;min-height: 71px;max-height: 71px;">
                        <p id="fan_econo" class="text-center" style="background: #ffffff00;color: #ffffff;border-width: 1px;border-style: solid;border-radius: 10px;width: 68px;height: 25px;font-size: 12px;letter-spacing: 4px;margin-left: 3px;margin-top: 7px;line-height: 22px;">ECONO</p>
                        <p id="fan_turbo" class="text-center" style="background: #ffffff00;color: #ffffff;border-width: 1px;border-style: solid;border-radius: 10px;width: 68px;height: 25px;font-size: 12px;letter-spacing: 4px;margin-left: 3px;margin-top: -10px;line-height: 22px;">TURBO</p>
                    </div>
                    <div style="width: 94px;height: 69px;border-left-width: 1px;border-left-style: solid;"><i id="mode_icon" class="fas fa-font" style="font-size: 40px;margin-top: 15px;width: 39.2px;"></i></div>
                </div>
                <div class="d-flex" style="height: 79px;width: 365px;background: var(--bs-gray-900);">
                    <div style="height: 78px;width: 61px;"><button class="btn btn-primary text-center" type="button" onclick="modeBtn()" style="padding: 0px;background: rgba(255,255,255,0);margin-top: 16px;border-width: 0px;"><i class="far fa-sun" style="font-size: 43px;"></i></button></div>
                    <div style="height: 78px;width: 61px;"><button class="btn btn-primary text-center" type="button" onclick="upBtn()" style="padding: 0px;background: rgba(255,255,255,0);border-width: 0px;margin-top: 15px;"><i class="fas fa-angle-double-up" style="font-size: 45px;width: 35px;"></i></button></div>
                    <div style="height: 78px;width: 61px;"><button class="btn btn-primary text-center" type="button" onclick="downBtn()" style="background: rgba(255,255,255,0);border-width: 0px;padding: 0px;margin-top: 16px;"><i class="fas fa-angle-double-down" style="font-size: 45px;width: 35px;"></i></button></div>
                    <div style="height: 78px;width: 61px;"><button class="btn btn-primary text-center" type="button" onclick="fanBtn()" style="padding: 0px;background: rgba(255,255,255,0);border-width: 0px;margin-top: 15px;"><i class="fas fa-fan" style="font-size: 43px;"></i></button></div>
                    <div style="height: 78px;width: 61px;"><button class="btn btn-primary text-center" type="button" onclick="horizontalBtn()" style="padding: 0px;background: rgba(255,255,255,0);border-width: 0px;margin-top: 15px;"><i class="fas fa-arrows-alt-h" style="font-size: 45px;border-width: -1px;"></i></button></div>
                    <div style="height: 78px;width: 61px;"><button class="btn btn-primary text-center" type="button" onclick="verticalBtn()" style="padding: 0px;background: rgba(255,255,255,0);border-width: 0px;margin: 15px;"><i class="fas fa-arrows-alt-v" style="font-size: 45px;"></i></button></div>
                </div>
                <div style="height: 79px;width: 365px;background: var(--bs-gray-900);"><button class="btn btn-primary text-center" type="button" onclick="powerBtn()" style="background: rgba(255,255,255,0);padding: 0px 0px;border-width: 0px;"><i class="fa fa-power-off" id="powerBtn_color" style="font-size: 75px;color: rgb(255,255,255);"></i></button></div>
            </div>
        </div>
    </div>
    <script src="bootstrap.min.js"></script>
    <script src="jquery.js"></script>
  <script>
  var state = {}
  
  var fan_auto = document.getElementById("fan_auto").style;
  var fan_max = document.getElementById("fan_max").style;
  var fan_turbo = document.getElementById("fan_turbo").style;
  var fan_econo = document.getElementById("fan_econo").style;
  var fan_0 = document.getElementById("fan_0").style;
  var fan_1 = document.getElementById("fan_1").style;
  var fan_2 = document.getElementById("fan_2").style;
  var fan_3 = document.getElementById("fan_3").style;
  var fan_4 = document.getElementById("fan_4").style;

function updateStatus() {
  $.ajax({
    type: 'GET',
    url: "state",
    dataType: "json",
    success: function(data) {
      if(!data) {
        return;
      }
      state = data;
      if(state["power"] === true) {
        document.getElementById("powerBtn_color").style.color="rgb(0,255,0)";
      } else if(state["power"] === false) {
        document.getElementById("powerBtn_color").style.color="rgb(200,0,0)";
      }
      $("#temperature").text(state["temp"]);
      if(state["mode"] == 0){
        $("#mode_icon").removeClass();
        $("#mode_icon").addClass("fas fa-font");
       } else if(state["mode"] == 1){
        $("#mode_icon").removeClass();
        $("#mode_icon").addClass("fa fa-snowflake-o");
       } else if(state["mode"] == 2){
        $("#mode_icon").removeClass();
        $("#mode_icon").addClass("fab fa-cloudversify");
       } else if(state["mode"] == 3){
        $("#mode_icon").removeClass();
        $("#mode_icon").addClass("fas fa-fan");
       } else if(state["mode"] == 4){
        $("#mode_icon").removeClass();
        $("#mode_icon").addClass("fa fa-sun-o");
       }
      if(state["fan"] == 0){
        fan_auto.color="rgb(0,0,0)";
        fan_auto.background="rgb(255,255,255)";
        fan_max.color="rgb(255,255,255)";
        fan_max.background="rgba(255,255,255,0)";
        fan_turbo.color="rgb(255,255,255)";
        fan_turbo.background="rgba(255,255,255,0)";
        fan_econo.color="rgb(255,255,255)";
        fan_econo.background="rgba(255,255,255,0)";
        fan_0.display="inline";
        fan_1.display="none";
        fan_2.display="none";
        fan_3.display="none";
        fan_4.display="none";

      } else if(state["fan"] == 4){
        fan_auto.color="rgb(255,255,255)";
        fan_auto.background="rgba(255,255,255,0)";
        fan_max.color="rgb(0,0,0)";
        fan_max.background="rgb(255,255,255)";
        fan_turbo.color="rgb(255,255,255)";
        fan_turbo.background="rgba(255,255,255,0)";
        fan_econo.color="rgb(255,255,255)";
        fan_econo.background="rgba(255,255,255,0)";
        fan_0.display="none";
        fan_1.display="none";
        fan_2.display="none";
        fan_3.display="none";
        fan_4.display="inline";

      } else if(state["fan"] == 6){
        fan_auto.color="rgb(255,255,255)";
        fan_auto.background="rgba(255,255,255,0)";
        fan_max.color="rgb(255,255,255)";
        fan_max.background="rgba(255,255,255,0)";
        fan_turbo.color="rgb(255,255,255)";
        fan_turbo.background="rgba(255,255,255,0)";
        fan_econo.color="rgb(0,0,0)";
        fan_econo.background="rgb(255,255,255)";
        fan_0.display="inline";
        fan_1.display="none";
        fan_2.display="none";
        fan_3.display="none";
        fan_4.display="none";

      } else if(state["fan"] == 8){
        fan_auto.color="rgb(255,255,255)";
        fan_auto.background="rgba(255,255,255,0)";
        fan_max.color="rgb(255,255,255)";
        fan_max.background="rgba(255,255,255,0)";
        fan_turbo.color="rgb(0,0,0)";
        fan_turbo.background="rgb(255,255,255)";
        fan_econo.color="rgb(255,255,255)";
        fan_econo.background="rgba(255,255,255,0)";
        fan_0.display="none";
        fan_1.display="none";
        fan_2.display="none";
        fan_3.display="none";
        fan_4.display="inline";

      } else if(state["fan"] == 1){
        fan_auto.color="rgb(255,255,255)";
        fan_auto.background="rgba(255,255,255,0)";
        fan_max.color="rgb(255,255,255)";
        fan_max.background="rgba(255,255,255,0)";
        fan_turbo.color="rgb(255,255,255)";
        fan_turbo.background="rgba(255,255,255,0)";
        fan_econo.color="rgb(255,255,255)";
        fan_econo.background="rgba(255,255,255,0)";
        fan_0.display="none";
        fan_1.display="inline";
        fan_2.display="none";
        fan_3.display="none";
        fan_4.display="none";

      } else if(state["fan"] == 2){
        fan_auto.color="rgb(255,255,255)";
        fan_auto.background="rgba(255,255,255,0)";
        fan_max.color="rgb(255,255,255)";
        fan_max.background="rgba(255,255,255,0)";
        fan_turbo.color="rgb(255,255,255)";
        fan_turbo.background="rgba(255,255,255,0)";
        fan_econo.color="rgb(255,255,255)";
        fan_econo.background="rgba(255,255,255,0)";
        fan_0.display="none";
        fan_1.display="none";
        fan_2.display="inline";
        fan_3.display="none";
        fan_4.display="none";

      } else if(state["fan"] == 3){
        fan_auto.color="rgb(255,255,255)";
        fan_auto.background="rgba(255,255,255,0)";
        fan_max.color="rgb(255,255,255)";
        fan_max.background="rgba(255,255,255,0)";
        fan_turbo.color="rgb(255,255,255)";
        fan_turbo.background="rgba(255,255,255,0)";
        fan_econo.color="rgb(255,255,255)";
        fan_econo.background="rgba(255,255,255,0)";
        fan_0.display="none";
        fan_1.display="none";
        fan_2.display="none";
        fan_3.display="inline";
        fan_4.display="none";
      }
    },
    error: function() {
      console.log('error getting state');
    },
    timeout: 1000
  });
}
    // button function
    function powerBtn() {
      var xhttp = new XMLHttpRequest();
      xhttp.open("GET", "powerBtn", true);
      xhttp.send();
      updateStatus();
    }
    function modeBtn() {
      var xhttp = new XMLHttpRequest();
      xhttp.open("GET", "modeBtn", true);
      xhttp.send();
      updateStatus();
      }
    function upBtn() {
      var xhttp = new XMLHttpRequest();
      xhttp.open("GET", "upBtn", true);
      xhttp.send();
      updateStatus();
    }
    function downBtn() {
      var xhttp = new XMLHttpRequest();
      xhttp.open("GET", "downBtn", true);
      xhttp.send();
      updateStatus();
    }
    function fanBtn() {
      var xhttp = new XMLHttpRequest();
      xhttp.open("GET", "fanBtn", true);
      xhttp.send();
      updateStatus();
    }
    function verticalBtn() {
      var xhttp = new XMLHttpRequest();
      xhttp.open("GET", "vertBtn", true);
      xhttp.send();
      updateStatus();
    }
    function horizontalBtn() {
      var xhttp = new XMLHttpRequest();
      xhttp.open("GET", "horizonBtn", true);
      xhttp.send();
      updateStatus();
    }
    setInterval(function(){
      updateStatus();
    }, 1000); 
</script>
</body>
</html>
)=====";
