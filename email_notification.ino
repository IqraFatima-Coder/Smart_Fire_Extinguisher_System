#include <ESP8266WiFi.h>
#include <ESP_Mail_Client.h>

// WiFi configuration for eduroam
#define WIFI_SSID "Sparx"
#define WIFI_PASSWORD ""

// SMTP configuration for Gmail
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

// Email configuration
#define AUTHOR_EMAIL "razanidrive87442@gmail.com"
#define AUTHOR_PASSWORD "umwy dcvd vprv unif"  // Use App Password if 2FA enabled
#define RECIPIENT_EMAIL "iqrafatima1717@gmail.com"

SMTPSession smtp;

void setup() {
  Serial.begin(9600);
  
  // Connect to eduroam WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  Serial.print("Connecting to wifi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Waiting for Arduino alerts...");
}

void loop() {
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    message.trim();
    
    if (message == "ALERT_TRIGGERED") {
      Serial.println("Fire/Gas alert detected! Sending email...");
      sendEmailAlert();
      delay(5000); // Prevent multiple emails for same alert
    }
  }
}

void sendEmailAlert() {
  smtp.debug(1);  // Enable debug output

  ESP_Mail_Session session;
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  SMTP_Message msg;
  msg.sender.name = "Fire Safety System";
  msg.sender.email = AUTHOR_EMAIL;
  msg.subject = "URGENT: Fire/Gas Detected!";
  msg.addRecipient("Owner", RECIPIENT_EMAIL);

  // HTML Email Content
  String htmlMsg = R"(
  <div style="font-family: Arial, sans-serif; color: #d32f2f;">
    <h2 style="color: #b71c1c;">🚨 EMERGENCY ALERT 🚨</h2>
    <p>The fire safety system has detected a potential hazard!</p>
    
    <h3>⚠ Possible Hazards:</h3>
    <ul>
      <li>Fire detected by flame sensor</li>
      <li>Dangerous gas concentration detected</li>
    </ul>
    
    <p><strong>Action Required:</strong> Please check the premises immediately!</p>
    
    <div style="margin-top: 20px; padding: 10px; background-color: #ffebee; border-left: 4px solid #f44336;">
      <p>System alert triggered at: )";
  htmlMsg += String(millis() / 1000);
  htmlMsg += R"( seconds after startup</p>
    </div>
  </div>
  )";

  msg.html.content = htmlMsg.c_str();
  msg.text.content = "EMERGENCY: Fire/Gas detected! Check premises immediately.\n\nTrigger time: " + String(millis() / 1000) + "s after system start";
  msg.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_high;

  if (!smtp.connect(&session)) {
    Serial.println("Connection error!");
    return;
  }

  if (!MailClient.sendMail(&smtp, &msg)) {
    Serial.print("Error sending email: ");
    Serial.println(smtp.errorReason());
  }
}

void smtpCallback(SMTP_Status status) {
  Serial.println("----------------");
  Serial.println("Email Status:");
  Serial.print("Info: ");
  Serial.println(status.info());
  
  if (status.success()) {
    Serial.println("Result: Success");
    Serial.print("Messages sent: ");
    Serial.println(status.completedCount());
    Serial.print("Messages failed: ");
    Serial.println(status.failedCount());
  } else {
    Serial.println("Result: Failed");
  }
  Serial.println("----------------");
}
