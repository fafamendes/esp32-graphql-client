/**
 * @file send_esp32_stats.ino
 * @brief Demonstrates sending ESP32 device statistics via a GraphQL mutation. 
 * 
 * This example connects to a Wi-Fi network, periodically collects device metrics 
 * (uptime and free heap), and sends them to a GraphQL server using a mutation.
 * 
 * @note You must create a `config.h` file in this directory with your Wi-Fi 
 *       credentials and GraphQL server endpoint. See `config.h.example`.
 */

#include <WiFi.h>
#include <GraphQLClient.h>
#include <ArduinoJson.h>
#include "config.h" // Contains WIFI_SSID, WIFI_PASSWORD, and GRAPHQL_ENDPOINT

// Instantiate the GraphQL client
GraphQLClient client(GRAPHQL_ENDPOINT);

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Set a custom header for authentication if your server requires it
  // client.setHeader("Authorization", "Bearer YOUR_API_TOKEN");
}

void loop() {
  // 1. Define the GraphQL mutation
  // This mutation sends device stats. The server is expected to return the ID of the created record.
  const char* recordDeviceStats = R"(
    mutation RecordStats($deviceId: ID!, $uptime: Int!, $freeHeap: Int!) {
      recordDeviceStats(deviceId: $deviceId, uptime: $uptime, freeHeap: $freeHeap) {
        id
        timestamp
      }
    }
  )";

  // 2. Populate the variables for the mutation
  StaticJsonDocument<200> variables;
  variables["deviceId"] = "esp32-living-room";
  variables["uptime"] = millis() / 1000; // Uptime in seconds
  variables["freeHeap"] = ESP.getFreeHeap();

  // 3. Execute the mutation
  Serial.println("Executing mutation to send device stats...");
  GraphQLResponse response = client.mutate(recordDeviceStats, variables.as<JsonObject>());

  // 4. Process the response
  if (response.hasError) {
    Serial.println("GraphQL Mutation Error:");
    Serial.println(response.getErrorMessage());
  } else {
    Serial.println("GraphQL Mutation Successful:");
    // Print the data returned by the server
    serializeJsonPretty(response.data, Serial);
    Serial.println();
  }

  // Wait for 60 seconds before sending the next update
  Serial.println("\nWaiting 60 seconds for the next update...");
  delay(60000);
}