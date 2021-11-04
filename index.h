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
                    <div style="width: 106px;height: 117px;margin-top: -117px;margin-left: 112px;">
                      <svg viewBox="253.803 186.466 15.324 10.673" xmlns="http://www.w3.org/2000/svg" class="img-fluid" style="margin-top: 20px;margin-left: 20px;" width="65" height="85" fill="#ffffff">
                        <path d="M 268.807 187.559 C 268.807 187.029 268.377 186.601 267.847 186.601 L 255.061 186.601 C 254.529 186.601 254.098 187.029 254.098 187.559 L 254.104 191.861 C 254.104 192.39 254.534 192.82 255.063 192.82 L 255.784 192.82 L 256.504 191.867 L 261.084 191.867 L 261.084 191.376 L 256.258 191.376 C 256.258 191.376 255.727 192.083 255.541 192.331 L 255.063 192.331 C 254.805 192.331 254.592 192.12 254.592 191.861 L 254.59 187.559 C 254.59 187.301 254.802 187.091 255.061 187.091 L 267.847 187.091 C 268.108 187.091 268.32 187.301 268.32 187.559 L 268.323 191.861 C 268.323 192.12 268.11 192.331 267.852 192.331 L 267.375 192.331 C 267.189 192.083 266.655 191.376 266.655 191.376 L 261.828 191.376 L 261.828 191.867 L 266.409 191.867 L 267.131 192.82 L 267.852 192.82 C 268.382 192.82 268.812 192.39 268.812 191.861 L 268.807 187.559"/>
                        <path id="h_2" style="display: inline" d="M 257.557 193.347 L 257.368 193.357 L 257.178 193.347 L 256.276 196.984 C 256.631 197.035 256.996 197.066 257.368 197.066 C 257.739 197.066 258.102 197.035 258.462 196.984 L 257.557 193.347"/>
                        <path id="h_3" style="display: inline" d="M 259.043 196.874 C 259.686 196.724 260.295 196.495 260.862 196.192 L 258.645 193.125 C 258.486 193.184 258.318 193.229 258.15 193.267 L 259.043 196.874"/>
                        <path id="h_1" style="display: inline" d="M 256.584 193.267 C 256.416 193.23 256.25 193.184 256.088 193.125 L 253.871 196.193 C 254.439 196.496 255.049 196.724 255.691 196.874 L 256.584 193.267"/>
                        <path id="h_5" style="display: inline" d="M 265.738 193.347 L 265.549 193.357 L 265.357 193.347 L 264.455 196.984 C 264.812 197.035 265.175 197.066 265.549 197.066 C 265.92 197.066 266.283 197.035 266.64 196.984 L 265.738 193.347"/>
                        <path id="h_6" style="display: inline" d="M 267.223 196.874 C 267.864 196.724 268.475 196.495 269.043 196.192 L 266.827 193.125 C 266.665 193.184 266.498 193.229 266.33 193.267 L 267.223 196.874"/>
                        <path id="h_4" style="display: inline" d="M 264.768 193.267 C 264.598 193.23 264.43 193.184 264.27 193.125 L 262.052 196.193 C 262.619 196.496 263.229 196.724 263.87 196.874 L 264.768 193.267"/>
                      </svg>
                    </div>
                    
                    <div style="width: 100px;height: 117px;margin-top: -117px;margin-left: 217px;">
                      <svg viewBox="432.825 237.25 8.243 10.925" xmlns="http://www.w3.org/2000/svg" class="img-fluid" style="margin-top: 40px;margin-left: 20px;" width="40" height="50" fill="#ffffff">
                        <path d="M 440.848 237.433 L 437.937 237.433 C 436.81 237.433 435.895 238.345 435.895 239.473 L 435.899 242.208 L 435.895 242.208 L 435.895 242.699 L 438.222 242.699 L 438.96 244.171 L 440.851 244.171 Z M 439.244 243.712 L 438.493 242.208 L 436.357 242.208 C 436.357 241.328 436.355 239.473 436.355 239.473 C 436.355 238.599 437.065 237.89 437.937 237.89 L 437.939 237.89 L 440.007 237.89 C 440.007 238.654 440.009 243.712 440.009 243.712 L 439.244 243.712"/>
                        <path id="v_highest" style="display: inline" d="M 435.527 243.097 L 433.026 243.097 C 433.026 243.481 433.082 243.853 433.183 244.209 L 435.63 243.646 C 435.566 243.469 435.527 243.285 435.527 243.097"/>
                        <path id="v_high" style="display: inline" d="M 435.818 244.031 L 433.318 244.609 C 433.486 245.035 433.725 245.437 434.025 245.802 L 436.21 244.491 C 436.054 244.347 435.922 244.194 435.818 244.031"/>
                        <path id="v_low" style="display: inline" d="M 437.48 245.222 L 435.843 247.243 C 436.265 247.457 436.719 247.626 437.202 247.749 L 437.978 245.36 C 437.806 245.325 437.639 245.278 437.48 245.222"/>
                        <path id="v_middle" style="display: inline" d="M 436.555 244.769 L 434.307 246.12 C 434.642 246.468 435.035 246.777 435.473 247.038 L 437.073 245.062 C 436.887 244.975 436.715 244.877 436.555 244.769"/>
                        <path id="v_lowest" style="display: inline" d="M 437.611 247.839 C 438.037 247.918 438.478 247.961 438.931 247.961 L 438.931 245.459 C 438.752 245.459 438.572 245.447 438.396 245.425 L 437.611 247.839"/>
                      </svg>
                    </div>
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

  var h_1 = document.getElementById("h_1").style;
  var h_2 = document.getElementById("h_2").style;
  var h_3 = document.getElementById("h_3").style;
  var h_4 = document.getElementById("h_4").style; 
  var h_5 = document.getElementById("h_5").style;
  var h_6 = document.getElementById("h_6").style; 

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

      if(state["vert"] == 0){
        document.getElementById("v_highest").style.display="inline";
        document.getElementById("v_high").style.display="inline";
        document.getElementById("v_middle").style.display="inline";
        document.getElementById("v_low").style.display="inline";
        document.getElementById("v_lowest").style.display="inline";
      } else if(state["vert"] == 1){
        document.getElementById("v_highest").style.display="inline";
        document.getElementById("v_high").style.display="none";
        document.getElementById("v_middle").style.display="none";
        document.getElementById("v_low").style.display="none";
        document.getElementById("v_lowest").style.display="none";
      } else if(state["vert"] == 2){
        document.getElementById("v_highest").style.display="none";
        document.getElementById("v_high").style.display="inline";
        document.getElementById("v_middle").style.display="none";
        document.getElementById("v_low").style.display="none";
        document.getElementById("v_lowest").style.display="none";
      } else if(state["vert"] == 3){
        document.getElementById("v_highest").style.display="none";
        document.getElementById("v_high").style.display="none";
        document.getElementById("v_middle").style.display="inline";
        document.getElementById("v_low").style.display="none";
        document.getElementById("v_lowest").style.display="none";
      } else if(state["vert"] == 4){
        document.getElementById("v_highest").style.display="none";
        document.getElementById("v_high").style.display="none";
        document.getElementById("v_middle").style.display="none";
        document.getElementById("v_low").style.display="inline";
        document.getElementById("v_lowest").style.display="none";
      } else if(state["vert"] == 5){
        document.getElementById("v_highest").style.display="none";
        document.getElementById("v_high").style.display="none";
        document.getElementById("v_middle").style.display="none";
        document.getElementById("v_low").style.display="none";
        document.getElementById("v_lowest").style.display="inline";
      } else if(state["vert"] == 6){
        document.getElementById("v_highest").style.display="none";
        document.getElementById("v_high").style.display="none";
        document.getElementById("v_middle").style.display="none";
        document.getElementById("v_low").style.display="none";
        document.getElementById("v_lowest").style.display="none";
      }

      if(state["horizon"] == 0){
        h_1.display="inline";
        h_2.display="inline";
        h_3.display="inline";
        h_4.display="inline";
        h_5.display="inline";
        h_6.display="inline";
      } else if(state["horizon"] == 1){
        h_1.display="inline";
        h_2.display="none";
        h_3.display="none";
        h_4.display="inline";
        h_5.display="none";
        h_6.display="none";
      } else if(state["horizon"] == 2){
        h_1.display="inline";
        h_2.display="none";
        h_3.display="none";
        h_4.display="none";
        h_5.display="inline";
        h_6.display="none";
      } else if(state["horizon"] == 3){
        h_1.display="none";
        h_2.display="inline";
        h_3.display="none";
        h_4.display="none";
        h_5.display="inline";
        h_6.display="none";
      } else if(state["horizon"] == 4){
        h_1.display="none";
        h_2.display="inline";
        h_3.display="none";
        h_4.display="none";
        h_5.display="none";
        h_6.display="inline";
      } else if(state["horizon"] == 5){
        h_1.display="none";
        h_2.display="none";
        h_3.display="inline";
        h_4.display="none";
        h_5.display="none";
        h_6.display="inline";
      } else if(state["horizon"] == 6){
        h_1.display="none";
        h_2.display="none";
        h_3.display="inline";
        h_4.display="inline";
        h_5.display="none";
        h_6.display="none";
      } else if(state["horizon"] == 7){
        h_1.display="inline";
        h_2.display="none";
        h_3.display="none";
        h_4.display="none";
        h_5.display="none";
        h_6.display="inline";
      } else if(state["horizon"] == 8){
        h_1.display="none";
        h_2.display="none";
        h_3.display="none";
        h_4.display="none";
        h_5.display="none";
        h_6.display="none";
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
