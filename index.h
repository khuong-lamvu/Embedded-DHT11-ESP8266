String MAIN_page = "<!DOCTYPE html>\
<html lang='en'>\
<head>\
    <meta charset='UTF-8'>\
    <title>Monitor Temperature&amp;Temperature</title>\
</head>\
<style>\
    h3{\
        font-family: monospace;\
        font-size: 85px;\
        text-align: center;\
        font-weight: bold;\
    }\
</style>\
<body>\
   <h1 style='text-align: center; font-family: monospace; font-size: 45px; color: blue; font-weight: bold;'>Monitor temperature and humidity with DHT11 sensor connected to ESP8266</h1>\
   <h3>Temperature: <span id='Temperature'>0</span><sup>&deg;C</sup><br>\
       Humidity: <span id='Humidity'>0</span><sup>%</sup>\
   </h3>\
    <script>\
        setInterval(function(){\
            getNhietdo();\
            getDoam();\
        }, 2000);\
        function getNhietdo(){\
            var xhttp = new XMLHttpRequest();\
            xhttp.onreadystatechange = function(){\
                if(this.readyState == 4 && this.status == 200){\
                    document.getElementById('Temperature').innerHTML = this.responseText;\
                }\
            };\
            xhttp.open('GET', 'docnhietdo', true);\
            xhttp.send();\
        }\
        function getDoam(){\
            var xhttp = new XMLHttpRequest();\
            xhttp.onreadystatechange = function(){\
                if(this.readyState == 4 && this.status == 200){\
                    document.getElementById('Humidity').innerHTML = this.responseText;\
                }\
            };\
            xhttp.open('GET', 'docdoam', true);\
            xhttp.send();\
        }\
    </script>\
</body>\
</html>";
