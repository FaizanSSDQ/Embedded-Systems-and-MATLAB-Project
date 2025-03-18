[Friday 12:07 PM] Faizan Saleem Siddiqui
#include <WiFi.h>
#include "esp_timer.h"
#include "img_converters.h"
#include "Arduino.h"
#include "fb_gfx.h"
#include "soc/soc.h"             // disable brownout problems
#include "soc/rtc_cntl_reg.h"    // disable brownout problems
#include "esp_http_server.h"
 
//Backward Right
#define IN1 27
#define IN2 14
 
//Backward Left
#define IN3 12
#define IN4 13
 
 
 esp_err_t res = ESP_OK;
 const char* ssid     = "ESP32";
const char* password = "FaizanSaleem";
 
WiFiServer server(80);
 
void Stop()
{
  Serial.println("Stop...");
  digitalWrite(IN1 , LOW);
  digitalWrite(IN2 , LOW);
  digitalWrite(IN3 , LOW);
  digitalWrite(IN4 , LOW);
}
void Forward()
{
  Serial.println("Forward...");
  digitalWrite(IN1 , HIGH);
  digitalWrite(IN2 , LOW);
  digitalWrite(IN3 , HIGH);
  digitalWrite(IN4 , LOW);
}
 
void Backward()
{
    Serial.println("Backward...");
  digitalWrite(IN1 , LOW);
  digitalWrite(IN2 , HIGH);
  digitalWrite(IN3 , LOW);
  digitalWrite(IN4 , HIGH);
}
 
void Right()
{
  Serial.println("Right....");
  digitalWrite(IN1 , HIGH);
  digitalWrite(IN2 , LOW);
  digitalWrite(IN3 , LOW);
  digitalWrite(IN4 , HIGH);
}
 
void Left()
{
  Serial.println("Right....");
  digitalWrite(IN1 , LOW);
  digitalWrite(IN2 , HIGH);
  digitalWrite(IN3 , HIGH);
  digitalWrite(IN4 , LOW);
}
 
 
static const char PROGMEM INDEX_HTML[] = R"rawliteral(
<html>
  <head>
    <title>ESP32-CAM Robot</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body { font-family: Arial; text-align: center; margin:0px auto; padding-top: 30px;}
      table { margin-left: auto; margin-right: auto; }
      td { padding: 8 px; }
      .button {
        background-color: #2f4468;
        border: none;
        color: white;
        padding: 10px 20px;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        font-size: 18px;
        margin: 6px 3px;
        cursor: pointer;
        -webkit-touch-callout: none;
        -webkit-user-select: none;
        -khtml-user-select: none;
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none;
        -webkit-tap-highlight-color: rgba(0,0,0,0);
      }
      img {  width: auto ;
        max-width: 100% ;
        height: auto ;
      }
    </style>
  </head>
  <body>
    <h1>ESP32-CAM Robot</h1>
    <img src="" id="photo" >
    <table>
      <tr><td colspan="3" align="center"><button class="button" onmousedown="toggleCheckbox('forward');" ontouchstart="toggleCheckbox('forward');" onmouseup="toggleCheckbox('stop');" ontouchend="toggleCheckbox('stop');">Forward</button></td></tr>
      <tr><td align="center"><button class="button" onmousedown="toggleCheckbox('left');" ontouchstart="toggleCheckbox('left');" onmouseup="toggleCheckbox('stop');" ontouchend="toggleCheckbox('stop');">Left</button></td><td align="center"><button class="button" onmousedown="toggleCheckbox('stop');" ontouchstart="toggleCheckbox('stop');">Stop</button></td><td align="center"><button class="button" onmousedown="toggleCheckbox('right');" ontouchstart="toggleCheckbox('right');" onmouseup="toggleCheckbox('stop');" ontouchend="toggleCheckbox('stop');">Right</button></td></tr>
      <tr><td colspan="3" align="center"><button class="button" onmousedown="toggleCheckbox('backward');" ontouchstart="toggleCheckbox('backward');" onmouseup="toggleCheckbox('stop');" ontouchend="toggleCheckbox('stop');">Backward</button></td></tr>                  
    </table>
   <script>
   function toggleCheckbox(x) {
     var xhr = new XMLHttpRequest();
     xhr.open("GET", "/action?go=" + x, true);
     xhr.send();
   }
   window.onload = document.getElementById("photo").src = window.location.href.slice(0, -1) + ":81/stream";
  </script>
  </body>
</html>
)rawliteral";
 
static esp_err_t index_handler(httpd_req_t *req){
  httpd_resp_set_type(req, "text/html");
  return httpd_resp_send(req, (const char *)INDEX_HTML, strlen(INDEX_HTML));
}
static esp_err_t cmd_handler(httpd_req_t *req){
  char*  buf;
  size_t buf_len;
  char variable[32] = {0,};
 
  buf_len = httpd_req_get_url_query_len(req) + 1;
  if (buf_len > 1) {
    buf = (char*)malloc(buf_len);
    if(!buf){
      httpd_resp_send_500(req);
      return ESP_FAIL;
    }
    if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) {
      if (httpd_query_key_value(buf, "go", variable, sizeof(variable)) == ESP_OK) {
      } else {
        free(buf);
        httpd_resp_send_404(req);
        return ESP_FAIL;
      }
    } else {
      free(buf);
      httpd_resp_send_404(req);
      return ESP_FAIL;
    }
    free(buf);
  } else {
    httpd_resp_send_404(req);
    return ESP_FAIL;
  }
 
 
 
  if(!strcmp(variable, "forward")) {
    Serial.println("Forward");
      Forward();
  }
  else if(!strcmp(variable, "left")) {
    Serial.println("Left");
      Left();
  }
  else if(!strcmp(variable, "right")) {
    Serial.println("Right");
      Right();
  }
  else if(!strcmp(variable, "backward")) {
    Serial.println("Backward");
      Backward();
  }
  else if(!strcmp(variable, "stop")) {
    Serial.println("Stop");
      Stop();
  }
  else {
    res = -1;
  }
 
  if(res){
    return httpd_resp_send_500(req);
  }
 
  httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
  return httpd_resp_send(req, NULL, 0);
}
 
 
 
 
  //config.server_port += 1;
  //config.ctrl_port += 1;
 
 
 
 
 
void setup() {
 
  pinMode(IN1 , OUTPUT);
  pinMode(IN2 , OUTPUT);
  pinMode(IN3 , OUTPUT);
  pinMode(IN4 , OUTPUT);
 
  Serial.begin(115200);
 
  // Wi-Fi connection
 
 
 
  WiFi.softAP(ssid,password);
 
  if (!WiFi.softAP(ssid, password)) {
    log_e("Soft AP creation failed.");
    while(1);
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
 
  Serial.println("Server started");
 
  Serial.println("");
  Serial.println("WiFi connected");
 
  Serial.print("Car control is ready! Go to: http://");
  Serial.println(WiFi.localIP());
 
  // Start streaming web server
 
 
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  httpd_uri_t index_uri = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = index_handler,
    .user_ctx = NULL
  };
  httpd_uri_t cmd_uri = {
    .uri = "/action",
    .method = HTTP_GET,
    .handler = cmd_handler,
    .user_ctx = NULL
  };
  httpd_handle_t server_handle;
  if (httpd_start(&server_handle, &config) == ESP_OK) {
    httpd_register_uri_handler(server_handle, &index_uri);
    httpd_register_uri_handler(server_handle, &cmd_uri);
  } else {
    Serial.println("Error starting HTTP server");
  }
 
}
 
void loop() {
 
}
 
 
 