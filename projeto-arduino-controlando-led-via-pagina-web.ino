/*

Projeto Gefferson costa 
Controlando um LED por uma página web com D1 - Wemos - ESP8266 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LED_verde 3
#define LED_vermelho 5

/* Configuração de rede e senha */
const char *rede = "NOS-820D";
const char *senha = "XREKKFGC";

 int estado_led_verde = 0; //desligado
 int estado_led_vermelho = 2; //desligado
 int piscar_led_vermelho = 5; //desligado

ESP8266WebServer server(80); //Objeto "servidor" na porta 80(porta HTTP)


void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(rede);

 
  WiFi.begin(rede, senha);

  while (WiFi.status() != WL_CONNECTED) //Aguarda a conexao
  {
    Serial.print("Estabelecendo conexão com ");
    Serial.println(WiFi.SSID()); //Imprime o nome da rede
    delay(500);
  }
  Serial.print("Conectado a rede! Endereco IP ESP -> ");
  Serial.println(WiFi.localIP()); //Imprime o IP local do ESP

  
  /* Cria a associacao entre endereço HTML as funções que serão utilizadas */
  server.on("/", paginaInicial);
 
  server.begin(); //Inicia o servidor
  pinMode(LED_verde, OUTPUT); //Configura LED Embutido como saída
  digitalWrite(LED_verde, LOW); //Inicia apagado -
  pinMode(LED_vermelho, OUTPUT); //Configura LED Embutido como saída
  digitalWrite(LED_vermelho, LOW); //Inicia apagado -
  
}

void loop() {
  //Analise das solicitacoes via web
  server.handleClient();
}

void paginaInicial()
{
  
 
  String verde_acende = "Acende LED verde";
  String verde_apaga = "Apaga LED verde";
  String vermelho_acende = "Acende LED vermelho";
  String vermelho_apaga = "Apaga LED vermelho";


  //============================
   String htmlMessage = "<!DOCTYPE html>"
                             "<html>"
                             "<head>"
                             "<meta http-equiv=\"refresh\" content=\"1\">" //Atualizar a pagina a cada 1s
                             "<title>Projeto - ESP8266</title>"
                             "</head>"
                             "<body><font face=\"verdana\">"
                             "<h2>Controlar LED via WEB</h2>";
                              
                            //---------------------LED VERDE-------------------------------------------------------
                              if(estado_led_verde == 0)
                              {
                                htmlMessage +=
                                "<a  href=\"/?ledstatus=0\" >"+ verde_acende +"</a><br>";
                                
                                if(server.arg("ledstatus") == "0")
                                {
                                  digitalWrite(LED_verde,HIGH);
                                  estado_led_verde = 1;
                                }
                              }
                              else{
                                htmlMessage +=
                             " <a href=\"/?ledstatus=1\" >"+ verde_apaga +"</a><br>";
                             
                             
                                if(server.arg("ledstatus") == "1")
                                {
                                  digitalWrite(LED_verde,LOW);
                                   estado_led_verde = 0;
                                }
                               
                              }

                              //---------------------LED VERMELHO-------------------------------------------------------
                              if(estado_led_vermelho == 2)
                              {
                                htmlMessage +=
                                "<a href=\"/?ledstatus=2\" >"+ vermelho_acende +"</a><br>";
                                 htmlMessage +=
                                "<a href=\"/?ledstatus=5\" >Piscar LED vermelho</a>";
                                
                                if(server.arg("ledstatus") == "2")
                                {
                                  digitalWrite(LED_vermelho,HIGH);
                                  estado_led_vermelho = 3;
                                }
                                if(server.arg("ledstatus") == "5")
                                {
                                  digitalWrite(LED_vermelho,HIGH);
                                  delay(100);
                                  digitalWrite(LED_vermelho,LOW);
                                  delay(100);
                                  piscar_led_vermelho = 2;
                                }
                              }
                              else{
                                htmlMessage +=
                             " <a href=\"/?ledstatus=3\" >"+ vermelho_apaga +"</a>";
                             
                             
                                if(server.arg("ledstatus") == "3")
                                {
                                  digitalWrite(LED_vermelho,LOW);
                                   estado_led_vermelho = 2;
                                }
                               
                              }

                              

                         
                              "<hr>"
                             "</html>";
                             

  //============================
  server.send(200, "text/html", htmlMessage); //Retorna resposta HTTP
}


